#include "switch.h"

///Rajzolás
void rajzol(Babu tabla[8][8], int mod){
    system("cls");
    printf("\n");
    int i;
    int j;
    int korlat;
    if(mod % 2 == 1){
        i = 7;
        korlat = -1;
    }
    else{
        i = 0;
        korlat = 8;
    }
    while(i != korlat){
        if(mod % 2 == 1)
            j = 7;
        else
            j = 0;
        printf("\t    ");
        for(int k = 0; k < 8; k++)
            printf("--- ");
        printf("\n\t");
        printf("%2.d |", i + 1);
        while(j != korlat){
            printf(" ");
            if(tabla[i][j].szin == 1)
                printf("%c", tabla[i][j].megjelenes-32);
            else if(tabla[i][j].szin == 0)
                printf("%c", tabla[i][j].megjelenes);
            else
                printf("%c", tabla[i][j].megjelenes);
            printf(" |");
            (mod % 2 == 1) ? j-- : j++;
        }
        printf("\n");
        (mod % 2 == 1) ? i-- : i++;
    }
    printf("\t    ");
    for(int i = 0; i < 8; i++)
        printf("--- ");
    printf("\n\t     ");
    if(mod % 2 == 1)
        for(int i = 0; i < 8; i++)
            printf("%c   ", 65 + i);
    else
        for(int i = 0; i < 8; i++)
            printf("%c   ", 72 - i);
    printf("\n\n");
}
void bejatszas(Babu tabla[8][8], int kor){
    system("cls");
    printf("\n");
    for(int i = 7; i > -1; i--){
        printf("\t    ");
        for(int k = 0; k < 8; k++)
            printf("--- ");
        printf("\n\t");
        printf("%2.d |", i + 1);
        for(int j = 7; j > -1; j--){
            printf(" ");
            if(tabla[i][j].szin == 1)
                printf("%c", tabla[i][j].megjelenes-32);
            else if(tabla[i][j].szin == 0)
                printf("%c", tabla[i][j].megjelenes);
            else
                printf("%c", tabla[i][j].megjelenes);
            printf(" |");
        }
        printf("\n");
    }
    printf("\t    ");
    for(int i = 0; i < 8; i++)
        printf("--- ");
    printf("\n\t     ");
    for(int i = 0; i < 8; i++)
            printf("%c   ", 65 + i);
    printf("\n\n----\n%d. kor\n----\n", kor);
}
