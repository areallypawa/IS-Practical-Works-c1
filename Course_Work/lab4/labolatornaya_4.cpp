#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h> 
#include <string>
#include <sstream>
#include <chrono>
#include "Header_common.h"

using namespace std;
using namespace std::chrono;

static string items[] = { "Ввести с клавиатуры строки", "Считать с файла строки", "Буквы - слова - цифры","Длина слов", "Найти подстроку (линейно)", "Найти подстроку (KMP)", "Выход" };
static int current = 0;

void show_menu(int current, int size_items, const string items[]);
void normalize_text(string& text);
void categorize_words(string& text);
void print_word_lengths(string& text);
void compute_lps(string& pattern, int lps[]);
void kmp_search(string& text, string& pattern);
void search_line(string& text, string& pattern, bool type_search);
int naive_search(string& text, string& pattern);
string normalize_spaces(string& s);
string normalize_punctuation(string& s);
string normalize_case(string& s);
string remove_punctuation(string& word);


// int lens(char *a) {
//     int l = 0;
//     while (a[l] != '\0') {
//         l++;
//     }

//     return l;
// }

// char del(char* a, int* n) {

//     a[*(n)] = '\0';

// }

// void plus(char* a, char* b) {
//     int j = 0;
//     for (int i = lens(a); ; i++) {
//         a[i] = b[j];
//         j++;
//     }
// }


int labolatornaya_4() {
    setlocale(0, "ru");
    string text, pattern;
    bool type_search = 0;
    do {
        while (true) {
            show_menu(current, size(items), items);
            int key = _getch();

            if (key == 72 && current > 0) current--;
            if (key == 80 && current < size(items) - 1) current++;
            if (key == 13) break;
        }

        switch (current) {
        case 0:
        {
            clear();
            cout << "Введите текст (заканчивается точкой):\n";
            getline(cin, text);
            normalize_text(text);
            pause();

            break;
        }
        case 1:
        {
            //system("chcp 0");
            ifstream  file("C:\\Users\\neiln\\source\\repos\\KursachLOl\\x64\\Debug\\input.txt");
            //file.imbue(locale("ru_RU.UTF-8"));
            //file.imbue(locale("Russian_Russia.1251"));
            if (!file.is_open()) {
                cout << "Ошибка: файл не найден\n";
                return 1;
            }
            clear();
            cout << "Отредактированное содержимое файла:";
            getline(file, text);
            file.close();
            normalize_text(text);
            pause();
            break;
        }
        case 2:
            categorize_words(text);
            pause();
            break;
        case 3:
            print_word_lengths(text);
            pause();
            break;
        case 4:
        {
            search_line(text, pattern, type_search);
            break;
        }
        case 5:
        {
            search_line(text, pattern, !type_search);
            break;
        }
        }
        clear();
    } while (current != size(items) - 1);


    return 0;
}

string normalize_spaces(string& s) {
    string res;
    bool space = false;

    for (char c : s) {
        if (isspace(c)) {
            if (!space) {
                res += ' ';
                space = true;
            }
        }
        else {
            res += c;
            space = false;
        }
    }

    if (!res.empty() && res.front() == ' ')
        res.erase(res.begin());

    return res;
}

string normalize_punctuation(string& s) {
    string res;
    for (int i = 0; i < s.size(); ) {
        char c = s[i];

        if (c == '.' || c == '!' || c == '?') {
            int j = i;
            while (j < s.size() && s[j] == c)
                j++;
            if (c == '.' && j - i >= 3)
                res += "...";
            else
                res += c;
            i = j;
        }
        else {
            res += s[i++];
        }
    }
    return res;
}

string normalize_case(string& s) {
    string res = s;
    for (char& c : res)
        c = tolower(c);
    return res;
}

void normalize_text(string& text) {
    // Этапы обработки
    text = normalize_spaces(text);
    text = normalize_punctuation(text);
    text = normalize_case(text);

    cout << "\nРезультат:\n";
    cout << text << endl;
}

void categorize_words(string& text) {
    clear();
    cout << "Только буквы: ";
    {
        istringstream iss(text);
        string word;
        while (iss >> word) {
            bool has_letter = false;
            bool has_digit = false;
            for (char c : word) {
                if (isalpha(c)) has_letter = true;
                if (isdigit(c)) has_digit = true;
            }
            if (has_letter && !has_digit) cout << word << " ";
        }
    }

    cout << "\nТолько цифры: ";
    {
        istringstream iss(text);
        string word;
        while (iss >> word) {
            bool has_letter = false;
            bool has_digit = false;
            for (char c : word) {
                if (isalpha(c)) has_letter = true;
                if (isdigit(c)) has_digit = true;
            }
            if (!has_letter && has_digit) cout << word << " ";
        }
    }

    cout << "\nБуквы и цифры: ";
    {
        istringstream iss(text);
        string word;
        while (iss >> word) {
            bool has_letter = false;
            bool has_digit = false;
            for (char c : word) {
                if (isalpha(c)) has_letter = true;
                if (isdigit(c)) has_digit = true;
            }
            if (has_letter && has_digit) cout << word << " ";
        }
    }

    cout << endl;
}

string remove_punctuation(string& word) {
    string clean;
    for (char c : word) {
        if (isalnum(c))
            clean += c;
    }
    return clean;
}

void print_word_lengths(string& text) {
    clear();
    istringstream iss(text);
    string word;
    while (iss >> word) {
        string clean_word = remove_punctuation(word);
        cout << clean_word << ": " << clean_word.size() << " символов" << endl;
    }
}

int naive_search(string& text, string& pattern) {
    int n = text.length(); 
    int m = pattern.length(); 

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j])
                break;
        }

        if (j == m) 
            return i; 
    }

    return -1; 
}

void compute_lps(string& pattern, int lps[]) {
    int len = 0;
    lps[0] = 0;

    for (int i = 1; i < pattern.size(); ) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmp_search(string& text, string& pattern) {

    int n = text.size();
    int m = pattern.size();

    int* lps = new int[m];
    compute_lps(pattern, lps);

    cout << "Индекс начала подстроки: ";
    bool found = false;

    int i = 0, j = 0;
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << i - j << " ";
            found = true;
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pattern[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (!found)
        cout << "такой подстроки нет";
    cout << endl;

    delete[] lps;
}

void search_line(string& text, string& pattern, bool type_search) {
    clear();
    cout << "Введите подстроку: ";
    getline(cin, pattern);

    switch (type_search) {
    case 0:
        if (naive_search(text, pattern) != -1) {
            cout << "Индекс начала подстроки: " << naive_search(text, pattern);
        }
        else {
            cout << "Такой подстроки нет!";
        }
        break;
    case 1:
        kmp_search(text, pattern);
        break;
    }

    pause();
}
