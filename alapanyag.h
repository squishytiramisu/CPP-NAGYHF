
#ifndef CPP_NAGYHF_ALAPANYAG_H
#define CPP_NAGYHF_ALAPANYAG_H
#include <iostream>
#include <utility>
#include "memtrace.h"



/*Az alapanyag egy ősosztály, amelyból leszármaznak a különböző alapanyag típusok.
 * Sok nem tisztán virtuális getter függvénye van. Öröklődés analitikus.
 * Egy koktélban egy ilyen osztálybéli pointer tömböt tárol. */
class Alapanyag{
protected: /* Ősosztály */
    std::string nev; /* Alapanyag neve*/
    int mennyiseg; /* Az alapanyag mennyisége Milliliterben, vagy darabban a Garnishesben. */
public:

    Alapanyag(const char * neve, int mennyiseg):nev(neve),mennyiseg(mennyiseg){}

    Alapanyag(std::string neve, int mennyiseg):mennyiseg(mennyiseg){
        nev=std::move(neve); /* Érték egyszer van csak használva ezért megéri mozgatni, kevesebb másolás a forditonak. */
    }

    /* Alapanyag mennyisege milliliterben*/
    int getQuantity() const{return mennyiseg;}
    std::string getNev(){return nev;}

    /* Nem tisztán virtuális függvények, előnye hogy származtatott oszályokban nem kell őket megvalósítani ha nem változik a működésük
     * és alaposztálynál is teljes mértékben működnek. */
    virtual double getAlkohol(){return 0;}
    virtual int getEdesseg(){return 0;}
    virtual int getSzensavas(){return 0;}
    virtual int getCitrus(){return 0;}
    virtual int getAllergen(){return 0;}
    virtual int getCsipos(){return 0;}
    virtual int getDisz(){return 0;}
    virtual std::string getTipus(){return std::string("Nincs tipusa");}

    /* Csak a mennyiséget és nevet adja értékként, mást nem! */
    Alapanyag& operator=(const Alapanyag& other);

    /* Csak a nevüket hasonlítja össze! */
    bool operator==(Alapanyag masik);
    bool operator!=(Alapanyag masik);

    virtual ~Alapanyag(){
        //DEBUG
    }

};

class Liquor: public Alapanyag{
    std::string tipus;
    double alkohol;
    bool edes;
public:
    Liquor(const char*neve,int mennyiseg,const char* tip,double alk=0,bool edese=false) :Alapanyag(neve,mennyiseg),tipus(tip){

        alkohol=alk;
        edes=edese;
    }
    Liquor(std::string neve,int mennyiseg,std::string tip,double alk=0,bool edese=false) :Alapanyag(neve,mennyiseg){
        tipus=std::move(tip);
        alkohol=alk;
        edes=edese;
    }


    std::string getTipus() override{return tipus;}


    /*Getter függvények azért intet adnak vissza, hogy a visszatérési értéket lehessen hozzáadni egy számlálóhoz.
     * Amikor össze van számolva a számuk akkor lehet a for loopban csak a return értéket kell hozzáadni. Lásd Koktel.getEdesseg() */
    double getAlkohol() override{return alkohol;}
    int getEdesseg() override{return edes? 1 : 0;}

};

class Mixer: public Alapanyag {
    bool szensavas; /* Szénsavas-e ? */
    bool edes; /* Édes-e az alapanyag? */
    bool allergen; /* Allergén anyag-e? */
public:

    /*
     * Mixer(const char* nev,int mennyi,bool szen=false,bool ede=false,bool al=false)
    :Alapanyag(nev,mennyi),
    szensavas(szen),
    edes(ede),
    allergen(al){}
    */
    Mixer(std::string nev,int mennyi,bool szen=false,bool ede=false,bool al=false)
    :Alapanyag(nev,mennyi),
    szensavas(szen),
    edes(ede),
    allergen(al){}

    /*Getter függvények azért intet adnak vissza, hogy a visszatérési értéket lehessen hozzáadni egy számlálóhoz.
     * Amikor össze van számolva a számuk akkor lehet a for loopban csak a return értéket kell hozzáadni. Lásd Koktel.getEdesseg() */
    int getEdesseg() override{return edes? 1 : 0;}
    int getSzensavas()override {return szensavas? 1 : 0;}
    int getAllergen()override {return allergen? 1 : 0;}
};

class Garnishes: public Alapanyag{
    bool citrus; /* Tartalmaz-e citrusfélét? */
    bool csipos; /* Csipős-e az alapanyag? */
    bool disz; /* Egy díszítés-e ?*/
public:


    Garnishes(std::string neve, int mennyi,bool cit=false, bool csip=false, bool disze=false):Alapanyag(neve,mennyi){
        citrus=cit;
        csipos=csip;
        disz=disze;
    }

    /*Getter függvények azért intet adnak vissza, hogy a visszatérési értéket lehessen hozzáadni egy számlálóhoz.
     * Amikor össze van számolva a számuk akkor lehet a for loopban csak a return értéket kell hozzáadni. Lásd Koktel.getEdesseg() */
    int getCsipos() override{return csipos? 1 : 0;}
    int getCitrus()override {return citrus? 1 : 0;}
    int getDisz()override {return disz? 1 : 0;}
};


#endif //CPP_NAGYHF_ALAPANYAG_H
