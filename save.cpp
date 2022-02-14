//
// Created by bruno on 16/01/2022.
//

#include "save.h"
#include "jogo.h"

void save::adicionaJogo(jogo *p) {

    jogos.push_back(p);



}

void save::loadJogo(int index) {



}

void save::deleteJogo(int index) {
    int a = 0;
    for (auto it: jogos) {
        if (index == a) {
            jogos.erase(jogos.begin() + a);
            delete it;
            break;
        }

        a++;
    }



}
