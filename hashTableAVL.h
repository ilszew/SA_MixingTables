#ifndef HASHTABLE_AVL_H
#define HASHTABLE_AVL_H

#include "arrayList.h"
#include <iostream>
#include <algorithm>

struct AVLNode {
    int key;
    int value;
    int height;
    AVLNode* left;
    AVLNode* right;

    explicit AVLNode(int k, int v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

class HashTableAVL {
private:
    ArrayList<AVLNode*> table;
    int size;

    int getHeight(AVLNode* node) const {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode* insertAVL(AVLNode* node, int key, int value) {
        if (!node) {
            return new AVLNode(key, value);
        }

        if (key < node->key) {
            node->left = insertAVL(node->left, key, value);
        } else if (key > node->key) {
            node->right = insertAVL(node->right, key, value);
        } else {
            node->value = value;
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }

        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }

        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* findMin(AVLNode* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    AVLNode* removeAVL(AVLNode* node, int key) {
        if (!node) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = removeAVL(node->left, key);
        } else if (key > node->key) {
            node->right = removeAVL(node->right, key);
        } else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;

                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                AVLNode* temp = findMin(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = removeAVL(node->right, temp->key);
            }
        }

        if (!node) {
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    int hashFunction(int key) const {
        return ((key % size) + size) % size;
    }

    void deleteTree(AVLNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    AVLNode* copyTree(AVLNode* node) {
        if (!node) {
            return nullptr;
        }
        AVLNode* newNode = new AVLNode(node->key, node->value);
        newNode->height = node->height;
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    bool findInTree(AVLNode* node, int key, int& value) const {
        while (node) {
            if (key == node->key) {
                value = node->value;
                return true;
            } else if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return false;
    }

public:
    explicit HashTableAVL(int tableSize = 101) : size(tableSize) {
        for (int i = 0; i < size; i++) {
            table.DodajK(nullptr);
        }
    }

    HashTableAVL(const HashTableAVL& other) : size(other.size) {
        for (int i = 0; i < size; i++) {
            table.DodajK(copyTree(other.table[i]));
        }
    }

    HashTableAVL& operator=(const HashTableAVL& other) {
        if (this != &other) {
            for (int i = 0; i < size; i++) {
                deleteTree(table[i]);
            }
            size = other.size;
            table = ArrayList<AVLNode*>();
            for (int i = 0; i < size; i++) {
                table.DodajK(copyTree(other.table[i]));
            }
        }
        return *this;
    }

    ~HashTableAVL() {
        for (int i = 0; i < size; i++) {
            deleteTree(table[i]);
        }
    }

    void insert(int key, int value) {
        int index = hashFunction(key);
        table[index] = insertAVL(table[index], key, value);
    }

    bool remove(int key) {
        int index = hashFunction(key);
        AVLNode* originalRoot = table[index];
        table[index] = removeAVL(table[index], key);
        return originalRoot != table[index] || (originalRoot == nullptr && table[index] == nullptr && contains(key));
    }

    bool find(int key, int& value) const {
        int index = hashFunction(key);
        return findInTree(table[index], key, value);
    }

    bool contains(int key) const {
        int value;
        return find(key, value);
    }

    void display() const {
        std::cout << "Hash Table AVL Content:" << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << "Bucket " << i << ": ";
            displayTree(table[i]);
            std::cout << std::endl;
        }
    }

private:
    void displayTree(AVLNode* node) const {
        if (node) {
            displayTree(node->left);
            std::cout << "(" << node->key << "," << node->value << ") ";
            displayTree(node->right);
        }
    }
};

#endif