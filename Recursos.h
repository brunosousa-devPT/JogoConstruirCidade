//
// Created by bruno on 16/01/2022.
//

#ifndef TRABALHO_RECURSOS_H
#define TRABALHO_RECURSOS_H
#include "utils.h"

class Recursos {

    float quantidade;
    string tipo;
    float preco;
public:
    Recursos(string type, float price);

    float getQuantidade() const;
    string getTipo() const;


    void aumentaQuantidade(float a);
    void setQuantidade(float a);
    void diminuiQuantidade(float a);

};


class Ferro: public Recursos{

public:
    Ferro();

};
class Carvao: public Recursos{
public:
    Carvao();

};

class BarraDeAco: public Recursos{

public:
    BarraDeAco();
};
class Madeira: public Recursos{
public:
    Madeira();
};
class VigasDeMadeira: public Recursos{
public:
    VigasDeMadeira();
};
class Eletricidade: public Recursos{
public:
    Eletricidade();

};


#endif //TRABALHO_RECURSOS_H
