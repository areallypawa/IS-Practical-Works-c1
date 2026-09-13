#include "Header_deafult.h"

int current = 0;
int currentChoice = 0;

string deleteBy = "value"; // value or index

int* arr = nullptr;
int ArrSize = 0;

int logCount = 0;
FuncLog* logs = nullptr;

string items[] =
{
    "Работа с двусвязным списком", 
    "Работа с динамическим массивом", 
    "Вывести скорость создания", 
    "Очистить логи",
    "Выход"
};

int countItems = 5;
int countItemsChoice = 8;

string itemsChoice[] =
{
    "Рандомное заполнение",
    "Ручное заполнение",
    "Вывести",
    "Вставить элемент", // *
    "Удалить элемент",  // *
    "Поменять элементы местами",
    "Получить элемент", // index or value *
    "Выход"
};


void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void clearInput() {
    cin.clear(); // сброс ошибок
    cin.ignore(10000000, '\n'); // очистка буфера
}


void cin_ignore() {
    cin.ignore(100000, '\n');
}


void pause() {
    cout << '\n';
    system("Pause");
}


void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}


void set_cords(int x, int y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hStdout, pos);
}


void show_menu(int current, int size_items, const string items[], const string str) {
    hideCursor();
    set_cords(0, 0);
    cout << "=============== " << str << " ===============\n";
    for (int i = 0; i < size_items; i++) {
        if (i == current)
            cout << " -> " << items[i] << "\n";
        else
            cout << "    " << items[i] << "\n";
    }
}


void addLog(string category, string name, double duration) {
    FuncLog* newLogs = new FuncLog[logCount + 1];

    for (int i = 0; i < logCount; i++) {
        newLogs[i] = logs[i];
    }

    newLogs[logCount].name = name;
    newLogs[logCount].duration_ms = duration;
    newLogs[logCount].category = category;
    delete[] logs;
    logs = newLogs;
    logCount++;
}


void drawWindow(int x, int y, int width, int height, const char* title) {
    set_cords(x, y);
    cout << "+";
    for (int i = 0; i < width - 2; i++) cout << "-";
    cout << "+";

    if (title != nullptr) {
        set_cords(x + 2, y);
        cout << title;
    }

    for (int i = 1; i < height - 1; i++) {
        set_cords(x, y + i);
        cout << "|";
        set_cords(x + width - 1, y + i);
        cout << "|";
    }

    set_cords(x, y + height - 1);
    cout << "+";
    for (int i = 0; i < width - 2; i++) cout << "-";
    cout << "+";
}



void getCategoryStats(CategoryStats stats[], int& statsCount) {
    const int MAX_CATEGORIES = 50;
    statsCount = 0;

    char categories[MAX_CATEGORIES][20];
    long long listSum[MAX_CATEGORIES] = { 0 };
    long long arraySum[MAX_CATEGORIES] = { 0 };
    int listCnt[MAX_CATEGORIES] = { 0 };
    int arrayCnt[MAX_CATEGORIES] = { 0 };

   
    for (int i = 0; i < logCount; i++) {
        
        int foundIndex = -1;
        for (int j = 0; j < statsCount; j++) {
            if (strcmp(categories[j], logs[i].category.c_str()) == 0) {
                foundIndex = j;
                break;
            }
        }

        
        if (foundIndex == -1) {
            strcpy(categories[statsCount], logs[i].category.c_str());
            foundIndex = statsCount;
            statsCount++;
        }

        bool isList = (logs[i].name.find("List") != string::npos);
        bool isArray = (logs[i].name.find("Array") != string::npos);

        if (isList) {
            listSum[foundIndex] += logs[i].duration_ms;
            listCnt[foundIndex]++;
        }
        if (isArray) {
            arraySum[foundIndex] += logs[i].duration_ms;
            arrayCnt[foundIndex]++;
        }
    }


    for (int i = 0; i < statsCount; i++) {
        strcpy(stats[i].category, categories[i]);

        if (listCnt[i] > 0)
            stats[i].listTotalTime = listSum[i] / listCnt[i]; // среднее время
        else
            stats[i].listTotalTime = 0;

        if (arrayCnt[i] > 0)
            stats[i].arrayTotalTime = arraySum[i] / arrayCnt[i]; // среднее время
        else
            stats[i].arrayTotalTime = 0;

        stats[i].listCount = listCnt[i];
        stats[i].arrayCount = arrayCnt[i];
    }
}


