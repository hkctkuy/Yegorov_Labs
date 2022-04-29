#pragma once

#include "lex.h"

#include <cstring>
#include <string>

class Ident {

    char* name;

    bool declare, assign;

    type_of_lex type;

    int value; float real_value;

public:

    Ident();

    ~Ident();

    void set_name(const char* n);

    char* get_name() const;

    void put_declare();

    bool get_declare() const;

    void put_assign();

    bool get_assign() const;

    void set_type(type_of_lex t);

    type_of_lex get_type() const;

    void set_value(int v);

    int get_value() const;

    void set_real_value(float v);

    float get_real_value() const;

    explicit operator char*&();
};
