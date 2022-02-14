//
// Created by bruno on 21/11/2021.
//

#ifndef TP_COMANDOS_H
#define TP_COMANDOS_H

#include "utils.h"

#include <fstream>
#include <sstream>

/*
 * Class: Comandos
 * Objetivo: Pretende-se que esta classe seja capaz de analizar os diferentes comandos que o user faz input.
 * CALL: jogo.h
 * */


class Comandos {


    vector <string> commands {
            "exec", "cons", "liga", "des", "move", "vende", "cont","list", "next", "save","load","apaga","config","debcash","debed","debkill","fim", "update"
    };

    int comandoIndex=-1;
public:
    Comandos() = default; //default

    string mostraComandos();

    int getComandoIndex() const;
    bool verificaComando(const string& comando);

};


#endif //TP_COMANDOS_H
