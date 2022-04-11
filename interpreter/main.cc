#include "lex.h"
#include "parser.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    try {

        Parser pars(argv[1]);

        pars.analyze();

        return 0;
    }
    catch (char c) {

        cout << "unexpected symbol " << c << endl;

        return 1;
    }
    catch (Lex l) {

        cout << "unexpected lexeme " << l << endl;

        return 1;
    }
    catch (const char* str) {

        cout << "(WTF?) " << str << endl;

        return 1;
    }
}
