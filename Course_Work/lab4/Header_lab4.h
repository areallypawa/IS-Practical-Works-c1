#pragma once
#include <string>
using namespace std;

void normalize_text(string& text);
void categorize_words(string& text);
void print_word_lengths(string& text);
void compute_lps(string& pattern, int lps[]);
void kmp_search(string& text, string& pattern);
void search_line(string& text, string& pattern, bool type_search);
int naive_search(string& text, string& pattern);
int labolatornaya_4();
string normalize_spaces(string& s);
string normalize_punctuation(string& s);
string normalize_case(string& s);
string remove_punctuation(string& word);
