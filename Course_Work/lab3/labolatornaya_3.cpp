#include <iostream>
#include <Windows.h>
#include <conio.h> 
#include "Header_common.h"

using namespace std;
const int N = 6;

static string items[] = { "Вывести матрицу на экран", "Заполнить матрицу (спираль)", "Заполнить матрицу (змейка)", "Перестановка по квадрату", "Перестановка по кресту", "Перестановка по вертикальным паралельным","Перестановка по горизонтальным паралельным", "Отсортировать", "Уменьшить, увеличить, умножить или поделить", "IDZ #17", "Выход" };
static int current_operators = 0;
static int current = 0;

void print_matrix(int* array);
void print_success(int* array, int* transform_array);
void fill_snake(int* array);
void fill_spiral(int* array);
void transform_a(int* array, int* transform_array);
void transform_b(int* array, int* transform_array);
void transform_c(int* array, int* transform_array);
void transform_d(int* array, int* transform_array);
void bubble_sort(int* matrix);
void matrix_operation(int* array, int value, const string& op);
void idz_matrix();

int labolatornaya_3() {
    setlocale(LC_ALL, "rus");
    int array[N][N];
    int transform_array[N][N];
    bool flag = false;

    do {
        while (true) {
            show_menu(current, size(items), items);
            int key = _getch();

            if (key == 72 && current > 0) current--;
            if (key == 80 && current < size(items) - 1) current++;
            if (key == 13) break;
        }

        switch (current) {
        case 0:
            clear();
            print_matrix(*array);
            pause();
            break;
        case 1:
            fill_spiral(*array);
            break;
        case 2:
            fill_snake(*array);
            break;
        case 3:
            flag = true;
            transform_a(*array, *transform_array);
            print_success(*array, *transform_array);
            break;
        case 4:
            flag = true;
            transform_b(*array, *transform_array);
            print_success(*array, *transform_array);
            break;
        case 5:
            flag = true;
            transform_c(*array, *transform_array);
            print_success(*array, *transform_array);
            break;
        case 6:
            flag = true;
            transform_d(*array, *transform_array);
            print_success(*array, *transform_array);
            break;
        case 7:
        {
            clear();
            print_matrix(*array);
            bubble_sort(*array);
            cout << "SORT\n";
            print_matrix(*array);
            pause();
            break;
        }

        case 8:
        {
            clear();
            int a;
            string operators[5] = { "+", "-", "*", "/", "Выход" };
            while (true) {
                show_menu(current_operators, size(operators), operators);
                int key2 = _getch();

                if (key2 == 72 && current_operators > 0) current_operators--;
                if (key2 == 80 && current_operators < size(operators) - 1) current_operators++;
                if (key2 == 13) break;
            }

            clear();
            if (operators[current_operators] == "Выход") {

                break;
            }
            cout << "Операция: " << operators[current_operators] << "\nВведи число а: ";
            cin >> a;
            clear();
            print_matrix(*array);
            matrix_operation(*array, a, operators[current_operators]);
            cout << "SUCCESSFUL\n";
            print_matrix(*array);
            pause();
            break;
        }
        case 9:
        {
            idz_matrix();
            break;
        }
        }
        clear();

        if (flag) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    *(&array[0][0] + i * N + j) = *(&transform_array[0][0] + i * N + j);
                }
            }
            flag = false;
        }

    } while (current != size(items) - 1);


    return 0;
}


void print_matrix(int* array) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << *((array + i * N) + j) << "\t";
        }
        cout << "\n";
    }
}

void print_success(int* array, int* transform_array) {
    clear();
    print_matrix(array);
    cout << "SUCCESSFUL\n";
    print_matrix(transform_array);
    pause();
}

void fill_snake(int* array) {
    clear();
    int val = rand() % 100 + 1;

    for (int col = 0; col < N; col++) {
        if (col % 2 == 0) {
            // сверху вниз
            for (int row = 0; row < N; row++) {
                int val = rand() % (N * N) + 1;
                *((array + row * N) + col) = val;

                set_cords(col * 4, row);
                cout << val;
                Sleep(80);
            }
        }
        else {
            // снизу вверх
            for (int row = N - 1; row >= 0; row--) {
                int val = rand() % (N * N) + 1;
                *((array + row * N) + col) = val;

                set_cords(col * 4, row);
                cout << val;
                Sleep(80);
            }
        }
    }
}

void fill_spiral(int* array) {
    clear();
    int top = 0, bottom = N - 1;
    int left = 0, right = N - 1;
    int val = 1;

    while (top <= bottom && left <= right) {

        for (int j = left; j <= right; j++) {
            int val = rand() % (N * N) + 1;
            *((array + top * N) + j) = val;

            set_cords(j * 4, top);
            cout << val;
            Sleep(80);
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            int val = rand() % (N * N) + 1;
            *((array + i * N) + right) = val;

            set_cords(right * 4, i);
            cout << val;
            Sleep(80);
        }
        right--;

        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                int val = rand() % (N * N) + 1;
                *((array + bottom * N) + j) = val;

                set_cords(j * 4, bottom);
                cout << val;
                Sleep(80);
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                int val = rand() % (N * N) + 1;
                *((array + i * N) + left) = val;

                set_cords(left * 4, i);
                cout << val;
                Sleep(80);
            }
            left++;
        }
    }
}

