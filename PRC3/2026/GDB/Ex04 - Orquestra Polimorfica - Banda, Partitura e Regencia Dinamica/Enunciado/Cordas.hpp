#ifndef _CORDAS_HPP_
#define _CORDAS_HPP_

#include "Musico.hpp"

class Cordas : public Musico {
public:
    Cordas(string nome, string instrumento);
    char getTipo() const override;
    void tocar(const Nota& n) override;
};

#endif
