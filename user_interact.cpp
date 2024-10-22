#include <iostream>
#include <string>
using namespace std;

int getInitParams(unsigned int &array_size, unsigned int &len_min, unsigned int &len_max, string &substr)
{
    cout << "->Принять параметры по умолчанию? Lmin = 5, Lmax = 10, Size = 10 (1/0) > ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        array_size = 10;
        len_min = 5;
        len_max = 10;
    }
    else {
        cout << "Введите размеры случайных строк: от n до m:" << endl;

        cin >> len_min;
        if (len_min < 1) { cout << "Длина не может быть меньше 1"; return -1; }
        cin >> len_max;
        if (len_max < 1) { cout << "Длина не может быть меньше 1"; return -1; }


        cout << "Введите размер массива:" << endl;

        cin >> array_size;
        if (array_size < 1) { cout << "Размер не может быть меньше 1"; return -1; }
    }

    cout << "->Введите искомую подстроку: ";
    cin >> substr;

    cout << "->Ввод значений завершён" << endl;
    return 0;
}