void transform_a(int* array, int* transform_array) {
    int half = N / 2;

    // A B
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *((transform_array + i * N) + (j + half)) =
                *((array + i * N) + j);
        }
    }

    // B D
    for (int i = 0; i < half; i++) {
        for (int j = half; j < N; j++) {
            *((transform_array + (i + half) * N) + j) =
                *((array + i * N) + j);
        }
    }

    // D C
    for (int i = half; i < N; i++) {
        for (int j = half; j < N; j++) {
            *((transform_array + i * N) + (j - half)) =
                *((array + i * N) + j);
        }
    }

    // C A
    for (int i = half; i < N; i++) {
        for (int j = 0; j < half; j++) {
            *((transform_array + (i - half) * N) + j) =
                *((array + i * N) + j);
        }
    }
}

void transform_b(int* array, int* transform_array) {
    int half = N / 2;

    // A D
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *((transform_array + (i + half) * N) + (j + half)) =
                *((array + i * N) + j);
        }
    }

    // B C
    for (int i = 0; i < half; i++) {
        for (int j = half; j < N; j++) {
            *((transform_array + (i + half) * N) + (j - half)) =
                *((array + i * N) + j);
        }
    }

    // C B
    for (int i = half; i < N; i++) {
        for (int j = 0; j < half; j++) {
            *((transform_array + (i - half) * N) + (j + half)) =
                *((array + i * N) + j);
        }
    }

    // D A
    for (int i = half; i < N; i++) {
        for (int j = half; j < N; j++) {
            *((transform_array + (i - half) * N) + (j - half)) =
                *((array + i * N) + j);
        }
    }
}

void transform_c(int* array, int* transform_array) {
    int half = N / 2;

    // A C
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *((transform_array + (i + half) * N) + j) =
                *((array + i * N) + j);
        }
    }

    // C A
    for (int i = half; i < N; i++) {
        for (int j = 0; j < half; j++) {
            *((transform_array + (i - half) * N) + j) =
                *((array + i * N) + j);
        }
    }

    // B D
    for (int i = 0; i < half; i++) {
        for (int j = half; j < N; j++) {
            *((transform_array + (i + half) * N) + j) =
                *((array + i * N) + j);
        }
    }

    // D B
    for (int i = half; i < N; i++) {
        for (int j = half; j < N; j++) {
            *((transform_array + (i - half) * N) + j) =
                *((array + i * N) + j);
        }
    }
}

void transform_d(int* array, int* transform_array) {
    int half = N / 2;

    // A B
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            *((transform_array + i * N) + (j + half)) =
                *((array + i * N) + j);
        }
    }

    // B A
    for (int i = 0; i < half; i++) {
        for (int j = half; j < N; j++) {
            *((transform_array + i * N) + (j - half)) =
                *((array + i * N) + j);
        }
    }

    // C D
    for (int i = half; i < N; i++) {
        for (int j = 0; j < half; j++) {
            *((transform_array + i * N) + (j + half)) =
                *((array + i * N) + j);
        }
    }

    // D C
    for (int i = half; i < N; i++) {
        for (int j = half; j < N; j++) {
            *((transform_array + i * N) + (j - half)) =
                *((array + i * N) + j);
        }
    }
}

void bubble_sort(int* matrix) {
    for (int i = 0; i < N * N - 1; i++) {
        for (int j = 0; j < N * N - 1 - i; j++) {
            if (matrix[j] > matrix[j + 1]) {
                swap(matrix[j], matrix[j + 1]);
            }
        }
    }
}


void matrix_operation(int* array, int value, const string& op) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int* elem = array + i * N + j;

            if (op == "+") {
                *elem += value;
            }
            else if (op == "-") {
                *elem -= value;
            }
            else if (op == "*") {
                *elem *= value;
            }
            else if (op == "/") {
                if (value != 0) {
                    *elem /= value;
                }
            }
        }
    }
}


void idz_matrix() {
    clear();
    int matrix[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 100 + 1;  // от 1 до 100
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "\nСуммы строк:\n";
    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = 0; j < N; j++) {
            sum += matrix[i][j];
        }
        cout << "Строка " << i + 1 << ": " << sum << endl;
    }

    cout << "\nСуммы столбцов:\n";
    for (int j = 0; j < N; j++) {
        int sum = 0;
        for (int i = 0; i < N; i++) {
            sum += matrix[i][j];
        }
        cout << "Столбец " << j + 1 << ": " << sum << endl;
    }
    pause();
}
