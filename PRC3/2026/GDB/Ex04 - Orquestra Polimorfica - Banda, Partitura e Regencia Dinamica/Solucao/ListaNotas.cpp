#include "ListaNotas.hpp"

ListaNotas::ListaNotas() : _inicio(nullptr), _fim(nullptr), _cursor(nullptr) {
}

ListaNotas::~ListaNotas() {
    NoNota* atual = _inicio;
    while (atual != nullptr) {
        NoNota* prox = atual->_prox;
        delete atual;
        atual = prox;
    }
}

void ListaNotas::inserir(Nota n) {
    NoNota* novo = new NoNota(n);
    if (_inicio == nullptr) {
        _inicio = novo;
        _fim = novo;
        _cursor = novo;
    } else {
        _fim->_prox = novo;
        _fim = novo;
    }
}

void ListaNotas::reiniciar() {
    _cursor = _inicio;
}

bool ListaNotas::temProxima() const {
    return _cursor != nullptr;
}

Nota ListaNotas::proxima() {
    if (_cursor == nullptr) {
        return Nota("", 0, "");
    }
    Nota n = _cursor->_dado;
    _cursor = _cursor->_prox;
    return n;
}
