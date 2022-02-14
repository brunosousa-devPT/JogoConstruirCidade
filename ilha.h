//
// Created by bruno on 02/01/2022.
//

#ifndef TRABALHO_ILHA_H
#define TRABALHO_ILHA_H

#include "zona.h"

class ilha {

    int colunas, linhas;
    Zona **zonas{};
    vector <string> zonasDisponiveis {
            "mnt","dsr","pas","flr","pnt","vul"
    };
    vector <string> edificiosDisponiveis {
            "mnF","mnC","elec","bat","fun","ser","res"
    };
    int xpas,ypas;
public:
    ilha(int lines, int columns);

    int getxPas()const;
    int getyPas()const;

    void construirIlha();
    int getColunas() const;
    int getLinhas() const;
    string getTipoZona(int linha, int coluna);
    string getWorkersZona(int linha, int coluna);
    void contWorker(char tipo, int linha, int coluna, int dias);
    string getEdificioZona(int linha, int coluna);
    bool edificioDisponivel(const string& tipo) ;
    bool verificaEdificioZona(int linha, int coluna);
    void construirEdificio(int linha,int coluna,const string& tipo);
    string devolveEdiciosDisponiveis();
    void moveTrabalhador(int linha, int coluna,const string& id );
    void removerTrabalhador(const string& id);
    void makeZonasAdjacentes();
    void adicionaDiaZonas();
    int getNumberWorksZona(int linha, int  coluna);
    float getArmazenamentoZona(int linha, int coluna);
    void executaxDias();
    int getArmazenamentoEdificio(int linha, int  coluna);
    bool getEdifUpgradable(int linha, int coluna);
    void upgradeEdificio(int linha, int coluna);
    int obtemRecursos(const string& Recurso);
    string getEdificioRecurso(int linha,int coluna);
    bool getEstadoEdificio(int linha, int coluna);
    void setEstadoEdificio(int linha, int coluna , bool value);
    void removerEdificio(int linha, int coluna);
    void retiraRecursoEdificio(int linha, int coluna, int a);
};


#endif //TRABALHO_ILHA_H
