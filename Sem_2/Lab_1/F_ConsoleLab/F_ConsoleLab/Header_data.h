#pragma once

struct Profile
{
	std::string fullName;// Фамилия Имя Отчество
	char sex;            // Пол: M/W
	int group;           // Номер группы
	int id;				 // Номер студента в списке 
	int grades[8];	     // Оценки за экзамены и диф. зачёты
	char depart[9];	     // Форма обучения
	std::string date;    // Дата внесения изменнеия в запись (post/update) 
};

