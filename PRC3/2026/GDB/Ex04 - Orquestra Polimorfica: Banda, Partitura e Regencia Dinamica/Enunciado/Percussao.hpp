#ifndef _PERCUSSAO_HPP_
#define _PERCUSSAO_HPP_

#include "Musico.hpp"

class Percussao : public Musico {
public:
    Percussao(string nome, string instrumento);
    char getTipo() const override;
    void tocar(const Nota& n) override;
};

#endif
