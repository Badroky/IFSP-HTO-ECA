#ifndef _BANDA_HPP_
#define _BANDA_HPP_

#include <string>
#include "Musico.hpp"

class NoMusico {
private:
    Musico* _musico;
    NoMusico* _prox;

    NoMusico(Musico* m) : _musico(m), _prox(nullptr) {}
    friend class Banda;
};

class Banda {
private:
    string _nome;
    NoMusico* _inicio;
    NoMusico* _fim;

public:
    Banda(string nome);
    ~Banda();
    void adicionarMusico(Musico* m);
    void tocarNota(const Nota& n);
    string getNome() const;
};

#endif
