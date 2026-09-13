#pragma once
#include <iostream>
#include <random>
#include <conio.h>
#include "Header_deafult.h"
using namespace std;

void resizeArray(int*& arr, int oldSize, int newSize);
void inputArr(int*& arr, int& size);
void createArrAuto(int*& arr, int& arrSize);
void createArrHand(int*& arr, int& size, int* source, int sourceSize);
void printArr(int* arr, int arrSize);
void printArrWithoutPause(int* arr, int size);
void insertElement(int*& arr, int& size, int& pos, int& value);
void deleteByIndex(int*& arr, int& arrSize, int& pos);
void deleteByValue(int*& arr, int& arrSize, int& value);
void swapElements(int* arr, int arrSize, int& pos1, int& pos2);
int getElementByValueArr(int* arr, int arrSize, int posOrVal);
int getElementByIndexArr(int* arr, int arrSize, int posOrVal);