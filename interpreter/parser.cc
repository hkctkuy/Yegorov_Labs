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
    //std::cout << curr_lex << std::endl;
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

    int curr_ident;

    if (curr_type == LEX_ID) {

        curr_ident = curr_int_value;

        dec();

        st.push(ident_type);

        gl();
    }
    else throw curr_lex;

    if (curr_type == LEX_ASSIGN) {

        st.push(curr_type);

        gl();

        if (curr_type == LEX_INT_CONST || curr_type == LEX_REAL_CONST || curr_type == LEX_STRING_CONST) {

            prog.push_back(Lex(POLIZ_ADDRESS, curr_ident));

            prog.push_back(curr_lex);

            push_const();

            eq_type();

            prog.push_back(Lex(LEX_SEMICOLON));

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

            curr_ident = curr_int_value;

            dec();

            st.push(ident_type);

            gl();
        }
        else throw curr_lex;

        if (curr_type == LEX_ASSIGN) {

            st.push(curr_type);

            gl();

            if (curr_type == LEX_INT_CONST || curr_type == LEX_REAL_CONST || curr_type == LEX_STRING_CONST) {

                prog.push_back(Lex(POLIZ_ADDRESS, curr_ident));

                prog.push_back(curr_lex);

                push_const();

                eq_type();

                prog.push_back(Lex(LEX_SEMICOLON));

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

        int else_lp, from_lp;

        gl();

        if (curr_type == LEX_LPAREN) {

            gl();

            E();

            st.pop();

            else_lp = prog.size();

            prog.push_back(Lex());

            prog.push_back(Lex(POLIZ_FGO));
        }
        else throw curr_lex;

        if (curr_type == LEX_RPAREN) {

            gl();

            S();

            from_lp = prog.size();

            prog.push_back(Lex());

            prog.push_back(Lex(POLIZ_GO));
        }
        else throw curr_lex;

        if (curr_type == LEX_ELSE) {

            gl();

            prog[else_lp] = Lex(POLIZ_LABEL, prog.size());

            S();

            prog[from_lp] = Lex(POLIZ_LABEL, prog.size());
        }
        else throw curr_lex;
    }
    else if (curr_type == LEX_WHILE) {

        int continue_l, break_lp;

        gl();

        if (curr_type == LEX_LPAREN) {

            gl();

            continue_l = prog.size();

            continue_st.push(continue_l);

            E();

            st.pop();

            break_lp = prog.size();

            prog.push_back(Lex());

            prog.push_back(Lex(POLIZ_FGO));
        }
        else throw curr_lex;

        if (curr_type == LEX_RPAREN) {

            gl();

            S();

            prog.push_back(Lex(POLIZ_LABEL, continue_l));

            prog.push_back(Lex(POLIZ_GO));

            prog[break_lp] = Lex(POLIZ_LABEL, prog.size());
        }
        else throw curr_lex;

        continue_st.pop();

    }
    else if (curr_type == LEX_FOR) {

        int continue_l, condition_l, iter_lp, break_lp;

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

            st.pop();

            prog.push_back(Lex(LEX_SEMICOLON));

            if (curr_type == LEX_SEMICOLON) {

                gl();
            }
            else throw curr_lex;
        }
        condition_l = prog.size();

        if (curr_type == LEX_SEMICOLON) {

            prog.push_back(Lex(LEX_INT_CONST, 1));

            gl();
        }
        else {

            E();

            st.pop();

            if (curr_type == LEX_SEMICOLON) {

                gl();
            }
            else throw curr_lex;
        }
        break_lp = prog.size();

        prog.push_back(Lex());

        prog.push_back(Lex(POLIZ_FGO));

        iter_lp = prog.size();

        prog.push_back(Lex());

        prog.push_back(Lex(POLIZ_GO));

        continue_l = prog.size();

        continue_st.push(continue_l);

        if (curr_type == LEX_RPAREN) {

            gl();
        }
        else {

            E();

            st.pop();

            prog.push_back(Lex(LEX_SEMICOLON));

            if (curr_type == LEX_RPAREN) {

                gl();
            }
            else throw curr_lex;
        }
        prog.push_back(Lex(POLIZ_LABEL, condition_l));

        prog.push_back(Lex(POLIZ_GO));

        prog[iter_lp] = Lex(POLIZ_LABEL, prog.size());

        S();

        prog.push_back(Lex(POLIZ_LABEL, continue_l));

        prog.push_back(Lex(POLIZ_GO));

        prog[break_lp] = Lex(POLIZ_LABEL, prog.size());

        continue_st.pop();
    }
    else if (curr_type == LEX_CONTINUE) {

        if(continue_st.is_empty()) throw "unexpected continue";

        int continue_l = continue_st.pop();

        continue_st.push(continue_l);

        prog.push_back(Lex(POLIZ_LABEL, continue_l));

        prog.push_back(Lex(POLIZ_GO));

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

            prog.push_back(Lex(POLIZ_ADDRESS, curr_int_value));

            prog.push_back(Lex(LEX_READ));

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

        st.pop();

        prog.push_back(Lex(LEX_WRITE));

        while (curr_type == LEX_COMMA) {

            gl();

            E();

            st.pop();

            prog.push_back(Lex(LEX_WRITE));
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

        st.pop();

        prog.push_back(Lex(LEX_SEMICOLON));

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

        st.push(curr_type);

        gl();

        E();

        eq_type();
    }
}

void Parser::O() {

    A();

    while (curr_type == LEX_OR) {

        l_value_flag = false;

        st.push(curr_type);

        gl();

        A();

        check_O();
    }
}

void Parser::A() {

    L();

    while (curr_type == LEX_AND) {

        l_value_flag = false;

        st.push(curr_type);

        gl();

        L();

        check_A();
    }
}

void Parser::L() {

    E1();

    while (curr_type == LEX_EQ || curr_type == LEX_NEQ || curr_type == LEX_GTR || curr_type == LEX_GEQ || curr_type == LEX_LSS || curr_type == LEX_LEQ) {

        l_value_flag = false;

        st.push(curr_type);

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

        st.push(curr_type);

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

        prog.push_back(curr_lex);

        gl();
    }
    else if(curr_type == LEX_ID) {

        check_id();

        st.push(Scanner::TID[curr_int_value].get_type());

        prog.push_back(Lex(POLIZ_ADDRESS, curr_int_value));

        gl();
    }
    else throw curr_lex;
}

void Parser::check_id() {

    if(!Scanner::TID[curr_int_value].get_declare()) throw "ID is not declared";
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

    type_of_lex r_value = st.pop(), operation = st.pop(), l_value = st.pop();

    if (l_value == LEX_INT) {

        if(r_value == LEX_STRING) throw "Different types in = !";

        st.push(l_value);

        prog.push_back(Lex(operation));
    }
    else if (l_value == LEX_REAL) {

        if(r_value == LEX_STRING) throw "Different types in = !";

        st.push(l_value);

        prog.push_back(Lex((type_of_lex)(operation + REAL_OFFSET)));
    }
    else if (l_value == LEX_STRING || r_value == LEX_STRING) {

      st.push(l_value);

      prog.push_back(Lex((type_of_lex)(operation + STRING_OFFSET)));
    }
    else throw "Different types in = !";
}

void Parser::check_O() {

    type_of_lex operand1 = st.pop(), operation = st.pop(), operand2 = st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT) {

        st.push(LEX_INT);

        prog.push_back(Lex(operation));
    }
    else throw "Wrong types in operation";
}

