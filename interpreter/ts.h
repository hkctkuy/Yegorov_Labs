#pragma once

#include "string.h"

#define MAX_SIZE 100
#define MAX_STR_SIZE 100

template <class T>
class TS {

    T* table;

    int size, top;

public:

    TS();

    ~TS();

    T& operator[](int i);

    int put(const char* buf);  // Add ID named buf to TID and return its number in TID
};

template <class T>
TS<T>::TS() : size(MAX_SIZE), top(1) {

    table = new T[size];
}

template <class T>
TS<T>::~TS() { delete[] table; }

template <class T>
T& TS<T>::operator[](int i) { return table[i]; }

template <class T>
int TS<T>::put(const char* buf) {

    for (int i = 1; i < top; i++) {

        if (!strcmp(buf, (char*&)table[i])) {

            return i;
        }
    }
    (char*&)table[top] = new char[strlen(buf)];

    strcpy((char*&)table[top++], buf);

    return top - 1;
}
