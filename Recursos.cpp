//
// Created by bruno on 16/01/2022.
//

#include "Recursos.h"



Recursos::Recursos(string type, float price): quantidade(0), tipo(std::move(type)),preco(price) {

}

float Recursos::getQuantidade() const {
    return quantidade;
}

string Recursos::getTipo() const {
    return tipo;
}



void Recursos::aumentaQuantidade(float a) {
    quantidade += a;
}

void Recursos::setQuantidade(float a) {
    quantidade = a;
}

void Recursos::diminuiQuantidade(float a) {
    cout <<"Chegou aqui 1";
    quantidade = quantidade - a;

}

Ferro::Ferro() : Recursos("Ferro", 1) {

}

Carvao::Carvao() : Recursos("Carvao", 1) {

}

BarraDeAco::BarraDeAco() : Recursos("BarraDeAco", 2) {

}

Madeira::Madeira() : Recursos("Madeira", 1) {

}

VigasDeMadeira::VigasDeMadeira() : Recursos("Vigas", 2) {

}

Eletricidade::Eletricidade() : Recursos("Eletricidade", 1.5) {

}
