//
// Created by Balint on 2021. 03. 30..
//

#ifndef CPP_NAGYHF_KOKTEL_TAROLO_H
#define CPP_NAGYHF_KOKTEL_TAROLO_H

/* Ez a fájl tartalmazza a tároló osztályokat. */



#include <fstream>
#include "Koktel.h"

/* Az alapanyag tároló egy fix méretű tároló, amely tárolja alapanyagok nevét. */
struct alapanyag_tarolo{
    static const size_t max=20; /* A tároló maximális megengedett mérete. */
    size_t db; /* Jelenleg bennelevő alapanyag száma. Hatékonyság miatt érdemes eltárolni. */
    bool van[max]; /* Egy olyan tömb, amely eltárolja, hogy egy adott indexen van- e aktiv alapanyag, ha nem, akkor azt felul lehet írni.*/
    std::string anyagok[max]; /*Az alapanyagok neveit eltároló tömb. */


    /*A konstruktor inicializal minden elemet "alap"-ra és a foglaltsági tömböt false-ra állítja. */
    alapanyag_tarolo(){
        for (size_t i = 0; i < max; ++i) {
            van[i]=false;
            anyagok[i]=std::string("alap");
        }
        db=0; /* Alapértelmezetten üres a tároló. */
    }


    /* Paraméterként kapott alapanyag nevet hozzáadja a tárolóhoz, ha van hely. Ha nincs kivételt dob. */
    void add(const std::string& nev);

    /* A paraméterként kapott indexű elemet beállítja nem használatban lévőre. Ezzel fölülírhatóvá válik. */
    void del(size_t i);

    /*A paraméterként kapott alapanyag névről megmondja, hogy benne van-e a tárolóban, visszatérési értéke boolean. */
    bool vanebenne(const std::string& nev);

};

struct koktel_tarolo {
    static const size_t kapacitas=10; /* A maximális mérete a konténernek. */
    size_t db; /* A jelenleg tárolt koktélok száma. */
    Koktel *tar[kapacitas]; /* Koktélokra mutató pointereket tároló tömb. */

    /*  A konstruktorban megtörténik, a koktélok dinamikus foglalása, és alapértelmezettre inicializálása. */
    koktel_tarolo():db(0){
        for (size_t i = 0; i < kapacitas; ++i) {
            tar[i]=new Koktel("Alap",0);
        }
    }
    ~koktel_tarolo();

    /*A paraméterként kapott fájlnév alapján megnyitja a fájlt, ha nem létezik létrehoz, ha már igen fölülír egy fájlt.
 * A koktél tároló teljes tartalmát ki fogja írni, ami beolvasható akár azonnal. */
    void mentes(const std::string& nev);

    /* A függvény a paraméterként kapott fájlnevet megnyitja, kivételt dob ha nem sikerul.
     * A megnyitás után megtörténik a beolvasás, a konténer eddigi tartalmát fölülírja.*/
    void munkamenetbe(const std::string& fnev);

    /* A paraméterként kapott koktélt törli az adatbázisból.*/
    void del(size_t);

    /* A tároló tejes dinamikusan foglalt tartalmát felszabadítja. */
    void koktel_torles();

    /* Paramétere egy alapanyag tároló. A szabványos kimenetre írja, hogy hány és milyen koktélokat lehetséges elkészíteni
     * a tárolóból, amelyhez van minden szükséges alapanyag. Ha egy koktélnak az összes alapanyaga megtalálható a bemenetként kapott alapanyag tárolóban, megtörténik a kiírás. */
    void autokoktel(alapanyag_tarolo aptarolo);

    /* A paraméterként kapott koktélt hozzáadja a tárolóhoz, ha nincs hely kivételt dob. */
    void add(Koktel be);

    /* Az indexelő operátor a tároló indexedik elemét tároló koktél referenciáját adja vissza. */
    Koktel& operator[](int i) {
        return *tar[i];
    }
};


/* Paraméterként kapott stringet alakít át boolean-ra.
 * true->true vagy 1->true minden más false.
 * Elnevezés: string to bool ->stob */
bool stob(const std::string& s);


#endif //CPP_NAGYHF_KOKTEL_TAROLO_H
