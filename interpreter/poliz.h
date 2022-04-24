#pragma once

#include "lex.h"
#include "scanner.h"

#include <iostream>

class Poliz {

    int curr_size, max_size;

    Lex* p;

public:

    Poliz(int);

    ~Poliz();

    void push_back(Lex);

    int size() const;

    Lex& operator[](int);

    friend std::ostream& operator<<(std::ostream&, Poliz);
};
