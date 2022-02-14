//
// Created by bruno on 30/12/2021.
//

#include "zona.h"
#include <sstream>


Zona::Zona(Recursos * rec, string tp,int arv, float materialProdz, int days, int mArvo, int trabPro, float red): tipoZona(std::move(tp)), linha(0), coluna(0),
                                                                    temEdificio(false),edif(nullptr),arvores(arv),
                                                                    materialProduzidoPT(materialProdz),dias(days),
                                                                    MaxArvores(mArvo), armazenamento(0),reducao(red),trabProb(trabPro),diasSeguidos(0),recur(rec){
}

int Zona::obtemLinha() const {
    return linha;
}

int Zona::obtemColuna() const {
    return coluna;
}


bool Zona::adicionarTrabalhador(char tipo, int x, int y, int diass) {

    if (tipo == 'O' or tipo == 'o') {
        trabalhadores.push_back(new operario(tipo,x,y,diass));

        return true;
    }
    if (tipo == 'M' or tipo == 'm') {
        trabalhadores.push_back(new mineiro(tipo,x,y,diass));
        return true;
    }
    if (tipo == 'L' or tipo == 'l') {
        trabalhadores.push_back(new lenhador(tipo,x,y,diass));
        return true;
    }
    return false;

}

bool Zona::removerTrabalhador(const string& id) {
    int i = 0;
    for (auto it: trabalhadores) {
        if (it->obterID() == id) {
            trabalhadores.erase(trabalhadores.begin()+i);
            delete it;
            return true;
        }
        i++;
    }
    return false;
}
void Zona::construirEdificio(const string& tipo) {
    if (tipo == "mnF")
        edif = new mina(new Ferro,tipo, this,"Ferro",15);
    if (tipo == "mnC")
        edif = new mina(new Carvao,tipo, this,"Carvao",10);
    if (tipo == "elec")
        edif = new centralEletrica( this);
    if (tipo == "bat")
        edif = new bateria(this);
    if (tipo == "fun")
        edif = new fundicao(this);
    if (tipo == "ser")
        edif = new serracao(this);
    temEdificio = true;

} /*ALERT : DEBUG: CONSTRUIR SERRACAO*/

void Zona::destruirEdificio() {

    if (temEdificio)
        delete(edif);


    temEdificio = false;

}

string Zona::obtemTipoZona() const {
    return tipoZona;
}

void Zona::setColuna(int col) {
    coluna = col;
}

void Zona::setLinha(int lin) {
    linha = lin;
}

void Zona::seTtemEdificio(bool value) {
    temEdificio = value;
}

string Zona::getTrabalhadores() const {
    ostringstream  std;
    int a = 0;
    for (auto it:trabalhadores) {
        if (a == 4)
            break;
        std << it->obterTipoTrabalhador();
        a++;
    }
    return std.str();

}

string Zona::getEdificio() {
    if (temEdificio)
        return edif->getTipo();
    else
        return " ";
}

bool Zona::getTemEdificio() const {
    return temEdificio;
}

bool Zona::verificaTrabalhador(const string& id) {
    for (auto it:  trabalhadores ) {
        if (it->obterID() == id )
            return true;
        if (it->getDias() < -100) return false;
    }
    return false;



}


Floresta::Floresta() : Zona(new Madeira,"flr",20, 1, 2, 100,0) {

}

Deserto::Deserto() : Zona(nullptr,"dsr",0, 0, 0, 0, 0,0.5) {

}

Montanha::Montanha(): Zona(new Ferro,"mnt",0,0.1,0,0,5){

}

void Zona::funcaoXDias() {
    if (temEdificio)
        edif->verifcaAdj();

    if (tipoZona == "vul" and dias == diasSeguidos) {
       diasSeguidos= 0;
       destruirEdificio();
       for (auto it: trabalhadores) {
           removerTrabalhador(it->obterID());
       }

    }


    if (tipoZona == "pnt" and dias == diasSeguidos) {

        diasSeguidos = 0;

        destruirEdificio();

        for(auto it: trabalhadores) {

            removerTrabalhador(it->obterID());
        }
    }

    if (tipoZona == "flr" and dias == diasSeguidos) {
        diasSeguidos = 0;
        if (arvores <= 100 and !temEdificio) arvores ++;


    }



}

