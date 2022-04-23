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

void Parser::push_const(){

    if (curr_type == LEX_INT_CONST) st.push(LEX_INT);

    else if (curr_type == LEX_REAL_CONST) st.push(LEX_REAL);

    else if (curr_type == LEX_STRING_CONST) st.push(LEX_STRING);

    else throw "isn't const";
}

void Parser::P() {

    if(curr_type == LEX_PROGRAM) {

        gl();
    }
    else throw curr_lex;

    if(curr_type == LEX_LBRACE) {

        gl();

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

    while (curr_type == LEX_INT || curr_type == LEX_REAL || curr_type == LEX_STRING) {

        ident_type = curr_type;

        gl();

        D();

        if (curr_type == LEX_SEMICOLON) {

            gl();
        }
        else throw curr_lex;
    }
}

void Parser::D() {

    if (curr_type == LEX_ID) {

        dec();

        st.push(ident_type);

        gl();
    }
    else throw curr_lex;

    if (curr_type == LEX_ASSIGN) {

        gl();

        if (curr_type == LEX_INT_CONST || curr_type == LEX_REAL_CONST || curr_type == LEX_STRING_CONST) {

            push_const();

            eq_type();

            gl();
        }
        else throw curr_lex;
    }
    else {

        st.pop();
    }

    while(curr_type == LEX_COMMA) {

        gl();

        if (curr_type == LEX_ID) {

            dec();

            st.push(ident_type);

            gl();
        }
        else throw curr_lex;

        if (curr_type == LEX_ASSIGN) {

            gl();

            if (curr_type == LEX_INT_CONST || curr_type == LEX_REAL_CONST || curr_type == LEX_STRING_CONST) {

                push_const();

                eq_type();

                gl();
            }
            else throw curr_lex;
        }
        else {

            st.pop();
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

            check_id_in_read();

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

    l_value_flag = true;

    O();

    if (curr_type == LEX_ASSIGN) {

        if(!l_value_flag) throw "Not l_value expression";

        gl();

        E();

        eq_type();
    }
}

void Parser::O() {

    A();

    while (curr_type == LEX_OR) {

        l_value_flag = false;

        gl();

        A();

        check_O();
    }
}

void Parser::A() {

    L();

    while (curr_type == LEX_AND) {

        l_value_flag = false;

        gl();

        L();

        check_A();
    }
}

void Parser::L() {

    E1();

    while (curr_type == LEX_EQ || curr_type == LEX_NEQ || curr_type == LEX_GTR || curr_type == LEX_GEQ || curr_type == LEX_LSS || curr_type == LEX_LEQ) {

        l_value_flag = false;

        gl();

        E1();

        check_L();
    }
}

void Parser::E1() {

    T();

    while (curr_type == LEX_PLUS || curr_type == LEX_MINUS) {

        l_value_flag = false;

        st.push(curr_type);

        gl();

        T();

        check_E1();
    }
}

void Parser::T() {

    N();

    while (curr_type == LEX_TIMES || curr_type == LEX_SLASH) {

        l_value_flag = false;

        gl();

        N();

        check_T();
    }
}

void Parser::N() {

    if (curr_type == LEX_NOT || curr_type == LEX_PLUS || curr_type == LEX_MINUS) { // NOT, unary plus and unary minus

        l_value_flag = false;

        st.push(curr_type);

        gl();

        N();

        check_N();
    }
    else {

        F();
    }
}

void Parser::F() {

    if (curr_type == LEX_LPAREN) {

        l_value_flag = false;

        gl();

        E();

        if (curr_type == LEX_RPAREN) {

            gl();
        }
        else throw curr_lex;
    }
    else if (curr_type == LEX_INT_CONST || curr_type == LEX_REAL_CONST || curr_type == LEX_STRING_CONST) {

        l_value_flag = false;

        push_const();

        gl();
    }
    else if(curr_type == LEX_ID) {

        st.push(Scanner::TID[curr_int_value].get_type());

        gl();
    }
    else throw curr_lex;
}

void Parser::check_id() {

    if(Scanner::TID[curr_int_value].get_declare()) {

        st.push(Scanner::TID[curr_int_value].get_type());
    }
    else throw "ID is not declared";
}

void Parser::check_id_in_read() {

    if(!Scanner::TID[curr_int_value].get_declare()) throw "ID is not declared";
}

void Parser::dec() {

    if(Scanner::TID[curr_int_value].get_declare()) throw "ID has been already declared!";

    else {

        Scanner::TID[curr_int_value].put_declare();

        Scanner::TID[curr_int_value].set_type(ident_type);
    }
}

void Parser::eq_type() {

    type_of_lex operand1 = st.pop(), operand2 = st.pop();

    if(operand1 == operand2) {

        st.push(operand1);
    }
    else throw "Different types in = !";
}

void Parser::check_O() {

    type_of_lex operand1 = st.pop(), operand2 = st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT) {

        st.push(LEX_INT);
    }
    else throw "Wrong types in operation";
}

void Parser::check_A() {

    type_of_lex operand1 = st.pop(), operand2 = st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT) {

        st.push(LEX_INT);
    }
    else throw "Wrong types in operation";
}

void Parser::check_L() {

    type_of_lex operand1 = st.pop(), operand2 = st.pop();

    if (operand1 == LEX_STRING) {

        if (operand2 == LEX_STRING) {

            st.push(LEX_INT);
        }
        else throw "Wrong types in operation";
    }
    else if (operand2 == LEX_STRING) throw "Wrong types in operation";

    else st.push(LEX_INT);
}

void Parser::check_E1() {

    type_of_lex operand1 = st.pop(), operation = st.pop(), operand2 = st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT) {

        st.push(LEX_INT);
    }
    else if (operand1 == LEX_STRING) {

        if (operation == LEX_PLUS || operand2 == LEX_STRING) {

            st.push(LEX_STRING);
        }
        else throw "Wrong types in operation";
    }
    else if (operand2 == LEX_STRING) throw "Wrong types in operation";

    else st.push(LEX_REAL);
}

void Parser::check_T() {

    type_of_lex operand1 = st.pop(), operand2 = st.pop();

    if (operand1 == LEX_STRING || operand2 == LEX_STRING) throw "Wrong types in operation";

    else if (operand1 == LEX_INT && operand2 == LEX_INT) {

        st.push(LEX_INT);
    }
    else st.push(LEX_REAL);
}

void Parser::check_N() {

    type_of_lex operand = st.pop(), operation = st.pop();

    if(operand == LEX_INT) {

        st.push(LEX_INT);
    }
    else if(operand == LEX_REAL) {

        if(operation == LEX_NOT) throw "Wrong types in operation";

        else st.push(LEX_REAL);
    }
    else if(operand == LEX_STRING) throw "Wrong types in operation";

    else throw "WTF?";
}

Parser::Parser(const char* buf) : scan(buf) {}

void Parser::analyze() {

    gl();

    P();

    std::cout << "SUCCESS" <<std::endl;
}
