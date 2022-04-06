#include "scanner.h"

#define MAX_NAME_LEN 80

Table_Ident Scanner::TID(100);

const char* Scanner::TW[] = { "", "and", "begin", "bool", "continue", "do", "else", "end", "false", "for", "if", "int",
                           "not", "or", "program", "read", "real", "string", "then", "true", "var", "while", "write", NULL };

const char* Scanner::TD[] = { "", "@ was here before", ";", ",", ":", ":=", "(", ")", "{", "}", "=", "<", ">", "+", "++", "-", "--", "*", "/", "<=", "!=", ">=", NULL };

Scanner::Scanner(const char* program) {

    if (!(fp = fopen(program, "r"))) {

        throw  "can’t open file";
    }
}

void Scanner::gc() { c = fgetc(fp); }

int Scanner::look(const char* buf, const char** list) {

    int i = 0;

    while (list[i]) {

        if (!strcmp(buf, list[i])) {

            return i;
        }
        i++;
    }
    return 0;
}

Lex Scanner::get_lex() {

    enum state { H, IDENT, NUMB, REAL, STR, SLASH, COM, ALE, PLUS, MINUS, NEQ};

    state CS = H;

    int d, n, p, minus_flag = 1; float f; char buf[MAX_NAME_LEN]; int buf_top = 0;

    for (int i = 0; i < MAX_NAME_LEN; i++) { buf[i] = '\0'; }

    do {

        gc();

        switch (CS) {

        case H:

            if (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
            }
            else if (isalpha(c)) {

                buf[buf_top++] = c;

                CS = IDENT;
            }
            else if (isdigit(c)) {

                d = c - '0';

                CS = NUMB;
            }
            else if (c == '"') {

                CS = STR;
            }
            else if (c == '/') {

                CS = SLASH;
            }
            else if (c == ':' || c == '<' || c == '>') {

                buf[buf_top++] = c;

                CS = ALE;
            }
            else if (c == '+') {

                buf[buf_top++] = c;

                CS = PLUS;
            }
            else if (c == '-') {

                buf[buf_top++] = c;

                CS = MINUS;
            }
            else if (c == '!') {

                buf[buf_top++] = c;

                CS = NEQ;
            }
            else if (c == EOF) {

                return Lex(LEX_FIN);
            }
            else {

                buf[buf_top++] = c;

                if ((n = look(buf, TD))) { return Lex((type_of_lex)(n + LEX_FIN)); }

                else { throw c; }
            }
            break;
        case IDENT:

            if (isalpha(c) || isdigit(c)) {

                buf[buf_top++] = c;
            }
            else {

                ungetc(c, fp);

                if ((n = look(buf, TW))) {

                    return Lex((type_of_lex)n);
                }
                else {

                    n = TID.put(buf);

                    TID[n].set_name(buf);

                    return Lex(LEX_ID, n);
                }
            }
            break;

        case NUMB:

            if (isdigit(c)) {

                d = d * 10 + (c - '0');
            }
            else if(c == '.') {

                f = d; p = 1;

                CS = REAL;
            }
            else {
                ungetc(c, fp);

                d *= minus_flag;

                return Lex(LEX_INT, d);
            }
            break;

        case REAL:

            if (isdigit(c)) {

                f += (c - '0') / pow(10, p++);
            }
            else {

                ungetc(c, fp);

                f *= minus_flag;

                return Lex(LEX_REAL, f);
        }
            break;

        case STR:

            if (c == '"') {

                return Lex(LEX_STRING, buf);
            }
            else if (c == EOF) {

                throw "Bed String";
            }
            else {

                buf[buf_top++] = c;
            }
            break;

        case SLASH:

            if (c == '*') {

                CS = COM;
            }
            else {

                ungetc(c, fp);

                buf[buf_top++] = '/';

                n = look(buf, TD);

                return Lex((type_of_lex)(n + LEX_FIN));
            }
            break;

        case COM:

            if (c == '*') {

                gc();

                if (c == '/') {

                    CS = H;
                }
            }
            else if (c == EOF) {

                throw "Bad comment";
            }
            break;

        case ALE:

            if (c == '=') {

                buf[buf_top++] = c;

                n = look(buf, TD);

                return Lex((type_of_lex)(n + LEX_FIN));
            }
            else {

                ungetc(c, fp);

                n = look(buf, TD);

                return Lex((type_of_lex)(n + LEX_FIN));
            }
            break;

        case PLUS:

            if (c == '+') {

                buf[buf_top++] = c;

                n = look(buf, TD);

                return Lex((type_of_lex)(n + LEX_FIN));
            }
            else if (isdigit(c)) {

                d = c - '0';

                CS = NUMB;
            }
            else {

                ungetc(c, fp);

                n = look(buf, TD);

                return Lex((type_of_lex)(n + LEX_FIN));
            }
            break;

        case MINUS:

            if (c == '-') {

                buf[buf_top++] = c;

                n = look(buf, TD);

                return Lex((type_of_lex)(n + LEX_FIN));
            }
            else if (isdigit(c)) {

                d = (c - '0'); minus_flag = -1;

                CS = NUMB;
            }
            else {

                ungetc(c, fp);

                n = look(buf, TD);

                return Lex((type_of_lex)(n + LEX_FIN));
            }
            break;

        case NEQ:

            if (c == '=') {

                buf[buf_top++] = c;

                n = look(buf, TD);

                return Lex(LEX_NEQ);
            }
            else {
                throw '!';
            }
            break;
        }
    } while (true);
}

std::ostream& operator<<(std::ostream& out, Lex l) {

    if (l.type == LEX_ID) { out << "(TID) " << l.int_value << ' ' << Scanner::TID[l.int_value].get_name(); }

    else if (l.type < LEX_FIN) { out << "(TW) " << Scanner::TW[l.type] << ' '; }

    else { out << "(TD) " << Scanner::TD[l.type - LEX_FIN] << ' '; }

    if (l.type == LEX_INT) { out << l.int_value; }

    else if (l.type == LEX_REAL) { out << l.real_value; }

    else if (l.type == LEX_STRING) { out << l.str_value; }

    return out;
}
