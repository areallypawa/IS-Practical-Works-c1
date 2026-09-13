#include <iostream>
#include <conio.h> 
#include <chrono>
#include "Header_deafult.h"
#include "Header_workWithList.h"
#include "Header_workWithArr.h"
using namespace std;

// ПРИВЕТ

int main() {
	setlocale(0, "RU");
	List* NewList = nullptr;

	do {
		while (true) {
			show_menu(current, countItems, items, "МЕНЮ");
			int key = _getch();

			if (key == 72 && current > 0) current--;
			if (key == 80 && current < countItems - 1) current++;
			if (key == 13) break;
		}
		switch (current) {
		case 0:
		{
			do {
				clear();
				while (true) {
					show_menu(currentChoice, countItemsChoice, itemsChoice, "Заполнение");
					int key = _getch();

					if (key == 72 && currentChoice > 0) currentChoice--;
					if (key == 80 && currentChoice < countItemsChoice - 1) currentChoice++;
					if (key == 13) break;
				}

				switch (currentChoice) {
				case 0:
				{
					deleteList(NewList);
					clear();
					int len;
					cout << "Введи длину списка: ";
					cin >> len;
					clearInput();
					NewList = measureTime("List", "Create Auto", [&]() {
						return createListAuto(len);
						});

					readList(NewList);
					break;
				}
				case 1:
				{
					deleteList(NewList);
					clear();
					int* array = nullptr;
					int sizePost = 0;

					inputArr(array, sizePost);
					NewList = measureTime("List", "Create Hand", [&]() {
						return createListHand(array, sizePost);
						});
					readList(NewList);
					delete[] array;
					break;
				}
				case 2:
				{
					readList(NewList);
					measureTime("List", "Read", [&]() {
						readListWithoutPause(NewList);
						return 0;
						});
					break;
				}
				case 3:
				{
					int pos, value;
					cout << "Введите позицию элемента в списке (от 1) и значение: ";
					cin >> pos >> value;
					clearInput();
					NewList = measureTime("List", "Insert Element", [&]() {
						return insertElementList(NewList, pos, value);
						});

					readList(NewList);
					break;
				}
				case 4:
				{
					cout << YELLOW << "До " << RESET;
					readListWithoutPause(NewList);
					cout << endl;
					if (deleteBy == "value") {
						if (!NewList) {
							cout << RED << "Создайте лист!" << RESET << endl;
							pause();
							break;
						}
						int value;
						cout << "Введите значение элемента для удаления: ";
						cin >> value;
						clearInput();
						NewList = measureTime("List", "delete By Value", [&]() {
							return deleteElementByValue(NewList, value);
							});
					}
					else {
						if (!NewList) {
							cout << RED << "Создайте лист!" << RESET << endl;
							pause();
							break;
						}
						int pos;
						cout << "Введите номер элемента в списке: ";
						cin >> pos;
						clearInput();
						NewList = measureTime("List", "delete By Index", [&]() {
							return deleteElementByIndex(NewList, pos);
							});
					}
					cout << YELLOW << "После " << RESET;
					readList(NewList);
					break;
				}
				case 5:
				{
					if (!NewList || !NewList->tail) {
						cout << RED << "Список должен содержать как минимум 2 элемента!" << RESET << endl;
						pause();
						break;
					}
					int pos1, pos2;
					cout << "Введите номера элементов: ";
					cin >> pos1 >> pos2;
					clearInput();
					cout << YELLOW << "До " << RESET;
					readListWithoutPause(NewList);

					cout << endl;
					NewList = measureTime("List", "Swap By Index", [&]() {
						return swapNodesByIndex(NewList, pos1, pos2);
						});
					cout << YELLOW << "После " << RESET;
					readList(NewList);
					break;
				}
				case 6:
				{
					List* result;
					if (!NewList) {
						cout << RED << "Создайте лист!" << RESET << endl;
						pause();
						break;
					}

					if (deleteBy == "value") {
						int value;
						cout << "Введите значение элемента: ";
						cin >> value;
						clearInput();
						result = measureTime("List", "get By Value", [&]() {
							return getElementByValueMain(NewList, value);
							});
					}
					else {
						int pos;
						cout << "Введите индекс элемента в списке: ";
						cin >> pos;
						clearInput();
						result = measureTime("List", "get By Index", [&]() {
							return getElementByIndexMain(NewList, pos);
							});
					}

					if (result) {
						cout << GREEN << result << RESET;
					}
					else {
						cout << RED << "Элемент не найден!" << RESET;
					}
					pause();
					break;
				}
				}
			} while (currentChoice != countItemsChoice - 1);
			break;
		}
		case 1:
		{
			do {
				clear();
				while (true) {
					show_menu(currentChoice, countItemsChoice, itemsChoice, "Заполнение");
					int key = _getch();

					if (key == 72 && currentChoice > 0) currentChoice--;
					if (key == 80 && currentChoice < countItemsChoice - 1) currentChoice++;
					if (key == 13) break;
				}

				switch (currentChoice) {
				case 0:
				{
					clear();
					delete[] arr;
					cout << "Введите размер: ";
					arr = nullptr;
					arrSize = 0;
					cin >> arrSize;
					clearInput();
					measureTime("Dinamic Array", "Create Auto", [&]() {
						createArrAuto(arr, arrSize);
						return 0;
						});
					printArr(arr, arrSize);
					break;
				}
				case 1:
				{
					delete[] arr;
					clear();
					arr = nullptr;
					arrSize = 0;
					int* tempArr = nullptr;
					int tempSize = 0;
					inputArr(tempArr, tempSize);
					measureTime("Dinamic Array", "Create Hand", [&]() {
						createArrHand(arr, arrSize, tempArr, tempSize);
						return 0;
						});
					printArr(arr, arrSize);
					delete[] tempArr; 
					break;
				}
				case 2:
				{
					printArr(arr, arrSize);
					measureTime("Dinamic Array", "Read", [&]() {
						printArrWithoutPause(arr, arrSize);
						return 0;
						});
					break;
				}
				case 3:
				{
					cout << YELLOW << "До " << RESET;
					printArrWithoutPause(arr, arrSize);

					int pos, value;
					cout << "Введите позицию (с 1) и значение: ";
					cin >> pos >> value;
					clearInput();
					measureTime("Dinamic Array", "Insert Element", [&]() {
						insertElement(arr, arrSize, pos, value);
						return 0;
						});

					cout << YELLOW << "После " << RESET;
					printArr(arr, arrSize);
					break;
				}
				case 4:
				{
					cout << YELLOW << "До " << RESET;
					printArrWithoutPause(arr, arrSize);

					if (deleteBy == "value") {
						int value;
						cout << "Введите значение: ";
						cin >> value;
						clearInput();
						measureTime("Dinamic Array", "delete By Value", [&]() {
							deleteByValue(arr, arrSize, value);
							return 0;
							});
					}
					else {
						int pos;
						cout << "Введите номер: ";
						cin >> pos;
						clearInput();
						measureTime("Dinamic Array", "delete By Index", [&]() {
							deleteByIndex(arr, arrSize, pos);
							return 0;
							});
					}
					cout << YELLOW << "После " << RESET;
					printArr(arr, arrSize);
					break;
				}
				case 5:
				{
					cout << YELLOW << "До " << RESET;
					printArrWithoutPause(arr, arrSize);

					if (!arr || arrSize < 2) {
						cout << "Массив должен содержать как минимум 2 элемента!" << endl;
						break;
					}

					int pos1, pos2;
					cout << "Введите номера элементов для обмена (от 1 до " << arrSize << "): ";
					cin >> pos1 >> pos2;
					clearInput();
					measureTime("Dinamic Array", "Swap By Index", [&]() {
						swapElements(arr, arrSize, pos1, pos2);
						return 0;
						});
					cout << YELLOW << "После " << RESET;
					printArr(arr, arrSize);
					break;
				}
				case 6:
				{
					int posOrVal;
					if (deleteBy == "value") {
						cout << "Введите значение элемента: ";
						cin >> posOrVal;
						clearInput();
						int index = measureTime("Dinamic Array", "get By Value", [&]() {
							return getElementByValueArr(arr, arrSize, posOrVal);
							
							});
						//int index = getElementByValueArr(arr, arrSize, posOrVal);
						if (index != -1) cout << GREEN << arr[index - 1] << RESET;
						else cout << RED << "Элемент не найден!" << RESET;
					}
					else {
						cout << "Введите индекс элемента: ";
						cin >> posOrVal;
						clearInput();
						int value = measureTime("Dinamic Array", "get By Index", [&]() {
							return getElementByValueArr(arr, arrSize, posOrVal);
							});
						if (value != -1) cout << GREEN << value << RESET;
						else cout << RED << "Элемент не найден!" << RESET;
					}
					pause();
					break;
				}
				}

			} while (currentChoice != countItemsChoice - 1);

			break;
		}
		case 2:
		{
			showSplitScreen();
			_getch();
			break;
		}
		case 3:
		{
			delete[] logs;
			logs = nullptr;  
			logCount = 0;
			break;
		}
		}

		clear();

	} while (current != countItems - 1);

	deleteAllLists(NewList);
	return 0;
}