#include <stdlib.h>
#include <stdio.h>
#define incrementaX 0x01<<6
#define decrementaX 0x01<<5
#define incrementaY 0x01<<4
#define decrementaY 0x01<<3


enum estados {inicio=0, dir, esq, baixo, cima};

char funcao(int entrada)
{
    char saida=inicio;
    int estadoAtual=(entrada&0x07);
    int start=(entrada&0x08)>>3;
    int direcao=(entrada&0x030)>>4;

    if(estadoAtual==inicio)
    {
        if(start)
        {
            saida=saida+dir;
        }
        else
        {
            saida=saida+inicio;
        }
    }

    else if(estadoAtual==dir)
    {
        saida=saida+incrementaX;
        if(direcao==0)
        {
            saida=saida+dir;
        }
        else if(direcao==1)
        {
            saida=saida+baixo;
        }
        else if(direcao==2)
        {
            saida=saida+dir;
        }
        else if(direcao==3)
        {
            saida=saida+cima;
        }
    }

    else if(estadoAtual==esq)
    {
        saida=saida+decrementaX;
        if(direcao==0)
        {
            saida=saida+esq;
        }
        else if(direcao==1)
        {
            saida=saida+baixo;
        }
        else if(direcao==2)
        {
            saida=saida+esq;
        }
        else if(direcao==3)
        {
            saida=saida+cima;
        }
    }

    else if(estadoAtual==baixo)
    {
        saida=saida+decrementaY;
        if(direcao==0)
        {
            saida=saida+esq;
        }
        else if(direcao==1)
        {
            saida=saida+baixo;
        }
        else if(direcao==2)
        {
            saida=saida+dir;
        }
        else if(direcao==3)
        {
            saida=saida+baixo;
        }
    }

    else if(estadoAtual==cima)
    {
        saida=saida+incrementaY;
        if(direcao==0)
        {
            saida=saida+esq;
        }
        else if(direcao==1)
        {
            saida=saida+cima;
        }
        else if(direcao==2)
        {
            saida=saida+dir;
        }
        else if(direcao==3)
        {
            //saida=saida+incrementaX;
            saida=saida+cima;
        }
    }
    return saida;
}

void main ()
{
    FILE *arquivo1;
    arquivo1 = fopen("snake.bin","w+");
    int entrada;
    char nois=0;
    for(entrada=0; entrada<64; entrada++)
    {
        nois=funcao(entrada);
        fprintf(arquivo1,"%02x ",nois);
    }
    fclose(arquivo1);
}

