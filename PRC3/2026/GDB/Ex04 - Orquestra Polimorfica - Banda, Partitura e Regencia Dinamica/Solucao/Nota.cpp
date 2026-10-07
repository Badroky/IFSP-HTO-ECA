#include "Nota.hpp"

Nota::Nota(string tom, int duracao, string filtro)
    : _tom(tom), _duracao(duracao), _filtro(filtro) {
}

string Nota::getTom() const {
    return _tom;
}

int Nota::getDuracao() const {
    return _duracao;
}

string Nota::getFiltro() const {
    return _filtro;
}
