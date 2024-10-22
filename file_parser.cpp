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

    // ���������, ����������� �� ����
    if (!file.is_open())
    {
        cerr << "������ �������� �����: " << filename << endl;
        return lines;
    }

    string line;
    while (getline(file, line))
    {        
            // ������� ����� ����������
            line.erase(remove_if(line.begin(), line.end(), [](char c) {return ispunct(c) || isdigit(c) || c == '�' || c == '�';}), line.end());

            // �������� ����� � ������� ��������
            for (char& c : line)
            {
                c = tolower(c);
            }
            // ���� ����� �� ������, ��������� ��� � ������
            if (!line.empty())
            {
                lines.push_back(line);
            }
        
    }

    file.close(); // ��������� ����
    return lines;
}
