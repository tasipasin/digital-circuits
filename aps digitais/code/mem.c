#include <stdlib.h>
#include <stdio.h>
#define led << 5


char funcao(int entrada){
int estadoAtual=entrada&0x03;
int botao=entrada&0x04;
int rand=entrada&0x06;
int sens1=entrada&0x07;
int sens2=entrada&0x08;
int sens3=entrada&0x09;
}

void main ()
{
    int entrada = 0;
    for(int x=0; x<8192; x++){
funcao(entrada);
    }

}


