#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <Windows.h>
#include <map>
#include <queue>
#include "user_interact.h"
#include "random_gen.h"
#include "file_parser.h"
#include "substringer.h"

using namespace std;

typedef unsigned int unsint;

//class BorNode;
//typedef map<const char, BorNode*> LinksMap;
//
//// Следующий класс может быть целесообразно поместить внутрь автомата среди приватных полей.
//class BorNode {
//public:
//    LinksMap links;
//    BorNode* fail;  // Предыдущее состояние для функции отката. Только для root равно NULL.
//    BorNode* term; // Ближайшее терминальное состояние. Если отстутствует - NULL
//    int out;
//
//public:
//    BorNode(BorNode* fail_node = NULL)
//        : fail(fail_node)
//        , term(NULL)
//        , out(-1)
//    { }
//
//    BorNode* getLink(const char c) const
//    {
//        LinksMap::const_iterator iter = links.find(c);
//        if (iter != links.cend()) {
//            return iter->second;
//        }
//        else {
//            return NULL;
//        }
//    }
//
//    bool isTerminal() const
//    {
//        return (out >= 0);
//    }
//};
//
//class AhoCorasick
//{
//public:
//    typedef void (*Callback) (const char* substr);
//    BorNode root;
//    vector<string> words;
//    BorNode* current_state;
//
//public:
//    void addString(const char* const str)
//    {
//        BorNode* current_node = &root;
//        for (const char* cp = str; *cp; ++cp) {
//            BorNode* child_node = current_node->getLink(*cp);
//            if (!child_node) {
//                child_node = new BorNode(&root);
//                current_node->links[*cp] = child_node;
//            }
//            current_node = child_node;
//        }
//        current_node->out = words.size();
//        words.push_back(str);
//    }
//
//    void init()
//    {
//        queue<BorNode*> q;
//        q.push(&root);
//        while (!q.empty()) {
//            BorNode* current_node = q.front();
//            q.pop();
//            for (LinksMap::const_iterator iter = current_node->links.cbegin();
//                iter != current_node->links.cend(); ++iter)
//            {
//                const char symbol = iter->first;
//                BorNode* child = iter->second;
//
//                // Defining .fail for the childnode
//                BorNode* temp_node = current_node->fail;
//                while (temp_node) {
//                    BorNode* fail_candidate = temp_node->getLink(symbol);
//                    if (fail_candidate) {
//                        child->fail = fail_candidate;
//                        break;
//                    }
//                    temp_node = temp_node->fail;
//                }
//
//                // Defining .term for the childnode using .term of current node
//                if (child->fail->isTerminal()) {
//                    child->term = child->fail;
//                }
//                else {
//                    child->term = child->fail->term;
//                }
//                q.push(child);
//            }
//        }
//    }
//
//    void step(const char c)
//    {
//        while (current_state) {
//            BorNode* candidate = current_state->getLink(c);
//            if (candidate) {
//                current_state = candidate;
//                return;
//            }
//            current_state = current_state->fail;
//        }
//        current_state = &root;
//    }
//
//    void printTermsForCurrentState(Callback callback) const
//    {
//        if (current_state->isTerminal()) {
//            callback(words[current_state->out].c_str());
//        }
//        BorNode* temp_node = current_state->term;
//        while (temp_node) {
//            callback(words[temp_node->out].c_str());
//            temp_node = temp_node->term;
//        }
//    }
//
//    void search(const char* str, Callback callback)
//    {
//        current_state = &root;
//        for (; *str; ++str) {
//            cout << *str << ':' << endl;
//            step(*str);
//            printTermsForCurrentState(callback);
//        }
//    }
//};
//
//void print(const char* str)
//{
//    cout << "found substring " << str << "\n";
//}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    unsint startTime;
    unsint stopTime;

    unsint i = 0;
    unsint arraySize = 1; // Размер массива
    unsint minLength = 1;  // Минимальная длина строки
    unsint maxLength = 1; // Максимальная длина строки
    string filename = "Text.txt";
    string substring = "!";

    AhoCorasick ak_file;
    AhoCorasick ak_gen;

    // Получение данных от пользователя
    if (getInitParams(arraySize, minLength, maxLength, substring) != 0) return -1;
    // Генерация случайных строк
    vector<string> randomStrings = generateRandomStrings(arraySize, minLength, maxLength);

    // Вывод массива случайных строк
    //cout << "->Сгенерированные строки:" << endl;
    //for (const auto& str : randomStrings)
    //{
    //    cout << str << endl;
    //}
    
    // Считывание строк из файла и очистка от знаков
    vector<string> fileStrings = parseTextFile(filename);

    //cout << "->Прочитанные строки:" << endl;
    //for (const auto& str : fileStrings)
    //{
    //    cout << str << endl;
    //}

    // Построчный прогон алгоритма по строкам из файла и сбор позиций подстрок
    vector<int> positionsNaive_file;
    startTime = clock();
    for (const auto& str : fileStrings)
    {
        vector<int> current_pos = naiveStringMatcher(str, substring);
        positionsNaive_file.insert(positionsNaive_file.end(), current_pos.begin(), current_pos.end());
    }
    stopTime = clock();
    unsint naiveTime_file = stopTime - startTime; // время работы наивного алгоритма

    // Построчное заполнение структур алгоритма Ахо-Корасик строками файла
    for (const auto& str : fileStrings)
    {
        ak_file.addString(str.c_str());
    }

    // Поиск подстроки алгоритмом Ахо-Корасика на данных из файла
    const char* c_substr_file = substring.c_str();
    startTime = clock();
    ak_file.init();
    vector<int> positionsAho = ak_file.search(c_substr_file);
    stopTime = clock();
    unsint AhoTime_file = stopTime - startTime; // время работы алгоритма Ахо-Корасика

    // Теперь работа с сгенерированными строками

    // Построчный прогон наивного алгоритма по сгенерированным строкам и сбор позиций подстрок
    vector<int> positionsNaive_gen;
    startTime = clock();
    for (const auto& str : randomStrings)
    {
        vector<int> current_pos = naiveStringMatcher(str, substring);
        positionsNaive_gen.insert(positionsNaive_gen.end(), current_pos.begin(), current_pos.end());
    }
    stopTime = clock();
    unsint naiveTime_gen = stopTime - startTime; // время работы наивного алгоритма

    // Построчное заполнение структур алгоритма Ахо-Корасик сгенерированными строками
    for (const auto& str : randomStrings)
    {
        ak_gen.addString(str.c_str());
    }

    // Поиск подстроки алгоритмом Ахо-Корасика на сген данных
    const char* c_substr_gen = substring.c_str();
    startTime = clock();
    ak_gen.init();
    vector<int> positionsAho_gen = ak_gen.search(c_substr_gen);
    stopTime = clock();
    unsint AhoTime_gen = stopTime - startTime; // время работы алгоритма Ахо-Корасика

    // Вывод позиций для наивного алго
   // i = 1;
   // for (const auto& str : positionsNaive)
   //{
   //    cout << i << ") " << str << endl;
   //    i++;
   //}


    cout << endl << "<--------------->";
    cout << endl << "Время выполнения наивного алгоритма на сгенерированных данных: " << naiveTime_gen << endl;
    cout << endl << "Время выполнения алгоритма Ахо-Корасик на сгенерированных данных: " << AhoTime_gen << endl;
    cout << "---------------";
    cout << endl << "Время выполнения наивного алгоритма на данных из файла: " << naiveTime_file << endl;
    cout << endl << "Время выполнения алгоритма Ахо-Корасик на данных из файла: " << AhoTime_file << endl;

    return 0;
}
