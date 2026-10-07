#ifndef _CLASS_PILHA_PESSOAS_
#define _CLASS_PILHA_PESSOAS_

#include<iostream>
#include "Pessoa.hpp"

using namespace std;


class No{
    private:
        Pessoa* _dado;
        No* _prev;
    public:
        No(Pessoa* p):
            _dado(move(p)),
            _prev(nullptr)
        {
            
        }
        void setPrev(No* p){
            _prev = p;
        }
        
        No* getPrev(void){
            return _prev;
        }
        
        void setDado(Pessoa* p){
            dado = p;
        }
        
        Pessoa* getDado(void){
            return _dado;
        }
}

class PilhaPessoas{
    private:
        No* cabeca;
    public:
        PilhaPessoas():
            cabeca(nullptr)
        {
        }
        void insere 
};

class Aluno: public Pessoa{
    private:
        string _prontuario;
        string _senha;
        float _ira;
    public:
        Aluno(string nome, int idade, string prontuario, string senha, float ira);
        void estudar(string materia);
        void fazerprova(void);
        string getSenha(void);
        void setSenha(string senha);
        string getProntuario(void);
        float getIra(void);
        void setIra(float ira);
        void apresentar(string cumprimento) /*override*/;
};

#endif