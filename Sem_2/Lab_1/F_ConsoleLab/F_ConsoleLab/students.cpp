#include <iostream>
#include <fstream>

bool writeFile(char* FileName) 
{
    std::ofstream File(FileName, std::ios::app);  // Создаем поток для записи и сразу открываем файл

    if (!File.is_open()) 
    {
        std::cout << "Открыть файл не удалось! \n";
        return 404;   
    }

    // to do
    File << "Student";

    File.close();  // Закрываем файл
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

//bool createNewStudent()
//{
//
//    return 0;
//}