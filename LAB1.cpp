﻿//# include <iostream>
//# include <map>
//# include <vector>
//# include <string>
//# include <queue>
//
//using namespace std;
//
//class BorNode;
//typedef map<const char, BorNode*> LinksMap;
//
//// Следующий класс может быть целесообразно поместить внутрь автомата среди приватных полей.
//class BorNode {
//public:
//    LinksMap links; // сопоставляем каждой вершине символ в словаре map
//    BorNode* fail;  // Предыдущее состояние для функции отката. Только для root равно NULL.
//    BorNode* term; // Ближайшее терминальное состояние. Если отсутствует - NULL
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
//
//int main()
//{
//    AhoCorasick ak;
//
//    ak.addString("test");
//    ak.addString("rok");
//    ak.addString("roka");
//    ak.addString("strok");
//    ak.addString("t");
//
//    ak.init();
//
//    ak.search("testovaya_stroka!", print);
//
//    cin.get();
//
//    return 0;
//}