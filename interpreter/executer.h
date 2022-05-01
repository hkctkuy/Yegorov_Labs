#pragma once

#include "lex.h"
#include "ident.h"
#include "scanner.h"
#include "stack.h"
#include "parser.h"

#include "string.h"

enum type {

    INT, REAL
};

class Ex_Stack {

    Stack<int> st_int;

    Stack<float> st_real;

    struct chain {

        type value;

        chain* next;
    };

    chain* top;

    int size;

public:

    Ex_Stack();

    ~Ex_Stack();

    bool is_empty() const;

    void push(int);

    void push(float);

    int int_pop();

    float real_pop();
};

class Executer {

    Ex_Stack st;

public:

    void execute(Poliz&);
};

char* cat(const char*, const char*);

void read_str(char*&);
