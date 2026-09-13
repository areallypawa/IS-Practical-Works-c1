#include "Header_workWithArr.h"



void resizeArray(int*& arr, int oldSize, int newSize) {
    int* temp = new int[newSize];

    int minSize = (oldSize < newSize) ? oldSize : newSize;
    for (int i = 0; i < minSize; i++) {
        temp[i] = arr[i];
    }

    delete[] arr;
    arr = temp;
    for (int i = oldSize; i < newSize; i++) {
        arr[i] = 0; 
    }
}


void inputArr(int*& arr, int& size) {
    cout << "Введите числа через пробел: ";
   
    string line;
    getline(cin >> ws, line);

    size = 0;
    stringstream ssCount(line);
    int temp;
    while (ssCount >> temp) {
        size++;
    }

    arr = new int[size];

    stringstream ssFill(line);
    int i = 0;
    while (ssFill >> temp) {
        arr[i++] = temp;
    }
}


int getElementByValueArr(int* arr, int arrSize, int posOrVal) {
    if (arr == nullptr || arrSize <= 0) {
        return -1;
    }

    for (int i = 0; i < arrSize; i++) {
        if (arr[i] == posOrVal) {
            return arr[i];
        }
    }

    return -1;
}


int getElementByIndexArr(int* arr, int arrSize, int posOrVal) {
    if (arr == nullptr || arrSize <= 0 || posOrVal < 0 || posOrVal >= arrSize) {
        return -1;
    }
    return arr[posOrVal];
}


void createArrAuto(int*& arr, int& size) {
    arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1;
    }
}


void createArrHand(int*& arr, int& size, int* source, int sourceSize) {
    arr = new int[sourceSize];
    size = sourceSize;

    for (int i = 0; i < size; i++) {
        arr[i] = source[i];
    }
}


void printArr(int* arr, int size) {
    if (!arr || size == 0) {
        cout << RED << "Массив пуст!" << RESET << endl;
        return;
    }
    cout << GREEN << "Массив в памяти: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << RESET;
    pause();
}


void printArrWithoutPause(int* arr, int size) {
    if (!arr || size == 0) {
        cout << RED << "Массив пуст!" << RESET << endl;
    }
    cout << GREEN << "Массив в памяти: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << RESET << endl;
}


void insertElement(int*& arr, int& size, int& pos, int& value) {

    if (pos < 1) pos = 1;
    if (pos > size + 1) pos = size + 1;

    int oldSize = size;
    resizeArray(arr, size, size + 1);
    size++;

    // сдвиг 
    for (int i = size - 1; i >= pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos - 1] = value;
}


void deleteByIndex(int*& arr, int& size, int& pos) {

    if (pos < 1 || pos > size) return;

    for (int i = pos - 1; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    resizeArray(arr, size, size - 1);
    size--;
}


void deleteByValue(int*& arr, int& size, int& value) {

    int index = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            index = i;
            break;
        }
    }
    if (index == -1) return;

    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    resizeArray(arr, size, size - 1);
    size--;
}


void swapElements(int* arr, int arrSize, int& pos1, int& pos2) {

    if (pos1 < 1 || pos1 > arrSize || pos2 < 1 || pos2 > arrSize) {
        cout << "Некорректные индексы!" << endl;
        return;
    }

    if (pos1 == pos2) return; 

    int temp = arr[pos1 - 1];
    arr[pos1 - 1] = arr[pos2 - 1];
    arr[pos2 - 1] = temp;

    cout << "Элементы успешно обменяны!" << endl;
}