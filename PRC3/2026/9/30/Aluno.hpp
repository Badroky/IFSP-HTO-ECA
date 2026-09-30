#ifndef _CLASS_ALUNO_
#define _CLASS_ALUNO_

#include<iostream>
#include "Pessoa.hpp"

using namespace std;

class Aluno: public Pessoa{
    private:
        string _protuario;
        string _senha;
        float _ira;
    public:
        luno(string nome, int idade, string prontuario, string senha, float ira);
        void estudar(string materia);
        void fazerprova(void);
        string getSenha(void);
        void setSenha(string senha);
        string getProntuario(void);
        float getIra(void);
        void setIra(float ira);
};

#endif