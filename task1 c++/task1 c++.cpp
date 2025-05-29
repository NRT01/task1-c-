#include <iostream>
#include <stdexcept> // Для обработки исключений
#include <cstdlib>   // Для rand() и srand()
#include <ctime>     // Для time()

using namespace std;

// Функция для ввода матрицы
void inputMatrix(int**& matrix, int rows, int cols) {
    cout << "Введите элементы матрицы " << rows << "x" << cols << ":\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Введите элемент [" << i + 1 << "][" << j + 1 << "]: ";
            while (!(cin >> matrix[i][j])) { // Проверка на корректность ввода
                cin.clear(); // Очищаем ошибку ввода
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем неверный ввод
                cout << "Ошибка! Введите целое число для элемента [" << i + 1 << "][" << j + 1 << "]: ";
            }
        }
    }
}

// Функция для генерации случайной матрицы
void generateRandomMatrix(int**& matrix, int rows, int cols) {
    srand(time(0)); // Инициализация генератора случайных чисел
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100; // Заполнение случайными числами от 0 до 99
        }
    }
}

// Функция для вывода матрицы
void printMatrix(int** matrix, int rows, int cols) {
    cout << "Матрица:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция для обмена строк матрицы
void reverseRows(int**& matrix, int rows, int cols) {
    for (int i = 0; i < rows / 2; i++) {
        for (int j = 0; j < cols; j++) {
            // Обмен элементов строк
            swap(matrix[i][j], matrix[rows - 1 - i][j]);
        }
    }
}

int main() {
    int rows, cols;
    char useExample;

    // Запросить размерность матрицы у пользователя с проверками
    cout << "Введите количество строк матрицы: ";
    while (!(cin >> rows) || rows <= 0) { // Проверка на корректность ввода
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка! Введите положительное целое число для количества строк: ";
    }

    cout << "Введите количество столбцов матрицы: ";
    while (!(cin >> cols) || cols <= 0) { // Проверка на корректность ввода
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка! Введите положительное целое число для количества столбцов: ";
    }

    // Запросить, использовать ли автоматический пример
    cout << "Хотите использовать автоматический пример (y/n)? ";
    cin >> useExample;

    // Динамическое выделение памяти под матрицу
    int** matrix = nullptr;
    try {
        matrix = new int* [rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
        }
    }
    catch (bad_alloc& e) { // Обработка ошибок выделения памяти
        cerr << "Ошибка выделения памяти: " << e.what() << endl;
        return 1;
    }

    try {
        if (useExample == 'y' || useExample == 'Y') {
            // Генерация случайной матрицы для примера
            generateRandomMatrix(matrix, rows, cols);

            // Вывод случайной матрицы
            cout << "\nАвтоматически сгенерированная матрица:\n";
            printMatrix(matrix, rows, cols);
        }
        else {
            // Ввод данных в матрицу
            inputMatrix(matrix, rows, cols);
        }

        // Вывод исходной матрицы
        cout << "\nИсходная матрица:\n";
        printMatrix(matrix, rows, cols);

        // Изменение порядка строк
        reverseRows(matrix, rows, cols);

        // Вывод матрицы после изменения порядка строк
        cout << "\nМатрица после изменения порядка строк:\n";
        printMatrix(matrix, rows, cols);
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    // Освобождение памяти
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
 