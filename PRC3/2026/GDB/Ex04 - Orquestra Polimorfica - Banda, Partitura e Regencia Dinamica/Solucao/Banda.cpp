#include <iostream>
#include "Banda.hpp"

using namespace std;

Banda::Banda(string nome) : _nome(nome), _inicio(nullptr), _fim(nullptr) {
}

Banda::~Banda() {
    NoMusico* atual = _inicio;
    while (atual != nullptr) {
        NoMusico* prox = atual->_prox;
        delete atual->_musico;
        delete atual;
        atual = prox;
    }
}

void Banda::adicionarMusico(Musico* m) {
    NoMusico* novo = new NoMusico(m);
    if (_inicio == nullptr) {
        _inicio = novo;
        _fim = novo;
    } else {
        _fim->_prox = novo;
        _fim = novo;
    }
}

void Banda::tocarNota(const Nota& n) {
    string filtro = n.getFiltro();
    NoMusico* atual = _inicio;
    while (atual != nullptr) {
        if (atual->_musico != nullptr) {
            char tipo = atual->_musico->getTipo();
            if (filtro.find(tipo) != string::npos) {
                atual->_musico->tocar(n);
            }
        }
        atual = atual->_prox;
    }
}

string Banda::getNome() const {
    return _nome;
}
