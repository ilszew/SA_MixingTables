#pragma once
#ifndef HASHTABLELINEAR_H
#define HASHTABLELINEAR_H

#include "arrayList.h"
#include <stdexcept>
#include <cmath>

class HashTableLinear {
private:
    enum State { EMPTY, OCCUPIED, DELETED };

    struct Entry {
        int key;
        int value;
        State state;
        Entry() : key(0), value(0), state(EMPTY) {}
    };

    ArrayList<Entry> table;
    int sz;
    double maxLoadFactor;

    int capacity() const {
        return table.wielkosc();
    }

    int hashIndex(int key) const {
        int h = key % capacity();
        return (h < 0 ? h + capacity() : h);
    }

    void rehash() {
        int oldCap = capacity();
        int newCap = (oldCap == 0 ? 8 : oldCap * 2);
        ArrayList<Entry> oldTable = table;

        table = ArrayList<Entry>();
        sz = 0;
        for (int i = 0; i < newCap; ++i) {
            table.DodajK(Entry());
        }

        for (int i = 0; i < oldCap; ++i) {
            const Entry& e = oldTable[i];
            if (e.state == OCCUPIED) {
                insert(e.key, e.value);
            }
        }
    }

    void ensureCapacityForInsert() {
        if (capacity() == 0) {
            rehash();
        }
        if ((double)(sz + 1) / capacity() > maxLoadFactor) {
            rehash();
        }
    }

public:
    HashTableLinear(double loadFactor = 0.6)
        : table(), sz(0), maxLoadFactor(loadFactor) {
        rehash();
    }

    void insert(int key, int value) {
        ensureCapacityForInsert();
        int idx = hashIndex(key);

        while (table[idx].state == OCCUPIED && table[idx].key != key) {
            idx = (idx + 1) % capacity();
        }

        if (table[idx].state != OCCUPIED) {
            table[idx].key = key;
            table[idx].value = value;
            table[idx].state = OCCUPIED;
            ++sz;
        }
        else {
            table[idx].value = value;
        }
    }

    void remove(int key) {
        if (capacity() == 0) return;
        int idx = hashIndex(key);
        int probes = 0;
        while (probes < capacity()) {
            if (table[idx].state == EMPTY) return;
            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                table[idx].state = DELETED;
                --sz;
                return;
            }
            idx = (idx + 1) % capacity();
            ++probes;
        }
    }

    int get(int key) const {
        if (capacity() == 0) throw std::out_of_range("Brak element?w w tabeli");
        int idx = hashIndex(key);
        int probes = 0;
        while (probes < capacity()) {
            if (table[idx].state == EMPTY) break;
            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                return table[idx].value;
            }
            idx = (idx + 1) % capacity();
            ++probes;
        }
        throw std::out_of_range("Klucz nie istnieje");
    }

    bool contains(int key) const {
        try {
            get(key);
            return true;
        }
        catch (...) {
            return false;
        }
    }

    int size() const {
        return sz;
    }

    int bucketCount() const {
        return capacity();
    }
};

#endif
