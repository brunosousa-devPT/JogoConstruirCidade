//
// Created by bruno on 02/01/2022.
//

#include "ilha.h"
#include <sstream>
#include <ctime>

ilha::ilha(int lines, int columns): linhas(lines), colunas(columns),xpas(0),ypas(0) {
    construirIlha();
    makeZonasAdjacentes();

    cout <<"Ilha construida com sucesso!" <<endl;
}

/*****************************/
/*      Construir Ilha       */
/*****************************/


void ilha::construirIlha() {
    srand(time(nullptr)); //bilbioteca from c

    vector <string> zonasUsadas;
    zonasUsadas.reserve(linhas*colunas);
    zonas = new Zona*[linhas];

    for (int k = 0; k < linhas ; k++) {
        zonas[k] = new Floresta[colunas];
    }


    bool continua;
    int tam = linhas * colunas;
    int a = 0, linhaLoop = 0, colunaLoop = 0; //linhaLoop e colunaLoop são usadas para preencher **zonas no loop
    int random, p=0;

    while (a < tam) {
        continua = false;
        random = randomNumber();


        //random = randomNumber();



        for (const auto& it:zonasUsadas) {
            if (it == zonasDisponiveis[random]) {
                continua = true;
                break;
            }
        }

        if (continua)
            continue;
        zonasUsadas.emplace_back(zonasDisponiveis[random]);
        switch (random) {
            case 0:
                zonas[linhaLoop][colunaLoop] = Montanha();
                break;
            case 1:
                zonas[linhaLoop][colunaLoop] = Deserto();
                break;
            case 2:
                zonas[linhaLoop][colunaLoop] = Pastagem();
                xpas = linhaLoop;
                ypas=colunaLoop;
                break;

            case 3:
                zonas[linhaLoop][colunaLoop] = Floresta();
                break;
            case 4:
                zonas[linhaLoop][colunaLoop] = Pantano();
                break;
            case 5:
                zonas[linhaLoop][colunaLoop] = Vulcao();
                break;
            default:
               cout << "Erro!";
                exit(1);

        }
        zonas[linhaLoop][colunaLoop].setColuna(colunaLoop);
        zonas[linhaLoop][colunaLoop].setLinha(linhaLoop);

        if (a==5 or p> 0) {
            p++;
            zonasUsadas.clear();
        }

        colunaLoop ++;

        if (colunaLoop >= colunas) {

            linhaLoop ++;
            colunaLoop = 0;
        }

        a++;
    }

}

int ilha::getColunas() const {
    return colunas;
}

int ilha::getLinhas() const {
    return linhas;
}

string ilha::getTipoZona(int linha, int coluna) {
    if (zonas != nullptr)
        return zonas[linha][coluna].obtemTipoZona();
    return "Erro";
}

string ilha::getWorkersZona(int linha, int coluna) {
    if (zonas != nullptr) return zonas[linha][coluna].getTrabalhadores();
    return "Erro";

}

/*****************************/
/*      Contratar Worker     */
/*****************************/


void ilha::contWorker(char tipo, int linha, int coluna,int dias) {
   if( zonas != nullptr and zonas[linha][coluna].adicionarTrabalhador(tipo,linha,coluna,dias)) {
       cout <<"Worker done!\n" <<endl;
   }
}


/*****************************/
/*    Obter tipo Edificio    */
/*****************************/


string ilha::getEdificioZona(int linha, int coluna) {
    if (zonas != nullptr) return zonas[linha][coluna].getEdificio();
    return "Erro";
}


bool ilha::edificioDisponivel(const string& tipo) {
    vector<string>::iterator it;
    for (it = edificiosDisponiveis.begin(); it != edificiosDisponiveis.end(); it++) {
        if (*it == tipo) return true;
    }
    return false;
}

bool ilha::verificaEdificioZona(int linha, int coluna) {
    if (zonas != nullptr) return zonas[linha][coluna].getTemEdificio();
    return false;
}

/*****************************/
/*     Construir edificio    */
/*****************************/
void ilha::construirEdificio(int linha, int coluna, const string& tipo) {
    if (zonas != nullptr) {
        zonas[linha][coluna].construirEdificio(tipo);
        zonas[linha][coluna].seTtemEdificio(true);

    }

}

/*****************************/
/* Obter edificios possiveis */
/*****************************/

string ilha::devolveEdiciosDisponiveis() {
    ostringstream  std;

    for (const auto& it: edificiosDisponiveis) {
        std << it <<" ";
    }
    return std.str();
}

/*****************************/
/*     Mover Trabalhador     */
/*****************************/

