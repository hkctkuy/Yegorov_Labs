#include "poliz.h"

Poliz::Poliz(int max) {

    p = new Lex[max_size = max];

    curr_size = 0;
}

Poliz::~Poliz() {

    delete [] p;
}

void Poliz::push_back(Lex l) {

    p[curr_size++] = l;
}

int Poliz::size() const { return curr_size; }

Lex& Poliz::operator[](int i) { return p[i]; }

std::ostream& operator<<(std::ostream& out, Poliz& poliz) {

    out << "POLIZ" << std::endl;

    for (int i = 0; i < poliz.curr_size; i++) {

        out << i << ' ' << poliz.p[i] << std::endl;
    }
    return out;
}
