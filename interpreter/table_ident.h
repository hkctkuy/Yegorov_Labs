#pragma once

#include "ident.h"

class Table_Ident {

    Ident* table;

    int size, top;

public:

    Table_Ident(int max_size);

    ~Table_Ident();

    Ident& operator[](int i);

    int put(const char* buf);  // Add ID named buf to TID and return its number in TID
};
