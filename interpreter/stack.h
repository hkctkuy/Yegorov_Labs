#pragma once

template <class T>
class Stack {

    struct chain {

        T value;

        chain* next;
    };

    chain* top;

public:

    Stack();

    ~Stack();

    bool is_empty() const;

    void push(T);

    T pop();
};

template <class T>
Stack<T>::Stack() {

    top = NULL;
}

template <class T>
Stack<T>::~Stack() {

    while(!is_empty()) {

        pop();
    }
}

template <class T>
bool Stack<T>::is_empty() const {

    if(top == NULL) return true;

    else return false;
}

template <class T>
void Stack<T>::push(T t) {

    chain* new_chain = new chain;

    new_chain->value = t;

    new_chain->next = top;

    top = new_chain;
}

template <class T>
T Stack<T>::pop() {

    if(is_empty()) throw "Stack is empty";

    T res = top->value;

    chain* pop_chain = top;

    top = top->next;

    delete pop_chain;

    return res;
}
