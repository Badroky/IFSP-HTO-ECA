#include <iostream>
#include "Maestro.hpp"

using namespace std;

Maestro::Maestro(string nome) : _nome(nome) {
}

void Maestro::reger(Banda* banda, Musica* musica) {
    if (banda == nullptr || musica == nullptr) {
        return;
    }

    cout << "Maestro " << _nome << " inicia a regencia de \"" << musica->getTitulo() << "\" com a banda " << banda->getNome() << "!" << endl;

    musica->reiniciarPartitura();
    int compasso = 1;
    while (musica->temProximaNota()) {
        Nota n = musica->proximaNota();
        cout << "-- Compasso " << compasso << ": Nota " << n.getTom() << " (" << n.getDuracao() << "t) [Filtro: " << n.getFiltro() << "] --" << endl;
        banda->tocarNota(n);
        compasso++;
    }

    cout << "Fim da apresentacao de \"" << musica->getTitulo() << "\"." << endl;
}

string Maestro::getNome() const {
    return _nome;
}
