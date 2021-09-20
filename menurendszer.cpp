//
// Created by Balint on 2021. 04. 03..
//


/* A menürendszer működését valósítja meg ez a fájl. */
/*Jportán a clearscrean és menürajzolás deaktiválva van */

#include "menurendszer.h"
#include "koktel_tarolo.h"
#include "econio.h"
#include "memtrace.h"


/* Ha nem JPORTA/TESZTELÉS , távolítsa el! */
//#define SIM


/* Cross-platform getline. Minden operációsrendszeren működik.
 * Forrás: Infocpp
 * Nem saját! */
namespace cp {

    std::istream& getline(std::istream& is, std::string& str) {
        std::getline(is, str);
        if (str.size() && *str.rbegin() == '\r')
            str.erase(str.size()-1);
        return is;
    }

}

/* Ha a SIM (szimuláció) makró nincs definiálva, ezzel rajzol a képernyőre egy dobozt, benne szöveggel.*/
void box(const std::string& be, bool aktiv) {
    std::string check = "[   ]";
    if (aktiv)
        check = "[ X ]";

    /*Egy ASCII dobozt rajzol, belsejébe a be paramétert írja és a Checkbox-ot ami lehet aktív és inaktív.*/
    std::cout << char(218);
    for (int i = 0; i < 21; i++) { std::cout << char(196); }
    std::cout << char(191) << std::endl;
    std::cout << char(179) << " " << std::setw(15) << std::left << be << check << char(179) << std::endl;
    std::cout << char(192);
    for (int i = 0; i < 21; i++) { std::cout << char(196); }
    std::cout << char(217) << std::endl;
}

/* A paraméterként kapott string tömböt ami a menü egyes pontjai, azt kirajzolja egymás alá a box függvénnyel.
 * A másik paramétere, hogy hanyadik menüpont legyen aktív. Ahol lesz egy [ X ] a név mellett.*/
void menu(int index, std::string *tomb) {
    //SZIN1;

    bool check = false;
    for (int i = 0; !tomb[i].empty(); ++i) {
        if (i == index - 1) {
            check = true;
        }
        box(tomb[i], check);
        check = false;

    }
}

/*Megvalósítja, hogy a menüben a w és s gombokkal fel le lehessen navigálni a menüpontok közott.
 * Visszatérési értéke egy szám, amely a menüpont száma aminél a felhasználó entert nyomott (Melyiket választotta). */
int navigation(std::string *tomb) {

    econio_rawmode(); /* Szüksége van a getchar függvénynek a működéséhez. */
    int x = 1; /* Alapértelmezetten az első menüpont aktív. */
    int meret; /* Hány menüpont van összesen? */
    int key; /* Melyik gombot nyomta meg a felhasználó? */

    #ifndef SIM /* Jportán nem kell rajzolni. */
    menu(x, tomb);
    #endif

    for (meret = 0; !tomb[meret].empty(); ++meret) {  /* Hany elemu a tomb? */    }

    while (true) {

        #ifndef SIM  /* Jportán nem kell rajzolni. */
        econio_clrscr();
        menu(x, tomb);
        #endif

        //key = econio_getch(); /* Bekérjük az inputot? w vagy s */
        key = econio_getch();
        if (key == 119 && x > 1) /*Ha s betűt nyomott lelép a következőre kivéve ha ez a legalsó menüpont. */
            x--;
        if (key == 115 && x < meret) /*Ha w betűt nyomott fellép a következőre kivéve ha ez a legfelső menüpont. */
            x++;
        if (key == 10) /* Ha entert nyom a felhasználó kilépés. */
            break;

    }
    if(tomb[4]=="KILEPES"&&x==meret)
        return -1; /*KILEPESRE KATTINTOTT*/
    if (x==meret)
        return 0; /*A VISSZA GOMBRA KATTINTOTT*/

    return x;
}



/*A főmenü két dimenziós ezért kétszer meghívja a navigációs függvényt, amely megmondja, hogy hanyadik menüpontra nyomott,
 * ezeket eltároljuk, és egy egymásba ágyazott switch hajtja végre a megfelelő funckiót.*/
