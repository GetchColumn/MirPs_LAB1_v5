#include <iostream>
#include <string>
using namespace std;

int getInitParams(unsigned int &array_size, unsigned int &len_min, unsigned int &len_max, string &substr)
{
    cout << "->������� ��������� �� ���������? Lmin = 5, Lmax = 10, Size = 10 (1/0) > ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        array_size = 10;
        len_min = 5;
        len_max = 10;
    }
    else {
        cout << "������� ������� ��������� �����: �� n �� m:" << endl;

        cin >> len_min;
        if (len_min < 1) { cout << "����� �� ����� ���� ������ 1"; return -1; }
        cin >> len_max;
        if (len_max < 1) { cout << "����� �� ����� ���� ������ 1"; return -1; }


        cout << "������� ������ �������:" << endl;

        cin >> array_size;
        if (array_size < 1) { cout << "������ �� ����� ���� ������ 1"; return -1; }
    }

    cout << "->������� ������� ���������: ";
    cin >> substr;

    cout << "->���� �������� ��������" << endl;
    return 0;
}