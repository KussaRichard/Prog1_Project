#include "switch.h"

int atvalt(char sor[16]){
    int szam = 0;
    for(int i = 0; sor[i] != '.' && sor[i] != '['; i++)
        szam = szam * 10 + (sor[i] - '0');
    return szam;
}
void kovetkezo_kor(int kor){
    Babu tabla[8][8];
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            tabla[i][j] = babu_letrehozasa(' ', -1, 0, 0);
    char sor[16];
    FILE* lepes;
    lepes = fopen("mentett_lepesek.txt", "r");
    while(fgets(sor, 16, lepes) != NULL){
        if(atvalt(sor) == kor){
            fgets(sor, 16, lepes);
            while(sor[0] != '.'){
                int i = szam_dekod(sor[1]);
                int j = szam_dekod(sor[3]);
                Babu egyseg = babu_letrehozasa(sor[8], szam_dekod(sor[10]), szam_dekod(sor[12]), szam_dekod(sor[14]));
                tabla[i][j] = egyseg;
                fgets(sor, 16, lepes);
            }
            break;
        }
    }
    fclose(lepes);
    bejatszas(tabla, kor);
}
void visszajatszas(Babu tabla[8][8]){
    int korok_szama = 0;
    char sor[16];
    FILE* korok;
    korok = fopen("mentett_lepesek.txt", "r");
    while(fgets(sor, 16, korok) != NULL)
        if(sor[0] == '.')
            korok_szama++;
    fclose(korok);
    int kor = 0;
    int fut = 1;
    while(fut){
        if(kor != 0)
            kovetkezo_kor(kor);
        else
            bejatszas(tabla, 0);
        char *bemenet;
        if(kor > 0 && kor < korok_szama)
            printf("(1) Kovetkezo kor\n(2) Elozo kor\n\n(3) Kilepes\n----\n");
        else if(kor > 0)
            printf("\n(2) Elozo kor\n\n(3) Kilepes\n----\n");
        else
            printf("(1) Kovetkezo kor\n\n\n(3) Kilepes\n----\n");
        bemenet = sort_beolvas(0);
        if(bemenet[1] == '\0'){
            if(bemenet[0] == '1' && kor < korok_szama){
                kor++;
            }
            else if(bemenet[0] == '2' && kor > 0){
                kor--;
            }
            else if(bemenet[0] == '3'){
                int kilep = 0;
                while(!kilep){
                    system("cls");
                    printf("Biztosan ki szeretnel lepni?\n----\n(i) Igen\n(n) Nem\n----\n");
                    char *valasz = sort_beolvas(0);
                    if(valasz[1] == '\0'){
                        switch(valasz[0]){
                            case 'I' :
                            case 'i' :
                                system("cls");
                                kilep = 1;
                                fut = 0;
                                break;
                            case 'N' :
                            case 'n' :
                                system("cls");
                                kilep = 1;
                                break;
                            default:
                                rossz_bemenet();
                                break;
                        }
                    }
                    else
                        rossz_bemenet();
                    free(valasz);
                }
            }
            else
                rossz_bemenet();
        }
        else
            rossz_bemenet();
        free(bemenet);
    }
}
