#pragma once

#include <iostream>
#include <cstring>
#include <string>

enum type_of_lex {
    LEX_NULL, /*0*/
    LEX_AND, LEX_BEGIN, LEX_BOOL, LEX_CONTINUE, LEX_DO, LEX_ELSE, LEX_END, LEX_FALSE, LEX_FOR, LEX_IF, LEX_INT, /*11*/
    LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_REAL, LEX_STRING, LEX_THEN, LEX_TRUE, LEX_VAR, LEX_WHILE, LEX_WRITE, /*22*/
    LEX_FIN, /*23*/
    LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_LBRACE, LEX_RBRACE, LEX_EQ, LEX_LSS, /*33*/
    LEX_GTR, LEX_PLUS, LEX_PLUSPLUS, LEX_MINUS, LEX_MINUSMINUS, LEX_TIMES, LEX_SLASH, LEX_LEQ, LEX_NEQ, LEX_GEQ, /*43*/
    LEX_INT_CONST, LEX_REAL_CONST, LEX_STRING_CONST, /*46*/
    LEX_ID, /*47*/
    POLIZ_LABEL, /*48*/
    POLIZ_ADDRESS, /*49*/
    POLIZ_GO, /*50*/
    POLIZ_FGO  /*51*/
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
