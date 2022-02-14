
#include "jogo.h"

jogo::jogo(ilha *island): ilhaJogo(island) {
    criaRecursos(); //DEBUG
    runGame();
}

void jogo::runGame() {
    cin.sync();

    while (runningGame) {
        if (faseJogo == 0) {
            mostrarIlha();

            faseJogo ++;

        }
        if (faseJogo == 1) {


            ilhaJogo->adicionaDiaZonas();


            obtemRecursos();
            cout << "\nAmanhecer\n" ;
            faseJogo ++;
        }
        if (faseJogo == 2) {
            cout <<"\nMeio-Dia\n";
           // string com;
            //getline(cin, com );
            obtemRecursos();
            runningGame = fasePedirComandos();
            if (!runningGame) break;
            faseJogo ++;

        }
        if (faseJogo == 3 and runningGame) {
            ilhaJogo->executaxDias();
            cout <<"\nAnoitecer\n";
            faseJogo = 1;
            dias++;
        }

    }
    mostrarIlha();


}


void jogo::mostrarIlha() {
    bool passou = false;
    bool passou2 = false;
    cout <<"\n\t";
    for (int i = 0; i < ilhaJogo->getColunas(); i++) {
        cout << "_____";
    }
    cout<<"_";
    if (!passou)
        cout <<"\t\t\t RECURSOS: ";
    cout <<"\n";
    for (int k = 0; k < ilhaJogo->getLinhas(); k++) {
        cout<<"\t";
        for (int j = 0; j < ilhaJogo->getColunas(); j++) {
            cout << "|"<< ilhaJogo->getTipoZona(k,j) << " ";


        }
        cout <<"|";
        if (passou and !passou2)
                cout <<"\t\t\t\t "<< recursosIlha[4]->getTipo() << ": "<< recursosIlha[4]->getQuantidade();
        cout << "\n\t";
        for (int j = 0; j<ilhaJogo->getColunas();j++) {
            int a = 0;
            if (ilhaJogo->verificaEdificioZona(k, j)) {
                cout << "|" << ilhaJogo->getEdificioZona(k, j);
                if (ilhaJogo->getEdificioZona(k, j).length() < 4) {
                    cout << " ";
                }
            }
            else
                cout <<"|    ";

        }

        cout <<"|";
        if (!passou)
            cout <<"\t\t\t\t "<< recursosIlha[0]->getTipo() << ": "<< recursosIlha[0]->getQuantidade();
        if (passou and !passou2)
                cout <<"\t\t\t\t "<< recursosIlha[5]->getTipo() << ": "<< recursosIlha[5]->getQuantidade();
        cout <<"\n\t";
        for (int j = 0 ; j < ilhaJogo->getColunas(); j++) {
            cout <<"|";
            int a = 0;
            cout << ilhaJogo->getWorkersZona(k,j);

            a = ilhaJogo->getNumberWorksZona(k,j);
            for (; a < 4; a++) {
                cout <<" ";
            }

        }
        cout <<"|";
        if (!passou)
            cout <<"\t\t\t\t "<< recursosIlha[1]->getTipo() << ": "<< recursosIlha[1]->getQuantidade();
        if (passou and !passou2) {
            cout <<"\t\t\t\t Dinheiro: " << cash;
            passou2 = true;
        }
        cout <<"\n\t";
        for (int j = 0; j < ilhaJogo->getColunas(); j ++) {
            cout << "|";
            int a = ilhaJogo->getNumberWorksZona(k,j);
            cout <<a;
            if (a >= 10)
                cout << "  ";
            if (a < 10 and a >= 0)
                cout <<"   ";

        }
        cout <<"|";
        if (!passou)
            cout <<"\t\t\t\t "<< recursosIlha[2]->getTipo() << ": "<< recursosIlha[2]->getQuantidade();
        cout << "\n\t";
        for (int j = 0; j < ilhaJogo->getColunas(); j++) {

            cout << "-----";
        }
        cout<<"-";
        if (!passou)
            cout <<"\t\t\t\t "<< recursosIlha[3]->getTipo() << ": "<< recursosIlha[3]->getQuantidade();
        cout <<"\n";
        passou = true;
    }

}

