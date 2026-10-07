#ifndef _SOPRO_HPP_
#define _SOPRO_HPP_

#include "Musico.hpp"

class Sopro : public Musico {
public:
    Sopro(string nome, string instrumento);
    char getTipo() const override;
    void tocar(const Nota& n) override;
};

#endif
