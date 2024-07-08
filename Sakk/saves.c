#include "switch.h"

///Mentés
void allas_mentese(Babu tabla[8][8], int kor){
    FILE* allas;
    allas = fopen("mentett_allas.txt", "a");
    fprintf(allas, "%d. kor\n", kor);
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(tabla[i][j].megjelenes != ' ')
                fprintf(allas, "[%d,%d] : %c %d %d %d\n", i, j, tabla[i][j].megjelenes, tabla[i][j].szin, tabla[i][j].megmozdult, tabla[i][j].en_passant);
    fprintf(allas, ".\n");
    fclose(allas);
}
void lepesek_mentese(){
    FILE* allas;
    FILE* osszes_lepes;
    osszes_lepes = fopen("mentett_lepesek.txt", "w");
    allas = fopen("mentett_allas.txt", "r");
    char c = getc(allas);
    while(c != EOF){
        fputc(c, osszes_lepes);
        c = getc(allas);
    }
    fclose(allas);
    fclose(osszes_lepes);
}
