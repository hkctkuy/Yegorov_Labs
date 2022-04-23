#pragma once

#include "lex.h"

struct chain {

    type_of_lex type;

    chain* next;
};

class Sem_stack {

    chain* top;

    bool is_empty();

public:

    Sem_stack();

    ~Sem_stack();

    void push(type_of_lex);

    type_of_lex pop();
};