void displayStatsTable(int startX, int startY, int width, int height) {
    const int MAX_STATS = 50;
    CategoryStats stats[MAX_STATS];
    int statsCount = 0;

    getCategoryStats(stats, statsCount);

    if (statsCount == 0) {
        set_cords(startX + 2, startY + 2);
        cout << "Нет данных для отображения";
        return;
    }

    int currentY = startY + 1;
    int maxRows = height - 3;
    int rowsUsed = 0;

    set_cords(startX + 2, currentY);
    cout << "Категория";
    set_cords(startX + 25, currentY);
    cout << "List (ср. ns)";
    set_cords(startX + 45, currentY);
    cout << "Array (ср. ns)";
    currentY++;
    rowsUsed++;

    set_cords(startX + 1, currentY);
    for (int i = 0; i < width - 2; i++) cout << "-";
    currentY++;
    rowsUsed++;

    for (int i = 0; i < statsCount && rowsUsed < maxRows; i++) {
        set_cords(startX + 2, currentY);
        cout << stats[i].category;

        set_cords(startX + 25, currentY);
        if (stats[i].listCount > 0) {
            cout << stats[i].listTotalTime << " ns";
            set_cords(startX + 40, currentY);
            cout << "(" << stats[i].listCount << " опер.)";
        }
        else {
            cout << "---";
        }
 
        set_cords(startX + 45, currentY);
        if (stats[i].arrayCount > 0) {
            cout << stats[i].arrayTotalTime << " ns";
            set_cords(startX + 60, currentY);
            cout << "(" << stats[i].arrayCount << " опер.)";
        }
        else {
            cout << "---";
        }

        currentY++;
        rowsUsed++;
    }
}


void displayDetailedLogs(int startX, int startY, int width, int height) {
    if (logCount == 0) {
        set_cords(startX + 2, startY + 2);
        cout << "Нет данных о времени выполнения";
        return;
    }

    int currentY = startY + 1;
    int maxRows = height - 3;
    int rowsUsed = 0;

    // Заголовки
    set_cords(startX + 2, currentY);
    cout << "Операция";
    set_cords(startX + 25, currentY);
    cout << "Категория";
    set_cords(startX + 45, currentY);
    cout << "Время (ns)";
    currentY++;
    rowsUsed++;

    set_cords(startX + 1, currentY);
    for (int i = 0; i < width - 2; i++) cout << "-";
    currentY++;
    rowsUsed++;

    for (int i = 0; i < logCount && rowsUsed < maxRows; i++) {
        set_cords(startX + 2, currentY);
        string name = logs[i].name;
        if (name.length() > 20) name = name.substr(0, 17) + "...";
        cout << name;

        set_cords(startX + 25, currentY);
        cout << logs[i].category;

        set_cords(startX + 45, currentY);
        cout << logs[i].duration_ms;

        currentY++;
        rowsUsed++;
    }
}


