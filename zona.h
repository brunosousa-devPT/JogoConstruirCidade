//
// Created by bruno on 30/12/2021.
//

#ifndef TRABALHO_ZONA_H
#define TRABALHO_ZONA_H

#include "trabalhador.h"
#include "edificio.h"
#include <vector>

class Zona {
    string tipoZona;
    vector <trabalhador *> trabalhadores;
    vector <Zona *> zonasAdjacentes;
    edificio *edif;
    int coluna;
    int linha;
    bool temEdificio;
    //Floresta
    int arvores;
    float materialProduzidoPT; // PT-> Por trabalhador
    int dias;
    int diasSeguidos; // A cada x dias algo acontece
    int MaxArvores;
    float armazenamento;
    float reducao;
    int trabProb; // Prob aumentada do trabalhador ir se embora;
    Recursos * recur;

public:
    Zona(Recursos * rc,string tp,int arv,  float materialProdz, int days, int mArvo,int trabPro, float red = 0);
    int obtemLinha() const;
    int obtemColuna() const;

    bool adicionarTrabalhador(char tipo, int x, int y, int diass);
    bool removerTrabalhador(const string& id);
    string obtemTipoZona() const;
    void construirEdificio(const string& tipo);
    void destruirEdificio();
    void setColuna(int col);
    void setLinha(int lin);
    void seTtemEdificio(bool value);
    string getEdificio();
    string getTrabalhadores() const;
    int getNumberWorker() const;
    bool getTemEdificio() const;
    bool verificaTrabalhador(const string& id);
    void funcaoXDias();
    void funcaoPorDia();
    void addZonaAdjacente(Zona * z);
    void limpaVetor();
    bool verificaAdjacenciaEdificio(const string& tipo);
    bool verificaAdjacenciaZona(const string& tipo);
    edificio * getObjectEdificio(const string& tipo);
    int getNumberOfAdjacentEdif(const string& tipo) ;
    float getArmazenamentoZonas() const;
    void adicionaDia();
    int getArmazenamentoEdificio();
    bool edifUpgradable();
    void upgradeEdificio();

    trabalhador * getTrabalhador(const string& id);
    void adicionarTrabalhador(trabalhador * p);

    float getQuantidadeRecurso();
    bool verificaRecurso();
    string getTipoRecurso() ;
    void aumentaQtdRecurso(float a);
    void diminuiQtdRecurso(float a);
    bool retiraRecursoZonaAdj(int a, const string& rec);
    string getRecursoEdificio();

    bool retiraRecursoEdifAdj(int a, const string& rec);

    bool getEstadoEdificio();
    void setEstadoEdificio(bool value);


};


class Deserto:public Zona {
public:
    Deserto();

};

class Pastagem: public Zona {
public:
    Pastagem();
};

class Floresta: public Zona {



public:
    Floresta();


};

class Montanha: public Zona {

public:
    Montanha();

};

class Pantano: public Zona {


public:
    Pantano();

};

class Vulcao: public Zona {
public:
    Vulcao();
};


#endif //TRABALHO_ZONA_H
