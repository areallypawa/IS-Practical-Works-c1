#include "Header_deafult.h"

char fileName[20] = "out.txt";
char fileNameIn[20] = "input.txt";

int current = 0;
int current_change = 0;
int current_change_what = 0;

int count_grades = 2;

std::string items[] =
{
    "Добавить студента", "Добавить студентов с файла" ,"Внести правки в данные студента",
    "Все студенты университета", "Числануть всех", "Выход"
};

std::string structure_items[] =
{
    "ФИО",
    "Пол (М/Ж)",
    "Группа",
    "Id",
    "Оценки",
    "Форма обучения",
    "Дата изменения",
    "Числануть по приколу"
};


void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void cin_ignore() {
    std::cin.ignore(100000, '\n');
}

void pause() {
    std::cout << '\n';
    system("Pause");
}


int getItemsCount() { return sizeof(items) / sizeof(items[0]); }
int getStructureItemsCount() { return sizeof(structure_items) / sizeof(structure_items[0]); }


void set_cords(int x, int y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hStdout, pos);
}


void show_menu(int current, int size_items, const std::string items[], const std::string str) {
    set_cords(0, 0);
    std::cout << "=============== " << str << " ===============\n";
    for (int i = 0; i < size_items; i++) {
        if (i == current)
            std::cout << " -> " << items[i] << "\n";
        else
            std::cout << "    " << items[i] << "\n";
    }
}


bool writeFile(char* FileName, Profile *p, int reWrite)
{
    if (reWrite == -1) {
        std::ofstream File(FileName);
        File << "";
        File.close();
        return 0;
    }

    std::ofstream File(FileName, (reWrite) ? (std::ios::app) : (0));  // Создаем поток для записи и сразу открываем файл
    
    if (!File.is_open())
    {
        std::cout << "Открыть файл не удалось! \n";
        return 404;
    }
    

    // to do
    for (int i = 0; i < N; i++) {
        if ((p->fullName) != "") {
            File << "Студент " << p->fullName << "\nГруппа: " <<
                p->group << "\nId: " << p->id << "\nПол: " << p->sex << "\nОценки: ";
            for (int i = 0; i < count_grades; i++) {
                File << (p->grades)[i] << ' ';
            }
            File << "\nФорма обучения: " << p->depart <<
                "\nДата последнего изменения: " << p->date << '\n' << '\n';
        }
        p += 1;
    }
    
    File.close();  // Закрываем файл
    std::cout << "Данные внесены!";
    return 0;
}


bool readFile(char* FileName)
{
    std::ifstream File(FileName);   // Создали поток ввода для чтения данных из файла

    if (!File.is_open())
    {
        std::cout << "Открыть файл не удалось! \n";
        return 404;
    }

    char S[100];
    while (!File.eof()) // Читаем все строки из файла и выводим их на экран
    {
        File.getline(S, 100);
        std::cout << S << std::endl;
    }

    File.close();  // Закрываем файл
    return 0;
}


int loadFromFile(Profile* students, Profile** p_profile)
{
    std::ifstream File(fileNameIn);

    if (!File.is_open()) {
        std::cout << "Файл не найден!\n";
        return 404;
    }

    *p_profile = students;  // начинаем с начала массива
    std::string line;
    int loadedCount = 0;

    while (getline(File, line))
    {
        if (line.find("Студент ") == 0)
        {
            if (loadedCount >= N)
                break;

            Profile* p = *p_profile;

            // ФИО
            p->fullName = line.substr(8);

            // Группа
            getline(File, line);
            p->group = stoi(line.substr(8));

            // Id
            getline(File, line);
            p->id = stoi(line.substr(4));

            // Пол
            getline(File, line);
            p->sex = line.substr(5)[0];

            // Оценки
            getline(File, line);
            std::string gradesLine = line.substr(8);
            std::stringstream ss(gradesLine);

            for (int i = 0; i < count_grades; i++) {
                ss >> p->grades[i];
            }
            // Форма обучения
            getline(File, line);
            std::string dep = line.substr(16);
            strcpy(p->depart, dep.c_str());

            getline(File, line);
            p->date = line.substr(27);

            (*p_profile)++;

            if ((*p_profile - students) >= N)
                break;
        }
    }
    clear();
    std::cout << GREEN << "Студенты добавлены!" << RESET;
    pause();
    File.close();
    writeFile(fileName, students, 1);
    return loadedCount;
}

int countStudents(Profile*p) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (p[i].fullName != "" && p[i].depart != "") {
            count++;
        }
    }
    return count;
}
