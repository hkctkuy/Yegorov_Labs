#include "parser.h"

void Parser::gl() {

    curr_lex = scan.get_lex();

    curr_type = curr_lex.get_type();

    if (curr_type == LEX_STRING) {

        curr_str_value = curr_lex.get_str_value();
    }
    else if (curr_type == LEX_REAL) {

        curr_real_value = curr_lex.get_real_value();
    }
    else {

        curr_int_value = curr_lex.get_int_value();
    }
    std::cout << curr_lex << std::endl;
}

void Parser::P() {

    gl();

    if(curr_type == LEX_PROGRAM) {

        gl();
    }
    else throw curr_lex;

    if(curr_type == LEX_LBRACE) {

        D1();

        B();
    }
    else throw curr_lex;

    if(curr_type == LEX_RBRACE) {

        gl();
    }
    else throw curr_lex;

    if(curr_type == LEX_FIN) {}

    else throw curr_lex;
}

void Parser::D1() {

    gl();

    while (curr_type == LEX_INT || curr_type == LEX_REAL || curr_type == LEX_STRING) {

        D();

        if (curr_type == LEX_SEMICOLON) {

            gl();
        }
        else throw curr_lex;
    }
}

void Parser::D() {

    gl();

    if (curr_type == LEX_ID) {

        gl();
    }
    else throw curr_lex;

    if (curr_type == LEX_ASSIGN) {

        gl();

        if (curr_type == LEX_INT_CONST || curr_type == LEX_REAL_CONST || curr_type == LEX_STRING_CONST) {

            gl();
        }
        else throw curr_lex;
    }

    while(curr_type == LEX_COMMA) {

        gl();

        if (curr_type == LEX_ID) {

            gl();
        }
        else throw curr_lex;

        if (curr_type == LEX_ASSIGN) {

            gl();

            if (curr_type == LEX_INT_CONST || curr_type == LEX_REAL_CONST || curr_type == LEX_STRING_CONST) {

                gl();
            }
            else throw curr_lex;
        }
    }
}

void Parser::B() {

    while (curr_type != LEX_RBRACE && curr_type != LEX_FIN) {

        S();
    }
}

void Parser::S() {

    if (curr_type == LEX_IF) {

        gl();

        if (curr_type == LEX_LPAREN) {

            gl();

            E();
        }
        else throw curr_lex;

        if (curr_type == LEX_RPAREN) {

            gl();

            S();
        }
        else throw curr_lex;

        if (curr_type == LEX_ELSE) {

            gl();

            S();
        }
        else throw curr_lex;
    }
    else if (curr_type == LEX_WHILE) {

        gl();

        if (curr_type == LEX_LPAREN) {

            gl();

            E();
        }
        else throw curr_lex;

        if (curr_type == LEX_RPAREN) {

            gl();

            S();
        }
        else throw curr_lex;

    }
    else if (curr_type == LEX_FOR) {

        gl();

        if (curr_type == LEX_LPAREN) {

            gl();
        }
        else throw curr_lex;

        if (curr_type == LEX_SEMICOLON) {

            gl();
        }
        else {

            E();

            if (curr_type == LEX_SEMICOLON) {

                gl();
            }
            else throw curr_lex;
        }
        if (curr_type == LEX_SEMICOLON) {

            gl();
        }
        else {

            E();

            if (curr_type == LEX_SEMICOLON) {

                gl();
            }
            else throw curr_lex;
        }
        if (curr_type == LEX_RPAREN) {

            gl();
        }
        else {

            E();

            if (curr_type == LEX_RPAREN) {

                gl();
            }
            else throw curr_lex;
        }
        S();
    }
    else if (curr_type == LEX_CONTINUE) {

        gl();

        if (curr_type == LEX_SEMICOLON) {

            gl();
        }
        else throw curr_lex;
    }
    else if (curr_type == LEX_READ) {

        gl();

        if (curr_type == LEX_LPAREN) {

            gl();
        }
        else throw curr_lex;

        if (curr_type == LEX_ID) {

            gl();
        }
        else throw curr_lex;

        if (curr_type == LEX_RPAREN) {

            gl();
        }
        else throw curr_lex;

        if (curr_type == LEX_SEMICOLON) {

            gl();
        }
        else throw curr_lex;
    }
    else if (curr_type == LEX_WRITE) {

        gl();

        if (curr_type == LEX_LPAREN) {

            gl();
        }
        else throw curr_lex;

        E();

        while (curr_type == LEX_COMMA) {

            gl();

            E();
        }
        if (curr_type == LEX_RPAREN) {

            gl();
        }
        else throw curr_lex;

        if (curr_type == LEX_SEMICOLON) {

            gl();
        }
        else throw curr_lex;
    }
    else if (curr_type == LEX_LBRACE) {

        gl();

        B();

        if (curr_type == LEX_RBRACE) {

            gl();
        }
        else throw curr_lex;
    }
    else {

        E();

        if (curr_type == LEX_SEMICOLON) {

            gl();
        }
        else throw curr_lex;
    }
}

void Parser::E() {

    O();

    if (curr_type == LEX_ASSIGN) {

        gl();

        E();
    }
}

void Parser::O() {

    A();

    while (curr_type == LEX_OR) {

        gl();

        A();
    }
}

void Parser::A() {

    L();

    while (curr_type == LEX_AND) {

        gl();

        L();
    }
}

void Parser::L() {

    E1();

    while (curr_type == LEX_EQ || curr_type == LEX_NEQ || curr_type == LEX_GTR || curr_type == LEX_GEQ || curr_type == LEX_LSS || curr_type == LEX_LEQ) {

        gl();

        E1();
    }
}

void Parser::E1() {

    T();

    while (curr_type == LEX_PLUS || curr_type == LEX_MINUS) {

        gl();

        T();
    }
}

void Parser::T() {

    N();

    while (curr_type == LEX_TIMES || curr_type == LEX_SLASH) {

        gl();

        N();
    }
}

void Parser::N() {

    while (curr_type == LEX_NOT || curr_type == LEX_PLUS || curr_type == LEX_MINUS) { // NOT, unary plus and unary minus

        gl();
    }
    F();
}

void Parser::F() {

    if (curr_type == LEX_LPAREN) {

        gl();

        E();

        if (curr_type == LEX_RPAREN) {

            gl();
        }
        else throw curr_lex;
    }
    else if (curr_type == LEX_INT_CONST || curr_type == LEX_REAL_CONST || curr_type == LEX_STRING_CONST || curr_type == LEX_ID) {

        gl();
    }
    else throw curr_lex;
}

Parser::Parser(const char* buf) : scan(buf) {}

void Parser::analyze() {

    P();

    std::cout << "SUCCESS" <<std::endl;
}