bool jogo::fasePedirComandos() {

    bool continua = true;
    while (continua) {
        int a = pedirComandos();
        switch (a) {
            case -1:
                cout <<"\nComando Nao existe! Tente um dos seguintes: \n"<<cmd.mostraComandos() << "\n";
                break;
            case 0:
                continua = exec(args);

                break;
            case 1:
                cons(0);
                break;
            case 2:
                liga_Desliga(0);
                break;
            case 3:
                liga_Desliga(1);
                break;
            case 4:
                move();
                break;
            case 5:
                vende();
                break;
            case 6:
                cont();
                break;
            case 7:
                if (args.length() == 0) {
                    mostrarIlha();

                }
                else
                    mostrarZona();

                break;

            case 8:
                continua = false;
                break;
            case 9:
                save();
                break;
            case 10:
                load();
                break;
            case 11:
                apaga();
                break;
            case 12:
                config(args);
                break;
            case 13:
                debcash();
                break;
            case 14:
                cons(1);
                break;
            case 15:
                debkill();
                break;
            case 16:

                return false;
            case 17:
                update();
                break;
            default:
                cout << "\nFatal error\n";
        }
    }
    return true;
}


int jogo::pedirComandos(const string& com) {
    args = "";
    string command, comandos, argss,aux;
    if (com.empty()) {
        cout << "Insira um comando: ";
        getline(cin, command);
    }
    else
        command = com;

    istringstream st(command);

    while (st >> aux) {

        if (comandos.empty())
            comandos = aux;


    }
    command.erase(0, comandos.length() +1); // tirar o comando principal para colocar os argumentos noutra variavel
    cout << command;

    if (cmd.verificaComando(comandos)) {

        this->comando = comandos;
        this->args = command;
        return cmd.getComandoIndex();

    }

    return -1;

}
/***************************************/
/*             CONTRATAR               */
/***************************************/

void jogo::cont() {
//obtem o x e o y da zona com a pastagem
    int x = ilhaJogo->getxPas();
    int y = ilhaJogo->getyPas();
    int prec;
    bool continua = true;
    if (args.length() > 1) {
        continua = false;}

    //verifica se o tipo de trabalhador e possivel
    char tipo = args[0];
    if((tipo == 'O' or tipo == 'M' or tipo =='L') and continua) {
        if (tipo == 'O') {
            prec = defs.getPrecTrab(0);
        }
        if (tipo == 'L') {
            prec = defs.getPrecTrab(1);
        }

        if (tipo == 'M') {
            prec = defs.getPrecTrab(2);
        }

        if (cash - prec >= 0) {
            ilhaJogo->contWorker(tipo, x, y,dias);
            cash -= prec;
            cout <<"Dinehiro: " <<cash << endl;
        }
        else {
            cout <<"Dinheiro Insuficiente para contratar o trabalhador" <<"\n";
        }

    }
    else
        cout << "\n cont <tipo>  Tipos: O, M, L\n";
}
/***************************************/
/*            FIM CONTRATAR            */
/***************************************/

//comandos pelo ficheiro
bool jogo::exec(const string &nomeFicheiro) {
    ifstream fich_leitura(nomeFicheiro);
    bool continua = true;
    if (fich_leitura.is_open()){

        while (getline(fich_leitura,comando)) {
            int a = pedirComandos(comando);
            switch (a) {
                case -1:
                    cout <<"\nComando Nao existe! Tente um dos seguintes: \n"<<cmd.mostraComandos() << "\n";
                    break;
                case 0:
                    exec(args);
                    break;
                case 1:
                    cons(0);
                    break;
                case 2:
                    liga_Desliga(0);
                    break;
                case 3:
                    liga_Desliga(1);
                    break;
                case 4:
                    move();
                    break;
                case 5:
                    vende();
                    break;
                case 6:
                    cont();
                    break;
                case 7:
                    if (args.length() == 0) {
                        mostrarIlha();
                        break;

                    }
                    else
                        mostrarZona();

                    break;
                case 8:

                    fich_leitura.close();
                    return false;
                case 9:
                    save();
                    break;
                case 10:
                    load();
                    break;
                case 11:
                    apaga();
                    break;
                case 12:
                    config(args);
                    break;
                case 13:
                    debcash();
                    break;
                case 14:
                    cons(1);
                    break;
                case 15:
                    debkill();
                    break;
                case 16:
                    runningGame = false;
                    fich_leitura.close();

                    return false;
                case 17:
                    update();
                    break;

                default:
                    cout << "\nFatal error\n";
            }

        }
    }
    else
        cout <<"error";



    fich_leitura.close();
    return continua;
}

