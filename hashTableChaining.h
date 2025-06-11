#ifndef HASHTABLE_CHAINING_H
#define HASHTABLE_CHAINING_H
#include "arrayList.h"
#include "singlyLinkedList.h"
#include <utility>
#include <iostream>

class HashTableChaining {
private:
    ArrayList<SinglyLinkedList<std::pair<int, int>>> table;
    int size;
    
    int hashFunction(int key) const {
        return ((key % size) + size) % size;
    }
    
public:
    explicit HashTableChaining(int tableSize = 101) : size(tableSize) {
        for (int i = 0; i < size; i++) {
            table.DodajK(SinglyLinkedList<std::pair<int, int>>());
        }
    }
    
    void insert(int key, int value) {
        int index = hashFunction(key);
        
        // Sprawdzamy czy klucz już istnieje
        for (int i = 0; i < table[index].getSize(); i++) {
            if (table[index].getAt(i).first == key) {
                // Aktualizujemy wartość
                table[index].getAt(i).second = value;
                return;
            }
        }
        
        table[index].addLast(std::make_pair(key, value));
    }
    
    void remove(int key) {
        int index = hashFunction(key);

        for (int i = 0; i < table[index].getSize(); i++) {
            if (table[index].getAt(i).first == key) {
                table[index].removeAt(i);
                return;
            }
        }
    }
    
    bool find(int key, int& value) {
        int index = hashFunction(key);
        
        for (int i = 0; i < table[index].getSize(); i++) {
            if (table[index].getAt(i).first == key) {
                value = table[index].getAt(i).second;
                return true;
            }
        }
        return false;
    }
    
    void display() {
        for (int i = 0; i < size; i++) {
            std::cout << "Bucket " << i << ": ";
            for (int j = 0; j < table[i].getSize(); j++) {
                std::cout << "(" << table[i].getAt(j).first << "," 
                         << table[i].getAt(j).second << ") ";
            }
            std::cout << std::endl;
        }
    }
};

#endif
