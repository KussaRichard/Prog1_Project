#include "switch.h"

///Hibás bemenet
void rossz_bemenet(){
    system("cls");
    printf("Hibas bemenet\n----\n");
    sleep(2);
}
int main(){
    ///Menü
    char *sel;
    char *valasz;
    int fut = 1;
    int kilep = 0;
    while(fut){
        system("cls");
        printf("  _______  _______  ___   _  ___   _ \n");
        printf(" |       ||   _   ||   | | ||   | | |\n");
        printf(" |  _____||  |_|  ||   |_| ||   |_| |\n");
        printf(" | |_____ |       ||      _||      _|\n");
        printf(" |_____  ||       ||     |_ |     |_ \n");
        printf("  _____| ||   _   ||    _  ||    _  |\n");
        printf(" |_______||__| |__||___| |_||___| |_|\n");
        printf("\n----\n(1) Uj jatek\n(2) Meglevo jatek folytatasa\n(3) Utolso jatek visszajatszasa \n\n(4) Kilepes \n----\n");
        sel = sort_beolvas(0);
        if(sel[1] == '\0'){
            switch(sel[0]){
                    case '4':
                        while(!kilep){
                            system("cls");
                            printf("Biztosan ki szeretnel lepni?\n----\n(i) Igen\n(n) Nem\n----\n");
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
                            free(valasz);
                        }
                        kilep = 0;
                        break;
                    case '1':
                        while(!kilep){
                            system("cls");
                            printf("A mentett jatekod elveszhet. Biztosan uj jatekot szeretnel kezdeni?\n----\n(i) Igen\n(n) Nem\n----\n");
                            valasz = sort_beolvas(0);
                            if(valasz[1] == '\0'){
                                switch(valasz[0]){
                                        case 'I' :
                                        case 'i' :
                                            system("cls");
                                            kilep = 1;
                                            remove("mentett_allas.txt");
                                            remove("mentett_lepesek.txt");
                                            tabla_letrehozasa(1);
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

                        kilep = 0;
                        break;
                    case '2':
                        system("cls");
                        if (access("mentett_allas.txt", F_OK) == 0) {
                            tabla_betoltese();
                        } else {
                            printf("Jelenleg nincsen mentett jatekod\n----\n");
                            sleep(2);
                        }
                        break;
                    case '3':
                        system("cls");
                        if (access("mentett_lepesek.txt", F_OK) == 0) {
                            tabla_letrehozasa(2);
                        } else {
                            printf("Meg nem volt parti, amit vissza lehetne jatszani\n----\n");
                            sleep(2);
                        }
                        break;
                    default:
                        rossz_bemenet();
                        break;
                }
        }
        else
            rossz_bemenet();
        free(sel);
    }
    return 0;
}
