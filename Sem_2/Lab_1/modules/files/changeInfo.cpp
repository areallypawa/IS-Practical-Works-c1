#include "Header_changeInfo.h"
#include "Header_deafult.h"

/*
    ÇÄÅÑÜ ÔÓÍÊÖÈÈ ÄËß ÐÅÄÀÊÒÈÐÎÂÀÍÈß ÈÍÔÎÐÌÀÖÈÈ Î ÑÒÓÄÅÍÒÅ + ÎÒ×ÈÑËÅÍÈÅ
*/

void changeFio(Profile* p) {
    std::cout << "Òåêóùåå ÔÈÎ: " << p->fullName << std::endl;
    std::cout << "Ââåäèòå íîâîå ÔÈÎ: ";
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::getline(std::cin, p->fullName);
    std::cout << "ÔÈÎ èçìåíåíî!" << std::endl;
    pause();
}


void changeSex(Profile* p) {

    SetConsoleCP(1251);       // Ââîä â CP1251
    SetConsoleOutputCP(1251); // Âûâîä â CP1251

    std::cout << "Òåêóùèé ïîë: " << p->sex << '\n';
    std::cout << "Ââåäèòå íîâûé ïîë (Ì/Æ): ";

    std::cin >> p->sex;
    p->sex = std::toupper(p->sex);

    while (std::cin.fail() || (p->sex != 'Æ' && p->sex != 'Ì')) {
        std::cin.clear();
        cin_ignore();
        std::cout << "\aÎøèáêà ââîäà ïîëà! Ââåäèòå Ì èëè Æ: ";
        std::cin >> p->sex;
        p->sex = std::toupper(p->sex);
    }
    cin_ignore();
    std::cout << "Ïîë èçìåíåí íà " << p->sex << '\n';
    pause();
}

void changeGroup(Profile* p) {
    std::cout << "Òåêóùàÿ ãðóïïà: " << p->group << '\n';
    std::cout << "Ââåäèòå íîâûé íîìåð ãðóïïû: ";

    std::cin >> p->group;
    while (std::cin.fail()) {
        std::cin.clear();
        cin_ignore();
        std::cout << "\aÎøèáêà! Ââåäèòå ÷èñëî: ";
        std::cin >> p->group;
    }
    cin_ignore();
    std::cout << "Ãðóïïà èçìåíåíà íà " << p->group << '\n';
    pause();
}


void changeId(Profile* p) {
    std::cout << "Òåêóùèé íîìåð â ñïèñêå: " << p->id << "\n";
    std::cout << "Ââåäèòå íîâûé íîìåð â ñïèñêå: ";

    std::cin >> p->id;
    while (std::cin.fail()) {
        std::cin.clear();
        cin_ignore();
        std::cout << "\aÎøèáêà! Ââåäèòå ÷èñëî: ";
        std::cin >> p->id;
    }
    cin_ignore();
    std::cout << "Íîìåð èçìåíåí íà " << p->id << "\n";
    pause();
}


bool changeGrades(Profile* p, Profile** p_profile) {
    std::cout << "Òåêóùèå îöåíêè: " << p->grades[0] << " " << p->grades[1] << "\n";
    std::cout << "Ââåäèòå íîâûå îöåíêè çà ñåññèþ (" << count_grades << " îöåíêè):\n";

    for (int i = 0; i < count_grades; i++) {
        std::cin >> p->grades[i];

        while (std::cin.fail() || (p->grades[i] < 2 || p->grades[i] > 5)) {
            std::cin.clear();
            cin_ignore();
            std::cout << "\aÎøèáêà! Îöåíêà äîëæíà áûòü îò 2 äî 5: ";
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
        std::cout << "Âñå îòëè÷íî, äàííûå èçìåíåíû!\n";
    }
    else {
        bool chislanut;
        std::cout << "Ñòóäåíò íå ìîæåò áûòü çà÷èñëåí ñ äâîéêàìè! Îò÷èñëèòü ñòóäåíòà?(Yes - 1/No - 0): ";
        std::cin >> chislanut;
        if (chislanut) {
            int total = *p_profile - p;   // ñêîëüêî ðåàëüíî ñòóäåíòîâ

            // Ñäâèã ýëåìåíòîâ âëåâî
            for (int i = current_change; i < total - 1; i++) {
                p[i] = p[i + 1];
            }

            // Î÷èñòêà ïîñëåäíåãî ýëåìåíòà (íå îáÿçàòåëüíî, íî àêêóðàòíî)
            p[total - 1] = Profile();

            // Ñäâèãàåì óêàçàòåëü ñâîáîäíîé ïîçèöèè íàçàä
            (*p_profile)--;

            std::cout << GREEN << "Ñòóäåíò óäàë¸í!" << RESET;
            pause();
        }
        else {
            std::cout << "\nÕîðîøî\n";
            changeGrades(p, p_profile);
        }
        return 1;
    }
    pause();
    return 0;
}


void changeDepart(Profile* p) {
    std::cout << "Òåêóùàÿ ôîðìà îáó÷åíèÿ: " << p->depart << "\n";
    std::cout << "Ââåäèòå íîâóþ ôîðìó îáó÷åíèÿ: ";

    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::cin >> p->depart;
    std::cout << "Ôîðìà îáó÷åíèÿ èçìåíåíà íà " << p->depart << "\n";
    pause();
}


void changeDate(Profile* p) {
    std::cout << "Òåêóùàÿ äàòà èçìåíåíèÿ: " << p->date;

    // Data
    time_t rawtime; time(&rawtime);
    p->date = ctime(&rawtime);

    std::cout << "Äàòà îáíîâëåíà íà " << p->date;
    pause();
}



