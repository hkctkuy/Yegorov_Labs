#pragma once

#include "string.h"

#define MAX_TABLE_SIZE 100
#define MAX_STR_SIZE 100

template <class T>
class TS {

    T* table;

    int size, top;

public:

    TS();

    ~TS();

    T& operator[](int i);

    int put(const char* buf);
};

template <class T>
TS<T>::TS() : size(MAX_TABLE_SIZE), top(1) {

    table = new T[size];
}

template <class T>
TS<T>::~TS() { delete[] table; }

template <class T>
T& TS<T>::operator[](int i) { return table[i]; }

template <class T>
int TS<T>::put(const char* buf) {

    if(top >= MAX_TABLE_SIZE) throw "table overflow";

    for (int i = 1; i < top; i++) {

        if (!strcmp(buf, (char*&)table[i])) {

            return i;
        }
    }
    (char*&)table[top] = new char[strlen(buf)];

    strcpy((char*&)table[top++], buf);

    return top - 1;
}
