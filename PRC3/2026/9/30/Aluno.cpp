#include<iostream>
#include "Aluno.hpp"

using namespace std;

Aluno::Aluno(string nome, int idade, string prontuario, string senha, float ira):
Pessoa(nome, idade),
_prontuario(prontuario),
_senha(senha),
_ira(ira)
{
    //propositalmente em branco
}


void Aluno::estudar(string materia){
    cout<<"Estudando "<<materia<<" agora"<<endl;
}

void Aluno::fazerprova(void){
    cout<<"Estou fazendo uma prova"<<endl;
}
string Aluno::getSenha(void){
    return _senha;
}
void Aluno::setSenha(string senha){
    _senha=senha;
}
string Aluno::getProntuario(void){
    return _prontuario;
}
float Aluno::getIra(void){
    return _ira;
}
void Aluno::setIra(float ira){
    _ira = ira;
}

void Aluno::apresentar(string cumprimento){
    cout<<cumprimento<<" Eu sou "<<getNome()<<" Tenho "<<getIdade()<< "anos.\n"<< "Eu sou um aluno\n";
}