#include <iostream>
#include <Windows.h>
using namespace std;

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << '\n';
    system("Pause");
}

void set_cords(int x, int y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hStdout, pos);
}

void show_menu(int current, int size_items, const string items[]) {
    set_cords(0, 0);
    cout << "=============== МЕНЮ ===============\n";
    for (int i = 0; i < size_items; i++) {
        if (i == current)
            cout << " -> " << items[i] << "\n";
        else
            cout << "    " << items[i] << "\n";
    }
}
