#include <iostream> // Для работы с вводом/выводом
#include <fstream>  // Для работы с файлами
#include <vector>   // Для использования контейнера vector
#include <string>   // Для работы со строками

// Класс GpuSpec: хранит информацию о характеристиках графического процессора
class GpuSpec {
public:
    std::string model; // Модель GPU
    int cores;         // Количество ядер
    float frequency;   // Частота в GHz

    // Метод для вывода информации о GPU в консоль
    void Print() const {
        std::cout << "GPU: Model: " << model << ", Cores: " << cores << ", Frequency: " << frequency << " GHz\n";
    }

    // Метод для импорта данных о GPU из файла
    void Import(std::ifstream &file) {
        file >> model >> cores >> frequency; // Считываем модель, ядра и частоту
    }

    // Метод для экспорта данных о GPU в файл
    void Export(std::ofstream &file) const {
        file << model << " " << cores << " " << frequency << "\n"; // Записываем данные в файл
    }
};

// Класс CpuSpec: хранит информацию о характеристиках процессора
class CpuSpec {
public:
    std::string model; // Модель CPU
    int cores;         // Количество ядер
    float frequency;   // Частота в GHz

    // Метод для вывода информации о CPU в консоль
    void Print() const {
        std::cout << "CPU: Model: " << model << ", Cores: " << cores << ", Frequency: " << frequency << " GHz\n";
    }

    // Метод для импорта данных о CPU из файла
    void Import(std::ifstream &file) {
        file >> model >> cores >> frequency; // Считываем модель, ядра и частоту
    }

    // Метод для экспорта данных о CPU в файл
    void Export(std::ofstream &file) const {
        file << model << " " << cores << " " << frequency << "\n"; // Записываем данные в файл
    }
};

// Класс RamSpec: хранит информацию о характеристиках оперативной памяти
class RamSpec {
public:
    int capacity;   // Объём памяти в GB
    float frequency; // Частота памяти в MHz

    // Метод для вывода информации о RAM в консоль
    void Print() const {
        std::cout << "RAM: Capacity: " << capacity << " GB, Frequency: " << frequency << " MHz\n";
    }

    // Метод для импорта данных о RAM из файла
    void Import(std::ifstream &file) {
        file >> capacity >> frequency; // Считываем объём и частоту
    }

    // Метод для экспорта данных о RAM в файл
    void Export(std::ofstream &file) const {
        file << capacity << " " << frequency << "\n"; // Записываем данные в файл
    }
};

// Класс LanSpec: хранит информацию о характеристиках сети
class LanSpec {
public:
    float bandwidth;  // Пропускная способность в Gbps
    std::string type; // Тип сети (например, Ethernet или WiFi)

    // Метод для вывода информации о сети в консоль
    void Print() const {
        std::cout << "LAN: Bandwidth: " << bandwidth << " Gbps, Type: " << type << "\n";
    }

    // Метод для импорта данных о сети из файла
    void Import(std::ifstream &file) {
        file >> bandwidth >> type; // Считываем пропускную способность и тип
    }

    // Метод для экспорта данных о сети в файл
    void Export(std::ofstream &file) const {
        file << bandwidth << " " << type << "\n"; // Записываем данные в файл
    }
};

// Класс ClusterNode: моделирует вычислительный узел кластера
class ClusterNode {
public:
    GpuSpec gpu; // Объект GPU спецификаций
    CpuSpec cpu; // Объект CPU спецификаций
    RamSpec ram; // Объект RAM спецификаций
    LanSpec lan; // Объект LAN спецификаций

    // Метод для вывода информации об узле в консоль
    void Print() const {
        std::cout << "Cluster Node:\n";
        gpu.Print();
        cpu.Print();
        ram.Print();
        lan.Print();
    }

    // Метод для импорта данных об узле из файла
    void Import(std::ifstream &file) {
        gpu.Import(file); // Импортируем спецификации GPU
        cpu.Import(file); // Импортируем спецификации CPU
        ram.Import(file); // Импортируем спецификации RAM
        lan.Import(file); // Импортируем спецификации LAN
    }

// Метод для экспорта данных об узле в файл
    void Export(std::ofstream &file) const {
        gpu.Export(file); // Экспортируем спецификации GPU
        cpu.Export(file); // Экспортируем спецификации CPU
        ram.Export(file); // Экспортируем спецификации RAM
        lan.Export(file); // Экспортируем спецификации LAN
    }
};

// Класс Cluster: моделирует кластер, состоящий из нескольких узлов
class Cluster {
public:
    std::vector<ClusterNode> nodes; // Список узлов кластера

    // Метод для вывода информации о кластере в консоль
    void Print() const {
        std::cout << "Cluster:\n";
        for (size_t i = 0; i < nodes.size(); ++i) { // Итерируемся по всем узлам
            std::cout << "Node " << i + 1 << ":\n";
            nodes[i].Print(); // Выводим информацию об узле
        }
    }

    // Метод для импорта данных о кластере из файла
    void Import(const std::string &filename) {
        std::ifstream file(filename); // Открываем файл на чтение
        if (!file.is_open()) { // Проверяем, удалось ли открыть файл
            std::cerr << "Error: Unable to open file for importing.\n";
            return;
        }
        int nodeCount;
        file >> nodeCount; // Считываем количество узлов
        nodes.resize(nodeCount); // Задаём размер вектора узлов
        for (auto &node : nodes) {
            node.Import(file); // Импортируем данные для каждого узла
        }
        file.close(); // Закрываем файл
    }

    // Метод для экспорта данных о кластере в файл
    void Export(const std::string &filename) const {
        std::ofstream file(filename); // Открываем файл на запись
        if (!file.is_open()) { // Проверяем, удалось ли открыть файл
            std::cerr << "Error: Unable to open file for exporting.\n";
            return;
        }
        file << nodes.size() << "\n"; // Записываем количество узлов
        for (const auto &node : nodes) {
            node.Export(file); // Экспортируем данные для каждого узла
        }
        file.close(); // Закрываем файл
    }
};

// Функция для тестирования кода
void Test() {
    Cluster cluster;

    // Создаём первый узел вручную
    ClusterNode node1;
    node1.gpu = {"RTX3090", 10496, 1.7f}; // Устанавливаем характеристики GPU
    node1.cpu = {"Ryzen9", 16, 3.8f};     // Устанавливаем характеристики CPU
    node1.ram = {32, 3200.0f};            // Устанавливаем характеристики RAM
    node1.lan = {10.0f, "Ethernet"};      // Устанавливаем характеристики LAN

    // Создаём второй узел вручную
    ClusterNode node2;
    node2.gpu = {"RTX2080", 8704, 1.6f};
    node2.cpu = {"i7-10700K", 8, 3.6f};
    node2.ram = {16, 3000.0f};
    node2.lan = {1.0f, "WiFi"};

    cluster.nodes.push_back(node1); // Добавляем первый узел в кластер
    cluster.nodes.push_back(node2); // Добавляем второй узел в кластер

    cluster.Export("cluster_data.txt"); // Экспортируем данные кластера в файл
    cluster.Print();                    // Выводим информацию о кластере

    Cluster importedCluster;          // Создаём пустой кластер
    importedCluster.Import("cluster_data.txt"); // Импортируем данные из файла

    std::cout << "\nImported Cluster:\n";
    importedCluster.Print(); // Выводим информацию о импортированном кластере
}

// Точка входа в программу
int main() {
    Test(); // Запускаем тестовую функцию
    return 0;
}