void showSplitScreen() {
    system("cls");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int leftWidth = screenWidth / 2;
    int rightWidth = screenWidth - leftWidth - 1;
    int windowHeight = screenHeight - 2;

    drawWindow(0, 0, leftWidth, windowHeight, " СРАВНЕНИЕ LIST vs ARRAY ");

    if (logCount == 0) {
        set_cords(2, 2);
        cout << "Нет данных. Выполните операции.";
    }
    else {
        struct OpStat {
            char operation[30];
            double listTime;
            double arrayTime;
            int listCount;
            int arrayCount;
        };

        OpStat stats[50];
        int statCount = 0;

        for (int i = 0; i < logCount; i++) {
            string opName = logs[i].name;  // "Create Auto", "Read" и т.д.

            int found = -1;
            for (int j = 0; j < statCount; j++) {
                if (strcmp(stats[j].operation, opName.c_str()) == 0) {
                    found = j;
                    break;
                }
            }

            if (found == -1) {
                strcpy(stats[statCount].operation, opName.c_str());
                stats[statCount].listTime = 0;
                stats[statCount].arrayTime = 0;
                stats[statCount].listCount = 0;
                stats[statCount].arrayCount = 0;
                found = statCount;
                statCount++;
            }


            if (strcmp(logs[i].category.c_str(), "List") == 0) {
                stats[found].listTime += logs[i].duration_ms;
                stats[found].listCount++;
            }
            else if (strcmp(logs[i].category.c_str(), "Dinamic Array") == 0) {
                stats[found].arrayTime += logs[i].duration_ms;
                stats[found].arrayCount++;
            }
        }

        int currentY = 1;


        set_cords(2, currentY++);
        cout << "+----------------------+-------------------+-------------------+";
        set_cords(2, currentY++);
        cout << "| Операция             | List (ср. ns)     | Array (ср. ns)    |";
        set_cords(2, currentY++);
        cout << "+----------------------+-------------------+-------------------+";

        // Вывод данных
        for (int i = 0; i < statCount && currentY < windowHeight - 2; i++) {
            set_cords(2, currentY);
            printf("| %-20s | ", stats[i].operation);

            // List
            if (stats[i].listCount > 0) {
                double avgList = stats[i].listTime / stats[i].listCount;
                printf("%-17.1f | ", avgList);
            }
            else {
                printf("%-17s | ", "---");
            }

            // Array
            if (stats[i].arrayCount > 0) {
                double avgArray = stats[i].arrayTime / stats[i].arrayCount;
                printf("%-17.1f", avgArray);
            }
            else {
                printf("%-17s", "---");
            }
            cout << " |";
            currentY++;
        }

        set_cords(2, currentY);
        cout << "+----------------------+-------------------+-------------------+";
    }

    // ========== ПРАВАЯ ЧАСТЬ - Детальные логи ==========
    drawWindow(leftWidth + 1, 0, rightWidth, windowHeight, " ДЕТАЛЬНЫЕ ЛОГИ ");

    int currentY = 1;

    set_cords(leftWidth + 3, currentY++);
    cout << "Операция                 Категория          Время (ns)";
    set_cords(leftWidth + 3, currentY++);
    for (int i = 0; i < rightWidth - 6; i++) cout << "-";

    // Вывод логов
    for (int i = 0; i < logCount && currentY < windowHeight - 1; i++) {
        set_cords(leftWidth + 3, currentY);
        printf("%-24s %-18s %.1f",
            logs[i].name.c_str(),
            logs[i].category.c_str(),
            logs[i].duration_ms);
        currentY++;
    }

    // Информация внизу
    set_cords(0, screenHeight - 1);
    cout << "Всего операций: " << logCount;

    // Подсчет статистики
    int listCount = 0, arrayCount = 0;
    double listTotal = 0, arrayTotal = 0;
    for (int i = 0; i < logCount; i++) {
        if (strcmp(logs[i].category.c_str(), "List") == 0) {
            listCount++;
            listTotal += logs[i].duration_ms;
        }
        else if (strcmp(logs[i].category.c_str(), "Dinamic Array") == 0) {
            arrayCount++;
            arrayTotal += logs[i].duration_ms;
        }
    }

    cout << " | List: " << listCount << " опер. (ср. ";
    if (listCount > 0) cout << listTotal / listCount;
    else cout << "0";
    cout << " ns) | Array: " << arrayCount << " опер. (ср. ";
    if (arrayCount > 0) cout << arrayTotal / arrayCount;
    else cout << "0";
    cout << " ns)";

    cout << " | Нажмите любую клавишу...";
}