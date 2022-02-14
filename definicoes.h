//
// Created by bruno on 13/01/2022.
//

#ifndef TRABALHO_DEFINICOES_H
#define TRABALHO_DEFINICOES_H

/*
 * Class: definicoes
 * Objetivo: Orientar os precos do jogo, visto que alguns sao modificaveis pelo utilizador
 * CALL: jogo.h
 * */


#include "utils.h"
class definicoes {

    int arr[3]{15,20,10}; //operario , lenhador, mineiro

    int construcoesPreco[6][2]{{10,100}, {10,100}, {0, 15}, {10,10},{0,10}, {0,5}};//vigas ou € // mina de Ferro, mina de Carvao, Central Eletrica, Bateria, Fundicao, serracao
    string Construcoes[6]{"mnF", "mnC","elec", "bat", "fun","ser"};

    string recursos[6] {"Ferro","BarraDeAco", "Carvao", "Madeira", "Vigas", "Eletricidade"};

    int melhoramentos[6][2] {{1,15}, {1,10}, {0,0}, {0,5},{0,0},{0,10}}; // vigas e € //  mina de Ferro, mina de Carvao, Central Eletrica, Bateria, Fundicao, serracao


    float RecursosPrecos[6]{1.0,2.0,1.0,1.0,2.0,1.5};
public:
    definicoes();
    int getPrecTrab(int index) const;
    int getConsPrecoEu(int index) const;
    int getConsPrecoVig(int index) const;
    int getPrecoMelhEu(int index) const;
    int getPrecoMelhVig(int index) const;

    int getIndexConstrucoes(const string& tipo) const;
    int getIndexRecursos(const string&tipo)const;
    int getRecursosPrecos(int index)const;

    void modificaPrecoTrabalhador(int preco, int index);
    void modificaPrecoConstrucaoEuros(int preco, int index);


};


#endif //TRABALHO_DEFINICOES_H
