//
// Created by bruno on 30/12/2021.
//

#include "edificio.h"
#include "zona.h"



edificio::edificio(Recursos* recu, string type,Zona *zonaEdif,const string& recur, int nivelM,int armMAC,int quantProd): tipo(std::move(type)),
        zonaDoEdificio(zonaEdif),armazenamento(0),armazenamentoMax(armMAC),
        quantidadeProduzida(quantProd),nivelAtual(1),nivelMax(nivelM),recur(recu),ligado(false){
        cout << "Edificio Criado!";

}

void edificio::aumentarNivel(int qtdProdAum, int qtdArmAum) {
    ++ nivelAtual;
    quantidadeProduzida += qtdProdAum;
    armazenamentoMax += qtdArmAum;

}

string edificio::getTipo() const {
    return tipo;
}

int edificio::getArmazenamento() const {
    return armazenamento;
}

bool edificio::produzir() {
    cout <<"Prod Edificio"<<endl;
    return false;
}

edificio::~edificio() {
    cout << "Edificio destruido na zona: Linha: " << zonaDoEdificio->obtemLinha() << "|| Coluna: "<< zonaDoEdificio->obtemColuna()<< endl;

}

bool edificio::Desabou() {
    return false;
}

int edificio::getArmazenamentoMax() const {
    return armazenamentoMax;
}

int edificio::getQuantidadeProduzida() const {
    return quantidadeProduzida;
}

Zona *edificio::getZonaEdificio() const {
    return zonaDoEdificio;
}



void edificio::verifcaAdj() {
    cout <<""<<endl;
}

void edificio::changeArmazenamento(int a) {
    armazenamento += a;

}

bool edificio::aumentarNivel() {
    return false;
}

int edificio::getnivelAtual() const {
    return nivelAtual;
}

int edificio::getnivelMAX() const {
    return nivelMax;
}

bool edificio::itsUpgradable() const {
    if (nivelMax == nivelAtual) {
        return false;
    }
    else
        return true;
}

string edificio::getRecurso() const {
    return recur->getTipo();
}



int edificio::getRecursoQuantidade() {
    return int(recur->getQuantidade());
}

void edificio::aumentaQuantidade() {
    recur->aumentaQuantidade(float(quantidadeProduzida)/2);
}



void edificio::diminuiQuantidade(int a) {
    cout <<"Chegou aqui 2";

    recur->diminuiQuantidade(float(a));
}

bool edificio::getEstadoEdificio() const {
    return ligado;
}

void edificio::setEstado(bool value) {
    ligado = value;
}





bateria::bateria(Zona *zonaEdif) : edificio(new Eletricidade,"bat", zonaEdif, "eletricidade", 5, 100,1),aumArmPorLevel(10),adajacenteCentral(false) {

}

bool bateria::produzir() {

    if (getEstadoEdificio() and adajacenteCentral and getArmazenamento() +1 <= getArmazenamentoMax() ) {
        Zona *a = getZonaEdificio();
        edificio *e;

        e  = a->getObjectEdificio("elec");
        if (!getEstadoEdificio() or getRecursoQuantidade() + a->getNumberOfAdjacentEdif("elec") > getArmazenamentoMax()) return false;

            changeArmazenamento(e->getQuantidadeProduzida()* a->getNumberOfAdjacentEdif("elec"));
        //setQuantidade(e->getQuantidadeProduzida()* a->getNumberOfAdjacentEdif("elec"));
            aumentaQuantidade();

/*DEBUG:: bat auto produz*/
        return true;
    }
    return false;
}

void bateria::verifcaAdj() {
    Zona *a = getZonaEdificio();
    if (a->verificaAdjacenciaEdificio("elec")) {
        adajacenteCentral = true;
    }
    else {
        adajacenteCentral = false;
    }

}

bool bateria::aumentarNivel() {
    if (getnivelMAX() <= getnivelAtual()) return false;
    edificio::aumentarNivel(0, aumArmPorLevel);
    return true;
}





centralEletrica::centralEletrica(Zona *zonaEdif)
        : edificio(new Carvao,"elec", zonaEdif, "Carvao", 1, 100, 1),
        adajcenteFloresta(false) {

}




void centralEletrica::verifcaAdj() {
    Zona *a = getZonaEdificio();
    if (a->verificaAdjacenciaZona("flr")) {
        adajcenteFloresta = true;
    }
    else {
        adajcenteFloresta = false;
    }


}

