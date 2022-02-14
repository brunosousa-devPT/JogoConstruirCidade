//
// Created by bruno on 16/01/2022.
//

#ifndef TRABALHO_SAVE_H
#define TRABALHO_SAVE_H

#include "utils.h"

class jogo;

class save {

    vector <jogo*> jogos;

public:
    save()=default;
    void adicionaJogo(jogo * p);
    void loadJogo(int index);
    void deleteJogo(int index);

};


#endif //TRABALHO_SAVE_H
