#pragma once
#include <vector>
#include <string>

using namespace std;

vector<int> naiveStringMatcher(string t, string p);

class BorNode {
public:
    map<const char, BorNode*> links;
    BorNode* fail;
    BorNode* term;
    int out;

public:
    BorNode()
        : fail(nullptr), term(nullptr), out(-1)
    { }

    BorNode* getLink(const char c) const {
        auto iter = links.find(c);
        if (iter != links.end()) {
            return iter->second;
        }
        else {
            return nullptr;
        }
    }

    bool isTerminal() const {
        return (out >= 0);
    }
};

class AhoCorasick {
public:
    BorNode root;
    vector<string> words;
    BorNode* current_state;

public:
    void addString(const char* const str) {
        BorNode* current_node = &root;
        for (const char* cp = str; *cp; ++cp) {
            if (current_node->links.find(*cp) == current_node->links.end()) {
                current_node->links[*cp] = new BorNode();
            }
            current_node = current_node->links[*cp];
        }
        current_node->out = words.size();
        words.push_back(str);
    }

    // сплошная магия
    void init() {
        queue<BorNode*> q;
        q.push(&root);
        while (!q.empty()) {
            BorNode* current_node = q.front();
            q.pop();
            for (const auto& pair : current_node->links) {
                const char symbol = pair.first;
                BorNode* child = pair.second;

                BorNode* temp_node = current_node;
                while (temp_node->fail) {
                    BorNode* fail_candidate = temp_node->fail->getLink(symbol);
                    if (fail_candidate) {
                        child->fail = fail_candidate;
                        break;
                    }
                    temp_node = temp_node->fail;
                }

                if (child->fail && child->fail->isTerminal()) {
                    child->term = child->fail;
                }
                else {
                    child->term = (child->fail) ? child->fail->term : nullptr;
                }
                q.push(child);
            }
        }
    }

    vector<int> search(const char* str) {
        current_state = &root;
        vector<int> matches;

        for (const char* ptr = str; *ptr; ++ptr) {
            step(*ptr);
            vector<int> localMatches = findAllMatches();
            matches.insert(matches.end(), localMatches.begin(), localMatches.end());
        }
        return matches;
    }

private:
    void step(const char c) {
        while (current_state && current_state->getLink(c) == nullptr) {
            current_state = current_state->fail;
        }
        if (current_state) {
            current_state = current_state->getLink(c);
        }
        else {
            current_state = &root;
        }
    }

    vector<int> findAllMatches() {
        vector<int> matches;
        BorNode* node = current_state;
        while (node) {
            if (node->isTerminal()) {
                matches.push_back(node->out);
            }
            node = node->term;
        }
        return matches;
    }
};