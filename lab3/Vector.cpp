#include <iostream>
#include <stdexcept>
#include <random> // Для генерации случайных чисел
#include <vector> 
#include <fstream>   // Для работы с файлами
#include <chrono>    // Для замера времени выполнения
#include <thread>    // Для работы с потоками (std::thread)
#include <mutex>     // Для синхронизации потоков с помощью мьютекса
#include <omp.h>     // Для использования OpenMP
#include <tuple>

std::mutex mtx;

template <typename T>
class Vector {
private:
    T* data;            // Указатель на массив элементов
    size_t n;           // Размерность вектора
    bool is_initialized; // Флаг инициализации

public:
    // Конструктор с одним параметром - размерность вектора
    Vector(size_t size) : data(nullptr), n(size), is_initialized(false) {
        data = new T[n]; // Выделяем память, но не инициализируем массив
    }

    // Деструктор - освобождает выделенную память
    ~Vector() {
        delete[] data; // Освобождаем память
    }

    // Проверка состояния инициализации
    void check_initialized() const {
        if (!is_initialized) {
            throw std::logic_error("Массив не инициализирован!");
        }
    }

    // Метод для инициализации всех элементов одной константой
    void initialize_with_constant(T value) {
        for (size_t i = 0; i < n; ++i) {
            data[i] = value;
        }
        is_initialized = true; // Устанавливаем флаг инициализации
    }

    // Метод для инициализации случайными числами в диапазоне [min, max]
    void initialize_with_random(T min, T max) {
        if (min > max) {
            throw std::invalid_argument("Минимальное значение больше максимального!");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(min, max);

        for (size_t i = 0; i < n; ++i) {
            data[i] = static_cast<T>(dist(gen));
        }
        is_initialized = true; // Устанавливаем флаг инициализации
    }

    // Метод для получения размера вектора
    size_t size() const {
        return n;
    }

    // Перегрузка оператора [] для удобного доступа к элементам
    T& operator[](size_t index) {
        check_initialized();
        if (index >= n) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        return data[index];
    }

    // Константная версия оператора []
    const T& operator[](size_t index) const {
        check_initialized();
        if (index >= n) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        return data[index];
    }

    // Метод для проверки, инициализирован ли массив
    bool isInitialized() const {
        return is_initialized;
    }

// Экспорт в файл
    void export_to_file(const std::string& filename) {
        check_initialized();
        std::ofstream file(filename);
        file << n << std::endl;
        for (size_t i = 0; i < n; ++i) {
            file << data[i] << std::endl;
        }
    }

    // Импорт из файла
    void import_from_file(const std::string& filename) {
        std::ifstream file(filename);
        file >> n;
        data = new T[n];
        for (size_t i = 0; i < n; ++i) {
            file >> data[i];
        }
        is_initialized = true;
    }


// Функция для поиска минимального элемента и его индекса
    std::tuple<T, size_t, double> findMinSequential() {
        if (!is_initialized) {
            throw std::logic_error("Вектор не инициализирован!");
        }

        auto start = std::chrono::high_resolution_clock::now();
        
        T min_value = data[0]; // Инициализация минимального значения первым элементом
        size_t min_index = 0; // Индекс минимального элемента
        for (size_t i = 1; i < n; ++i) {
            if (data[i] < min_value) { // Если текущий элемент меньше минимального
                min_value = data[i]; // Обновляем минимальное значение
                min_index = i; // Обновляем индекс минимального элемента
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        return {min_value, min_index, duration.count()}; // Возвращаем пару (значение, индекс)
    }


// Параллельный поиск минимального элемента с использованием std::thread
    std::tuple<T, size_t, double> findMinParallelThreads(size_t num_threads) {
        if (!is_initialized) {
            throw std::logic_error("Вектор не инициализирован!");
        }

        auto start = std::chrono::high_resolution_clock::now();
        T min_value = data[0];
        size_t min_index = 0;

        std::vector<std::thread> threads;
        std::vector<T> min_values(num_threads, std::numeric_limits<T>::max());
        std::vector<size_t> min_indexes(num_threads, 0);

        // Функция для поиска минимального элемента в каждой части вектора
        auto findMinInRange = [&](size_t thread_id, size_t start, size_t end) {
            T local_min_value = data[start];
            size_t local_min_index = start;

            for (size_t i = start + 1; i < end; ++i) {
                if (data[i] < local_min_value) {
                    local_min_value = data[i];
                    local_min_index = i;
                }
            }

            min_values[thread_id] = local_min_value;
            min_indexes[thread_id] = local_min_index;
        };

        // Разбиение работы между потоками
        size_t chunk_size = n / num_threads;
        for (size_t i = 0; i < num_threads; ++i) {
            size_t start = i * chunk_size;
            size_t end = (i == num_threads - 1) ? n : (i + 1) * chunk_size;
            threads.push_back(std::thread(findMinInRange, i, start, end));
        }

        // Ожидание завершения всех потоков
        for (auto& th : threads) {
            th.join();
        }

        // Обработка результатов
        for (size_t i = 0; i < num_threads; ++i) {
            if (min_values[i] < min_value) {
                min_value = min_values[i];
                min_index = min_indexes[i];
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        return {min_value, min_index, duration.count()};
    }


// Метод для поиска минимального элемента (параллельный с OpenMP)
    std::tuple<T, size_t, double> findMinParallelOpenMP(size_t num_threads) {
        if (!is_initialized) {
            throw std::logic_error("Вектор не инициализирован!");
        }

        T min_value = data[0];
        size_t min_index = 0;

        auto start = std::chrono::high_resolution_clock::now();

        // Открытие области параллельных вычислений
        #pragma omp parallel for num_threads(num_threads) reduction(min:min_value)
        for (size_t i = 0; i < n; ++i) {
            if (data[i] < min_value) {
                min_value = data[i];
                min_index = i;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        return {min_value, min_index, duration.count()};
    }


    // Функция для поиска максимального элемента и его индекса
    std::pair<T, size_t> find_max() {
        check_initialized(); // Проверка, инициализирован ли вектор

        T max_value = data[0]; // Инициализация максимального значения первым элементом
        size_t max_index = 0; // Индекс максимального элемента
        for (size_t i = 1; i < n; ++i) {
            if (data[i] > max_value) { // Если текущий элемент больше максимального
                max_value = data[i]; // Обновляем максимальное значение
                max_index = i; // Обновляем индекс максимального элемента
            }
        }
        return {max_value, max_index}; // Возвращаем пару (значение, индекс)
    }
};