void jogo::mostrarZona() {
    int iterador = 0;
    stringstream ss(args);
    bool continua = true;
    bool temEdif;
    int linha, coluna;
    int index = 0;

    ss >> linha >>coluna;
    linha--;
    coluna --;

    if (linha > ilhaJogo->getLinhas() or linha < 0 or coluna >ilhaJogo->getColunas() or coluna < 0) {
        cout <<"\nInsira uma posicao disponivel\n";
        continua = false;
    }

    if (continua) {

        //obtem informacoes da zona pedida
        cout << "\n\n\n\nTipo de Zona: "<< ilhaJogo->getTipoZona(linha, coluna)<< "\n";
        temEdif = ilhaJogo->verificaEdificioZona(linha,coluna);
        if (!temEdif)
            cout << "Tem edificio construido: nao\n" ;

        else{
            cout << "Tem edificio construido: sim\n" ;

            cout << "Tipo Edificio: " << ilhaJogo->getEdificioZona(linha,coluna)<<"\n";
            cout << "Tipo de Recurso: "<< ilhaJogo->getEdificioRecurso(linha,coluna)<<"\n";
            cout << "Armazenamento Edificio: "<< ilhaJogo->getArmazenamentoEdificio(linha,coluna)<< "\n"; /***DEBUG:: ARMAZENAMENTO EDIFICIO E RECURSO **/
        }
        cout << "\nTrabalhadores na zona: ";
        cout << ilhaJogo->getWorkersZona(linha,coluna);



        cout << "\n Numero de trabalhadores na zona: " << ilhaJogo->getNumberWorksZona(linha,coluna) << endl;
        string b = ilhaJogo->getTipoZona(linha,coluna);
        if (b =="vul" or b == "mnt" or b == "flr")
            cout <<"\n Armazenamento: "<< ilhaJogo->getArmazenamentoZona(linha,coluna) <<"\n";
        if (b == "flr")
            cout <<"Quantidade de árvores: \n"; /*DEBUG*/
    }

    if (!continua)
        cout << "\nComando Invalido: " << "list <linha> <coluna> \n";

}

void jogo::liga_Desliga(int ligades) {
    stringstream ss(args);
    int linha, coluna;
    bool continua= true;
    ss >> linha >>coluna;
    linha--;
    coluna--;
    //verifica se as linhas estao possiveis
    if (linha >= ilhaJogo->getLinhas() and linha < 0 and coluna >=ilhaJogo->getColunas() and coluna < 0) {
        cout <<"\nInsira uma posicao disponivel\n";
        continua = false;
    }
    if (!ilhaJogo->verificaEdificioZona(linha,coluna)) continua = false;

    if (continua) {


        if (ligades == 0) {//comando liga
            if (ilhaJogo->getEstadoEdificio(linha,coluna))
                cout << "\nEdificio ja esta ligado. \n";
            else {
                if (ilhaJogo->verificaEdificioZona(linha,coluna)) {
                    ilhaJogo->setEstadoEdificio(linha,coluna,true);
                    cout <<"\n Edificio ligado\n";
                }
                else {
                    cout <<"\nNão existe um edificio!\n";
                }

            }

        }
        else {
            if (!ilhaJogo->getEstadoEdificio(linha,coluna))
                cout << "\nEdificio ja esta desligado. \n";
            else {
                ilhaJogo->setEstadoEdificio(linha,coluna,false);
                cout <<"\n Edificio desligado\n";
            }
        }

    }
    else {
        if (!ilhaJogo->verificaEdificioZona(linha,coluna)) {
            cout <<"\nNao existe um edificio nesta zona!"<<endl;
        }
        else {
            if (ligades == 0)
                cout << "\nCOMANDO ERRADO: liga <linha> <coluna>";
            else
                cout << "\nCOMANDO ERRADO: desliga <linha> <coluna>";
        }

    }
}
/*DEBUG::*/
void jogo::config(const string &nome) {
    ifstream fich_leitura(nome);
    int a;

    string st;
    int i = 0;
    string op1;
    string op2;
    string aux;
    int c;
    if (fich_leitura.is_open()) {
        cout <<"\n";
        while(getline(fich_leitura,st)) {
            cout << "Lido do ficheiro: " << st << "\n";

            if (st.length() > 4){
                aux = st;
                op1 =st.substr(0,4);
                op2 = st.substr(4,5);
                cout <<"DE:"<<op1<<" "<<op2;
            }
            else {
                aux = st;
                op1 =st.substr(0,2);
                op2 = st.substr(2,3);
                cout <<"DE:"<<op1<<" "<<op2;
            }
            istringstream ss(op2);

            if (op1 == "mnF ") {
                ss >> c;
                defs.modificaPrecoConstrucaoEuros(c, 0);
            }
            if (op1 == "mnC ") {
                ss >> c;
                defs.modificaPrecoConstrucaoEuros(c, 1);
            }
            if (op1 == "elec") {
                ss >> c;
                defs.modificaPrecoConstrucaoEuros(c, 2);
            }
            if (op1 == "bat ") {
                ss >> c;
                defs.modificaPrecoConstrucaoEuros(c, 3);
            }
            if (op1 == "fun ") {
                ss >> c;
                cout <<"DEBUG:"<<c;
                defs.modificaPrecoConstrucaoEuros(c, 4);
            }
            if (op1 == "ser ") {
                ss >> c;
                defs.modificaPrecoConstrucaoEuros(c, 5);
            }
            if (op1 == "O ") {
                ss >> c;
                defs.modificaPrecoTrabalhador(c, 0);
            }
            if (op1 == "L ") {
                ss >> c;
                cout << "DEB: "<< ss.str();
                defs.modificaPrecoTrabalhador(c, 0);
            }
            if (op1 == "M ") {
                ss >> c;
                defs.modificaPrecoTrabalhador(c, 0);
            }

        }
    }
    else
        cout << "Nome do ficheiro errado!\n";
    fich_leitura.close();

}

