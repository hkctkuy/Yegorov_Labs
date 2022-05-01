#include "executer.h"

void Executer::execute(Poliz& poliz) {

    //std::cout << "EXECUTE" << std::endl;

    int size = poliz.size(), index = 0;

    int id, cmp, n;

    int int_operand1, int_operand2;

    float real_operand1,  real_operand2;

    int str_operand1, str_operand2;

    char* str1; char* str2; char* strsum;

    type_of_lex type;

    while (index < size) {

        Lex el = poliz[index++];

        switch (el.get_type()) {
// Putting values to stack
            case LEX_INT_CONST: case LEX_STRING_CONST: case POLIZ_ADDRESS: case POLIZ_LABEL:

                st.push(el.get_value());

                break;

            case LEX_REAL_CONST:

                st.push(el.get_real_value());

                break;

            case LEX_ID:

                id = el.get_value();

                if (!Scanner::TID[id].get_assign()) throw "ID is not assigned";

                if (Scanner::TID[id].get_type() == LEX_REAL) {

                    st.push(Scanner::TID[id].get_real_value());
                }
                else {

                    st.push(Scanner::TID[id].get_value());
                }
                break;
// Assign operations
            case LEX_ASSIGN:

                int_operand1 = st.int_pop(); id = st.int_pop();

                Scanner::TID[id].set_value(int_operand1);

                Scanner::TID[id].put_assign();

                st.push(Scanner::TID[id].get_value());

                //std::cout << Scanner::TID[id].get_value() << std::endl;

                break;

            case LEX_R_ASSIGN:

                real_operand1 = st.real_pop(); id = st.int_pop();

                Scanner::TID[id].set_real_value(real_operand1);

                Scanner::TID[id].put_assign();

                st.push(Scanner::TID[id].get_real_value());

                //std::cout << Scanner::TID[id].get_real_value() << std::endl;

                break;

            case LEX_S_ASSIGN:

                str_operand1 = st.int_pop(); id = st.int_pop();

                Scanner::TID[id].set_value(str_operand1);

                Scanner::TID[id].put_assign();

                st.push(Scanner::TID[id].get_value());

                //std::cout << Scanner::TID[id].get_value() << ' ' << Scanner::TCS[Scanner::TID[id].get_value()] << std::endl;

                break;
// Comparison operations
            case LEX_EQ:

                int_operand2 = st.int_pop(); int_operand1 = st.int_pop();

                st.push((int)(int_operand1 == int_operand2));

                //std::cout << (int)(int_operand1 == int_operand2) << std::endl;

                break;

            case LEX_R_EQ:

                real_operand2 = st.real_pop(); real_operand1 = st.real_pop();

                st.push((int)(real_operand1 == real_operand2));

                //std::cout << (int)(real_operand1 == real_operand2) << std::endl;

                break;

            case LEX_S_EQ:

                str_operand2 = st.int_pop(); str_operand1 = st.int_pop();

                str1 = Scanner::TCS[str_operand1]; str2 = Scanner::TCS[str_operand2];

                cmp = strcmp(str1, str2);

                st.push((int)(cmp == 0));

                //std::cout << (int)(cmp == 0) << std::endl;

                break;

            case LEX_NEQ:

                int_operand2 = st.int_pop(); int_operand1 = st.int_pop();

                st.push((int)(int_operand1 != int_operand2));

                //std::cout << (int)(int_operand1 != int_operand2) << std::endl;

                break;

            case LEX_R_NEQ:

                real_operand2 = st.real_pop(); real_operand1 = st.real_pop();

                st.push((int)(real_operand1 != real_operand2));

                //std::cout << (int)(real_operand1 != real_operand2) << std::endl;

                break;

            case LEX_S_NEQ:

                str_operand2 = st.int_pop(); str_operand1 = st.int_pop();

                str1 = Scanner::TCS[str_operand1]; str2 = Scanner::TCS[str_operand2];

                cmp = strcmp(str1, str2);

                st.push((int)(cmp != 0));

                //std::cout << (int)(cmp != 0) << std::endl;

                break;

            case LEX_LSS:

                int_operand2 = st.int_pop(); int_operand1 = st.int_pop();

                st.push((int)(int_operand1 < int_operand2));

                //std::cout << (int)(int_operand1 < int_operand2) << std::endl;

                break;

            case LEX_R_LSS:

                real_operand2 = st.real_pop(); real_operand1 = st.real_pop();

                st.push((int)(real_operand1 < real_operand2));

                //std::cout << (int)(real_operand1 < real_operand2) << std::endl;

                break;

            case LEX_S_LSS:

                str_operand2 = st.int_pop(); str_operand1 = st.int_pop();

                str1 = Scanner::TCS[str_operand1]; str2 = Scanner::TCS[str_operand2];

                cmp = strcmp(str1, str2);

                st.push((int)(cmp < 0));

                //std::cout << (int)(cmp < 0) << std::endl;

                break;

            case LEX_GTR:

                int_operand2 = st.int_pop(); int_operand1 = st.int_pop();

                st.push((int)(int_operand1 > int_operand2));

                //std::cout << (int)(int_operand1 > int_operand2) << std::endl;

                break;

            case LEX_R_GTR:

                real_operand2 = st.real_pop(); real_operand1 = st.real_pop();

                st.push((int)(real_operand1 > real_operand2));

                //std::cout << (int)(real_operand1 > real_operand2) << std::endl;

                break;

            case LEX_S_GTR:

                str_operand2 = st.int_pop(); str_operand1 = st.int_pop();

                str1 = Scanner::TCS[str_operand1]; str2 = Scanner::TCS[str_operand2];

                cmp = strcmp(str1, str2);

                st.push((int)(cmp > 0));

                //std::cout << (int)(cmp > 0) << std::endl;

                break;

            case LEX_LEQ:

                int_operand2 = st.int_pop(); int_operand1 = st.int_pop();

                st.push((int)(int_operand1 <= int_operand2));

                //std::cout << (int)(int_operand1 <= int_operand2) << std::endl;

                break;

            case LEX_R_LEQ:

                real_operand2 = st.real_pop(); real_operand1 = st.real_pop();

                st.push((int)(real_operand1 <= real_operand2));

                //std::cout << (int)(real_operand1 <= real_operand2) << std::endl;

                break;

            case LEX_S_LEQ:

                str_operand2 = st.int_pop(); str_operand1 = st.int_pop();

                str1 = Scanner::TCS[str_operand1]; str2 = Scanner::TCS[str_operand2];

                cmp = strcmp(str1, str2);

                st.push((int)(cmp <= 0));

                //std::cout << (int)(cmp <= 0) << std::endl;

                break;

            case LEX_GEQ:

                int_operand2 = st.int_pop(); int_operand1 = st.int_pop();

                st.push((int)(int_operand1 >= int_operand2));

                //std::cout << (int)(int_operand1 >= int_operand2) << std::endl;

                break;

            case LEX_R_GEQ:

                real_operand2 = st.real_pop(); real_operand1 = st.real_pop();

                st.push((int)(real_operand1 >= real_operand2));

                //std::cout << (int)(real_operand1 >= real_operand2) << std::endl;

                break;

            case LEX_S_GEQ:

                str_operand2 = st.int_pop(); str_operand1 = st.int_pop();

                str1 = Scanner::TCS[str_operand1]; str2 = Scanner::TCS[str_operand2];

                cmp = strcmp(str1, str2);

                st.push((int)(cmp >= 0));

                //std::cout << (int)(cmp >= 0) << std::endl;

                break;
// Arithmetic operations
            case LEX_PLUS:

                int_operand2 = st.int_pop(); int_operand1 = st.int_pop();

                st.push(int_operand1 + int_operand2);

                //std::cout << int_operand1 + int_operand2 << std::endl;

                break;

            case LEX_R_PLUS:

                real_operand2 = st.real_pop(); real_operand1 = st.real_pop();

                st.push(real_operand1 + real_operand2);

                //std::cout << real_operand1 + real_operand2 << std::endl;

                break;

            case LEX_MINUS:

                int_operand2 = st.int_pop(); int_operand1 = st.int_pop();

                st.push(int_operand1 - int_operand2);

                //std::cout << int_operand1 - int_operand2 << std::endl;

                break;

            case LEX_R_MINUS:

                real_operand2 = st.real_pop(); real_operand1 = st.real_pop();

                st.push(real_operand1 - real_operand2);

                //std::cout << real_operand1 - real_operand2 << std::endl;

                break;

            case LEX_TIMES:

                int_operand2 = st.int_pop(); int_operand1 = st.int_pop();

                st.push(int_operand1 * int_operand2);

                //std::cout << int_operand1 * int_operand2 << std::endl;

                break;

            case LEX_R_TIMES:

                real_operand2 = st.real_pop(); real_operand1 = st.real_pop();

                st.push(real_operand1 * real_operand2);

                //std::cout << real_operand1 * real_operand2 << std::endl;

                break;

            case LEX_SLASH:

                int_operand2 = st.int_pop(); int_operand1 = st.int_pop();

                st.push(int_operand1 / int_operand2);

                //std::cout << int_operand1 / int_operand2 << std::endl;

                break;

            case LEX_R_SLASH:

                real_operand2 = st.real_pop(); real_operand1 = st.real_pop();

                st.push(real_operand1 / real_operand2);

                //std::cout << real_operand1 / real_operand2 << std::endl;

                break;

            case LEX_U_PLUS:

                int_operand1 = st.int_pop();

                st.push(int_operand1);

                //std::cout << int_operand1 << std::endl;

                break;

            case LEX_U_R_PLUS:

                real_operand1 = st.real_pop();

                st.push(real_operand1);

                //std::cout << real_operand1 << std::endl;

                break;

            case LEX_U_MINUS:

                int_operand1 = st.int_pop();

                st.push(- int_operand1);

                //std::cout << - int_operand1 << std::endl;

                break;

            case LEX_U_R_MINUS:

                real_operand1 = st.real_pop();

                st.push(-real_operand1);

                //std::cout << -real_operand1 << std::endl;

                break;

            case LEX_S_PLUS:

                str_operand2 = st.int_pop(); str_operand1 = st.int_pop();

                str1 = Scanner::TCS[str_operand1]; str2 = Scanner::TCS[str_operand2];

                strsum = cat(str1, str2);

                n = Scanner::TCS.put(strsum);

                st.push(n);

                //std::cout << n << " " << Scanner::TCS[n] << std::endl;

                break;
// Logic operations
            case LEX_OR:

                int_operand2 = st.int_pop(); int_operand1 = st.int_pop();

                st.push((int)(int_operand1 || int_operand2));

                //std::cout << (int)(int_operand1 || int_operand2) << std::endl;

                break;

            case LEX_AND:

                int_operand2 = st.int_pop(); int_operand1 = st.int_pop();

                st.push((int)(int_operand1 && int_operand2));

                //std::cout << (int)(int_operand1 && int_operand2) << std::endl;

                break;

            case LEX_NOT:

                int_operand1 = st.int_pop();

                st.push((int)(!int_operand1));

                //std::cout << (int)(!int_operand1) << std::endl;

                break;
// Transer
            case POLIZ_GO:

                index = st.int_pop();

                //std::cout << "goto " << index << std::endl;

                break;

            case POLIZ_FGO:

                int_operand1 = st.int_pop(); int_operand2 = st.int_pop();

                if(!int_operand2) {

                    index = int_operand1;

                    //std::cout << "goto " << index << std::endl;
                }
                break;
// Input/output statement
            case LEX_READ:

                id = st.int_pop(); type = Scanner::TID[id].get_type();

                if (type == LEX_INT) {

                    std::cin >> int_operand1;

                    Scanner::TID[id].set_value(int_operand1);

                    Scanner::TID[id].put_assign();

                    //std::cout << Scanner::TID[id].get_value() << std::endl;
                }
                else if (type == LEX_REAL) {

                    std::cin >> real_operand1;

                    Scanner::TID[id].set_real_value(real_operand1);

                    Scanner::TID[id].put_assign();

                    //std::cout << Scanner::TID[id].get_real_value() << std::endl;
                }
                else {

                    read_str(str1);

                    n = Scanner::TCS.put(str1);

                    Scanner::TID[id].set_value(n);

                    Scanner::TID[id].put_assign();

                    //std::cout << n << " " << Scanner::TCS[n] << std::endl;
                }
                break;

            case LEX_WRITE:

                std::cout << st.int_pop() << std::endl;

                break;

            case LEX_R_WRITE:

                std::cout << st.real_pop() << std::endl;

                break;

            case LEX_S_WRITE:

                std::cout << Scanner::TCS[st.int_pop()] << std::endl;

                break;
// Clearing execute stack top
            case LEX_SEMICOLON:

                st.int_pop();

                break;

            default:

                throw "executer dumped";
        }
    }
}

