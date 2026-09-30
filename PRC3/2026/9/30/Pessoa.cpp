#include<iostream>
#include "Pessoa.hpp"

using namespace std;

Pessoa::Pessoa(string nome, int idade):
_nome(move(nome)),
_idade(idade)
{
}


void Pessoa::setIdade(int idade) {
    this->_idade = idade;
}

void Pessoa::apresentar(string cumprimento) {
    cout << cumprimento << ", eu sou " << getNome() << " e tenho " << this->_idade << " anos." << endl;
}

string Pessoa::getNome(void) {
    return this->_nome;
}