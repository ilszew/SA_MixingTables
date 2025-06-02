#ifndef HASHTABLE_CHAINING_H
#define HASHTABLE_CHAINING_H

#include "arrayList.h"
#include <list>
#include <utility>
#include <iostream>

class HashTableChaining {
private:
    ArrayList<std::list<std::pair<int, int>>> table;
    int size;

    int hashFunction(int key) const {
        return ((key % size) + size) % size;
    }

public:
    explicit HashTableChaining(int tableSize = 101) : size(tableSize) {
        for (int i = 0; i < size; i++) {
            table.DodajK(std::list<std::pair<int, int>>());
        }
    }

    void insert(int key, int value) {
        int index = hashFunction(key);

        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }

        table[index].emplace_back(key, value);
    }

    void remove(int key) {
        int index = hashFunction(key);

        auto it = table[index].begin();
        while (it != table[index].end()) {
            if (it->first == key) {
                table[index].erase(it);
                return;
            }
            ++it;
        }
    }

    bool find(int key, int& value) {
        int index = hashFunction(key);

        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < size; i++) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& pair : table[i]) {
                std::cout << "(" << pair.first << "," << pair.second << ") ";
            }
            std::cout << std::endl;
        }
    }
};

#endif