#include <iostream>
using namespace std;

#include "ListaDeEventos.h"
#include "Evento.h"
#include "ListaDeReacoes.h"
#include "Reacao.h"
#include "MVN.h"

/*Funcoes globais*/
ListaDeEventos* eventosIniciais();
void menu(ListaDeReacoes* listaReacoes);
void reacaoLista(ListaDeEventos* listaEventos, ListaDeReacoes* listaReacoes);
void reacaoListaMVN(ListaDeEventos);

int main()
{
    cout << "Criacao da lista de Reacoes Global\n";
    Reacao* i = new Reacao("INICIO",2,false);
    ListaDeReacoes* listaReacoesGlobal = new ListaDeReacoes(i);

    Reacao* j = new Reacao("LISTA EVENTOS NOVA",1,false);
    i->proximo=j;

    /*Cria Lista De Eventos Inicial*/
    ListaDeEventos* listaInicio = eventosIniciais();
    cout << "INICIANDO O SIMULADOR...\n";
    reacaoLista(listaInicio,listaReacoesGlobal);

    int escolha;
    cout << "SIMULAR 0 - MVN OU 1- OUTRA LISTA DE EVENTOS?\n";
    if (escolha == 0){
        MVN* mvn = new MVN();

        /*Cria evento inicial de carregar programa e lista de eventos */
        Evento* carregar_programa = new Evento("CARREGAR PROGRAMA", 0, 0);
        ListaDeEventos* lista = new ListaDeEventos(carregar_programa);

        /*Cria demais eventos*/
        Evento* simular_programa = new Evento("SIMULAR PROGRAMA",0,0);
        Evento* decodifica = new Evento("DECODIFICA",0,0);
        Evento* executa = new Evento("EXECUTA",0,0);

        /*Cria lista de reacoes especificas para a MVN*/
        ReacaoMVN* c_p = new ReacaoMVN("CARREGAR PROGRAMA", false);
        ListaDeReacoes* listaMVN = new ListaDeReacoes(carregar_programa);

        ReacaoMVN* s_p = new ReacaoMVN("SIMULAR PROGRAMA",false);
        c_p->proximo = s_p;
        ReacaoMVN* d = new ReacaoMVN("DECODIFICA",false);
        s_p->proximo = d;
        ReacaoMVN* e = new Evento("EXECUTA",true);
        d->proximo = e;
    }
    if (escolha == 1){

    }

    /*menu();*/
    return 0;
}

ListaDeEventos* eventosIniciais(){
    Evento* inicio = new Evento("INICIO",0,false);
    ListaDeEventos* listaInicial = new ListaDeEventos(inicio);
    return listaInicial;
}

void menu(ListaDeReacoes* listaReacoes){
    bool acabou = false;
    int instante = 0;
    while (acabou == false){
        cout << "OPCOES DISPONIVEIS: \N";
        cout << "1- Obtencao da Lista de Reacoes Disponiveis: \n";
        cout << "2- Insercao de Eventos \n";
        cout << "3- Ligar Acompanhamento Passo a Passo \n";
        cout << "4- Desligar Acompanhamento Passo a Passo \n";
        cout << "5- Monitorar breakpoints \n";
        cout << "6- Incluir breakpoint \n";
        cout << "7- Excluir breakpoint \n";
        cout << "8- Apresentar partes Especificadas do Estado da Simulacao";
        cout << "9- Finalizar Simulacao \n";
        cout << "10- Imprimir Relatorios \n";
        cout << "11- Sair do Simulador \n";

        //Obtencao da lista de eventos iniciais
        Evento* inicio = new Evento("LISTA EVENTOS NOVA", instante,false);
        ListaDeEventos* lista = new ListaDeEventos(inicio);
        instante = instante+1;

        int decisao;
        cin >> decisao;

        if (decisao == 1){
            Reacao* reacao = listaReacoes->inicio;
            int i;
            for (i=0; i<listaReacoes->tamanho;i++){
                cout << "Reacao " << i << ": " << reacao->tipoDeReacao << "\n";
            }
        }

        if (decisao == 2){
            cout << "Digite o tipo de reacao desejado: \n";
            string reacao;
            cin >> reacao;
            Evento* evento = new Evento(reacao, instante, false);
            lista->fim->proximo = evento;
            lista->fim = evento;
        }

        if (decisao == 3){
            reacaoLista(lista,listaReacoes);
        }

        if (decisao == 4){
            cout << "INSERIR BREAKPOINT \n";
        }
        if (decisao == 11) acabou = true;
    }
}

void reacaoLista(ListaDeEventos* listaEventos, ListaDeReacoes* listaReacoes){
    Evento* evento = listaEventos->inicio;
    string tipoReacao = evento->tipoDeReacao;
    Reacao* reacao = listaReacoes->inicio;
    bool achou = false;
    if (listaEventos->inicio == listaEventos->fim){
            while (achou == false){
                if (tipoReacao == reacao->tipoDeReacao) {
                    achou = true;
                }
                else{
                    reacao = reacao->proximo;
                }
            }
            int i;
            for (i=0; i<reacao->numInstrucoes; i++){
                cout << "Passo " << i << "\n";
                if (reacao->listaInstrucoes[i] == 16) cout << "BEM VINDO AO SIMULADOR!\n";
                if (reacao->listaInstrucoes[i] == 17) cout << "INICIO SIMULACAO\n";
                if (reacao->listaInstrucoes[i] == 18) cout << "SIMULACAO NOVA LISTA DE EVENTOS \n";
            }
    }
    else{
        while (evento!=listaEventos->fim){
                while (achou == false){
                    if (tipoReacao == reacao->tipoDeReacao) {
                        achou = true;
                    }
                    else{
                        reacao = reacao->proximo;
                    }
                }
                achou = false;
                int i;
                for (i=0; i<reacao->numInstrucoes; i++){
                    cout << "Passo " << i << "\n";
                    if (reacao->listaInstrucoes[i] == 16) cout << "BEM VINDO AO SIMULADOR!\n";
                    if (reacao->listaInstrucoes[i] == 17) cout << "INICIO SIMULACAO\n";
                    if (reacao->listaInstrucoes[i] == 18) cout << "SIMULACAO NOVA LISTA DE EVENTOS \n";
                }
                evento = evento->proximo;
        }
        while (achou == false){
            if (tipoReacao == reacao->tipoDeReacao) {
                achou = true;
            }
            else{
                reacao = reacao->proximo;
            }
        }
            achou = false;
            int i;
            for (i=0; i<reacao->numInstrucoes; i++){
                cout << "Passo " << i << "\n";
                if (reacao->listaInstrucoes[i] == 16) cout << "BEM VINDO AO SIMULADOR!\n";
                if (reacao->listaInstrucoes[i] == 17) cout << "INICIO SIMULACAO\n";
                if (reacao->listaInstrucoes[i] == 18) cout << "SIMULACAO NOVA LISTA DE EVENTOS \n";
            }
    }

}


