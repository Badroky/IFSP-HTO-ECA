#include<iostream>
#include "Pessoa.hpp"

using namespace std;


Pessoa::Pessoa(string nome, int idade):
_nome(move(nome)),
_idade(idade)
{
    //propositalmente em branco
}

string Pessoa::getNome(void){
    return _nome;
}
int Pessoa::getIdade(void){
    return _idade;
}
void Pessoa::setIdade(int idade){
    _idade = idade;
}
void Pessoa::apresentar(string cumprimento){
    cout<<cumprimento<<" Eu sou "<<getNome()<<" Tenho "<<getIdade()<< "anos.\n";
}
