#pragma once

#include "lex.h"
#include "scanner.h"

#include <iostream>

class Parser {

    Lex curr_lex;

    type_of_lex curr_type;

    int curr_int_value; float curr_real_value; char* curr_str_value;

    Scanner scan;

    void gl();

    void P();

    void D1();

    void D();

    void B();

    void S();

    void E();

    void O();

    void A();

    void L();

    void E1();

    void T();

    void N();

    void F();

public:

    Parser(const char*);

    void analyze();
};
