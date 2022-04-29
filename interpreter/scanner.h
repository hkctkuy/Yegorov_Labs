#pragma once

#include "lex.h"
#include "ident.h"
#include "ts.h"

#include <iostream>
#include <cstdio>
#include <cmath>

class Scanner {

    FILE* fp;

    char c;

    static const char* TW[]; static const char* TD[];

    int look(const char* buf, const char** list);

    void gc();

public:

    static TS<Ident> TID;

    Scanner(const char* program);

    Lex get_lex();

    friend std::ostream& operator<<(std::ostream& out, Lex l);
};
