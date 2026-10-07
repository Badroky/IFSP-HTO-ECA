#include <iostream>
#include "Sopro.hpp"

using namespace std;

Sopro::Sopro(string nome, string instrumento)
    : Musico(nome, instrumento) {
}

char Sopro::getTipo() const {
    return 'S';
}

void Sopro::tocar(const Nota& n) {
    cout << "[Sopro] " << getNome() << " soprou " << n.getTom()
         << " no(a) " << getInstrumento() << " por " << n.getDuracao() << " tempos." << endl;
}
