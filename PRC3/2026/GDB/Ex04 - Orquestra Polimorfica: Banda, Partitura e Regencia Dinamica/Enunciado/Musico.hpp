#ifndef _MUSICO_HPP_
#define _MUSICO_HPP_

#include <iostream>
#include <string>
#include "Nota.hpp"

using namespace std;

class Musico {
private:
    string _nome;
    string _instrumento;

public:
    Musico(string nome, string instrumento);
    virtual ~Musico() {}
    string getNome() const;
    string getInstrumento() const;
    virtual char getTipo() const = 0;
    virtual void tocar(const Nota& n) = 0;
};

#endif
