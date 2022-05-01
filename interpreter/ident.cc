#include "ident.h"

Ident::Ident() : declare(false), assign(false) {}

Ident::~Ident() { if (name) delete[] name; }

char* Ident::get_name() const { return name; }

void Ident::put_declare() { declare = true; }

bool Ident::get_declare() const { return declare; }

void Ident::put_assign() { assign = true; }

bool Ident::get_assign() const { return assign; }

void Ident::set_type(type_of_lex t) { type = t; }

type_of_lex Ident::get_type() const { return type; }

void Ident::set_value(int v) { real_value = value = v; }

int Ident::get_value() const { return value; }

void Ident::set_real_value(float v) { value = real_value = v; }

float Ident::get_real_value() const { return real_value; }

Ident::operator char*&() { return name; }
