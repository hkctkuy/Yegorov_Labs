#pragma once

#include "lex.h"
#include "scanner.h"

#include <iostream>

#define MAX_POLIZ_SIZE 1000

class Poliz {

    int curr_size;

    Lex* p;

public:

    Poliz();

    ~Poliz();

    void push_back(Lex);

    int size() const;

    Lex& operator[](int);

    friend std::ostream& operator<<(std::ostream&, Poliz&);
};
