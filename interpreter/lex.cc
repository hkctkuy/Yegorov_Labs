#include "lex.h"

Lex::Lex(type_of_lex t) : type(t) { real_value = value = t; }

Lex::Lex(type_of_lex t, int v) : type(t) { real_value = value = v; }

Lex::Lex(type_of_lex t, float v) : type(t) { value = real_value = v; }

type_of_lex Lex::get_type() const { return type; }

int Lex::get_value() const { return value; }

float Lex::get_real_value() const { return real_value; }
