/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.
*******************************************************************************/
#include <iostream>
#include "Pessoa.hpp"
#include "Aluno.hpp"

int main()
{
    cout<<"p1"<<endl;
    Pessoa p1("William", 40);
    p1.apresentar("Tarde! ");
    
    cout<<endl<<"p2"<<endl;
    Pessoa p2("Vinicius", 10);
    p2.apresentar("Hola! ");
    
    cout<<endl<<"p3"<<endl;
    Pessoa p3 = p1;
    p3.setIdade(20);
    p3.apresentar("Uhuuu!");
    p1.apresentar("Diferente");
    cout<<endl;
    
    cout<<"p4"<<endl;
    Pessoa p4 = p2;
    p4.apresentar("Viva!  ");
    cout<<endl;
    
    Pessoa* p_ponteiro_a = &p1;
    cout<<"p_ponteiro_a"<<endl;
    p_ponteiro_a->apresentar("Eita!  ");
    cout<<endl;
    
    Pessoa* p_ponteiro_b = &p2;
    cout<<"p_ponteiro_b"<<endl;
    p_ponteiro_b->apresentar("Prazer!  ");
    cout<<endl;
    
    Pessoa* p_ponteiro_novo1 = new Pessoa("Miguelito1", 6);
    cout<<"p_ponteiro_novo1"<<endl;
    p_ponteiro_novo1->apresentar("Desprazer!! ");
    cout<<endl;
    
    Pessoa* p_ponteiro_novo2 = p_ponteiro_novo1;
    cout<<"p_ponteiro_novo2"<<endl;
    p_ponteiro_novo2->apresentar("Uuuuiii! ");
    p_ponteiro_novo1->apresentar("Outro! ");
    cout<<endl;
    
    p_ponteiro_novo1 = new Pessoa("Miguelito2", 6);
    cout<<"p_ponteiro_novo1"<<endl;
    p_ponteiro_novo1->apresentar("Aiiiii!  ");
    p_ponteiro_novo2->apresentar("Uuuuiii! ");
    
    delete p_ponteiro_novo2;
    delete p_ponteiro_novo1;
    
    //p_ponteiro_novo2->apresentar("Vazio");
    //p_ponteiro_novo1->apresentar("Vazio2");
    
    Aluno* aluno1 = new Aluno("Kaleo", 22, "HT666999", "USUHAQUI01", 999);
    aluno1->apresentar("Oi!");
    
    /*
    aluno1->estudar("Programacao");
    aluno1->fazerprova();
    string s = aluno1->getSenha() + "naodurmo";
    aluno1->setSenha(s);
    cout<< aluno1->getSenha()<<endl;
    cout<<"Prontuario: " << aluno1->getProntuario()<<endl;
    cout << "Ira: " << aluno1->getIra()<<endl;
    aluno1->setIra(666);
    cout << "Iranovo: "<<aluno1->getIra();
    */
    
    
    
    

    return 0;
}