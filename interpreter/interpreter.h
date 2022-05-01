#pragma once

#include "lex.h"
#include "parser.h"
#include "executer.h"

class Interpreter {

    Parser pars;

    Executer exec;

public:

    Interpreter(const char*);

    int interpretation();
};