void ilha::moveTrabalhador(int linha, int coluna,const string& id) {
    bool tru= false;
    for (int i = 0; i < linhas ; i++ ) { /*DEBUG ACABAR*/
        for (int j = 0; j < colunas; j ++) {
            if (zonas != nullptr and zonas[i][j].verificaTrabalhador(id)) {


                zonas[linha][coluna].adicionarTrabalhador(zonas[i][j].getTrabalhador(id));

                zonas[i][j].removerTrabalhador(id);
                tru = true;
                break;
            }
        }
        if (tru) break;
    }

}
/*****************************/
/*     Remover Trabalhador   */
/*****************************/
void ilha::removerTrabalhador(const string& id) {

    for (int i = 0; i < linhas ; i++ ) {
        for (int j = 0; j < colunas; j ++) {
            if (zonas != nullptr and zonas[i][j].verificaTrabalhador(id)) {
                zonas[i][j].removerTrabalhador(id);
            }
        }
    }
}


/*****************************/
/* Construir zonas adjacentes*/
/*****************************/
void ilha::makeZonasAdjacentes() {


    for (int i =0; i < getLinhas(); i++) {
        for(int j = 0; j < getColunas(); j++) {
            if(zonas != nullptr) zonas[i][j].limpaVetor();

            if ((i -1 >= 0) and zonas!= nullptr) zonas[i][j].addZonaAdjacente(&zonas[i-1][j]); // Acima da sua linha
            if ((j + 1 < getColunas()) and zonas!= nullptr) zonas[i][j].addZonaAdjacente(&zonas[i][j+1]); // Direita da coluna
            if ((i +1 < getLinhas()) and zonas!= nullptr) zonas[i][j].addZonaAdjacente(&zonas[i+1][j]);// Em baixo da linha
            if ((j-1 >= 0) and zonas!= nullptr) zonas[i][j].addZonaAdjacente(&zonas[i][j-1]);//Esquerda da coluna

        }

    }

}

void ilha::adicionaDiaZonas() {

    for(int i = 0; i< getLinhas(); i++) {
        for (int j = 0; j< getColunas(); j++) {
            if (zonas != nullptr) zonas[i][j].adicionaDia();
        }
    }

}

int ilha::getNumberWorksZona(int linha, int coluna) {
    if (zonas != nullptr) return zonas[linha][coluna].getNumberWorker();
    return 0;
}

float ilha::getArmazenamentoZona(int linha, int coluna) {
    if (zonas != nullptr) return zonas[linha][coluna].getArmazenamentoZonas();
    return 0;
}

int ilha::getArmazenamentoEdificio(int linha, int coluna) {
    if (zonas != nullptr) return zonas[linha][coluna].getArmazenamentoEdificio();
    return 0;
}

void ilha::executaxDias() {
    for (int i = 0; i < getLinhas(); i ++) {
        for (int j = 0; j<getColunas(); j++) {


            if(zonas != nullptr) zonas[i][j].adicionaDia();


            if (zonas != nullptr) zonas[i][j].funcaoXDias();


            if (zonas != nullptr) {zonas[i][j].funcaoPorDia();


            }
        }
    }
}

bool ilha::getEdifUpgradable(int linha, int coluna) {
    if (zonas != nullptr) return zonas[linha][coluna].edifUpgradable();
    return false;
}

void ilha::upgradeEdificio(int linha, int coluna) {
    if (zonas != nullptr) zonas[linha][coluna].upgradeEdificio();

}
/*****************************/
/*Obter totalidade Recursos  */
/*****************************/

/*Esta funcao e responsavel por informar o numero total de recursos na ilha permitindo assim saber quantos recursos
 * se podem vender ou nao. */

int ilha::obtemRecursos(const string& Recurso) {
    int a = 0;
    for (int i = 0 ; i < getLinhas();i++) {
        for (int j = 0 ; j < getColunas(); j++) {
            if (zonas != nullptr and zonas[i][j].verificaRecurso()) {
                if (zonas[i][j].getTipoRecurso() == Recurso)
                    a += int (zonas[i][j].getQuantidadeRecurso());
            }
            if (zonas != nullptr and zonas[i][j].getTemEdificio()) {
                if (zonas[i][j].getRecursoEdificio() == Recurso) {
                    a += zonas[i][j].getArmazenamentoEdificio();
                }
            }
        }

    }

    return a;
}

string ilha::getEdificioRecurso(int linha, int coluna) {
    if (zonas != nullptr) return zonas[linha][coluna].getRecursoEdificio();
    return "";
}

bool ilha::getEstadoEdificio(int linha, int coluna) {
    if (zonas != nullptr) return zonas[linha][coluna].getEstadoEdificio();
    return false;
}

void ilha::setEstadoEdificio(int linha, int coluna, bool value) {
   if (zonas != nullptr) zonas[linha][coluna].setEstadoEdificio(value);
}

void ilha::removerEdificio(int linha, int coluna) {

    if (zonas != nullptr) zonas[linha][coluna].destruirEdificio();

}

void ilha::retiraRecursoEdificio(int linha, int coluna,int a) {
    if (zonas != nullptr) return zonas[linha][coluna].diminuiQtdRecurso(float(a));
}

int ilha::getxPas() const {
    return xpas;
}

int ilha::getyPas() const {
    return ypas;
}




