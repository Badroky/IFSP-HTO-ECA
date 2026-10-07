#include "Musico.hpp"

Musico::Musico(string nome, string instrumento)
    : _nome(nome), _instrumento(instrumento) {
}

string Musico::getNome() const {
    return _nome;
}

string Musico::getInstrumento() const {
    return _instrumento;
}
