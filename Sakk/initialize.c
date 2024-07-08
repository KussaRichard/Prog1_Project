#include "switch.h"

///Tábla és bábuk létrehozása
Babu babu_letrehozasa(char megjelenes, int szin, int megmozdult, int en_passant){
    Babu egyseg;
    egyseg.megjelenes = megjelenes;
    egyseg.szin = szin;
    egyseg.megmozdult = megmozdult;
    egyseg.en_passant = en_passant;
    return egyseg;
}
void tabla_letrehozasa(int mod){
    Babu tabla[8][8];
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++){
            if(i == 1 || i == 6)
                tabla[i][j] = babu_letrehozasa('g', (i == 1), 0, 0);
            else if(i == 0 || i == 7){
                if(j == 0 || j == 7)
                    tabla[i][j] = babu_letrehozasa('b', (i == 0), 0, 0);
                else if(j == 1 || j == 6)
                    tabla[i][j] = babu_letrehozasa('h', (i == 0), 0, 0);
                else if(j == 2 || j == 5)
                    tabla[i][j] = babu_letrehozasa('f', (i == 0), 0, 0);
                else if(j == 3)
                    tabla[i][j] = babu_letrehozasa('k', (i == 0), 0, 0);
                else if(j == 4)
                    tabla[i][j] = babu_letrehozasa('v', (i == 0), 0, 0);
            }
            else
                tabla[i][j] = babu_letrehozasa(' ', -1, 0, 0);
        }
    (mod % 2 == 1) ? jatek(tabla, 1) : visszajatszas(tabla);
}
int szam_dekod(char szam){
    int valto;
    valto = szam - '0';
    return valto;
}
///Betöltés
void tabla_betoltese(){
    Babu tabla[8][8];
    int kor = 1;
    char sor[16];
    FILE* allas;
    allas = fopen("mentett_allas.txt", "r");
    if(allas != NULL){
        while(fgets(sor, 16, allas) != NULL){
            kor++;
            for(int i = 0; i < 8; i++)
                for(int j = 0; j < 8; j++)
                    tabla[i][j] = babu_letrehozasa(' ', -1, 0, 0);
            fgets(sor, 16, allas);
            while(sor[0] != '.'){
                int i = szam_dekod(sor[1]);
                int j = szam_dekod(sor[3]);
                Babu egyseg = babu_letrehozasa(sor[8], szam_dekod(sor[10]), szam_dekod(sor[12]), szam_dekod(sor[14]));
                tabla[i][j] = egyseg;
                fgets(sor, 16, allas);
            }
        }
    }
    fclose(allas);
    jatek(tabla, kor);
}
