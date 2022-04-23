#pragma once

#include "lex.h"

struct chain {

    type_of_lex type;

    chain* next;
};

class Stack {

    chain* top;

    bool is_empty();

public:

    Stack();

    ~Stack();

    void push(type_of_lex);

    type_of_lex pop();
};
