#include "ilha.h"
#include "jogo.h"
int main() {
    int a = getLinhas();
    int b = getColunas();

    ilha i(a,b);

    jogo jog(&i);


}
