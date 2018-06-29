#include "Evento.h"
#include "ListaDeEventos.h"
#include "Reacao.h"
#include "ListaDeReações.h"
#include <iostream>
using namespace std;
#include <string.h>

void eventosIniciais(ListaDeEventos* lista);
void listaDeReacoes();
void reacaoEventos(ListaDeEventos *eventos, ListaDeReacoes *reacoes);
bool finalizou = false;

int main()
{
    cout << "BEM VINDO AO SIMULADOR\n\n\n";
    instrucoes[128];

    while (finalizou == false)
    {
        cout << "Menu de Opcoes: \n";
        cout << "1. Criar Lista de Eventos\n";
        cout << "2. Simular Lista de Eventos\n";
        cout << "3. Imprimir Lista de Eventos\n";
        cout << "4. Editar Lista de Eventos\n";
        cout << "5. Finalizar\n";
        cout << "Escolha a opcao desejada: ";
        int opcao;
        cin >> opcao;
    }
    return 0;
}

/*void eventosIniciais(ListaDeEventos* lista)
{
    int i,n;
    n = lista->getNumeroDeEventos();
    i = 1;
    Evento* evento = lista->getInicio();
    while (i<=n){
        if (evento->identificador == "INICIO"){
            cout << "BEM VINDO AO SIMULADOR\n";
        }
        evento = evento->getProximo();
    }
}*/

ListaDeEventos* menu()
{
    Evento *inicioMenu = new Evento("MENU");
    ListaDeEventos *menu = new ListaDeEventos(inicioMenu);

    Evento *criarLista = new Evento("CRIAR LISTA");
    inicioMenu->setProximo(criarLista);

    Evento *simularLista = new Evento("SIMULAR LISTA");
    criarLista->setProximo(simularLista);

    Evento *imprimirLista = new Evento("IMPRIMIR LISTA");
    simularLista->setProximo(imprimirLista);

    Evento *editarLista = new Evento("EDITAR LISTA");
    imprimirLista->setProximo(editarLista);

    return menu;
}

void eventosFinais(ListaDeEventos* lista)
{
    Evento *finalizar = new Evento("FINALIZAR");
    ListaDeEventos *Final = new ListaDeEventos(finalizar);
}

ListaDeReacoes* listaReacoes()
{

}
