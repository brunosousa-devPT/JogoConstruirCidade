//
// Created by bruno on 30/12/2021.
//

#ifndef TRABALHO_EDIFICIO_H
#define TRABALHO_EDIFICIO_H

#include "utils.h"
#include "Recursos.h"

/*
 *  Class: Edificio
 *  Objetivo: Orientar as funcoes de um certo edificio.
 *  Neste ficheiro está presente poliformismo e herança.
 *  CALL: zona.h
 *
 *  declarar uma class zona e necessario pois iremos usufruir do vector das zonas adjacentes e de certas
 *  funcoes da zona do edificio para fazer certas verificacoes, facilitando assim o processo.
 * */

class Zona;

class edificio {

    string tipo;
    int nivelAtual; //Todos edificios começam a nivel 1 mas nem todos sao melhoraveis.
    int nivelMax;
    Zona *zonaDoEdificio;

    int quantidadeProduzida;
    int armazenamento;
    int armazenamentoMax;
    Recursos * recur;
    bool ligado;

public:
    edificio(Recursos* recu,string type,Zona *zonaEdif, const string& recur,int nivelM,int armMAC=0,int quantProd = 0);
    void aumentarNivel(int qtdProdAum, int qtdArmAum);
    string getTipo() const;
    virtual ~edificio();
    int getArmazenamento() const;
    int getArmazenamentoMax() const;
    int getQuantidadeProduzida() const;
    Zona *getZonaEdificio() const;
    virtual bool produzir() = 0;
    virtual bool Desabou();

    virtual void verifcaAdj();
    void changeArmazenamento(int a);
    virtual bool aumentarNivel() ;
    int getnivelAtual() const;
    int getnivelMAX() const;
    bool itsUpgradable() const;
    string getRecurso()const;


    int getRecursoQuantidade();
    void aumentaQuantidade();

    void diminuiQuantidade(int a);

    bool getEstadoEdificio() const;
    void setEstado(bool value);

};

class mina:public edificio {
    int probDesabar;

    int prodAumPorLev;
    int armAumPorLev;

public:
    mina(Recursos * recu,string type, Zona *zonaEdif, const string& recur,int prob);

    bool aumentarNivel() override;

    bool Desabou() override;
    bool produzir() override;


};


class centralEletrica: public edificio {

    bool adajcenteFloresta;




public:
    explicit centralEletrica(Zona *zonaEdif);

    void verifcaAdj() override;
    bool produzir() override;

};

class bateria: public edificio {
    bool adajacenteCentral;

    int aumArmPorLevel;


public:
    explicit bateria(Zona *zonaEdif);

    bool produzir() override;
    void verifcaAdj() override;
    bool aumentarNivel() override;
};

class fundicao: public edificio {

    bool adjacenteCentral;
    bool adjacenteMinaC;
    bool adjacenteMinaF;


public:
    explicit fundicao(Zona *zonaEdif);
    bool produzir() override;
    void verifcaAdj() override;
};


class serracao: public edificio {
    bool adjacenteFloresta;
    int aumArmPorLevel;
public:
    explicit serracao(Zona * zonaEdif);

    bool produzir() override;
    void verifcaAdj() override;
    bool aumentarNivel() override;



};

#endif //TRABALHO_EDIFICIO_H
