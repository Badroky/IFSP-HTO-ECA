#ifndef _NOTA_HPP_
#define _NOTA_HPP_

#include <string>

using namespace std;

class Nota {
private:
    string _tom;
    int _duracao;
    string _filtro;

public:
    Nota(string tom, int duracao, string filtro);
    string getTom() const;
    int getDuracao() const;
    string getFiltro() const;
};

#endif
