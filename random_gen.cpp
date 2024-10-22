#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;
#define characters ruCharacters

// Генерация одной случайной строки заданной длины
string generateRandomString(size_t length) {
    const string enCharacters = "abcdefghijklmnopqrstuvwxyz";
    const string ruCharacters = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    string randomString;

    random_device rd;  // Инициализация генератора случайных чисел
    mt19937 generator(rd()); // Мерсеннский генератор
    uniform_int_distribution<> distribution(0, characters.size() - 1);

    for (size_t i = 0; i < length; ++i) {
        // Выбор случайного символа из набора
        randomString += characters[distribution(generator)];
    }

    return randomString;
}

// Генерация вектора случайных строк
vector<string> generateRandomStrings(size_t arraySize, size_t minLength, size_t maxLength) {
    vector<string> randomStrings;

    random_device rd;  // Инициализация генератора случайных чисел
    mt19937 generator(rd()); // Мерсеннский твистер
    uniform_int_distribution<size_t> lengthDistribution(minLength, maxLength);

    for (size_t i = 0; i < arraySize; ++i) {
        size_t randomLength = lengthDistribution(generator); // Генерация случайной длины
        randomStrings.push_back(generateRandomString(randomLength)); // Добавление строки в вектор
    }

    return randomStrings;
}