#include <stdio.h>
#include <stdlib.h>

enum ESTADOS {inicio = 0, esperaSensor, led0, led1, led2, incrementa, zera, RESETA_JOGO};
enum SAIDAS {INI = 0, ATI = 0, LD1 = 16, LD2 = 8, LD3 = 4, acr = 2, rst = 1};

int main()
{
    FILE *arquivo1;
    FILE *arquivo2;
    FILE *arquivo3;
    arquivo1 = fopen("logica_hex","w+");
    arquivo2 = fopen("logica","w+");
    arquivo3 = fopen("bin.bin","wb");

    int str, sensor1, sensor2, sensor3, randm, sr, tmr, ini_bits, pr_state = inicio, nx_state = inicio;

    for(ini_bits = 0; ini_bits <= 3; ini_bits++)
    {
        for(str = 0; str <= 1; str++)
        {
            for(randm = 0; randm <= 3; randm++)
            {
                for(sensor1 = 0; sensor1 <= 1; sensor1++)
                {
                    for(sensor2 = 0; sensor2 <= 1; sensor2++)
                    {
                        for(sensor3 = 0; sensor3 <= 1; sensor3++)
                        {
                            for(sr = 0; sr <= 1; sr++)
                            {
                                for(tmr = 0; tmr <= 1; tmr++)
                                {
                                    for(pr_state = 0; pr_state <= 7; pr_state++)
                                    {
                                        nx_state = inicio;

                                        if(ini_bits == 0)
                                        {
                                            if(pr_state == inicio && str == 1)
                                            {
                                                nx_state = RESETA_JOGO;
                                            }
                                            else if(tmr == 0)
                                            {
                                                if(pr_state == esperaSensor)
                                                {
                                                    switch(sr)
                                                    {
                                                    case 1:
                                                        if(randm == 0)
                                                        {
                                                            nx_state = led0;
                                                            break;
                                                        }
                                                        else if(randm == 1)
                                                        {
                                                            nx_state = led1;
                                                            break;
                                                        }
                                                        else if(randm == 2)
                                                        {
                                                            nx_state = led2;
                                                            break;
                                                        }
                                                        break;

                                                    default:
                                                        nx_state=esperaSensor;
                                                    }
                                                }
                                                else if(pr_state == led0)
                                                {
                                                    if(sensor1 == 1 && sensor2 == 0 && sensor3 == 0) nx_state = incrementa;
                                                    else if(sensor2 == 1 || sensor3 == 1) nx_state = zera;
                                                    else nx_state = pr_state;
                                                }
                                                else if(pr_state == led1)
                                                {
                                                    if(sensor1 == 0 && sensor2 == 1 && sensor3 == 0) nx_state = incrementa;
                                                    else if(sensor1 == 1 || sensor3 == 1) nx_state = zera;
                                                    else nx_state = pr_state;
                                                }
                                                else if(pr_state == led2)
                                                {
                                                    if(sensor1 == 0 && sensor2 == 0 && sensor3 == 1) nx_state = incrementa;
                                                    else if(sensor1 == 1 || sensor2 == 1) nx_state = zera;
                                                    else nx_state = pr_state;
                                                }
                                                else if(pr_state == incrementa )
                                                {
                                                    nx_state = esperaSensor;
                                                }
                                                else if(pr_state == zera )
                                                {
                                                    nx_state = esperaSensor;
                                                }
                                                else if(pr_state == RESETA_JOGO)
                                                {
                                                    nx_state = esperaSensor;
                                                }
                                                else nx_state = pr_state;
                                            }
                                            else nx_state = inicio;
                                        }
                                        if(nx_state == inicio)
                                        {
                                            nx_state = ((INI << 3) & 248) | nx_state;
                                        }
                                        else if(nx_state == esperaSensor)
                                        {
                                            nx_state = ((ATI << 3) & 248) | nx_state;
                                        }
                                        else if(nx_state == led0)
                                        {
                                            nx_state = ((LD1 << 3) & 248) | nx_state;
                                        }
                                        else if(nx_state == led1)
                                        {
                                            nx_state = ((LD2 << 3) & 248) | nx_state;
                                        }
                                        else if(nx_state == led2)
                                        {
                                            nx_state = ((LD3 << 3) & 248) | nx_state;
                                        }
                                        else if(nx_state == incrementa)
                                        {
                                            nx_state = ((acr << 3) & 248) | nx_state;
                                        }
                                        else if(nx_state == zera)
                                        {
                                            nx_state = ((rst << 3) & 248) | nx_state;
                                        }
                                        else if(nx_state == RESETA_JOGO)
                                        {
                                            nx_state = ((rst << 3) & 248) | nx_state;
                                        }

                                        fwrite(&nx_state, sizeof( nx_state), 1, arquivo3);
                                        fprintf(arquivo1,"%d\n",nx_state);
                                        //printf("%d\n", nx_state);
                                        fprintf(arquivo2,"%02x ",nx_state);
                                    }
                                }
                                fprintf(arquivo2,"\n");
                            }
                        }
                    }
                }
            }
        }
    }

    // printf("Arquivo gerado com sucesso!");
    fclose(arquivo3);
    fclose(arquivo1);
    fclose(arquivo2);
    return 0;
}
