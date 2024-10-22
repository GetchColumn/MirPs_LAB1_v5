#pragma once
#include <string>
#include <vector>
using namespace std;
// Генерация одной случайной строки заданной длины
string generateRandomString(size_t length);
// Генерация вектора случайных строк
vector<string> generateRandomStrings(size_t arraySize, size_t minLength, size_t maxLength);
