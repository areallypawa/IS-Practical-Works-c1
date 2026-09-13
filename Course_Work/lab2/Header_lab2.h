#pragma once
#include <vector>
#include <string>
using namespace std;

void show_menus(const vector<string>& menu_items, int& current_index, bool is_array);
void show_menu_array(int current, int size_items, const string items[]);
void create_auto_array(int* array);
void create_hand_array(int* array);
void create_hand_array(int* array);
void copy_array(int* array, int* array_copy);
void create_auto_array(int* array);
void create_hand_array(int* array);
void delete_array(int* array);
void read_array(int* array);
int binary_search(int* arr, int& target);
int interpolation_search(int* arr, int& target);
void quick_sort(int* arr, int  st, int en, bool& flag);
void bubble_sort(int* arr, bool& flag);
void shaker_sort(int* arr, bool& flag);
void insertion_sort(int* arr, bool& flag);
void selection_sort(int* arr, bool& flag);
void chek_array_sort(int* array, bool& array_already_sort);
void search_medium_index(int* array, int& medium);
int labolatornaya_2();








