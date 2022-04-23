#include "Stack.h"

Stack::Stack() {

    top = NULL;
}

Stack::~Stack() {

    while(!is_empty()) {

        pop();
    }
}

bool Stack::is_empty() {

    if(top == NULL) return true;

    else return false;
}

void Stack::push(type_of_lex t) {

    chain* new_chain = new chain;

    new_chain->type = t;

    new_chain->next = top;

    top = new_chain;
}

type_of_lex Stack::pop() {

    type_of_lex res = top->type;

    chain* pop_chain = top;

    top = top->next;

    delete pop_chain;

    return res;
}
