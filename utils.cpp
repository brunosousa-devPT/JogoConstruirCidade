//
// Created by bruno on 20/11/2021.
//

#include "utils.h"
#include <sstream>
#include <time.h>

using namespace std;

//Funcao para obter Id do trabalhador em string FORMAT: NTRABALHADOR.DAYSOFTHEWORD EX: 12.3 -> 12 trabalhador criado no
//3 dia do mundo
string getWorkerString(int Days, int Ntrabalhador) {

    ostringstream  st;

    st << Ntrabalhador << '.' << Days;
    return st.str();

}


//uso da funcao rand para obter um numero random. Nao e necessario usar time pois esta funcao e chamada individualmente
//fazendo com que o numero seja sempre aleatorio
int randomNumber() {

   // srand(time(0));

    return rand()%6;

}
int randomNumber2(int a, int b) { // b- range, a- intervalo iniccial
    srand(time(0));
    return rand() % b + a;
}
//obter linhas do user, garante que este so use numeros
int getLinhas() {
    int linhas;
    do {
        cout << "\nInsira numero de linhas: ";
        cin >> linhas;
        while (cin.fail()) {
            cin.clear();
            cin.ignore();

            cout << "\nPut an integer between 3 and 8\n" << endl;
            cout << "\nInsira numero de linhas: ";
            cin >> linhas;
        }
        if (linhas < 3 or linhas > 8)  cout << "\nPut an integer between 3 and 8\n" << endl;
    }while(linhas < 3 or linhas > 8);

    return linhas;
}
int getColunas() {
    int colunas;
    do {

        cout << "\nInsira numero de colunas: ";
        cin >> colunas;
        while (cin.fail()) {
            cin.clear();
            cin.ignore();

            cout << "\nPut an integer between 3 and 16\n" << endl;
            cout << "\nInsira numero de colunas: ";
            cin >> colunas;
        }
        if (colunas < 3 or colunas > 16)  cout << "\nPut an integer between 3 and 16\n" << endl;

    }while(colunas < 3 or colunas > 16);
    return colunas;
}

