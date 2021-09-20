//
// Created by Balint on 2021. 04. 03..
//

#ifndef CPP_NAGYHF_MENURENDSZER_H
#define CPP_NAGYHF_MENURENDSZER_H

#include <iostream>
#include <string>
#include <iomanip>

/* Bemenete egy string tomb, amelyeknek elemei az egyes elerheto menupontok, ezeket írja ki egymás alá.
 * Visszateresi erteke, hogy hanyadik menuponton volt a felhasznalo, melyiket valasztotta.
 * Navigalni a w és s betukkel lehet benne.
 * */
int navigation(std::string *tomb);


/*Bemenete egy string tomb, ami a menupontok tombje és egy int,hogy melyik menuponton van a felhasznalo.
 * Csupán a képernyőre rajzol a box függvény segítségével.*/
void menu(int x, std::string *tomb);

/* A bemenetként kapott stringet kiírja a képernyőre egy ASCII-ból rajzolt dobozban,bool paramétere
 * a menüpont aktívságát jelzi. */
void box(const std::string& be, bool aktiv);

/* A főmenü képzi a program alapját. Végtelen ciklusban meghívja a menüt ameddig ki nem lép a felhasználó
 * Alapja egy egymásbaágyazott switch, melyekben a kívánt programfunkció hajtódik végre. Végén mindig főmenübe jut vissza.*/
void fomenu();

#endif //CPP_NAGYHF_MENURENDSZER_H
