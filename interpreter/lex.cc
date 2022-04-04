#include "lex.h"

Lex::Lex(type_of_lex t) : type(t) {}

Lex::Lex(type_of_lex t, int v) : type(t), int_value(v) {}

Lex::Lex(type_of_lex t, float v) : type(t), real_value(v) {}

Lex::Lex(type_of_lex t, char* buf) : type(t) {

    str_value = new char[strlen(buf) + 1];

    strcpy(str_value, buf);
}
type_of_lex Lex::get_type() const { return type; }

int Lex::get_int_value() const { return int_value; }

float Lex::get_float_value() const { return real_value; }

char* Lex::get_str_value() const { return str_value; }
