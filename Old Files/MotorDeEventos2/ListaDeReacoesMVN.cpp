#include <iostream>
using namespace std;

#include "ListaDeReacoes.h"
#include "Reacao.h"

ListaDeReacoes::ListaDeReacoes(Reacao* i){
    this->inicio = i;
    cout << "Lista de Reacoes Criada com Sucesso!\n";
}

ListaDeReacoes::~ListaDeReacoes(){

}

