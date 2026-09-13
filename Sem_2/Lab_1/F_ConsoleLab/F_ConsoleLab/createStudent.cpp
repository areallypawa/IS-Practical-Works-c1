#include "Header_createStudent.h"
#include "Header_deafult.h"

using namespace std;

void createStudent(Profile *p, Profile *p_students) {
    while (true) {
        clear();

        SetConsoleCP(1251);       // Ввод в CP1251
        SetConsoleOutputCP(1251); // Вывод в CP1251

        bool temp_two = 0;

        cout << "ФИО:";
        if (cin.peek() == '\n') {  
            cin.ignore(); 
        }
        getline(cin, p->fullName);
    
        cout << "Пол:"; 
        cin >> p->sex;
        p->sex = toupper(p->sex);
        // проверка
        while (cin.fail() || ((p->sex) != 'Ж' && (p->sex) != 'М')) {
            cin.clear();
            cin_ignore();
            cout << "\aОшибка ввода пола, попробуй еще раз\n";
            cout << "Пол:";
            cin >> p->sex;
            p->sex = toupper(p->sex);
        
        }
        cin_ignore();

        cout << "Номер группы:";
        cin >> p->group;
        // проверка
        while (cin.fail()) {
            cin.clear();
            cin_ignore();
            cout << "\aОшибка ввода группы, попробуй еще раз\n";
            cout << "Номер группы:";
            cin >> p->group;
        }
        cin_ignore();

        cout << "Номер в списке группы:"; 
        cin >> p->id;
        // проверка
        while (cin.fail()) {
            cin.clear();
            cin_ignore();
            cout << "\aОшибка ввода id, попробуй еще раз\n";
            cout << "Номер группы:";
            cin >> p->group;
        }
        cin_ignore();

        cout << "Оценки за прошедшую сессию:";
   
        for (int i = 0; i < count_grades; i++) {
            cin >> (p->grades)[i];
            // проверка
            while (cin.fail() || (p->grades[i]) == 2 || ((p->grades[i]) < 2 || (p->grades[i]) > 5)) {
                cin.clear();
                cin_ignore();
                cout << "\aОшибка ввода оценки, попробуй еще раз\n";
                cout << "Оценки: ";
                cin >> (p->grades)[i];
            }
            if ((p->grades)[i] == 2) temp_two = 1;
        }
        cin_ignore();

        cout << "Форма обучения:"; 
        cin >> p->depart;

        // Data
        time_t rawtime; time(&rawtime);
        p->date = ctime(&rawtime);

        if (!temp_two) {
            char ok;
            cout << "Данные введены верно? (Y/N)"; cin >> ok;
            if (ok == 'Y' || ok == 'y') {
                writeFile(fileName, p, 1);
                break;  // выходим из цикла
            }
        }
        else {
            cout << "Студент не может быть зачислен с двойками!";
            pause();
            continue;
        }

    }
    
    pause();
    clear();
}