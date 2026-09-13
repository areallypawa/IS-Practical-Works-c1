#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

extern string items[];
extern string itemsChoice[];

extern string deleteBy; // value or index

extern int* arr;
static int arrSize;

#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define RESET   "\033[0m"
#define USE_FTXUI 1

extern int current;
extern int currentChoice;
extern int countItems;
extern int countItemsChoice;

struct List {
	int value;
	List* head;
	List* tail;
};

struct FuncLog {
    string category;
	string name;
	double duration_ms;
};

struct CategoryStats {
    char category[20];
    long long listTotalTime;
    long long arrayTotalTime;
    int listCount;
    int arrayCount;
};

extern FuncLog* logs;
extern int logCount;

void addLog(string category, string name, double duration);

template<typename Func>
auto measureTime(string category, string name, Func f) {
    auto start = chrono::high_resolution_clock::now();
    auto result = f();
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, micro> duration = end - start;
    addLog(category, name, duration.count());

    return result;
}


void clear();
void pause();
void clearInput();
void cin_ignore();
void show_menu(int current, int size_items, const string items[], string str);
void showSplitScreen();
