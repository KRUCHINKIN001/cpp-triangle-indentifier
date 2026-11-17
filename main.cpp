#include <iostream>
#include <fstream>
#include <cmath>
#include <clocale>
#include <algorithm>

using namespace std;

const char* FILENAME = "sides.bin";

// Docstring: Записывает три стороны треугольника в бинарный файл.
void writeSidesToFile(double a, double b, double c) {
    fstream file(FILENAME, ios::out | ios::binary);

    if (!file) {
        cout << "Ошибка создания файла!" << endl;
        return;
    }

    file.write(reinterpret_cast<char*>(&a), sizeof(double));
    file.write(reinterpret_cast<char*>(&b), sizeof(double));
    file.write(reinterpret_cast<char*>(&c), sizeof(double));

    file.close();
    cout << "Стороны успешно записаны в бинарный файл." << endl;
}

// Docstring: Читает стороны из файла и проверяет, является ли треугольник прямоугольным.
void checkTriangle() {
    fstream file(FILENAME, ios::in | ios::binary);

    if (!file) {
        cout << "Ошибка: файл не найден или недоступен для чтения!" << endl;
        return;
    }

    double sides[3];
    int count = 0;

    // Читаем три числа типа double из файла
    while (count < 3 && file.read(reinterpret_cast<char*>(&sides[count]), sizeof(double))) {
        count++;
    }
    file.close();

    if (count != 3) {
        cout << "Ошибка: в файле должно быть ровно три числа (стороны)." << endl;
        return;
    }

    double a = sides[0];
    double b = sides[1];
    double c = sides[2];

    cout << "Считанные стороны: " << a << ", " << b << ", " << c << endl;

    // Сортируем стороны, чтобы самая большая была в переменной c
    double arr[3] = {a, b, c};
    sort(arr, arr + 3);
    a = arr[0];
    b = arr[1];
    c = arr[2];

    // Проверка 1: можно ли построить треугольник?
    if (a + b <= c) {
        cout << "Результат: Из этих отрезков нельзя построить треугольник (нарушено неравенство треугольника)." << endl;
        return;
    }

    // Проверка 2: является ли треугольник прямоугольным?
    // Используем небольшое число (1e-9) для компенсации погрешности вычислений с double
    double leftSide = c * c;
    double rightSide = a * a + b * b;

    if (abs(leftSide - rightSide) < 1e-9) {
        cout << "Результат: Треугольник является ПРЯМОУГОЛЬНЫМ." << endl;
    } else {
        cout << "Результат: Треугольник НЕ является прямоугольным." << endl;
    }
}

int main() {
    // Установка русской кодировки
    setlocale(LC_ALL, "Russian");

    int choice;
    double a, b, c;

    do {
        cout << "\n=== ОПРЕДЕЛИТЕЛЬ ТРЕУГОЛЬНИКА ===" << endl;
        cout << "1. Записать стороны в файл" << endl;
        cout << "2. Прочитать файл и проверить треугольник" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите сторону a: ";
                cin >> a;
                cout << "Введите сторону b: ";
                cin >> b;
                cout << "Введите сторону c: ";
                cin >> c;
                writeSidesToFile(a, b, c);
                break;
            case 2:
                checkTriangle();
                break;
            case 0:
                cout << "Выход." << endl;
                break;
            default:
                cout << "Неверный пункт меню!" << endl;
        }
    } while (choice != 0);

    return 0;
}
