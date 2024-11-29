#include "MatrixDiagonal.h"
#include <iostream>

int main() {
    try {
        // Создание матрицы 3x3 вручную
        MatrixDiagonal mat1(3);
        mat1.set(0, 0, 3.0);
        mat1.set(1, 1, 1.0);
        mat1.set(2, 2, 2.0);


        // Создание матрицы 3x3 из файла
        MatrixDiagonal mat2(3);
        mat2.importFromFile("diagonal_matrix.txt");

        std::cout << "Матрица 1 (вручную):\n";
        mat1.print();

        std::cout << "\nМатрица 2 (из файла):\n";
        mat2.print();

        Matrix* sum = mat1.add(mat2);  // Складываем матрицы
        std::cout << "\nСумма матриц:\n";
        sum->print();  // Выводим результат сложения на экран

        // Сохраняем результат в файл
        sum->exportToFile("result_sum_diagonal.txt");
        std::cout << "\nРезультат сложения сохранён в файл 'result_sum.txt'.\n";

        // Не забываем освободить память, если используется new
        delete sum;

        Matrix* mult = mat1.multiply(mat2);  //  умножение
        std::cout << "\nумножение матриц:\n";
        mult->print();  // Выводим результат 

        // Сохраняем результат в файл
        mult->exportToFile("result_mult_diagonal.txt");
        std::cout << "\nРезультат сохранён в файл 'result_mult.txt'.\n";

        // Не забываем освободить память, если используется new
        delete mult;



        Matrix* transpose = mat1.transpose();
        std::cout << "\nТранспонированная матрица 1:\n";
        transpose->print();

        // Сохраняем результат в файл
        transpose->exportToFile("result_transp_diagonal.txt");
        std::cout << "\nРезультат сохранён в файл 'result_transp.txt'.\n";

        delete transpose;

        




    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}