void Zona::funcaoPorDia() {

    for (auto it:trabalhadores) {
        it->aumentaDias();
        if (tipoZona != "pas") {
            if (it->obterTipoTrabalhador() == 'O')
                if (trabalhador::demitir(5) and it->getDiasTrabalhados())
                    removerTrabalhador(it->obterID());
            if (it->obterTipoTrabalhador() == 'M')
                if(trabalhador::demitir(10) and it->getDiasTrabalhados()) {
                    removerTrabalhador(it->obterID());
                }
        }
    }

    if (temEdificio) {
        if (verificaRecurso()) {


        }

        if (edif->produzir()) {
            edif->aumentaQuantidade();
            edif->changeArmazenamento(edif->getQuantidadeProduzida());
        }
    }


    if (temEdificio) {
        if ((edif->getTipo() == "mnF" or edif->getTipo() == "mnC") and edif->Desabou()) {

            destruirEdificio();

        }

    }


    if (tipoZona == "vul" ) {

        int count = 0;
        for (auto it: trabalhadores) {
            if (trabalhador::demitir(trabProb))
                removerTrabalhador(it->obterID());
            //condicao fase
            if (it->obterTipoTrabalhador() == 'L' or it->obterTipoTrabalhador() == 'l') count ++;
            if (it->obterTipoTrabalhador() == 'M' or it->obterTipoTrabalhador() == 'm') count += 2;

        }

        aumentaQtdRecurso(float(count));


    }
    if (tipoZona == "mnt") {
        float count = 0;


        for (auto it: trabalhadores) {
            if (trabalhador::demitir(trabProb + 5)) {
                removerTrabalhador(it->obterID());
            }
            count ++; // condicao fase
        }

        armazenamento += float(double(count) * 0.1);
        aumentaQtdRecurso(count);




    }

    if (tipoZona == "flr") {
       if (!temEdificio and arvores > 0) arvores--;
       float count = 0;
       for (auto it: trabalhadores) {
           if (it->obterTipoTrabalhador() == 'L' or it->obterTipoTrabalhador() == 'l') {
               count ++;
           }
       }
       armazenamento += (1* count);
       aumentaQtdRecurso(1*count);


    }

    if (tipoZona == "dsr" || tipoZona == "pnt") {
        for (auto it:trabalhadores) {
            if (trabalhador::demitir(trabProb)) {
                removerTrabalhador(it->obterID());
            }
        }
    }


    dias++;

}

int Zona::getNumberWorker() const {
    int count = 0;
    for (__attribute__((unused)) auto  it: trabalhadores)
        count ++;
    return count;
}

void Zona::addZonaAdjacente(Zona * z) {
    zonasAdjacentes.push_back(z);


}

void Zona::limpaVetor() {

    zonasAdjacentes.clear();
    zonasAdjacentes.shrink_to_fit();

}

bool Zona::verificaAdjacenciaEdificio(const string& tipo) {
    for(auto it: zonasAdjacentes) {
        if (it->temEdificio) {
            if (it -> getEdificio() == tipo)
                return true;
            }
        }
    return false;
}

bool Zona::verificaAdjacenciaZona(const string &tipo) {
    for (auto it: zonasAdjacentes) {
        if (it->obtemTipoZona() == tipo) return true;
        if(it->tipoZona == "DEBUG") return false;
    }

    return false;
}

edificio *Zona::getObjectEdificio(const string& tipo) {
    for(auto it: zonasAdjacentes) {

        if (it->getEdificio() == tipo) {
            return it->edif;
        }
    }
    return nullptr;
}

int Zona::getNumberOfAdjacentEdif(const string& tipo) {
    int a= 0;

    for (auto it:zonasAdjacentes) {
        if (it->getEdificio() == tipo)
            a++;
    }

    return a;
}

void Zona::adicionaDia() {
    diasSeguidos++;

}

float Zona::getArmazenamentoZonas() const {
    return armazenamento;
}

int Zona::getArmazenamentoEdificio() {
    return edif->getRecursoQuantidade();
}

trabalhador *Zona::getTrabalhador(const string& id) {
    for (auto it: trabalhadores) {
        if (it->obterID() == id) {
            return it;
        }
    }
    return nullptr;
}

bool Zona::edifUpgradable() {
    if (temEdificio)
        return edif->itsUpgradable();
    else return false;
}

void Zona::upgradeEdificio() {
    if (temEdificio)   edif->aumentarNivel();
}

void Zona::adicionarTrabalhador(trabalhador *p) {
    trabalhador * a = p->duplica();
    trabalhadores.push_back(a);
}

float Zona::getQuantidadeRecurso() {
    if (recur != nullptr)
        return recur->getQuantidade();
    return 0;
}

bool Zona::verificaRecurso() {
    if (recur != nullptr) return true;
    return false;
}

string Zona::getTipoRecurso() {
    return recur->getTipo();
}

void Zona::aumentaQtdRecurso(float a) {
    recur->aumentaQuantidade(a);

}

void Zona::diminuiQtdRecurso(float a) {
    cout <<"Chegou aqui 3";

    recur->diminuiQuantidade(a);
}

bool Zona::retiraRecursoZonaAdj(int a, const string& rec) {

    for (auto it: zonasAdjacentes) {



        if (it->verificaRecurso()) {



            if (it->getTipoRecurso() == rec) {



                if (it->getQuantidadeRecurso() >= 1) {



                    it->diminuiQtdRecurso(float(a));
                    return true;
                }

            }

        }
    }
    return false;
}

string Zona::getRecursoEdificio() {
    return edif->getRecurso();
}

bool Zona::retiraRecursoEdifAdj(int a, const string &rec) {
    cout <<"Hello1";
    for (auto it: zonasAdjacentes) {
        cout <<"Hello2";
        if (it->temEdificio) {
            if (it->getRecursoEdificio() == rec) {
                cout <<"Hello4";

                if (it->getArmazenamentoEdificio() >= 1) {
                    cout <<"Hello5";


                    it->edif->diminuiQuantidade(a);
                    return true;
                }

            }

        }



    }
    return false;
}

bool Zona::getEstadoEdificio() {
    return edif->getEstadoEdificio();
}

void Zona::setEstadoEdificio(bool value) {
    edif->setEstado(value);
}


/*********
 *  DEBUG RECURSOS
 * **/

Pantano::Pantano(): Zona(nullptr,"pnt",0,0,10,0,0) {

}

Pastagem::Pastagem():Zona(nullptr,"pas",0,0,0,0,0) {

}

Vulcao::Vulcao():Zona(new Carvao,"vul",0,2,5,0,25,300) {

}
