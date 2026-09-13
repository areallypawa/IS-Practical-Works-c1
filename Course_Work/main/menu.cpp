#include <iostream>
#include <conio.h> 
#include "Header_common.h"
#include "Header_lab1.h"
#include "Header_lab2.h"
#include "Header_lab3.h"
#include "Header_lab4.h"


static string items[] = { "Лаболаторная работа #1", "Лаболаторная работа #2", "Лаболаторная работа #3", "Лаболаторная работа #4", "Выход" };
static int current = 0;

int main() {
	setlocale(LC_ALL, "rus");

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
            labolatornaya_1();
            break;
        case 1:
            labolatornaya_2();
            break;
        case 2:
            labolatornaya_3();
            break;
        case 3:
            labolatornaya_4();
            break;
        }
        clear();

	} while (current != size(items) - 1);

	return 0;
}
