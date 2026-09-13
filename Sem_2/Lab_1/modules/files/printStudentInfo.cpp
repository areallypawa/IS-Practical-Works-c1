#include "Header_printStudentInfo.h"
#include "Header_deafult.h"


void printStudentInfo(const Profile& student, int number) {
    std::cout << "Студент #" << number << " (ID: " << student.id << "):\n";
    std::cout << "  ФИО: " << student.fullName << std::endl;
    std::cout << "  Пол: " << (student.sex == 'М' ? "Мужской" : "Женский") << std::endl;
    std::cout << "  Группа: " << student.group << std::endl;
    std::cout << "  Форма обучения: " << student.depart << std::endl;
    std::cout << "  Оценки: ";
    for (int i = 0; i < count_grades; i++) {
        if (student.grades[i] > 0) {
            if (student.grades[i] >= 4) {
                std::cout << GREEN << student.grades[i] << " " << RESET;
            }
            else if (student.grades[i] == 3) {
                std::cout << YELLOW << student.grades[i] << " " << RESET;
            }
            else {
                std::cout << RED << student.grades[i] << " " << RESET;
            }
        }
        else {
            std::cout << "- ";
        }
    }
    std::cout << std::endl;

    // Вычисление среднего балла
    double sum = 0;
    int count = 0;
    for (int i = 0; i < count_grades; i++) {
        sum += student.grades[i];
        count++;
    }
    double average = (count > 0) ? sum / count : 0;
    std::cout << "  Средний балл: " << average << std::endl;

    // Определение успеваемости
    if (average >= 4.5) {
        std::cout << "  Статус: " << GREEN << "Отличник" << RESET << std::endl;
    }
    else if (average >= 3.5) {
        std::cout << "  Статус: " << YELLOW << "Хорошист" << RESET << std::endl;
    }
    else if (average > 0) {
        std::cout << "  Статус: " << RED << "Троечник" << RESET << std::endl;
    }

    // Есть ли стипендия?
    bool hasScholarship = true;
    for (int i = 0; i < 8; i++) {
        if (student.grades[i] > 0 && student.grades[i] < 4) {
            hasScholarship = false;
            break;
        }
    }
    std::cout << "  Стипендия: " << (hasScholarship && average >= 4.0 ? GREEN "Да" : RED "Нет") << RESET << std::endl;

    // Дата изменения
    if (student.date != "") {
        std::cout << "  Дата изменения: " << student.date << std::endl;
    }

    std::cout << "------------------------\n";
}