void jogo::move() {
    istringstream st(args);
    stringstream ss;
    string aux;
    int line,coluna,iterador = 0;
    string tipos;
    while(st >> aux) {
        if (iterador == 0) {
            tipos = aux;
        }
        else
            ss << " " << aux;

        ++ iterador;
    }
    bool avanca = true;

    ss >> line >> coluna;
    line--;
    coluna--;
    if (coluna < 0 or line < 0 or coluna >= ilhaJogo->getColunas()  or line >= ilhaJogo->getLinhas() ) {

        avanca = false;

    }


    if (avanca) {
        ilhaJogo->moveTrabalhador(line, coluna, tipos);
        cout << "\nComando realizado com sucesso ID: " << tipos << "\n";
    }
    else
        cout <<"\nERRO NO COMANDO: move <ID> <linha> <coluna> \n";
}

void jogo::load() {

}

void jogo::save() {
    sSavesCurrent.adicionaJogo(this);
}

void jogo::apaga() {
    sSavesCurrent.deleteJogo(0);
}

void jogo::debkill() {
    bool eliminou = true;
    ilhaJogo->removerTrabalhador(args); // mudar para bool return


    if (eliminou)
        cout <<"\nTrabalhador eliminado com sucesso!\n";
    else
        cout <<"\nNão foi possível eliminar o trabalhador com o id "<< args<<"\n";

}

void jogo::debcash() {
    int saldo;
    stringstream ss(args);
    ss >> saldo;
    bool avanca = true;
    if (saldo == 0) {
        cout << "\nCOMANDO ERRADO: debcash <valor>\n";
        avanca = false;
    }
    if (avanca) {
        cash += saldo;
        cout << "\nDinheiro disponivel: " << cash << "\n";
    }
}

