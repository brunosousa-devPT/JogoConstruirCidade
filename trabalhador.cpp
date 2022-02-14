//
// Created by bruno on 20/11/2021.
//

#include "trabalhador.h"




// Tipos de trabalhador:  L(Lenhador)  O(Operário)   M(Mineiro)

trabalhador::trabalhador(char tipoTrab, int x, int y,int days):  id(getWorkerString(days,++contador)), tipoTrabalhador(tipoTrab), diaContratado(days), linha(x), colunas(y){

    cout << "\nWorker has been created with success: ID " << id << " Day: "<<diaContratado << "\n";

}


int trabalhador::contador = 0;

char trabalhador::obterTipoTrabalhador() const {
    return tipoTrabalhador;
}

string trabalhador::obterID() const {
    return id;
}



trabalhador &trabalhador::operator=(const trabalhador &outro) {
    if (this == &outro) {
        return *this;
    }
    this->id = outro.id;
    this->colunas = outro.colunas;
    this->linha = outro.linha;
    this->diaContratado = outro.diaContratado;
    this->tipoTrabalhador = outro.tipoTrabalhador;
    
    return *this;
}

bool trabalhador::demitir(int prob) {

    if (randomNumber2(0,100) < prob)
        return true;
    return false;

}

void trabalhador::aumentaDias() {
    dias++;
}

int trabalhador::getDias() const {
    return dias;
}


operario::operario(char tipoOperario, int x, int y, int days) : trabalhador(tipoOperario, x, y, days),limiteInfDia(10) {

}




trabalhador *operario::duplica() const {
    return new operario(*this);
}

operario::~operario() {
    cout <<"Operario com o id "<<obterID()<<" demitiu-se!";
}

bool operario::getDiasTrabalhados() {
    if (limiteInfDia > getDias()) return true;
    return false;
}


lenhador::lenhador(char tipoOperario, int x, int y, int days) : trabalhador(tipoOperario, x, y, days){

}


trabalhador *lenhador::duplica() const {
    return new lenhador(*this);
}

lenhador::~lenhador() {
   cout << "Operario com o id "<< obterID()<<" demitiu-se!";

}

bool lenhador::getDiasTrabalhados() {
    return false;
}

mineiro::mineiro(char tipoOperario, int x, int y, int days) : trabalhador(tipoOperario, x, y, days) {

}

trabalhador *mineiro::duplica() const {
    return new mineiro(*this);
}

mineiro::~mineiro() {
    cout << "Mineiro com o id "<<obterID()<<" demitiu-se!";

}

bool mineiro::getDiasTrabalhados() {
    if (getDias() > 2)
        return true;
    return false;
}


