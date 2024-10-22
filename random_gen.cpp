#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;
#define characters ruCharacters

// ��������� ����� ��������� ������ �������� �����
string generateRandomString(size_t length) {
    const string enCharacters = "abcdefghijklmnopqrstuvwxyz";
    const string ruCharacters = "��������������������������������";
    string randomString;

    random_device rd;  // ������������� ���������� ��������� �����
    mt19937 generator(rd()); // ����������� ���������
    uniform_int_distribution<> distribution(0, characters.size() - 1);

    for (size_t i = 0; i < length; ++i) {
        // ����� ���������� ������� �� ������
        randomString += characters[distribution(generator)];
    }

    return randomString;
}

// ��������� ������� ��������� �����
vector<string> generateRandomStrings(size_t arraySize, size_t minLength, size_t maxLength) {
    vector<string> randomStrings;

    random_device rd;  // ������������� ���������� ��������� �����
    mt19937 generator(rd()); // ����������� �������
    uniform_int_distribution<size_t> lengthDistribution(minLength, maxLength);

    for (size_t i = 0; i < arraySize; ++i) {
        size_t randomLength = lengthDistribution(generator); // ��������� ��������� �����
        randomStrings.push_back(generateRandomString(randomLength)); // ���������� ������ � ������
    }

    return randomStrings;
}