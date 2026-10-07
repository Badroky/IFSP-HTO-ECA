#ifndef _MAESTRO_HPP_
#define _MAESTRO_HPP_

#include <string>
#include "Banda.hpp"
#include "Musica.hpp"

using namespace std;

class Maestro {
private:
    string _nome;

public:
    Maestro(string nome);
    void reger(Banda* banda, Musica* musica);
    string getNome() const;
};

#endif
