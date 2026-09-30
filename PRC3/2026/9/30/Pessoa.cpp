#include "Pessoa.hpp"
#include <iostream>

using namespace std;

Pessoa::Pessoa(string nome, int idade) : _nome(move(nome)), _idade(idade) {}

string Pessoa::getNome(void) { return _nome; }

int Pessoa::getIdade(void) { return _idade; }

void Pessoa::setIdade(int idade) { _idade = idade; }

void Pessoa::apresentar(string cumprimento) {
  cout << cumprimento << "Eu sou " << getNome() << " e tenho " << getIdade()
       << " anos." << endl;
}