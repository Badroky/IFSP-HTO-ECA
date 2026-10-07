#ifndef _MUSICA_HPP_
#define _MUSICA_HPP_

#include <string>
#include "ListaNotas.hpp"

using namespace std;

class Musica {
private:
    string _titulo;
    ListaNotas _partitura;

public:
    Musica(string titulo);
    void adicionarNota(string tom, int duracao, string filtro);
    string getTitulo() const;
    void reiniciarPartitura();
    bool temProximaNota() const;
    Nota proximaNota();
};

#endif
