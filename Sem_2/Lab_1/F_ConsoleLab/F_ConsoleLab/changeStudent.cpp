#include "Header_changeStudent.h"
#include "Header_deafult.h"
#include "Header_createArrayOfNames.h"
#include "Header_changeInfo.h"

using namespace std;

void changeStudent(string *arrStudentNames, Profile* p, Profile** p_profile) {
    clear();
    createArrayOfNames(arrStudentNames, p);
    
    int count = 0;
    for (int i = 0; i < N; i++) {  
        if (!arrStudentNames[i].empty()) count++;
    }

    while (true) {
        show_menu(current_change, count, arrStudentNames, "Выбери студента");
        int key = _getch();

        if (key == 72 && current_change > 0) current_change--;
        if (key == 80 && current_change < count - 1) current_change++;
        if (key == 13) break;
    }
    clear();

    while (true) {
        show_menu(current_change_what, getStructureItemsCount(), structure_items, arrStudentNames[current_change]);
        int key = _getch();

        if (key == 72 && current_change_what > 0) current_change_what--;
        if (key == 80 && current_change_what < getStructureItemsCount() - 1) current_change_what++;
        if (key == 13) break;
    }
    switch (current_change_what) {
    case 0:
        changeFio(p+current_change);
        break;
    case 1:
        changeSex(p + current_change);
        break;
    case 2:
        changeGroup(p + current_change);
        break;
    case 3:
        changeId(p + current_change);
        break;
    case 4:
        changeGrades(p + current_change, p_profile);
        break;
    case 5:
        changeDepart(p + current_change);
        break;
    case 6:
        changeDate(p + current_change);
        break;
    case 7:
        int total = *p_profile - p;   // сколько реально студентов

        // Сдвиг элементов влево
        for (int i = current_change; i < total - 1; i++) {
            p[i] = p[i + 1];
        }

        // Очистка последнего элемента (не обязательно, но аккуратно)
        p[total - 1] = Profile();

        // Сдвигаем указатель свободной позиции назад
        (*p_profile)--;
        
        

        cout << GREEN << "Студент удалён!" << RESET;
        pause();
        break;
    }
    writeFile(fileName, p, 0);
    clear();
}