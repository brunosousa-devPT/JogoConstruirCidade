//
// Created by bruno on 13/01/2022.
//

#include "definicoes.h"

definicoes::definicoes() = default;

int definicoes::getPrecTrab(int index) const {
    return arr[index];
}

int definicoes::getConsPrecoEu(int index) const {
    return construcoesPreco[index][1];
}
int definicoes::getConsPrecoVig(int index) const {
    return construcoesPreco[index][0];
}



int definicoes::getRecursosPrecos(int index) const {
    return int(RecursosPrecos[index]);
}

void definicoes::modificaPrecoTrabalhador(int preco, int index) {
    arr[index] = preco;
}

void definicoes::modificaPrecoConstrucaoEuros(int preco, int index) {
    construcoesPreco[index][1] = preco;
}

int definicoes::getIndexConstrucoes(const string& tipo) const {
    int a =0;
    for (const auto& it: Construcoes) {
        if (it == tipo) {
            return a;
        }
        ++a;
    }
    return -1;
}

int definicoes::getPrecoMelhEu(int index) const {
    return melhoramentos[index][1];
}


int definicoes::getPrecoMelhVig(int index) const {
    return melhoramentos[index][0];
}

int definicoes::getIndexRecursos(const string &tipo) const {
    int a =0;
    for (const auto& it: recursos) {
        if (it == tipo) {
            return a;
        }
        ++a;
    }
    return -1;
}






