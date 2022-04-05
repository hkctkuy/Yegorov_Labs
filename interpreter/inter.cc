#include "lex.h"
#include "scanner.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    try {

        Scanner scan(argv[1]); Lex l;

        while ((l = scan.get_lex()).get_type() != LEX_FIN) { cout << l << endl; }

        return 0;
    }
    catch (char c) {

        cout << "unexpected symbol " << c << endl;

        return 1;
    }
    catch (Lex l) {

        cout << "unexpected lexeme" << l << endl;

        return 1;
    }
    catch (const char* str) {

        cout << "(WTF?) " << str << endl;

        return 1;
    }
}
