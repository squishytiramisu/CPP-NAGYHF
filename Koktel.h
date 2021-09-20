//
// Created by Balint on 2021. 03. 24..
//

#ifndef CPP_NAGYHF_KOKTEL_H
#define CPP_NAGYHF_KOKTEL_H



#include <string>
#include <iomanip>
#include <utility>
#include "alapanyag.h"



/* Az osztály amely egyetlen koktél korlátlan számú alapanyagát tárolja el. */
class Koktel {
    std::string koktel_nev; /* A koktél megnevezése */
    Alapanyag **ingridients = nullptr; /* Heterogén kollekció, Alapanyag pointerekre mutat, lehet: Liquor, Mixer és Garnishes osztály. */
    size_t dbIngridient = 0; /* Heterogén kollekció darabszáma*/

public:
    /* Triviális konstruktorok */
    explicit Koktel(const char *benev) : koktel_nev(benev) {}

    Koktel():ingridients(nullptr),dbIngridient(0){

    }

    Koktel(const char *benev, size_t dbing) : dbIngridient(dbing){
        ingridients = new Alapanyag *[dbing]; /*Minden alapanyag dinamikusan van foglalva. */
        koktel_nev = benev;
    }

    Koktel(std::string benev, size_t dbing) : dbIngridient(dbing) {
        koktel_nev =std::move(benev); /* Mozgatás oka az az, hogy csak egyszer van használva, fölösleges másolgatás lenne a fordítónak az értékátadás.*/
        ingridients = new Alapanyag *[dbing];
    }

    /*A konstruktor egy dinamikusan foglalt Alapanyag pointer tombot vesz át. */
    Koktel(std::string benev, Alapanyag **tomb, size_t dbing) : ingridients(tomb) {
        koktel_nev = std::move(benev); /* Mozgatás oka az az, hogy csak egyszer van használva, fölösleges másolgatás lenne a fordítónak az értékátadás.*/
        dbIngridient = dbing;
    }

    /* A dinamikusan lefoglalt teruleteket manualisan erdemes felszabaditani, az automatikus optimalizacio tobbszoros felszabaditast tud eredmenyezni. */
    void tolro(){
        delete[] ingridients;
        //ingridients=nullptr;
    }
    /* A koktel megnevezeset megvaltoztatja*/
    void atnevez(std::string ujnev) {
        koktel_nev = std::move(ujnev); /* Mozgatás oka az az, hogy csak egyszer van használva, fölösleges másolgatás lenne a fordítónak az értékátadás.*/
    }

    /* Az alapanyagok mennyisegenek osszeget  adja vissza milliliterben. */
    int getQuantity();

    /* A koktel alapanyagainak számát adja vissza. */
    size_t getDb() const{return dbIngridient;}

    /* A koktel megnevezését adja vissza string típusként. */
    std::string getNev() {
        return koktel_nev;
    }

    /* A koktel alkoholszázalékát adja vissza doublként a teljes koktélra nézve. */
    double getAlkohol();

    /* A paraméterként kapott alapanyag pointert adja hozzá a koktélhoz. */
    void addAlapanyag(Alapanyag *be);

    /* A koktel alapanyagait megvizsgalva megszámolja hány édes alapanyag van, darabszámmal tér vissza. */
    int getEdesseg();

    /* Egyenlőség operátor koktél referenciával tér vissza. Lemásolja a paraméterként kapott koktélt. */
    Koktel &operator=(const Koktel &other);

    /* Védelmet feloldó deklaráció a globális operátornak, paraméterként kapott koktél tulajdonságait írja ki a szabványos kimenetre. */
    friend std::ostream& operator<<(std::ostream&,Koktel&);


    /*Az indexelő operátor a paraméterként kapott indexedik elemét adja vissza a koktél alapanyag pointer tömbjének.*/
    Alapanyag* operator[](int i);

    /* Paraméterként kapott alapanyagot fűzi hozzá a koktélhoz, visszatérési értéke az új koktél. */
    template<typename TIPUS>
    Koktel operator+(TIPUS &alap);
};





#endif //CPP_NAGYHF_KOKTEL_H
