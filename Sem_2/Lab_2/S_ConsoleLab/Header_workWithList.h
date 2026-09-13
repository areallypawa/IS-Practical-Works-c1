#pragma once
#include <iostream>
#include <random>
#include <conio.h>
#include "Header_deafult.h"
using namespace std;

List* createListAuto(int len);
List* createListHand(int* arr, int size);
List* insertElementList(List* head, int pos, int value);
List* deleteElementByIndex(List* head, int pos);
List* deleteElementByValue(List* head, int value);
List* getElementByIndexMain(List* head, int pos);
List* getElementByIndex(List* head, int pos);
List* getElementByValueMain(List* head, int value);
List* getElementByValue(List* head, int value);
List* swapNodesByIndex(List* head, int pos1, int pos2);
void readList(List* p);
void deleteAllLists(List* NewList);
void readListWithoutPause(List* p);
void deleteList(List*& head);
