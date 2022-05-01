#include "interpreter.h"

int main(int argc, char** argv) {

    Interpreter inter(argv[1]);

    return inter.interpretation();
}