void Parser::check_A() {

    type_of_lex operand1 = st.pop(), operation = st.pop(), operand2 = st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT) {

        st.push(LEX_INT);

        prog.push_back(Lex(operation));
    }
    else throw "Wrong types in operation";
}

void Parser::check_L() {

    type_of_lex operand1 = st.pop(), operation = st.pop(), operand2 = st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT) {

        st.push(LEX_INT);

        prog.push_back(Lex(operation));
    }
    else if (operand1 == LEX_STRING && operand2 == LEX_STRING) {

        st.push(LEX_INT);

        prog.push_back(Lex((type_of_lex)(operation + STRING_OFFSET)));
    }
    else if (operand1 == LEX_STRING || operand2 == LEX_STRING) throw "Wrong types in operation";

    else {

        st.push(LEX_INT);

        prog.push_back(Lex((type_of_lex)(operation + REAL_OFFSET)));
    }
}

void Parser::check_E1() {

    type_of_lex operand1 = st.pop(), operation = st.pop(), operand2 = st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT) {

        st.push(LEX_INT);

        prog.push_back(Lex(operation));
    }
    else if (operand1 == LEX_STRING && operand2 == LEX_STRING) {

        if(operation != LEX_PLUS) throw "Wrong types in operation";

        st.push(LEX_STRING);

        prog.push_back(Lex((type_of_lex)(operation + STRING_OFFSET)));
    }
    else if (operand1 == LEX_STRING || operand2 == LEX_STRING) throw "Wrong types in operation";

    else {

        st.push(LEX_REAL);

        prog.push_back(Lex((type_of_lex)(operation + REAL_OFFSET)));
    }
}

void Parser::check_T() {

    type_of_lex operand1 = st.pop(), operation = st.pop(), operand2 = st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT) {

        st.push(LEX_INT);

        prog.push_back(Lex(operation));
    }
    else if (operand1 == LEX_STRING || operand2 == LEX_STRING) throw "Wrong types in operation";

    else {

        st.push(LEX_REAL);

        prog.push_back(Lex((type_of_lex)(operation + REAL_OFFSET)));
    }
}

void Parser::check_N() {

    type_of_lex operand = st.pop(), operation = st.pop();

    if(operand == LEX_STRING) throw "Wrong types in operation";

    else if(operation == LEX_NOT) {

        if(operand != LEX_INT) throw "Wrong types in operation";

        st.push(LEX_INT);

        prog.push_back(Lex(operation));
    }
    else {

        if(operand == LEX_INT) {

          st.push(LEX_INT);

          prog.push_back(Lex((type_of_lex)(operation + UNARY)));
        }

        else {

            st.push(LEX_REAL);

            prog.push_back(Lex((type_of_lex)(operation + REAL_OFFSET + UNARY)));
        }
    }
}

Parser::Parser(const char* buf) : scan(buf), prog(1000) {}

void Parser::analyze() {

    gl();

    P();

    //std::cout << "SUCCESS" <<std::endl;
}
