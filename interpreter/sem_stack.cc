#include "sem_stack.h"

Sem_stack::Sem_stack() {

    top = NULL;
}

Sem_stack::~Sem_stack() {

    while(!is_empty()) {

        pop();
    }
}

bool Sem_stack::is_empty() {

    if(top == NULL) return true;

    else return false;
}

void Sem_stack::push(type_of_lex t) {

    chain* new_chain = new chain;

    new_chain->type = t;

    new_chain->next = top;

    top = new_chain;
}

type_of_lex Sem_stack::pop() {

    type_of_lex res = top->type;

    chain* pop_chain = top;

    top = top->next;

    delete pop_chain;

    return res;
}
