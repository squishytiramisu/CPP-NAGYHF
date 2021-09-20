//
// Created by Balint on 2021. 03. 23..
//

#include "alapanyag.h"

/* Egyenlőségjel operátor egy konstans Alapanyag referenciát kap paraméterként, és értékül adja ezt az alapanyagnak. */
Alapanyag& Alapanyag::operator=(const Alapanyag& other){
    if (&other!=this){
        nev=other.nev;
        mennyiseg=other.mennyiseg;
    }
    return *this;
}

/* Bemenete két alapanyag, visszatérési boolean érték, hogy megegyezik-e a nevük. */
bool Alapanyag::operator==(Alapanyag masik){
    if(nev==masik.getNev())
        return true;
    return false;
}

/* Bemenete két alapanyag, visszatérési boolean érték, hogy megegyezik-e a nevük. */
bool Alapanyag::operator!=(Alapanyag masik){
    if(nev==masik.getNev())
        return false;
    return true;
}

