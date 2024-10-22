#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <string>

using namespace std;

vector<string> parseTextFile(const string& filename)
{
    vector<string> lines;
    ifstream file(filename);

    // Проверяем, открывается ли файл
    if (!file.is_open())
    {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return lines;
    }

    string line;
    while (getline(file, line))
    {        
            // Удаляем знаки препинания
            line.erase(remove_if(line.begin(), line.end(), [](char c) {return ispunct(c) || isdigit(c) || c == '«' || c == '»';}), line.end());

            // Приводим слово к нижнему регистру
            for (char& c : line)
            {
                c = tolower(c);
            }
            // Если слово не пустое, добавляем его в вектор
            if (!line.empty())
            {
                lines.push_back(line);
            }
        
    }

    file.close(); // Закрываем файл
    return lines;
}
