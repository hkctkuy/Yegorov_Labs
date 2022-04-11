#include "tid.h"

Table_Ident::Table_Ident(int max_size) : size(max_size), top(1) {

    table = new Ident[size];
}

Table_Ident::~Table_Ident() { delete[] table; }

Ident& Table_Ident::operator[](int i) { return table[i]; }

int Table_Ident::put(const char* buf) {

    for (int i = 1; i < top; i++) {

        if (!strcmp(buf, table[i].get_name())) {

            return i;
        }
    }
    table[top++].set_name(buf);

    return top - 1;
}