void jogo::vende() {
    int linha, coluna;
    stringstream ss(args);
    //verificar tipo de argumentos se linha ou coluna forem 0 sera considerado serem strings
    ss >> linha >> coluna;
    bool verificaVende=false;
    if (linha != 0 and coluna !=0 )
        verificaVende = true;
    bool continua = true;
    if (verificaVende and (linha < 0 or coluna <0 )) {
        cout <<"\n Linha ou coluna invalida\n";
        continua = false;
    }//verificar se linhas e o colunas sao validas
    if (verificaVende and continua) {
        linha--;
        coluna--;
        if (linha >= ilhaJogo->getLinhas() or ilhaJogo->getColunas() <= coluna or linha < 0 or coluna < 0) {
            cout << "\n Linha ou coluna invalida2" <<"\n";

        }
        else {
            if (ilhaJogo->verificaEdificioZona(linha,coluna)) {
                string edifi = ilhaJogo->getEdificioZona(linha,coluna);
                int preco = defs.getConsPrecoEu(defs.getIndexConstrucoes(edifi));
                string recurso = ilhaJogo->getEdificioRecurso(linha,coluna);
                int preco_VendaR = defs.getRecursosPrecos(defs.getIndexRecursos(recurso));
                int quantidade = ilhaJogo->getArmazenamentoEdificio(linha,coluna);
                cash += quantidade * preco_VendaR;
                cash += preco;
                ilhaJogo->removerEdificio(linha,coluna);

            }
            else {
                cout <<"Não tem edificio nesta zona!\n";
            }

        }
    }
    //verificacao do tipo de recursos ainda a ser implementada visto que recursos ainda nao foram implementados
    if(!verificaVende) {
        int quanto;
        stringstream std(args);
        string tipoRecurso;
        std >> tipoRecurso >> quanto;
        int auxilia;
        int i = 0,j=0;
        string axz;
        int resto ;
        int poc;
        poc = quanto;


        int precoRecurso = defs.getRecursosPrecos(defs.getIndexRecursos(tipoRecurso));

        if (quanto < 1) {
            cout << "\nCOMANDO VENDE RECURSOS: vende <tipo> <quanto> \n";
        }
        else {
            cout << "\nCOMANDO VALIDADO: " << tipoRecurso << " "<<quanto <<endl;
            if (quanto > 0 ) {
                if (quanto > ilhaJogo->obtemRecursos(tipoRecurso)) {
                    cout <<"Não tem recursos suficientes para isso!\n";
                }
                else {
                    cout <<"HELLO231\n";
                    while(quanto > 0) {
                        cout <<"HELLO100\n";
                        if (ilhaJogo->verificaEdificioZona(linha,coluna)){
                            cout <<"HELLO1\n";

                            axz = ilhaJogo->getEdificioRecurso(i,j);
                            cout <<"HELLO2\n";

                            if (axz == tipoRecurso) {
                                cout <<"HELLO3\n";

                                auxilia = ilhaJogo->getArmazenamentoEdificio(i,j);
                                cout <<"HELLO4\n";

                                quanto -= auxilia;
                                cout <<"HELLO5\n";

                                if (quanto < 0) {
                                    resto = -1 * quanto;
                                }
                                else {
                                    resto = auxilia;
                                }
                                cout <<"HELLO6\n";

                                ilhaJogo->retiraRecursoEdificio(i,j,resto);
                                cout <<"HELLO7\n";


                            }
                            if (quanto <= 0) {
                                cash += poc;
                                cout <<"Vendido com sucesso!\n";
                                obtemRecursos();
                                break;
                            }

                        }

                        j++;

                        if (j == ilhaJogo->getColunas()){
                            j = 0;
                            i++;
                        }



                    }
                }
            }
            else{
                cout <<"Insira uma quantia válida!\n";
            }

        }

    }

    if (!continua)
        cout <<"\nComandos Vende: vende <tipo> <quanto> ||  OR ||  vende <linha> <coluna> \n";
}


/***************************************/
/*            CONSTRUIR                */
/***************************************/

