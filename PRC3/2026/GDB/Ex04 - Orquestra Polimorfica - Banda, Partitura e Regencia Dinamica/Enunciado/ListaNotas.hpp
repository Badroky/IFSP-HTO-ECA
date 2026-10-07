#ifndef _LISTA_NOTAS_HPP_
#define _LISTA_NOTAS_HPP_

#include "Nota.hpp"

class NoNota {
private:
    Nota _dado;
    NoNota* _prox;

    NoNota(Nota n) : _dado(n), _prox(nullptr) {}
    friend class ListaNotas;
};

class ListaNotas {
private:
    NoNota* _inicio;
    NoNota* _fim;
    NoNota* _cursor;

public:
    ListaNotas();
    ~ListaNotas();
    void inserir(Nota n);
    void reiniciar();
    bool temProxima() const;
    Nota proxima();
};

#endif
