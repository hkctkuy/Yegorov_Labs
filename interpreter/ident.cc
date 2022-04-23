#include "ident.h"

Ident::Ident() : declare(false), assign(false) {}

Ident::~Ident() { if (name) delete[] name; }

void Ident::set_name(const char* n) { name = new char[strlen(n) + 1]; strcpy(name, n); }

char* Ident::get_name() const { return name; }

void Ident::put_declare() { declare = true; }

bool Ident::get_declare() const { return declare; }

void Ident::put_assign() { assign = true; }

bool Ident::get_assign() const { return assign; }

void Ident::set_type(type_of_lex t) { type = t; }

type_of_lex Ident::get_type() const { return type; }

void Ident::set_int_value(int v) { int_value = v; }

int Ident::get_int_value() const { return int_value; }

void Ident::set_real_value(float v) { real_value = v; }

float Ident::get_real_value() const { return real_value; }

void Ident::set_str_value(char* buf) { str_value = new char[strlen(buf) + 1]; strcpy(str_value, buf); }

char* Ident::get_str_value() const { return str_value; }
