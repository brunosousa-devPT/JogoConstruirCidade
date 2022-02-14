//
// Created by bruno on 02/01/2022.
//

#ifndef TRABALHO_JOGO_H
#define TRABALHO_JOGO_H

#include "ilha.h"
#include "Comandos.h"
#include "definicoes.h"
#include "save.h"

class jogo {
    ilha *ilhaJogo;
    int dias = 1;
    string comando;
    Comandos cmd;
    string args;
    int faseJogo = 0;
    bool runningGame = true;
    int cash = 100;
    int vigasdeMadeira = 100;
    definicoes defs;
    vector <Recursos* > recursosIlha;
    save sSavesCurrent;

public:
    explicit jogo(ilha *island);
    void runGame();
    void mostrarIlha();
    bool fasePedirComandos();
    int pedirComandos(const string& com = "");
    void cont();
    bool exec(const string& nomeFicheiro);
    void mostrarZona();
    void liga_Desliga(int ligades);
    void config(const string& nome);
    void move();
     void load();
     void save();
     void apaga();
    void debkill();
    void debcash();
    void vende();
    void cons(int a);
    void update();

    void criaRecursos();
    void obtemRecursos();

};


#endif //TRABALHO_JOGO_H
