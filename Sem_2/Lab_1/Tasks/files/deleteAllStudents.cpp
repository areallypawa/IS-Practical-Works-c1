#include "Header_deleteAllStudents.h"
using namespace std;

void deleteAllStudents(Profile* students, Profile** p_profile)
{
    int n = *p_profile - students;
    if (n == 0) {
        cout << RED << "База уже пуста!" << RESET;
        pause();
        return;
    }
    for (int i = 0; i < n; i++) {
        students[i] = Profile();  
    }

    *p_profile = students;

    ofstream file(fileName, ios::trunc);
    file.close();

    cout << GREEN << "Все студенты удалены!" << RESET;
    pause();
}
