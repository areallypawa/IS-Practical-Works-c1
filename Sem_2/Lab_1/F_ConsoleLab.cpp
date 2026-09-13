#include <iostream>
#include <string>
#include <conio.h> 
#include <chrono>
#include "Header_deafult.h"
#include "Header_createStudent.h"
#include "Header_changeStudent.h"
#include "Header_printStudent.h"
#include "Header_deleteAllStudents.h"
using namespace std;

const int N = 10;

int main()
{   
    setlocale(LC_ALL, "RU");
    
    Profile students[N];
    string arrStudentNames[N];
    Profile* p_profile = students;

    writeFile(fileName, students, -1);
    
    do {
        while (true) {
            show_menu(current, getItemsCount(), items, "МЕНЮ");
            int key = _getch();

            if (key == 72 && current > 0) current--;
            if (key == 80 && current < getItemsCount() - 1) current++;
            if (key == 13) break;
        }

        switch (current) {
        case 0:
            if (p_profile < &students[N]) {
                createStudent(p_profile, students);
                p_profile += 1;
            }
            else {
                cout << RED << "База переполнена! MAX - "  << N << RESET;
                pause();
            }
            break;
        case 1:
            
            p_profile += loadFromFile(students, &p_profile);
            break;
        case 2:
            if (countStudents(students)) {
                changeStudent(arrStudentNames, students, &p_profile);
            }
            else
            {
                clear();
                cout << RED << "Нет добавленных студентов!" << RESET;
                pause();
            }
            break;
        case 3:
            printStudent(students, countStudents(students));
            break;
        case 4:
            if (countStudents(students)) {
                deleteAllStudents(students, &p_profile);
            }
            else
            {
                clear();
                cout << RED << "Некого отчислять то!" << RESET;
                pause();
            }
            
            break;
        }
        clear();
    } while (current != getItemsCount() - 1);

    return 0;
    
}

