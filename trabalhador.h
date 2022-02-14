//
// Created by bruno on 20/11/2021.
//

#ifndef TP_TRABALHADOR_H
#define TP_TRABALHADOR_H

#include "utils.h"


class trabalhador {

    static int contador; //Numero de trabalhadores que existe

    int diaContratado; // Dia em que foi contratado

    string id; //Recebe o numero de trabalhador
    char tipoTrabalhador;

    int dias =0 ;
    int linha, colunas;


public:
    explicit trabalhador(char tipoOperario, int x, int y, int days);

    char obterTipoTrabalhador() const;
    string obterID () const;
    //int obterDiaContratado() const;
    void aumentaDias();
    int getDias()const;
    trabalhador &operator=(const trabalhador & outro);
    static bool demitir(int prob);
    virtual trabalhador * duplica()const=0;

    virtual bool getDiasTrabalhados() = 0;
    virtual ~trabalhador()= default;;
};

class operario: public trabalhador {
    //operar fundições e centrais elétricas

    int limiteInfDia; // Limite definido no enunciado (operario a partir do 10º dia pode sair com 5% prob)

public:
    operario(char tipoOperario, int x, int y, int days);

    trabalhador * duplica()const override;
    bool getDiasTrabalhados() override;
    ~operario() override;

};

class lenhador: public trabalhador {


public:
    lenhador(char tipoOperario, int x, int y, int days);
    bool getDiasTrabalhados() override;
    trabalhador * duplica()const override;
    ~lenhador() override;
};

class mineiro: public trabalhador {
public:
    mineiro(char tipoOperario, int x, int y, int days);
    trabalhador * duplica() const override;
    ~mineiro() override;
    bool getDiasTrabalhados() override;

};

#endif //TP_TRABALHADOR_H
