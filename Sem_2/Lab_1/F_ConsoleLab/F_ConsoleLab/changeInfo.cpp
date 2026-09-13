#include "Header_changeInfo.h"
#include "Header_deafult.h"

/*
    ЗДЕСЬ ФУНКЦИИ ДЛЯ РЕДАКТИРОВАНИЯ ИНФОРМАЦИИ О СТУДЕНТЕ + ОТЧИСЛЕНИЕ
*/

void changeFio(Profile* p) {
    std::cout << "Текущее ФИО: " << p->fullName << std::endl;
    std::cout << "Введите новое ФИО: ";
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::getline(std::cin, p->fullName);
    std::cout << "ФИО изменено!" << std::endl;
    pause();
}


void changeSex(Profile* p) {

    SetConsoleCP(1251);       // Ввод в CP1251
    SetConsoleOutputCP(1251); // Вывод в CP1251

    std::cout << "Текущий пол: " << p->sex << '\n';
    std::cout << "Введите новый пол (М/Ж): ";

    std::cin >> p->sex;
    p->sex = std::toupper(p->sex);

    while (std::cin.fail() || (p->sex != 'Ж' && p->sex != 'М')) {
        std::cin.clear();
        cin_ignore();
        std::cout << "\aОшибка ввода пола! Введите М или Ж: ";
        std::cin >> p->sex;
        p->sex = std::toupper(p->sex);
    }
    cin_ignore();
    std::cout << "Пол изменен на " << p->sex << '\n';
    pause();
}

void changeGroup(Profile* p) {
    std::cout << "Текущая группа: " << p->group << '\n';
    std::cout << "Введите новый номер группы: ";

    std::cin >> p->group;
    while (std::cin.fail()) {
        std::cin.clear();
        cin_ignore();
        std::cout << "\aОшибка! Введите число: ";
        std::cin >> p->group;
    }
    cin_ignore();
    std::cout << "Группа изменена на " << p->group << '\n';
    pause();
}


void changeId(Profile* p) {
    std::cout << "Текущий номер в списке: " << p->id << "\n";
    std::cout << "Введите новый номер в списке: ";

    std::cin >> p->id;
    while (std::cin.fail()) {
        std::cin.clear();
        cin_ignore();
        std::cout << "\aОшибка! Введите число: ";
        std::cin >> p->id;
    }
    cin_ignore();
    std::cout << "Номер изменен на " << p->id << "\n";
    pause();
}


bool changeGrades(Profile* p, Profile** p_profile) {
    std::cout << "Текущие оценки: " << p->grades[0] << " " << p->grades[1] << "\n";
    std::cout << "Введите новые оценки за сессию (" << count_grades << " оценки):\n";

    for (int i = 0; i < count_grades; i++) {
        std::cin >> p->grades[i];

        while (std::cin.fail() || (p->grades[i] < 2 || p->grades[i] > 5)) {
            std::cin.clear();
            cin_ignore();
            std::cout << "\aОшибка! Оценка должна быть от 2 до 5: ";
            std::cin >> p->grades[i];
        }
    }
    cin_ignore();

    bool temp_two = 0;
    for (int i = 0; i < 2; i++) {
        if (p->grades[i] == 2) {
            temp_two = 1;
        }
    }
    if (!temp_two) {
        std::cout << "Все отлично, данные изменены!\n";
    }
    else {
        bool chislanut;
        std::cout << "Студент не может быть зачислен с двойками! Отчислить студента?(Yes - 1/No - 0): ";
        std::cin >> chislanut;
        if (chislanut) {
            int total = *p_profile - p;   // сколько реально студентов

            // Сдвиг элементов влево
            for (int i = current_change; i < total - 1; i++) {
                p[i] = p[i + 1];
            }

            // Очистка последнего элемента (не обязательно, но аккуратно)
            p[total - 1] = Profile();

            // Сдвигаем указатель свободной позиции назад
            (*p_profile)--;

            std::cout << GREEN << "Студент удалён!" << RESET;
            pause();
        }
        else {
            std::cout << "\nХорошо\n";
            changeGrades(p, p_profile);
        }
        return 1;
    }
    pause();
    return 0;
}


void changeDepart(Profile* p) {
    std::cout << "Текущая форма обучения: " << p->depart << "\n";
    std::cout << "Введите новую форму обучения: ";

    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::cin >> p->depart;
    std::cout << "Форма обучения изменена на " << p->depart << "\n";
    pause();
}


void changeDate(Profile* p) {
    std::cout << "Текущая дата изменения: " << p->date;

    // Data
    time_t rawtime; time(&rawtime);
    p->date = ctime(&rawtime);

    std::cout << "Дата обновлена на " << p->date;
    pause();
}


