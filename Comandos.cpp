//
// Created by bruno on 21/11/2021.
//

#include "Comandos.h"



/*****************************/
/*     Valida Comando        */
/*****************************/

bool Comandos::verificaComando(const string& comando) {

    vector <string>::iterator it;
    int o = 0;
    for (it = commands.begin(); it!= commands.end(); it++,o++) {
        if (*it == comando) {

            comandoIndex = o;
            return true;
        }

    }
    this->comandoIndex = -1;
    return false;
}


int Comandos::getComandoIndex() const {
    return comandoIndex;

}

string Comandos::mostraComandos() {
    ostringstream  st;
    for (const auto& it: commands) {
        st << it + " ";
    }
    return st.str();
}