Ex_Stack::Ex_Stack() {

    top = NULL;
}

Ex_Stack::~Ex_Stack() {

    while (!is_empty()) {

        if (top->value == INT) {

            int_pop();
        }
        else {

            real_pop();
        }
    }
}

bool Ex_Stack::is_empty() const {

    if (top == NULL) return true;

    else return false;
}

void Ex_Stack::push(int v) {

    chain* new_chain = new chain;

    new_chain->value = INT;

    new_chain->next = top;

    top = new_chain;

    st_int.push(v);
}

void Ex_Stack::push(float v) {

    chain* new_chain = new chain;

    new_chain->value = REAL;

    new_chain->next = top;

    top = new_chain;

    st_real.push(v);
}

int Ex_Stack::int_pop() {

    if (is_empty()) throw "Stack is empty";

    type t = top->value;

    chain* pop_chain = top;

    top = top->next;

    delete pop_chain;

    int res;

    if (t == INT) res = st_int.pop();

    else res = st_real.pop();

    return res;
}

float Ex_Stack::real_pop() {

    if (is_empty()) throw "Stack is empty";

    type t = top->value;

    chain* pop_chain = top;

    top = top->next;

    delete pop_chain;

    float res;

    if (t == INT) res = st_int.pop();

    else res = st_real.pop();

    return res;
}

char* cat(const char* str1, const char* str2) {

    char* res = new char[strlen(str1) + strlen(str2)];

    strcpy(res, str1); strcat(res, str2);

    return res;
}

void read_str(char*& buf) {

    buf = new char[MAX_STR_SIZE];

    std::cin >> buf;
}
