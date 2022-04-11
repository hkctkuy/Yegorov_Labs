#pragma once

#include <iostream>
#include <cstring>
#include <string>

enum type_of_lex {
    LEX_NULL, /*0*/
    LEX_AND, LEX_CONTINUE, LEX_ELSE, LEX_FALSE, LEX_FOR, LEX_IF, LEX_INT, /*7*/
    LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_REAL, LEX_STRING, LEX_TRUE, LEX_WHILE, LEX_WRITE, /*16*/
    LEX_FIN, /*17*/
    LEX_SEMICOLON, LEX_COMMA, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_LBRACE, LEX_RBRACE, LEX_EQ, LEX_LSS, /*26*/
    LEX_GTR, LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_LEQ, LEX_NEQ, LEX_GEQ, /*34*/
    LEX_INT_CONST, LEX_REAL_CONST, LEX_STRING_CONST, /*37*/
    LEX_ID, /*38*/
    POLIZ_LABEL, /*39*/
    POLIZ_ADDRESS, /*40*/
    POLIZ_GO, /*41*/
    POLIZ_FGO  /*42*/
};

class Lex {

    type_of_lex type;

    int int_value; float real_value; char* str_value;

public:

    Lex(type_of_lex t = LEX_NULL);

    Lex(type_of_lex t, int v);

    Lex(type_of_lex t, float v);

    Lex(type_of_lex t, char* buf);

    type_of_lex get_type() const;

    int get_int_value() const;

    float get_real_value() const;

    char* get_str_value() const;

    friend std::ostream& operator<<(std::ostream& out, Lex l);
};
