#include <iostream>
#include <conio.h> 
#include "Header_common.h";

using namespace std;

int TASK2;
float TASK3;
double TASK4;

static string items[] = { "Вывести объём памяти под типы данных", "Вывести на экран двоичное представление в памяти целого числа.", "Вывести на экран двоичное представление в памяти типа float.", "Вывести на экран двоичное представление в памяти типа double.", "Выход" };
static int current = 0;

union MyFloatUnion {
    int tool;
    float num;
};
MyFloatUnion myFloatUnion;
union MyDoubleUnion {
    int tool[2];
    double num;
};
MyDoubleUnion myDoubleUnion;

void Algorithm_print_bits(int num);
void Algorithm_print_double();
void Algorithm_for_task_5(int number, int flag);
void Task_1();
void Task_2();
void Task_3();
void Task_4();
void Task_5(short num_type, short choice);

int labolatornaya_1() {
    setlocale(0, "");
    do {
        clear();
        while (true) {
            show_menu(current, size(items), items);
            int key = _getch();

            if (key == 72 && current > 0) current--;
            if (key == 80 && current < size(items) - 1) current++;
            if (key == 13) break;
        }

        switch (current) {
        case 0:
            Task_1();
            break;
        case 1:
            Task_2();
            Task_5(current, 0);
            break;
        case 2:
            Task_3();
            Task_5(current, 0);
            break;
        case 3:
            Task_4();
            Task_5(current, 0);
            break;
        }
        clear();
    } while (current != size(items) - 1);

    return 0;
}

void Algorithm_print_bits(int num) {
    const int BITS = sizeof(num) * 8;
    unsigned int mask = 1 << (BITS - 1);

    for (int i(0); i < BITS; i++) {
        if (((i == 1) || (i % 4 == 0)) && i != 0) {
            cout << ' ';
        }
        if (i == 0) { cout << "\033[31m"; }
        else { cout << "\033[36m"; }
        cout << ((num & mask) ? '1' : '0');
        mask >>= 1;
    }
    cout << "\033[0m\n" << endl;
}

void Algorithm_print_double() {
    // Bin-Code for tip double 
    const int BITS = sizeof(int) * 8;

    for (int j(1); j > -1; j--) {
        unsigned int mask = 1 << (BITS - 1);
        for (int i(0); i < BITS; i++) {
            int global_bit_index = (1 - j) * 32 + i;
            if (global_bit_index == 1 || global_bit_index == 12) { cout << "\033[0m|"; }
            else if (i % 4 == 0 && !(global_bit_index == 1 || global_bit_index == 12)) { cout << ' '; }
            // Цвета по зонам
            if (global_bit_index == 0) { cout << "\033[31m"; }
            else if (global_bit_index >= 1 && global_bit_index <= 11) { cout << "\033[33m"; }
            else { cout << "\033[36m"; }
            cout << ((myDoubleUnion.tool[j] & mask) ? '1' : '0');
            mask >>= 1;
        }
    }
    cout << "\033[0m\n" << endl;
}

void Algorithm_for_task_5(int number, int flag) {
    cout << "Введи индекс бита и значение на которое его поменять\n";
    int idx; bool value;
    cin >> idx >> value;

    int modify_num;
    const int BITS = sizeof(number) * 8;

    if (value) {
        unsigned int mask = (1 << idx);
        modify_num = number | mask;

        switch (flag) {
        case 1:
            cout << "Стало число " << modify_num << "\nBIN: ";
            Algorithm_print_bits(modify_num);
            break;
        case 2:
            myFloatUnion.tool = modify_num;
            cout << "Стало число " << myFloatUnion.num << "\nBIN: ";
            Algorithm_print_bits(modify_num);
            break;
        case 3:
            if (idx > 31) {
                unsigned int mask = (1 << (idx - 32));
                modify_num = myDoubleUnion.tool[1] | mask;
                myDoubleUnion.tool[1] = modify_num;
            }
            else {
                unsigned int mask = (1 << (idx));
                modify_num = myDoubleUnion.tool[0] | mask;
                myDoubleUnion.tool[0] = modify_num;
            }
            cout << "Стало число " << myDoubleUnion.num << "\nBIN: ";
            Algorithm_print_double();
            break;
        }
    }
    else {
        unsigned int mask = (1 << BITS) - 1 - (1 << idx);
        modify_num = number & mask;

        switch (flag) {
        case 1:
            cout << "Стало число " << modify_num << "\nBIN: ";
            Algorithm_print_bits(modify_num);
            break;
        case 2:
            myFloatUnion.tool = modify_num;
            cout << "Стало число " << myFloatUnion.num << "\nBIN: ";
            Algorithm_print_bits(modify_num);
            break;
        case 3:
            if (idx > 31) {
                unsigned int mask = (1 << BITS) - 1 - (1 << idx - 32);
                modify_num = myDoubleUnion.tool[1] & mask;
                myDoubleUnion.tool[1] = modify_num;
            }
            else {
                unsigned int mask = (1 << BITS) - 1 - (1 << idx);
                modify_num = myDoubleUnion.tool[0] & mask;
                myDoubleUnion.tool[0] = modify_num;
            }
            cout << "Стало число " << myDoubleUnion.num << "\nBIN: ";
            Algorithm_print_double();
            break;
        }
    }
}

void Task_1() {
    clear();
    cout
        << "int: " << sizeof(int) << " байта\n"
        << "short int: " << sizeof(short int) << " байта\n"
        << "long int: " << sizeof(long int) << " байта\n"
        << "long long int: " << sizeof(long long int) << " байт\n"
        << "float: " << sizeof(float) << " байта\n"
        << "double: " << sizeof(double) << " байт\n"
        << "long double: " << sizeof(long double) << " байт\n"
        << "char: " << sizeof(char) << " байт\n"
        << "bool: " << sizeof(bool) << " байт\n";
    pause();
}

void Task_2() {
    clear();
    cout << "Введи целое число: ";
    cin >> TASK2;
    Algorithm_print_bits(TASK2);
}

void Task_3() {
    clear();
    cout << "Введи число типа float: ";
    cin >> TASK3;
    myFloatUnion.num = TASK3;

    Algorithm_print_bits(myFloatUnion.tool);
    cout << '\n';
}

void Task_4() {
    clear();
    cout << "Введи число типа double: ";
    cin >> TASK4;
    myDoubleUnion.num = TASK4;

    Algorithm_print_double();
    cout << '\n';
}

void Task_5(short num_type, short choice) {
    cout << "Хочень изменить бит? 0 - нет/1 - да: ";
    cin >> choice;
    if (choice) {
        switch (num_type) {
        case 1:
            cout << "Было число " << TASK2 << "\nBIN: ";
            Algorithm_print_bits(TASK2);
            Algorithm_for_task_5(TASK2, 1);
            break;
        case 2:
            myFloatUnion.num = TASK3;
            cout << "Было число " << TASK3 << "\nBIN: ";
            Algorithm_print_bits(myFloatUnion.tool);
            Algorithm_for_task_5(myFloatUnion.tool, 2);
            break;
        case 3:
            myDoubleUnion.num = TASK4;
            cout << "Было число " << TASK4 << "\nBIN: ";
            Algorithm_print_double();
            Algorithm_for_task_5(myFloatUnion.tool, 3);
            break;
        }
    }
    pause();
}
