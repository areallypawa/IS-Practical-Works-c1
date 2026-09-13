#include "Header_printStudent.h"
#include "Header_deafult.h"
#include "Header_printStudentInfo.h"
using namespace std;

void printStudent(Profile* p, int studentCount) {

    clear();

    if ((p->fullName) == "") {
        cout << RED << "Нет добавленных студентов!" << RESET;
        pause();
        return;
    }

    const string printItems[] = {
        "Вывести всех студентов",
        "Все студенты группы",
        "Топ студентов",
        "Студенты - мужчины",
        "Студенты - девушки", 
        "Студенты без стипендии",
        "Студенты хорошисты",
        "Студенты отличники",
        "Студент по ID",
        "Назад"
    };
    int printCount = sizeof(printItems) / sizeof(printItems[0]);
    int printCurrent = 0;

    do {
        while (true) {
            show_menu(printCurrent, printCount, printItems, "ПЕЧАТЬ");
            int key = _getch();

            if (key == 72 && printCurrent > 0) printCurrent--;
            if (key == 80 && printCurrent < printCount - 1) printCurrent++;
            if (key == 13) break;
        }

        switch (printCurrent) {
        case 0: 
            clear();
            cout << "=== ВСЕ СТУДЕНТЫ (" << studentCount << ") ===\n\n";
            if (studentCount == 0) {
                cout << RED << "Список студентов пуст!" << RESET << endl;
            }
            else {
                for (int i = 0; i < studentCount; i++) {
                    printStudentInfo(p[i], i + 1);
                }
            }
            pause();
            clear();
            break;

        case 1: // Поиск по Group
            clear();
            cout << "Введите номер группы: ";
            {
                int searchGroup;
                cin >> searchGroup;

                bool found = false;
                cout << "\n=== СТУДЕНТЫ ГРУППЫ " << searchGroup << " ===\n\n";

                for (int i = 0; i < studentCount; i++) {
                    if (p[i].group == searchGroup) {
                        printStudentInfo(p[i], i + 1);
                        found = true;
                    }
                }

                if (!found) {
                    cout << RED << "Студенты группы " << searchGroup << " не найдены!" << RESET << endl;
                }
            }
            pause();
            clear();
            break;
        case 2: // Топ студентов
            clear();
            cout << "=== ТОП СТУДЕНТОВ (по среднему баллу) ===\n\n";
            if (studentCount == 0) {
                cout << RED << "Нет студентов для рейтинга!" << RESET << endl;
            }
            else {
                struct StudentRating {
                    string fullName;
                    int group;
                    int id;
                    double average;
                };

                StudentRating ratings[100];

                // Вычисляем средние баллы
                for (int i = 0; i < studentCount; i++) {
                    double sum = 0;
                    int count = 0;
                    for (int j = 0; j < 8; j++) {
                        if (p[i].grades[j] > 0) {
                            sum += p[i].grades[j];
                            count++;
                        }
                    }
                    ratings[i].average = (count > 0) ? sum / count : 0;
                    ratings[i].fullName = p[i].fullName;
                    ratings[i].group = p[i].group;
                    ratings[i].id = p[i].id;
                }

                // Сортировка
                for (int i = 0; i < studentCount - 1; i++) {
                    for (int j = 0; j < studentCount - i - 1; j++) {
                        if (ratings[j].average < ratings[j + 1].average) {
                            StudentRating temp = ratings[j];
                            ratings[j] = ratings[j + 1];
                            ratings[j + 1] = temp;
                        }
                    }
                }

                // Вывод
                for (int i = 0; i < studentCount; i++) {
                    if (ratings[i].average > 0) {
                        cout << "Место #" << i + 1 << ":\n";
                        cout << "  ФИО: " << ratings[i].fullName << endl;
                        cout << "  Группа: " << ratings[i].group << endl;
                        cout << "  ID: " << ratings[i].id << endl;
                        cout << "  Средний балл: " << ratings[i].average << endl;

                        if (ratings[i].average >= 4.5) {
                            cout << "  Статус: " << GREEN << "Отличник" << RESET << endl;
                        }
                        else if (ratings[i].average >= 3.5) {
                            cout << "  Статус: " << YELLOW << "Хорошист" << RESET << endl;
                        }
                        cout << "------------------------\n";
                    }
                }
            }
            pause();
            clear();
            break;
        case 3: // Студенты мужчины
            clear();
            cout << "=== СТУДЕНТЫ - МУЖЧИНЫ ===\n\n";
            {
                bool found = false;
                for (int i = 0; i < studentCount; i++) {
                    if (p[i].sex == 'М') {
                        printStudentInfo(p[i], i + 1);
                        found = true;
                    }
                }
                if (!found) {
                    cout << RED << "Студенты-мужчины не найдены!" << RESET << endl;
                }
            }
            pause();
            clear();
            break;
        case 4: // Студенты девушки
            clear();
            cout << "=== СТУДЕНТЫ - ДЕВУШКИ ===\n\n";
            {
                bool found = false;
                for (int i = 0; i < studentCount; i++) {
                    if (p[i].sex == 'Ж') {
                        printStudentInfo(p[i], i + 1);
                        found = true;
                    }
                }
                if (!found) {
                    cout << RED << "Студенты-девушки не найдены!" << RESET << endl;
                }
            }
            pause();
            clear();
            break;
        case 5: // Студенты без стипендии
            clear();
            cout << "=== СТУДЕНТЫ БЕЗ СТИПЕНДИИ ===\n\n";
            {
                bool found = false;
                for (int i = 0; i < studentCount; i++) {
                    bool hasScholarship = true;
                    for (int j = 0; j < 8; j++) {
                        if (p[i].grades[j] > 0 && p[i].grades[j] < 4) {
                            hasScholarship = false;
                            break;
                        }
                    }

                    if (!hasScholarship) {
                        printStudentInfo(p[i], i + 1);
                        found = true;
                    }
                }
                if (!found) {
                    cout << GREEN << "Все студенты получают стипендию!" << RESET << endl;
                }
            }
            pause();
            clear();
            break;
        case 6: // Студенты хорошисты
            clear();
            cout << "=== СТУДЕНТЫ - ХОРОШИСТЫ ===\n\n";
            {
                bool found = false;
                for (int i = 0; i < studentCount; i++) {
                    double sum = 0;
                    int count = 0;
                    for (int j = 0; j < 8; j++) {
                        if (p[i].grades[j] > 0) {
                            sum += p[i].grades[j];
                            count++;
                        }
                    }
                    double average = (count > 0) ? sum / count : 0;

                    if (average >= 3.5 && average < 4.5) {
                        printStudentInfo(p[i], i + 1);
                        found = true;
                    }
                }
                if (!found) {
                    cout << RED << "Хорошисты не найдены!" << RESET << endl;
                }
            }
            pause();
            clear();
            break;
        case 7: // Студенты отличники
            clear();
            cout << "=== СТУДЕНТЫ - ОТЛИЧНИКИ ===\n\n";
            {
                bool found = false;
                for (int i = 0; i < studentCount; i++) {
                    double sum = 0;
                    int count = 0;
                    for (int j = 0; j < 8; j++) {
                        if (p[i].grades[j] > 0) {
                            sum += p[i].grades[j];
                            count++;
                        }
                    }
                    double average = (count > 0) ? sum / count : 0;

                    if (average >= 4.5) {
                        printStudentInfo(p[i], i + 1);
                        found = true;
                    }
                }
                if (!found) {
                    cout << RED << "Отличники не найдены!" << RESET << endl;
                }
            }
            pause();
            clear();
            break;
        case 8: // Студенты по id
            clear();
            cout << "Введите ID студента: ";
            {
                int searchId;
                cin >> searchId;

                bool found = false;
                for (int i = 0; i < studentCount; i++) {
                    if (p[i].id == searchId) {
                        cout << "\n=== СТУДЕНТ С ID " << searchId << " ===\n\n";
                        printStudentInfo(p[i], i + 1);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << RED << "Студент с ID " << searchId << " не найден!" << RESET << endl;
                }
            }
            pause();
            clear();
            break;
        }

    } while (printCurrent != printCount - 1);
}