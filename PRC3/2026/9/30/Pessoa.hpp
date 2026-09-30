#ifndef _CLASS_PESSOA_
#define _CLASS_PESSOA_

#include <iostream>

using namespace std;

class Pessoa {
private:
  int idade;
  string nome;

public:
  Pessoa(string nome, int idade);
  string getNome(void);
  int getIdade(void);
  void setIdade(int idade);
  void apresentar(string cumprimento);
};