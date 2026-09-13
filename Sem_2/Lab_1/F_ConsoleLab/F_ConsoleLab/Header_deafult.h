#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>

extern const int N;
extern char fileName[20];


extern std::string items[];
extern std::string structure_items[];

#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define RESET   "\033[0m"

extern int current;
extern int current_change;
extern int current_change_what;
extern int count_grades;

struct Profile
{
	std::string fullName;// Фамилия Имя Отчество
	char sex;            // Пол: M/W
	int group;           // Номер группы
	int id;				 // Номер студента в списке 
	int grades[8];	     // Оценки за экзамены и диф. зачёты
	char depart[9];	     // Форма обучения
	std::string date;          // Дата внесения изменнеия в запись (post/update) 
};

void clear();
void pause();
void cin_ignore();
int getItemsCount();
int getStructureItemsCount();
void set_cords(int x, int y);
void show_menu(int current, int size_items, const std::string items[], std::string str);
bool writeFile(char* FileName, Profile *p, int reWrite);
bool readFile(char* FileName);
int countStudents(Profile* p);
int loadFromFile(Profile* students, Profile** p_profile);