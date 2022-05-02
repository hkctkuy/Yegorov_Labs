#include "interpreter.h"

Interpreter::Interpreter(const char* prog): pars(prog) {}

int Interpreter::interpretation() {

    try {

        pars.analyze();

        //std::cout << pars.poliz << std::endl;

        exec.execute(pars.poliz);

        return 0;
    }
    catch (char c) {

        std::cout << "unexpected symbol " << c << std::endl;

        return 1;
    }
    catch (Lex l) {

        std::cout << "unexpected lexeme " << l << std::endl;

        return 1;
    }
    catch (const char* str) {

        std::cout << str << std::endl;

        return 1;
    }
    catch(...) {

        std::cout << "unexpected error" << std::endl;

        return 1;
    }
}