void  fomenu() {

    #ifndef SIM
    econio_rawmode(); /* Getchar működéséhez kell. */
    #endif
    /* A Sok inicializalas elengedhetetlen, tulajdonkeppen ez a program fo magja */
    koktel_tarolo tarolo; /*Koktéltároló létrehozása */
    alapanyag_tarolo alaptarolo; /*Alapanyag tároló létrrehozása */


    /* Egy temporary koktél adatait tároljuk ezekben el. */
    Koktel uj;
    std::string bemeno_nev; /* Koktel neve */
    Alapanyag** betomb=nullptr; /* Koktel alapanyagainak neve */
    int be; /* Hány alapanyaga lesz? Bekérjük ebbe a változóba. */
    std::string alapnev; /*Alapanyag neve   */
    std::string tipus; /* Alapanyag típusa */
    double alkohol; /* Alapanyag alkoholszazaleka */
    std::string b1; /* Alapanyag bekért első tulajdonsága */
    std::string b2; /* Alapanyag bekért második tulajdonsága */
    std::string b3; /* Alapanyag bekért harmadik tulajdonsága */

    /* Pointere egy potenciálisan létrehozott alapanyagnak. */
    Liquor *liq=nullptr;
    Mixer *mix=nullptr;
    Garnishes *gar=nullptr;
    size_t db=0; /* Hány alapanyaga van? */

    /*A menüpontok tömbje, ezeket írja ki. Lehet módosítani a neveket. */
    std::string tomb[5][6] = {{"KOKTELOK", "ALAPANYAGOK", "AUTO-KOK","OPERACIOK","KILEPES"},{"LISTAZAS", "HOZZADAS", "TORLES", "VISSZA"},{"LISTAZAS","HOZZADAS","TORLES","VISSZA"},{"KERES","VISSZA"},{"BEOLVASAS","MENTES","VISSZA"}};

    /* Melyik menüpontra ment az előző és a mostani választásban? */
    int elozo=0;
    int melyik = 0;

    #ifdef SIM

    int menuindex=0;
    /*Szimulációhoz a menüpontokat adja sorban
    PL: 1->1= Koktél->Listázás, 4->1 Operációk->Mentés, -1 Kilépés
     */
    int menusimulation[]={1,1,1,2,2,1,2,2,2,3,3,1,3,0,4,2,4,1,1,1,1,3,-1};

    #endif

    /*Ameddig ki nem lép. */
    while(true){

    #ifdef SIM
        melyik=menusimulation[menuindex++];
        if(melyik==-1) /* Kilépés gombra nyomott. */
            break;
        elozo=melyik;
        melyik=menusimulation[menuindex++];

    #else
        melyik=navigation(tomb[melyik]);
        if(melyik==-1) /* Kilépés gombra nyomott. */
            break;
        elozo=melyik;
        melyik=navigation(tomb[melyik]); /* Almenü megnyitása a megfelelő menüpontokkal */

    #endif

    #ifndef SIM
        econio_clrscr();
    #endif

        switch(elozo){
            case 1:
                switch(melyik){
                    case 1: /* KOKTEL LISTAZAS*/
                        std::cout<<"A taroloban "<<tarolo.db<<" koktel van."<<std::endl;
                        for (size_t i = 0; i < tarolo.db; ++i) {
                            std::cout << tarolo[i]; /* Az operátor szépen megjeleníti a koktél adatait. */
                        }
                    #ifndef SIM
                        econio_getch(); /* Várakozás */
                    #endif
                        break;
                    case 2:{  /*KOKTEL HOZZADAS*/

                        std::cout << "Mi a koktel neve?: ";
                        cp::getline (std::cin,bemeno_nev);
                        std::cout <<"\nHany alapanyaga van?" ;
                        std::cin >> db;
                        betomb=new Alapanyag*[db];

                        /* Annyit olvasunk be, amennyit megadott db-ként !*/
                        for (size_t i = 0; i < db; ++i) {
                            std::cout<< "Mi az alapanyag tipusa?\n1.Liquor\n2.Mixer\n3.Garnish";
                            std::cin >>be;
                            if (be==1){ /* Liquore ment, ezt olvassuk be */
                                std::cout<<"\nAdja meg a Liquor nevet: ";
                                cp::getline(std::cin >> std::ws, alapnev);
                                std::cout<<"\nMennyisege(ml):";

                                /* Nem racionális adatbevitel esetén mégegyszer meg lehet adni. */
                                std::cin >>be;
                                if (be>10000||0>be){
                                    std::cout<<"Adjon meg egy valós mennyiséget milliliterben: ";
                                    std::cin >>be;
                                }
                                std::cout<<"\nAdja meg a Liquor tipusat: ";
                                cp::getline(std::cin>>std::ws,tipus);
                                std::cout<<"Alkohol %: ?";
                                std::cin >> alkohol;

                                /* */
                                if (alkohol>80.0){
                                    std::cout<<"Ilyen alkohol % nem lehetséges!\n"
                                               "Próbálja újra: ";
                                    std::cin >> alkohol;
                                }

                                std::cout<<"\nEdes vagy sem? (true or false)";
                                cp::getline(std::cin>>std::ws,b1);

                                /*A beolvasott adatokbol letrehozzuk az uj anyagot es hozzadjuk a tombhoz*/
                                liq=new Liquor(alapnev,be,tipus,alkohol,stob(b1));
                                betomb[i]=liq;
                            }
                            else if (be==2){ /* Mixers-re ment ezt olvassuk be*/
                                std::cout<<"\nAdja meg a Mixer nevet: ";
                                cp::getline (std::cin>>std::ws,alapnev);
                                std::cout<<"\nMennyisege(ml):";
                                std::cin >>be;
                                std::cout<<"\nSzensavas vagy sem? (true or false)";
                                cp::getline(std::cin>>std::ws,b1);
                                std::cout<<"\nEdes vagy sem? (true or false)";
                                cp::getline(std::cin>>std::ws,b2);
                                std::cout<<"\nAllergen anyag vagy sem? (true or false)";
                                cp::getline(std::cin>>std::ws,b3);

                                /*A beolvasott adatokbol letrehozzuk az uj anyagot es hozzadjuk a tombhoz*/
                                mix=new Mixer(alapnev,be,stob(b1),stob(b2),stob(b3));
                                betomb[i]=mix;
                            }
                            else{ /* Garnishes-re ment, ezt olvassuk be */
                                std::cout<<"\nAdja meg a Garnish nevet: ";
                                cp::getline(std::cin>>std::ws,alapnev);
                                std::cout<<"\nMennyisege(db):";
                                std::cin >>be;
                                std::cout<<"\nCitrusos vagy sem? (true or false)";
                                cp::getline(std::cin>>std::ws,b1);
                                std::cout<<"\nCsipos vagy sem? (true or false)";
                                cp::getline(std::cin>>std::ws,b2);
                                std::cout<<"\nDiszito anyag vagy sem? (true or false)";
                                cp::getline(std::cin>>std::ws,b3);

                                /*A beolvasott adatokbol letrehozzuk az uj anyagot es hozzadjuk a tombhoz*/
                                gar=new Garnishes(alapnev,be,stob(b1),stob(b2),stob(b3));
                                betomb[i]=gar;

                            }
                        }
                        /* A koktél elkészülte után a tárolóhoz adjuk és töröljük az ideigleneseket. */
                        tarolo.add(Koktel(bemeno_nev,betomb,db));

                        /* nullptr törlésnek nincs hatása, ha az lenne */
                        delete liq;
                        delete mix;
                        delete gar;
                        delete[] betomb;
                        break;
                    }
                    case 3: /*KOKTEL TORLES */
                        std::cout<<"Melyiket toroljuk?\n";
                        for (size_t i = 0; i < tarolo.db; ++i) {
                            std::cout <<i<<": "<< tarolo[i].getNev()<<std::endl;
                        }
                        std::cin >> be;
                        try {
                            tarolo.del(size_t(be));

                        }
                        catch(...){
                            puts("Hiba");
                        }
                        break;

                    default:
                        break;
                }
                break;

            case 2:
                switch(melyik){
                    case 1:/* ALAP LISTAZAS*/
                        #ifndef SIM
                        box(std::string("Alapanyagok "),false);
                        #endif
                        for (size_t i = 0; i < alaptarolo.db; ++i) {
                            std::cout <<"-"<< alaptarolo.anyagok[i]<<std::endl;
                        }
                    #ifndef SIM
                        econio_getch(); /* Várakozás */
                    #endif
                        break;

                    case 2: /*ALAP HOZZADAS*/
                        #ifndef SIM
                        std::cout << "Új koktél neve: ";
                        #endif
                        cp::getline(std::cin,bemeno_nev);
                        alaptarolo.add(bemeno_nev);
                        break;
                    case 3: /*ALAP TORLES*/

                        /* Számozva megjelennek az anyagok, sorszám bekérés után törlődik. */
                        std::cout<<"Melyik alapanyagot szeretne torolni?\n";
                        for (size_t i = 0; i < alaptarolo.db; ++i) {
                            std::cout <<i<<": "<< alaptarolo.anyagok[i]<<std::endl;
                        }
                        std::cin >>be;
                        alaptarolo.del(be);
                        break;
                    default:
                        break;
                }
                break;
            case 3: /* KOKTEL KERESO*/
                if(melyik==1){
                    tarolo.autokoktel(alaptarolo); /* Az kereséshez megadjuk az alapanyag tárolót */
                #ifndef SIM
                    econio_getch(); /* Várakozás */
                #endif
                }
                break;
            case 4:
                switch(melyik){
                    case 1:  /*BEOLVASAS*/
                        /*Fájnév bekérés után beolvasás történik */
                        std::cout<<"FAJL NEV: ";
                        cp::getline (std::cin,bemeno_nev);
                    #ifdef SIM
                        bemeno_nev="beolvasos.dat";
                    #endif
                        tarolo.munkamenetbe(bemeno_nev);
                        break;
                    case 2: /*MENTES*/

                        std::cout<<"FAJL NEV: "; /* Fajlnev beolvasas után megtörténik a kiírás. */
                        cp::getline (std::cin,bemeno_nev);
                    #ifdef SIM
                        bemeno_nev="mentett.dat";
                    #endif
                        tarolo.mentes(bemeno_nev);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }

        melyik=0; /* Újra főmenü*/
    }
    tarolo.koktel_torles();
}