void jogo::cons(int a) {



    istringstream st(args);
    stringstream ss;
    string aux;
    int line,coluna,iterador = 0;
    string tipos;
    //verificacao dos argumentos (tipo e limitaçoes)
    while(st >> aux) {
        if (iterador == 0) {
            tipos = aux;

        }
        else
            ss << " " << aux;

        ++ iterador;
    }
    if (iterador < 3 )
        return;
    bool avanca = false;
    bool ErrolIas= false;
    bool temedificio;
    ss >> line >> coluna;
    line--;
    coluna--;
    //verifica se a coluna e a linha sao possiveis
    if (coluna < ilhaJogo->getColunas() and line < ilhaJogo->getLinhas() and line >= 0 and coluna >= 0) {

        avanca = true;
    }
    if (coluna < 0 or line < 0 or line >=ilhaJogo->getLinhas() or coluna >= ilhaJogo->getColunas()) {

        avanca = false;
        ErrolIas = true;
    }

    int precoEu = 0;

    bool construi = false;
    if (avanca)
        temedificio = !ilhaJogo->verificaEdificioZona(line,coluna); // true (nao tem) false (tem)
    //verifica se ja esta construido algum edificio
    if (ilhaJogo->edificioDisponivel(tipos) and avanca and temedificio) {
        int index;
        index = defs.getIndexConstrucoes(tipos);
        if (a == 0){
            if ((defs.getPrecoMelhEu(index) < cash and defs.getConsPrecoVig(index) > vigasdeMadeira) or (defs.getConsPrecoVig(index) == 0 and defs.getPrecoMelhEu(index) < cash )) {
                if (index != 3) {
                    ilhaJogo->construirEdificio(line,coluna,tipos);
                    cash -= defs.getConsPrecoEu(index);
                    construi = true;
                }
                else
                    construi = false;
                    //cout <<"Recursos insuficientes para a construcao de: " << tipos << endl;
            }
            if (defs.getPrecoMelhEu(index) > cash and defs.getConsPrecoVig(index) < vigasdeMadeira) {
                if (index != 3) {
                    ilhaJogo->construirEdificio(line,coluna,tipos);
                    vigasdeMadeira -= defs.getConsPrecoVig(index);
                    construi = true;
                }
                else
                    construi = false;
            }
            if (!construi and defs.getPrecoMelhEu(index) < cash and defs.getConsPrecoVig(index) < vigasdeMadeira ) {
               if (index == 3){
                    ilhaJogo->construirEdificio(line,coluna,tipos);
                    cash -= defs.getConsPrecoEu(index);
                    vigasdeMadeira -= defs.getConsPrecoVig(index);
                    construi = true;}
               else {
                   ilhaJogo->construirEdificio(line,coluna,tipos);
                   vigasdeMadeira -= defs.getConsPrecoVig(index);
                   construi = true;
               }
            }

            if (!construi) {
                cout <<"Recursos insuficientes para a construcao de: " << tipos << endl;
            }
            else
                cout << "\nDinheiro: " << cash << " | Vigas: " << vigasdeMadeira << endl;
            //ilhaJogo->construirEdificio(line,coluna,tipos);

            cout <<"\nEdificio criado com sucesso!\n" << endl;
            args = "";

        }
        else{
            ilhaJogo->construirEdificio(line,coluna,tipos);
            cout <<"\nEdificio criado com sucesso!\n" << endl;
        }

    }
    else {
        if (ErrolIas) {
            cout << "\nLinhas Maximas: "<< ilhaJogo->getLinhas() << " | Colunas Maximas: " << ilhaJogo->getColunas() ;
        }
        else if(!temedificio) {
            cout << "\nJa existe um edificio nessa zona.\n";

        }
        else{
            cout << "\nErro na criacao de edificio\nCOMANDO: cons <tipo> <linha> <coluna> \n << Tipos: " << ilhaJogo->devolveEdiciosDisponiveis()<<"\n";
            args = ""; }
    }
}


/***************************************/
/*            FIM CONSTRUIR            */
/***************************************/


/***************************************/
/*             CONTRATAR               */
/***************************************/

void jogo::update() {
    stringstream ss(args);

    int linha, coluna;
    bool continua= true;
    if (args.empty()) {
        cout <<"Comando Invalidao!\n update <linha> <coluna>" << endl;
        return;
    }
    ss >> linha >>coluna;
    linha --;
    coluna--;
    //verifica se as linhas estao possiveis
    if (linha >= ilhaJogo->getLinhas() or linha < 0 or coluna >=ilhaJogo->getColunas() or coluna < 0 or linha < 0) {
        cout <<"\nInsira uma posicao disponivel\n";
        continua = false;
    }

    if (!ilhaJogo->verificaEdificioZona(linha,coluna)) continua = false;
    if (continua) {
        if (ilhaJogo->getEdifUpgradable(linha,coluna)) {
            string edificio = ilhaJogo->getEdificioZona(linha,coluna);
            int index = defs.getIndexConstrucoes(edificio);
            if (vigasdeMadeira >= defs.getPrecoMelhVig(index)  and cash >= defs.getPrecoMelhEu(index)){
                vigasdeMadeira -= defs.getPrecoMelhVig(index);
                cash -= defs.getPrecoMelhEu(index);
                ilhaJogo->upgradeEdificio(linha,coluna);
                cout << "Edificio Melhorado com sucesso!"<<endl;

            }
            else {
                cout <<"Recursos insuficientes!" << endl;
            }


        }
        else {
            cout << "Edificio nao melhoravels!"<<endl;
        }

    }
    else {
        cout <<"Comando Invalidao!\n upgrade <linha> <coluna>" << endl;
    }

}


void jogo::criaRecursos() {

    recursosIlha.push_back(new Ferro());
    recursosIlha.push_back(new Madeira());
    recursosIlha.push_back(new VigasDeMadeira());
    recursosIlha.push_back(new Eletricidade());
    recursosIlha.push_back(new Carvao());
    recursosIlha.push_back(new BarraDeAco());

}

void jogo::obtemRecursos() {

    for (auto it: recursosIlha) {
        it->setQuantidade(float(ilhaJogo->obtemRecursos(it->getTipo())));
    }

}
