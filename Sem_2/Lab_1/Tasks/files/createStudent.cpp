#include "Header_createStudent.h"
#include "Header_deafult.h"

using namespace std;

void createStudent(Profile *p, Profile *p_students) {
    while (true) {
        clear();

        SetConsoleCP(1251);       // Ââîä â CP1251
        SetConsoleOutputCP(1251); // Âűâîä â CP1251

        bool temp_two = 0;

        cout << "ÔČÎ:";
        if (cin.peek() == '\n') {  
            cin.ignore(); 
        }
        getline(cin, p->fullName);
    
        cout << "Ďîë:"; 
        cin >> p->sex;
        p->sex = toupper(p->sex);
        // ďđîâĺđęŕ
        while (cin.fail() || ((p->sex) != 'Ć' && (p->sex) != 'Ě')) {
            cin.clear();
            cin_ignore();
            cout << "\aÎřčáęŕ ââîäŕ ďîëŕ, ďîďđîáóé ĺůĺ đŕç\n";
            cout << "Ďîë:";
            cin >> p->sex;
            p->sex = toupper(p->sex);
        
        }
        cin_ignore();

        cout << "Íîěĺđ ăđóďďű:";
        cin >> p->group;
        // ďđîâĺđęŕ
        while (cin.fail()) {
            cin.clear();
            cin_ignore();
            cout << "\aÎřčáęŕ ââîäŕ ăđóďďű, ďîďđîáóé ĺůĺ đŕç\n";
            cout << "Íîěĺđ ăđóďďű:";
            cin >> p->group;
        }
        cin_ignore();

        cout << "Íîěĺđ â ńďčńęĺ ăđóďďű:"; 
        cin >> p->id;
        // ďđîâĺđęŕ
        while (cin.fail()) {
            cin.clear();
            cin_ignore();
            cout << "\aÎřčáęŕ ââîäŕ id, ďîďđîáóé ĺůĺ đŕç\n";
            cout << "Íîěĺđ ăđóďďű:";
            cin >> p->group;
        }
        cin_ignore();

        cout << "Îöĺíęč çŕ ďđîřĺäřóţ ńĺńńčţ:";
   
        for (int i = 0; i < count_grades; i++) {
            cin >> (p->grades)[i];
            // ďđîâĺđęŕ
            while (cin.fail() || (p->grades[i]) == 2 || ((p->grades[i]) < 2 || (p->grades[i]) > 5)) {
                cin.clear();
                cin_ignore();
                cout << "\aÎřčáęŕ ââîäŕ îöĺíęč, ďîďđîáóé ĺůĺ đŕç\n";
                cout << "Îöĺíęč: ";
                cin >> (p->grades)[i];
            }
            if ((p->grades)[i] == 2) temp_two = 1;
        }
        cin_ignore();

        cout << "Ôîđěŕ îáó÷ĺíč˙:"; 
        cin >> p->depart;

        // Data
        time_t rawtime; time(&rawtime);
        p->date = ctime(&rawtime);

        if (!temp_two) {
            char ok;
            cout << "Äŕííűĺ ââĺäĺíű âĺđíî? (Y/N)"; cin >> ok;
            if (ok == 'Y' || ok == 'y') {
                writeFile(fileName, p, 1);
                break;  // âűőîäčě čç öčęëŕ
            }
        }
        else {
            cout << "Ńňóäĺíň íĺ ěîćĺň áűňü çŕ÷čńëĺí ń äâîéęŕěč!";
            pause();
            continue;
        }

    }
    
    pause();
    clear();
}
