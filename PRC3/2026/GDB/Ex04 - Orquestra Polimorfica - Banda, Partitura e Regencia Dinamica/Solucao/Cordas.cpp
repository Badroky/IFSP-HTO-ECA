#include <iostream>
#include "Cordas.hpp"

using namespace std;

Cordas::Cordas(string nome, string instrumento)
    : Musico(nome, instrumento) {
}

char Cordas::getTipo() const {
    return 'C';
}

void Cordas::tocar(const Nota& n) {
    cout << "[Cordas] " << getNome() << " dedilhou " << n.getTom()
         << " no(a) " << getInstrumento() << " por " << n.getDuracao() << " tempos." << endl;
}
