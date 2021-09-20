//
// Created by Balint on 2021. 03. 24..
//

#include "Koktel.h"



/* Összeszámolja hogy összesen hány milliliter a koktél. */
int Koktel::getQuantity() {
    int osszeg = 0;
    for (size_t i = 0; i < dbIngridient; ++i) {
        osszeg += ingridients[i]->getQuantity();
    }
    return osszeg;

}

/* Összesíti, hogy az alapanyagok alapján hány százalék az alkoholszázalék a teljes koktélra tekintve. */
double Koktel::getAlkohol() {
    double osszeg = 0.0;
    for (size_t i = 0; i < dbIngridient; ++i) {
        osszeg += ingridients[i]->getAlkohol() * (0.01) * ingridients[i]->getQuantity();
    }
    return osszeg / getQuantity() * 100; /* Százalékká váltás*/
}

/* Összeszámolja hány alapanyag édes!
 * Lineáris keresés az alapanyagokon, ha édes, növeljük a számlálót. */
int Koktel::getEdesseg() {
    int osszeg = 0;
    for (size_t i = 0; i < dbIngridient; ++i) {
        osszeg += ingridients[i]->getEdesseg();
    }
    return osszeg;
}

/* Pointert ad vissza a koktél indexedik alapanyagára, lehet módosítani! */
Alapanyag *Koktel::operator[](int i) {
    return ingridients[i];


}

/*Template, amivel egyszerűen lehet alapanyagokat hozzáadni a koktélhoz
 * Nem biztos hogy hosználva lesz. */
template<typename TIPUS>
Koktel Koktel::operator+(TIPUS &alap) {
    Koktel uj(getNev(), dbIngridient + 1); /* Uj koktél létrehozása 1-el tobb alapanyaggal. */


    /* Eddigi alapanyagok átmásolása. */
    for (size_t i = 0; i < dbIngridient; ++i) {
        uj.ingridients[i] = ingridients[i];
    }

    /* Uj alapanyag hozzáadása. */
    uj.ingridients[uj.dbIngridient - 1] = &alap;
    return uj;

}



Koktel &Koktel::operator=(const Koktel &other) {
    if (&other != this) {
        koktel_nev = other.koktel_nev;
        if (ingridients != nullptr)
            delete[] ingridients;
        dbIngridient = other.dbIngridient;
        ingridients = new Alapanyag *[dbIngridient];

        for (size_t i = 0; i < dbIngridient; ++i) {
            ingridients[i] = other.ingridients[i];
        }

    }
    return *this;
}


/* Egy dinamikusan foglalt alapanyagnak a pointerét kapja meg, ezt fűzi hozzá a koktélhoz. */
void Koktel::addAlapanyag(Alapanyag *be) {

    /* Új tömb létrehozása és átmásolni az eddigieket. */
    auto **ujtomb = new Alapanyag *[dbIngridient + 1];
    for (size_t i = 0; i < dbIngridient; ++i) {
        ujtomb[i] = ingridients[i];
    }
    /* Hozzáadni az újat. */
    ujtomb[dbIngridient] = be;
    dbIngridient++;

    /* Régit felszabadítani. */
    delete[] ingridients;
    ingridients = ujtomb;

}

/* Friend függvény, a koktél adatait írja ki a kimenetre. */
std::ostream &operator<<(std::ostream &os, Koktel &kok) {
    os <<"\n\n\n"<< kok.getNev() << ":\n";
    for (size_t i = 0; i < kok.getDb(); ++i) {
        os << "     " << std::setw(15) << kok.ingridients[i]->getNev() << " : " << std::setw(4)
           << kok.ingridients[i]->getQuantity() << " ml" << std::endl;
    }
    os << "Tulajdonsagok\n     Mennyiseg:" << kok.getQuantity() << "\n     Alkohol%: " << kok.getAlkohol() << "\n     Edessegi szint: "
       << kok.getEdesseg();
    return os;
}
