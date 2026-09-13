#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
using namespace std;

const int N = 20;

struct Training
{
    string sport;
    string coachFio;
    string day;
    string startTime;
    string endTime;
    int totalPlaces;
    int busyPlaces;
};

Training trainings[N];
int trainingCount = 0;

string menuItems[] = {
    "Тренировки тренера по фамилии",
    "Все тренировки в указанный день",
    "Тренировки со свободными местами",
    "Выход"
};

void clear() { system("cls"); }

void showMenu(int current)
{
    clear();
    cout << "=== МЕНЮ ===\n\n";
    for (int i = 0; i < 4; i++)
    {
        if (i == current) cout << " -> ";
        else cout << "    ";
        cout << menuItems[i] << "\n";
    }
}

void printByCoach()
{
    if (trainingCount == 0)
    {
        cout << "Тренировок нет!\n";
        system("pause");
        return;
    }

    string surnames[N];
    int surnameCount = 0;

    for (int i = 0; i < trainingCount; i++)
    {
        string fullName = trainings[i].coachFio;
        size_t spacePos = fullName.find(' ');
        string surname = (spacePos != string::npos) ? fullName.substr(0, spacePos) : fullName;

        bool exists = false;
        for (int j = 0; j < surnameCount; j++)
        {
            if (surnames[j] == surname) { exists = true; break; }
        }

        if (!exists && surnameCount < N) { surnames[surnameCount] = surname; surnameCount++; }
    }

    if (surnameCount == 0) { cout << "Фамилии тренеров не найдены!\n"; system("pause"); return; }

    int current = 0, key;
    while (true)
    {
        clear();
        cout << "Выберите фамилию тренера:\n\n";
        for (int i = 0; i < surnameCount; i++)
        {
            if (i == current) cout << " -> ";
            else cout << "    ";
            cout << surnames[i] << "\n";
        }
        key = _getch();
        if (key == 72 && current > 0) current--;
        if (key == 80 && current < surnameCount - 1) current++;
        if (key == 13) break;
    }

    string selectedSurname = surnames[current];
    clear();
    cout << "Тренировки тренера " << selectedSurname << ":\n\n";

    bool found = false;
    for (int i = 0; i < trainingCount; i++)
    {
        string fullName = trainings[i].coachFio;
        size_t spacePos = fullName.find(' ');
        string surname = (spacePos != string::npos) ? fullName.substr(0, spacePos) : fullName;

        if (surname == selectedSurname)
        {
            cout << trainings[i].sport << " | "
                << trainings[i].day << " | "
                << trainings[i].startTime << "-" << trainings[i].endTime << "\n";
            found = true;
        }
    }
    if (!found) cout << "Тренировки не найдены!\n";
    system("pause");
}

void printByDay()
{
    if (trainingCount == 0)
    {
        cout << "Тренировок нет!\n";
        system("pause");
        return;
    }

    string days[N];
    int dayCount = 0;

    for (int i = 0; i < trainingCount; i++)
    {
        string day = trainings[i].day;
        bool exists = false;
        for (int j = 0; j < dayCount; j++)
        {
            if (days[j] == day) { exists = true; break; }
        }
        if (!exists && dayCount < N) { days[dayCount] = day; dayCount++; }
    }

    if (dayCount == 0) { cout << "Дни тренировок не найдены!\n"; system("pause"); return; }

    int current = 0, key;
    while (true)
    {
        clear();
        cout << "Выберите день:\n\n";
        for (int i = 0; i < dayCount; i++)
        {
            if (i == current) cout << " -> ";
            else cout << "    ";
            cout << days[i] << "\n";
        }
        key = _getch();
        if (key == 72 && current > 0) current--;
        if (key == 80 && current < dayCount - 1) current++;
        if (key == 13) break;
    }

    string selectedDay = days[current];
    clear();
    cout << "Тренировки в " << selectedDay << ":\n\n";

    bool found = false;
    for (int i = 0; i < trainingCount; i++)
    {
        if (trainings[i].day == selectedDay)
        {
            cout << trainings[i].sport << " | "
                << trainings[i].coachFio << " | "
                << trainings[i].startTime << "-" << trainings[i].endTime << "\n";
            found = true;
        }
    }
    if (!found) cout << "Тренировки не найдены!\n";
    system("pause");
}

void printWithFreePlaces()
{
    bool found = false;
    for (int i = 0; i < trainingCount; i++)
    {
        if (trainings[i].busyPlaces < trainings[i].totalPlaces)
        {
            cout << trainings[i].sport << " | "
                << trainings[i].coachFio << " | "
                << "Свободно мест: "
                << trainings[i].totalPlaces - trainings[i].busyPlaces << "\n";
            found = true;
        }
    }
    if (!found) cout << "Свободных мест нет!\n";
    system("pause");
}

void loadFromFile(const string& fileName)
{
    ifstream file(fileName);
    if (!file.is_open()) { cout << "Файл не найден!\n"; system("pause"); return; }

    trainingCount = 0;
    string line;
    while (getline(file, line) && trainingCount < N)
    {
        if (line.find("Тренировка ") == 0)
        {
            Training& t = trainings[trainingCount];
            t.sport = line.substr(11);

            if (!getline(file, line)) break;
            size_t pos = line.find(':');
            t.coachFio = (pos != string::npos) ? line.substr(pos + 2) : "";

            if (!getline(file, line)) break;
            pos = line.find(':');
            t.day = (pos != string::npos) ? line.substr(pos + 2) : "";

            if (!getline(file, line)) break;
            pos = line.find(':');
            t.startTime = (pos != string::npos) ? line.substr(pos + 2) : "";

            if (!getline(file, line)) break;
            pos = line.find(':');
            t.endTime = (pos != string::npos) ? line.substr(pos + 2) : "";

            if (!getline(file, line)) break;
            pos = line.find(':');
            t.totalPlaces = (pos != string::npos) ? stoi(line.substr(pos + 2)) : 0;

            if (!getline(file, line)) break;
            pos = line.find(':');
            t.busyPlaces = (pos != string::npos) ? stoi(line.substr(pos + 2)) : 0;

            trainingCount++;
        }
    }
    file.close();
}

int main()
{
    setlocale(0, "RU");
    loadFromFile("out.txt");

    int current = 0, key;

    do {
        showMenu(current);
        key = _getch();

        if (key == 72 && current > 0) current--;
        if (key == 80 && current < 3) current++;

        if (key == 13)
        {
            switch (current)
            {
            case 0: printByCoach(); break;
            case 1: printByDay(); break;
            case 2: printWithFreePlaces(); break;
            case 3: return 0;
            }
        }
    } while (true);
}