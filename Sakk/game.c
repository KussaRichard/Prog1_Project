#include "switch.h"

///Mozgások beolvasása
char* sort_beolvas(int meret){
    char *tomb = NULL;
    char c;
    scanf("%c", &c);
    if(c != '\n' && c != '\0')
        tomb = sort_beolvas(meret+1);
    else{
        tomb = (char*) malloc((meret+1) * sizeof(char));
        if(tomb == NULL)
            return NULL;
        tomb[meret] = '\0';
        return tomb;
    }
    if(tomb == NULL)
            return NULL;
    tomb[meret] = c;
    return tomb;
}
void lepes(Babu *a, Babu *b){
    //a-ból megyünk b-be
    b->megjelenes = a->megjelenes;
    b->szin = a->szin;
    b->en_passant = a->en_passant;
    b->megmozdult = 1;

    a->megjelenes = ' ';
    a->szin = -1;
    a->en_passant = 0;
    a->megmozdult = 0;
}
///Bemenetek vizsgálata
void szabalytalan_lepes(){
    system("cls");
    printf("Szabalytalan lepes\n----\n");
    sleep(2);
}
void kiraly_sakkban_van(){
    system("cls");
    printf("Kiralyod sakkban van\n----\n");
    sleep(2);
}
int mezo_letezik(char *mezo){
    int letezik = 1;
    if(mezo[2] != '\0' || mezo[0] < 65 || mezo[0] > 104 || (mezo[0] > 72 && mezo[0] < 97) || mezo[1] < 49 || mezo[1] > 56){
        system("cls");
        printf("Ilyen mezo nem letezik\n----\n");
        sleep(2);
        letezik = 0;
    }
    return letezik;
}
int mezo_ures_vagy_rossz_babu(Vektor poz, Babu tabla[8][8], int kor){
    int rossz = 0;
    if(tabla[poz.x][poz.y].megjelenes == ' '){
        system("cls");
        printf("Ez a mezo ures\n----\n");
        sleep(2);
        rossz = 1;
    }
    else if(tabla[poz.x][poz.y].szin != kor % 2){
        system("cls");
        printf("Ez nem a te babud\n----\n");
        sleep(2);
        rossz = 1;
    }
    return rossz;
}
int dekodolas(char *poz, int index){
    int ertek = -1;
    if(index == 0){
        if(poz[index] == 'A' || poz[index] == 'a')
            ertek = 7;
        else if(poz[index] == 'B' || poz[index] == 'b')
            ertek = 6;
        else if(poz[index] == 'C' || poz[index] == 'c')
            ertek = 5;
        else if(poz[index] == 'D' || poz[index] == 'd')
            ertek = 4;
        else if(poz[index] == 'E' || poz[index] == 'e')
            ertek = 3;
        else if(poz[index] == 'F' || poz[index] == 'f')
            ertek = 2;
        else if(poz[index] == 'G' || poz[index] == 'g')
            ertek = 1;
        else
            ertek = 0;
    }
    else{
        if(poz[index] == '8')
            ertek = 7;
        else if(poz[index] == '7')
            ertek = 6;
        else if(poz[index] == '6')
            ertek = 5;
        else if(poz[index] == '5')
            ertek = 4;
        else if(poz[index] == '4')
            ertek = 3;
        else if(poz[index] == '3')
            ertek = 2;
        else if(poz[index] == '2')
            ertek = 1;
        else
            ertek = 0;
    }
    return ertek;
}
int mezo_tamadott(Vektor cel, int szin, Babu tabla[8][8]){
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(tabla[i][j].megjelenes != ' ' && tabla[i][j].szin != szin){
                Vektor poz = {i , j};
                if(lepes_vizsgalat(poz, cel, tabla, 1) == 1)
                    return 1;
            }

    return 0;
}
int sakk(int szin, Babu tabla[8][8]){
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(tabla[i][j].megjelenes == 'k' && tabla[i][j].szin == szin){
                Vektor poz = {i, j};
                if(mezo_tamadott(poz, szin, tabla) == 1)
                    return 1;
                else
                    return 0;
            }
    return 0;
}
int patt(int szin, Babu tabla[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(tabla[i][j].szin == szin){
                for(int k = 0; k < 8; k++)
                    for(int l = 0; l < 8; l++){
                        Vektor poz = {i, j};
                        Vektor cel = {k, l};
                        if(lepes_vizsgalat(poz, cel, tabla, 1) != 0)
                            return 0;
                    }
            }
        }
    }
    return 1;
}
void gyalog_atvaltozas(Babu *egyseg){
    char *valasztott;
    while(1){
        system("cls");
        printf("Gyalog atvaltozas\n----\n(h) Huszar\n(f) Futo\n(b) Bastya\n(v) Vezer\n----\n");
        valasztott = sort_beolvas(0);
        if(valasztott[1] == '\0'){
            if(valasztott[0] == 'h' || valasztott[0] == 'H'){
                egyseg->megjelenes = 'h';
                break;
            }
            else if(valasztott[0] == 'f' || valasztott[0] == 'F'){
                egyseg->megjelenes = 'f';
                break;
            }
            else if(valasztott[0] == 'b' || valasztott[0] == 'B'){
                egyseg->megjelenes = 'b';
                break;
            }
            else if(valasztott[0] == 'v' || valasztott[0] == 'V'){
                egyseg->megjelenes = 'v';
                break;
            }
            else{
                rossz_bemenet();
                free(valasztott);
            }
        }
        else{
            rossz_bemenet();
            free(valasztott);
        }
    }
    free(valasztott);
}
int gyalog_lep(Vektor poz, Vektor cel, Babu tabla[8][8]){
    if(tabla[poz.x][poz.y].szin != tabla[cel.x][cel.y].szin){
        //Egyet lép elõre
        if(((poz.x - cel.x == 1 && tabla[poz.x][poz.y].szin == 0) || (poz.x - cel.x == -1 && tabla[poz.x][poz.y].szin == 1)) && poz.y - cel.y == 0 && tabla[cel.x][cel.y].megjelenes == ' '){
            if(cel.x == 0 || cel.x == 7)
                return 4;
            else
                return 5;
        }
        //Kettõt lép elõre
        else if(((poz.x - cel.x == 2 && tabla[poz.x][poz.y].szin == 0) || (poz.x - cel.x == -2 && tabla[poz.x][poz.y].szin == 1)) && poz.y - cel.y == 0 && tabla[poz.x][poz.y].megmozdult == 0 && tabla[cel.x][cel.y].megjelenes == ' '){
            if(tabla[poz.x][poz.y].szin == 1){
                if(tabla[poz.x+1][poz.y].megjelenes == ' ')
                    return 2;
            }
            else
                if(tabla[poz.x-1][poz.y].megjelenes == ' ')
                    return 2;
        }
        //Üt
        else if(((poz.x - cel.x == 1 && tabla[poz.x][poz.y].szin == 0) || (poz.x - cel.x == -1 && tabla[poz.x][poz.y].szin == 1)) && (poz.y - cel.y == -1 || poz.y - cel.y == 1) && tabla[cel.x][cel.y].megjelenes != ' '){
            if(cel.x == 0 || cel.x == 7)
                return 4;
            else
                return 1;
        }
        //En-passant
        else if(((poz.x - cel.x == 1 && tabla[poz.x][poz.y].szin == 0) || (poz.x - cel.x == -1 && tabla[poz.x][poz.y].szin == 1)) && (poz.y - cel.y == -1 || poz.y - cel.y == 1) && tabla[cel.x][cel.y].megjelenes == ' '){
            if(tabla[poz.x][poz.y].szin == 1){
                if(tabla[cel.x-1][cel.y].en_passant == 1)
                    return 3;
            }
            else
                if(tabla[cel.x+1][cel.y].en_passant == 1)
                    return 3;
        }
    }
    return 0;
}
int huszar_lep(Vektor poz, Vektor cel, Babu tabla[8][8]){
    if(tabla[poz.x][poz.y].szin != tabla[cel.x][cel.y].szin)
        if((poz.x - cel.x == 2 && poz.y - cel.y == 1) || (poz.x - cel.x == 2 && poz.y - cel.y == -1) || (poz.x - cel.x == -2 && poz.y - cel.y == 1) || (poz.x - cel.x == -2 && poz.y - cel.y == -1) || (poz.x - cel.x == 1 && poz.y - cel.y == 2) || (poz.x - cel.x == 1 && poz.y - cel.y == -2) || (poz.x - cel.x == -1 && poz.y - cel.y == 2) || (poz.x - cel.x == -1 && poz.y - cel.y == -2))
            return 1;
    return 0;
}
int futo_lep(Vektor poz, Vektor cel, Babu tabla[8][8]){
    if(tabla[poz.x][poz.y].szin != tabla[cel.x][cel.y].szin){
        //Egyenes arányosság
        if(poz.x - cel.x == poz.y - cel.y){
            if(poz.x > cel.x && poz.y > cel.y){
                int i = poz.x - 1;
                int j = poz.y - 1;
                while(i != cel.x && j != cel.y){
                    if(tabla[i][j].megjelenes != ' ')
                        return 0;
                    i--;
                    j--;
                }
                return 1;
            }
            else if(poz.x < cel.x && poz.y < cel.y){
                int i = poz.x + 1;
                int j = poz.y + 1;
                while(i != cel.x && j != cel.y){
                    if(tabla[i][j].megjelenes != ' ')
                        return 0;
                    i++;
                    j++;
                }
                return 1;
            }
        }
        //Fordított arányosság
        else if(poz.x - cel.x == -(poz.y - cel.y)){
            if(poz.x < cel.x && poz.y > cel.y){
                int i = poz.x + 1;
                int j = poz.y - 1;
                while(i != cel.x && j != cel.y){
                    if(tabla[i][j].megjelenes != ' ')
                        return 0;
                    i++;
                    j--;
                }
                return 1;
            }
            else if(poz.x > cel.x && poz.y < cel.y){
                int i = poz.x - 1;
                int j = poz.y + 1;
                while(i != cel.x && j != cel.y){
                    if(tabla[i][j].megjelenes != ' ')
                        return 0;
                    i--;
                    j++;
                }
                return 1;
            }
        }
    }
    return 0;
}
int bastya_lep(Vektor poz, Vektor cel, Babu tabla[8][8]){
    if(tabla[poz.x][poz.y].szin != tabla[cel.x][cel.y].szin){
        if(poz.x - cel.x == 0){
            if(poz.y < cel.y){
                int z = poz.y + 1;
                while(z != cel.y){
                    if(tabla[poz.x][z].megjelenes != ' ')
                        return 0;
                    z++;
                }
                return 1;
            }
            else if(poz.y > cel.y){
                int z = poz.y - 1;
                while(z != cel.y){
                    if(tabla[poz.x][z].megjelenes != ' ')
                        return 0;
                    z--;
                }
                return 1;
            }
        }
        else if(poz.y - cel.y == 0){
            if(poz.x < cel.x){
                int z = poz.x + 1;
                while(z != cel.x){
                    if(tabla[z][poz.y].megjelenes != ' ')
                        return 0;
                    z++;
                }
                return 1;
            }
            else if(poz.x > cel.x){
                int z = poz.x - 1;
                while(z != cel.x){
                    if(tabla[z][poz.y].megjelenes != ' ')
                        return 0;
                    z--;
                }
                return 1;
            }
        }
    }
    return 0;
}
int kiraly_lep(Vektor poz, Vektor cel, Babu tabla[8][8], int sanc){
    if(tabla[poz.x][poz.y].szin != tabla[cel.x][cel.y].szin){
        if(poz.x - cel.x == 1 && poz.y - cel.y == 0){
            return 1;
        }
        else if(poz.x - cel.x == 0 && poz.y - cel.y == 1){
            return 1;
        }
        else if(poz.x - cel.x == -1 && poz.y - cel.y == 0){
            return 1;
        }
        else if(poz.x - cel.x == 0 && poz.y - cel.y == -1){
            return 1;
        }
        else if(poz.x - cel.x == 1 && poz.y - cel.y == 1){
            return 1;
        }
        else if(poz.x - cel.x == 1 && poz.y - cel.y == -1){
            return 1;
        }
        else if(poz.x - cel.x == -1 && poz.y - cel.y == 1){
            return 1;
        }
        else if(poz.x - cel.x == -1 && poz.y - cel.y == -1){
            return 1;
        }
        else if(poz.x - cel.x == 0 && poz.y - cel.y == 2 && sanc != 1){
            if(tabla[cel.x][cel.y-1].megjelenes == 'b' && tabla[cel.x][cel.y-1].megmozdult == 0 && tabla[poz.x][poz.y].megmozdult == 0){
                int z = poz.y-1;
                while(z != cel.y-1){
                    if(tabla[poz.x][z].megjelenes != ' ')
                        return 0;
                    z--;
                }
                return 6;
            }
        }
        else if(poz.x - cel.x == 0 && poz.y - cel.y == -2 && sanc != 1){
            if(tabla[cel.x][cel.y+2].megjelenes == 'b' && tabla[cel.x][cel.y+2].megmozdult == 0 && tabla[poz.x][poz.y].megmozdult == 0){
                int z = poz.y+1;
                while(z != cel.y+2){
                    if(tabla[poz.x][z].megjelenes != ' ')
                        return 0;
                    z++;
                }
                return 6;
            }
        }
    }
    return 0;
}
int lepes_vizsgalat(Vektor poz, Vektor cel, Babu tabla[8][8], int sanc){
    int helyes_lepes = 0;
    ///Gyalog lépései
    if(tabla[poz.x][poz.y].megjelenes == 'g')
        helyes_lepes = gyalog_lep(poz, cel, tabla);
    ///Huszar lépései
    else if(tabla[poz.x][poz.y].megjelenes == 'h')
        helyes_lepes = huszar_lep(poz, cel, tabla);
    ///Futó lépései
    else if(tabla[poz.x][poz.y].megjelenes == 'f')
        helyes_lepes = futo_lep(poz, cel, tabla);
    ///Bástya lépései
    else if(tabla[poz.x][poz.y].megjelenes == 'b')
        helyes_lepes = bastya_lep(poz, cel, tabla);
    ///Vezér lépései
    else if(tabla[poz.x][poz.y].megjelenes == 'v'){
        helyes_lepes = futo_lep(poz, cel, tabla);
        if(helyes_lepes != 1)
            helyes_lepes = bastya_lep(poz, cel, tabla);
    }
    ///Király lépései
    else if(tabla[poz.x][poz.y].megjelenes == 'k')
        helyes_lepes = kiraly_lep(poz, cel, tabla, sanc);

    return helyes_lepes;
}
int matt(int szin, Babu tabla[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(tabla[i][j].szin == szin){
                for(int k = 0; k < 8; k++)
                    for(int l = 0; l < 8; l++){
                        Vektor poz = {i, j};
                        Vektor cel = {k, l};
                        if(lepes_vizsgalat(poz, cel, tabla, 1) != 0){
                            Babu elesett = tabla[cel.x][cel.y];
                            lepes(&tabla[poz.x][poz.y], &tabla[cel.x][cel.y]);
                            if(!sakk(szin, tabla)){
                                lepes(&tabla[cel.x][cel.y], &tabla[poz.x][poz.y]);
                                tabla[cel.x][cel.y] = elesett;
                                return 0;
                            }
                            else{
                                lepes(&tabla[cel.x][cel.y], &tabla[poz.x][poz.y]);
                                tabla[cel.x][cel.y] = elesett;
                            }
                        }
                    }
            }
        }
    }
    return 1;
}
///Játék
void jatek(Babu tabla[8][8], int kor){
    int fut = 1;
    int kilep = 0;
    while(fut){
        rajzol(tabla, kor);
        (kor % 2 == 1) ? printf("----\nFeher kovetkezik ") : printf("----\nFekete kovetkezik ");
        if(sakk(kor % 2, tabla) == 1)
            printf(": Sakk!");
        printf("\n----\n");
        printf("(1) Lepes\n(2) Feladas\n\n(3) Kilepes\n----\n");
        char *valasz = sort_beolvas(0);
        if(valasz[1] == '\0'){
            switch(valasz[0]){
                    case '1':
                        rajzol(tabla, kor);
                        printf("----\nHonnan: ");
                        char *honnan = sort_beolvas(0);
                        Vektor poz;
                        poz.y = dekodolas(honnan, 0);
                        poz.x = dekodolas(honnan, 1);
                        if(!mezo_letezik(honnan) || mezo_ures_vagy_rossz_babu(poz, tabla, kor)){
                            free(honnan);
                            break;
                        }
                        printf("Hova: ");
                        char *hova = sort_beolvas(0);
                        if(!mezo_letezik(hova)){
                            free(hova);
                            break;
                        }
                        Vektor cel;
                        cel.y = dekodolas(hova, 0);
                        cel.x = dekodolas(hova, 1);
                        ///Lépés vizsgálata és esetleges végrehajtása
                        int sanc = 0;
                        if(tabla[poz.x][poz.y].megjelenes == 'k')
                            sanc = sakk(tabla[poz.x][poz.y].szin, tabla);
                        int mod = lepes_vizsgalat(poz, cel, tabla, sanc);
                        if(mod != 0){
                            Babu elesett = tabla[cel.x][cel.y];
                            lepes(&tabla[poz.x][poz.y], &tabla[cel.x][cel.y]);
                            if(sakk(kor % 2, tabla) == 1){
                                lepes(&tabla[cel.x][cel.y], &tabla[poz.x][poz.y]);
                                tabla[cel.x][cel.y] = elesett;
                                kiraly_sakkban_van();
                                free(honnan);
                                free(hova);
                                break;
                            }
                            else{ ///Lépés feljegyzése
                                allas_mentese(tabla, kor);
                                lepesek_mentese();
                            }

                            for(int i = 3; i < 5; i++)
                                for(int j = 0; j < 8; j++)
                                    if(tabla[i][j].megjelenes == 'g')
                                        tabla[i][j].en_passant = 0;
                            if(mod == 2)
                                tabla[cel.x][cel.y].en_passant = 1;
                            else if(mod == 3){
                                if(tabla[cel.x][cel.y].szin == 1){
                                    tabla[cel.x-1][cel.y].megjelenes = ' ';
                                    tabla[cel.x-1][cel.y].szin = -1;
                                }
                                else{
                                    tabla[cel.x+1][cel.y].megjelenes = ' ';
                                    tabla[cel.x+1][cel.y].szin = -1;
                                }
                            }
                            else if(mod == 4){
                                gyalog_atvaltozas(&tabla[cel.x][cel.y]);
                            }
                            else if(mod == 6){
                                if(poz.y - cel.y == 2){
                                    lepes(&tabla[cel.x][cel.y-1], &tabla[cel.x][cel.y+1]);
                                }
                                else
                                    lepes(&tabla[cel.x][cel.y+2], &tabla[cel.x][cel.y-1]);
                            }
                            rajzol(tabla, kor);
                            if(sakk((kor+1) % 2, tabla)){
                                if(matt((kor + 1) % 2, tabla)){
                                    (kor % 2 == 1) ? printf("----\nMatt! Feher nyert!\n----\n") : printf("----\nMatt! Fekete nyert!\n----\n");
                                    sleep(2);
                                    fut = 0;
                                }
                                else{
                                    sleep(2);
                                    kor++;
                                }
                            }
                            else{
                                if(patt((kor + 1) % 2, tabla)){
                                    printf("----\nPatt! Dontetlen!\n----\n");
                                }
                                else{
                                    sleep(2);
                                    kor++;
                                }
                            }
                        }
                        else
                            szabalytalan_lepes();
                        free(honnan);
                        free(hova);
                        break;
                    case '2':
                        system("cls");
                        kilep = 0;
                        while(!kilep){
                            system("cls");
                            printf("Biztosan fel szeretned adni a jatekot?\n----\n(i) Igen\n(n) Nem\n----\n");
                            free(valasz);
                            valasz = sort_beolvas(0);
                            if(valasz[1] == '\0'){
                                switch(valasz[0]){
                                        case 'I' :
                                        case 'i' :
                                            system("cls");
                                            remove("mentett_allas.txt");
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
                        }
                        if(fut == 0){
                            rajzol(tabla, kor);
                            (kor % 2 == 0) ? printf("----\nFeladas! Feher nyert!\n----\n") : printf("----\nFeladas! Fekete nyert!\n----\n");
                            sleep(2);
                        }
                        break;
                    case '3':
                        system("cls");
                        kilep = 0;
                        while(!kilep){
                            system("cls");
                            printf("Biztosan ki szeretnel lepni? (Jatekod automatikusan mentesre kerul)\n----\n(i) Igen\n(n) Nem\n----\n");
                            free(valasz);
                            valasz = sort_beolvas(0);
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
                        }
                        break;
                    default:
                        rossz_bemenet();
                        break;
                }
        }
        else{
            rossz_bemenet();
        }
        free(valasz);
    }
}