bool centralEletrica::produzir() {
    Zona *a = getZonaEdificio();
    string c = a->getTrabalhadores();
    bool value = false;

    for (int i = 0; i < a->getNumberWorker(); i++) {
        if (c[i] == 'O') {
            value = true;
            break;
        }
    }
    if (!getEstadoEdificio() or getArmazenamentoMax() < getArmazenamento() + getQuantidadeProduzida()) return false;

    if (adajcenteFloresta and value) {
        if (a->retiraRecursoZonaAdj(1,"Madeira")){

        aumentaQuantidade();

      //  changeArmazenamento(getQuantidadeProduzida());
        return true;
        }
    }
    return false;
}



mina::mina(Recursos * recu,string type, Zona *zonaEdif, const string& recur,int prob) :
            edificio(recu,move(type), zonaEdif, recur, 5, 100, 2),probDesabar(prob),
            prodAumPorLev(1),armAumPorLev(10){

}



bool mina::aumentarNivel() {
    if (getnivelMAX() <= getnivelAtual()) return false;
    edificio::aumentarNivel(prodAumPorLev, armAumPorLev);
    return true;
}


bool mina::Desabou() {
    if (randomNumber2(0,100) < probDesabar) return true;
    return false;
}

bool mina::produzir() {


    Zona *zon = getZonaEdificio();
    string a = zon->getTrabalhadores();
    if (getEstadoEdificio() or getArmazenamento() + getQuantidadeProduzida() < getArmazenamentoMax()) {
        for (int i = 0; i< zon->getNumberWorker(); i++) {
            if (a[i] == 'm' or a[i] == 'M') {
                aumentaQuantidade();
                changeArmazenamento(getQuantidadeProduzida());
                return true;
            }
        }
    }
    return false;
}


fundicao::fundicao(Zona *zonaEdif) : edificio(new BarraDeAco,"fun", zonaEdif, "BarraDeAco", 1, 100, 1),
            adjacenteMinaF(false),adjacenteMinaC(false),adjacenteCentral(false){

}

bool fundicao::produzir() {
    Zona *a = getZonaEdificio();

    string c = a->getTrabalhadores();
    bool value = false;


    for (int i = 0; i < a->getNumberWorker(); i++) {
        if (c[i] == 'O') {
            value = true;
            break;
        }
    }




    if (getEstadoEdificio()and (adjacenteCentral or adjacenteMinaC) and adjacenteMinaF and value) {


        if (getArmazenamentoMax() > getArmazenamento() + getQuantidadeProduzida()) {

            if (a->retiraRecursoEdifAdj(1,"Carvao") and a->retiraRecursoEdifAdj(1,"Ferro")) {


                aumentaQuantidade();
                return true;
            }
        }

    }

    return false;
}

void fundicao::verifcaAdj() {
    Zona *a = getZonaEdificio();
    if (a->verificaAdjacenciaEdificio("mnC")) {
        adjacenteMinaC = true;
    }


    else {
        adjacenteMinaC = false;
    }
    if (a->verificaAdjacenciaEdificio("elec")) {
        adjacenteCentral = true;
    }
    else adjacenteCentral = false;
    if (a->verificaAdjacenciaEdificio("mnF")) {
        adjacenteMinaF = true;
    }
    else adjacenteMinaF = false;

}
/*
* Fazer adjacencia funçao global
*
* */
serracao::serracao(Zona * zonaEdif) : edificio(new VigasDeMadeira,"ser", zonaEdif, "vdm", 5, 100, 1),
                                        aumArmPorLevel(10), adjacenteFloresta(false){



}

bool serracao::produzir() {
    Zona *a = getZonaEdificio();

    string c = a->getTrabalhadores();
    bool value = false;


    for (int i = 0; i < a->getNumberWorker(); i++) {
        if (c[i] == 'L') {
            value = true;
            break;
        }
    }




    if (!getEstadoEdificio() and getArmazenamentoMax() < getArmazenamento() + getQuantidadeProduzida()) return false;

    if (adjacenteFloresta and value) {
        if (a->retiraRecursoZonaAdj(1,"Madeira")){

            aumentaQuantidade();

            //  changeArmazenamento(getQuantidadeProduzida());
            return true;
        }
    }
    return false;
}

void serracao::verifcaAdj() {
    Zona *a = getZonaEdificio();
    if (a->verificaAdjacenciaZona("flr")) {
        adjacenteFloresta = true;
    }
    else {
        adjacenteFloresta = false;
    }
}

bool serracao::aumentarNivel() {
    if (getnivelMAX() <= getnivelAtual()) return false;
    edificio::aumentarNivel(0, aumArmPorLevel);
    return true;
}



/***
 *
 *DEBUG:: SERRARIA
 */