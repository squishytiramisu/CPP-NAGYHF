//
// Created by Balint on 2021. 03. 30..
//

#include "koktel_tarolo.h"


/* Triviális destruktor */
koktel_tarolo::~koktel_tarolo() = default;


/* A bemenetként kapott koktélból létrehoz egy dinamikusan foglaltat és a tárolóhoz adja, ha van hely. */
void koktel_tarolo::add(Koktel be){

    /* Ha van hely */
    if (db!=kapacitas-1){

        /* Bemeneti koktél helyén lévő koktél minden adatát töröljük. */
        if(be.getDb() <= 0){
            for (size_t j = 0; j < tar[db]->getDb(); ++j) {
                delete tar[db]->operator[](j);
            }
            tar[db]->atnevez(be.getNev());
            return;
        }

        for (size_t j = 0; j < tar[db]->getDb(); ++j) {
            delete tar[db]->operator[](j);
        }
        tar[db]->tolro();
        delete tar[db];

        /* Új koktél alapanyagainak száma. */
        int idex=0;
        /* Új koktél heterogén kollekciója */
        Alapanyag** ujfoglalas=new Alapanyag*[be.getDb()];

        /* Minden egyes alapanyagát a bemenő koktélnak dinamikusan lefoglaljuk és inicializáljuk. */
        for (size_t i = 0; i < be.getDb(); ++i) {
            if (std::string(typeid(*(be[i])).name()) =="6Liquor"){
                auto *p1=new Liquor(be[i]->getNev(),be[i]->getQuantity(),be[i]->getTipus(),be[i]->getAlkohol(),be[i]->getEdesseg());
                ujfoglalas[idex]=p1;
                idex++;
            }
            else if(std::string(typeid(*(be[i])).name()) =="9Garnishes"){
                auto *p2=new Garnishes(be[i]->getNev(),be[i]->getQuantity(),be[i]->getCitrus(),be[i]->getCsipos(),be[i]->getEdesseg());
                ujfoglalas[idex]=p2;
                idex++;
            }
            else{
                auto *p3=new Mixer(be[i]->getNev(),be[i]->getQuantity(),be[i]->getEdesseg(),be[i]->getSzensavas(),be[i]->getAllergen());
                ujfoglalas[idex]=p3;
                idex++;
            }
        }
        /* A kész koktélt hozzáadjuk a tárolóhoz. */
        tar[db]=new Koktel(be.getNev(),ujfoglalas,be.getDb());
        db++;

    }
}

/* A bemetként kapott fájlt megnyitja és kiírja tároló alapanyagait úgy, hogy azt később be lehet olvasni. */
void koktel_tarolo::mentes(const std::string& nev){

    bool elso=true;
    std::ofstream file;
    file.open (nev);

    /* Végigmegyünk az összes koktélon, alapanyagait kiírjuk, a koktélok egy & jellel vannak elválasztva. */
    for (size_t i = 0; i < db; ++i) {
        /*Első alkalommal nem kell ezt kiíri. */
        if(!elso)
            file << "\n";
        elso=false;

        /* Koktél nevének kiírása. */
        file << tar[i]->getNev()<<"\n";
        for (size_t j = 0; j < tar[i]->getDb(); ++j) {

            /* Jelezni kell az alapanyag típusát */
            file << typeid(*(tar[i]->operator[](j))).name() << "\n";
            file << tar[i]->operator[](j)->getNev() << "\n";
            file <<tar[i]->operator[](j)->getQuantity() << "\n";

            /* Az írott alapanyag liquor. */
            if (std::string(typeid(*(tar[i]->operator[](j))).name()) =="6Liquor"){
                file << tar[i]->operator[](j)->getTipus()<< "\n";
                file << tar[i]->operator[](j)->getAlkohol()<< "\n";
                file << tar[i]->operator[](j)->getEdesseg()<< "\n";
            }
            /*Garnish-t írunk ki! */
            else if(std::string(typeid(*(tar[i]->operator[](j))).name()) =="9Garnishes"){
                file << tar[i]->operator[](j)->getCitrus()<< "\n";
                file << tar[i]->operator[](j)->getCsipos()<< "\n";
                file << tar[i]->operator[](j)->getDisz()<< "\n";
            }
            else{ /*Mixert írunk ki*/
                file << tar[i]->operator[](j)->getEdesseg()<< "\n";
                file << tar[i]->operator[](j)->getSzensavas()<< "\n";
                file << tar[i]->operator[](j)->getAllergen()<< "\n";
            }

        }
        /* Elválasztja egymástól a koktélokat.*/
        file <<"&";
    }

    file.close();
}

/* string to bool, 0 és false esetén false, minden más igaz*/
bool stob(const std::string& s){
    if (s=="0" || s=="false")
        return false;
    else
        return true;
}

/* Munkamenet beolvasása egy fájl alapján. Elvárás hogy jó formátumú legyen a fájl. */
void  koktel_tarolo::munkamenetbe(const std::string& fnev) {
    std::ifstream is;               // input file stream, vagyis olvasunk egy fájlból

    is.open(fnev);            // megnyitjuk a fájlt
    if (is.fail()) {
        std::cout << "Nincs ilyen fájl!";
        return;
    }

    std::string s;

    /* Az eddigi tárolót maradéktalanul töröljük. */
    koktel_torles();

    /* Új tároló inicializálás */
    for (auto & i : tar) {
        i=new Koktel("Alap",0);
    }


    /*Kezdetben nincs egy koktél sem*/
    db=0;


    /* Alapanyag mennyisége, neve, első, második harmadik tulajdonsága.
     * Többféle lehet az utolsó 3. */
    std::string mennyiseg;
    std::string nev;
    std::string egyes;
    std::string ketto;
    std::string harom;

    /* Kötelező paramétere a stod függvénynek. */
    size_t string_to_double_parameter=1;

    while (std::getline(is, s)) {
        /* Beolvasott adat a koktél neve, átnevezzük az alap koktélt erre. */
        tar[db]->atnevez(s);

        /*Az s itt most egy alapanyag típusának neve, értelemszerűen amit olvasott annak megfelelpen késziti el az alapanyagot. */
        std::getline(is, s);
        while(s!="&"){
            if (s=="6Liquor"){
                std::getline(is, nev);
                std::getline(is, mennyiseg);
                std::getline(is, egyes);
                std::getline(is, ketto);
                std::getline(is, harom);

                /* Lefoglalás és hozzáadjuk a koktélhoz az alapanyagot. */
                auto *id= new Liquor(nev,std::stoi(mennyiseg),egyes,std::stod(ketto,&string_to_double_parameter),stob(harom));
                tar[db]->addAlapanyag(id);
            }
            else if (s=="5Mixer"){
                std::getline(is, nev);
                std::getline(is, mennyiseg);
                std::getline(is, egyes);
                std::getline(is, ketto);
                std::getline(is, harom);
                auto *id= new Mixer(nev,std::stoi(mennyiseg),stob(egyes),stob(ketto),stob(harom));
                tar[db]->addAlapanyag(id);
            }
            else if (s=="9Garnishes"){
                std::getline(is, nev);
                std::getline(is, mennyiseg);
                std::getline(is, egyes);
                std::getline(is, ketto);
                std::getline(is, harom);
                auto *id= new Garnishes(nev,std::stoi(mennyiseg),stob(egyes),stob(ketto),stob(harom));
                tar[db]->addAlapanyag(id);
            }
            std::getline(is, s);
        }
        /* Egy koktél elkészült */
        db++;
    }
    is.close();
}
/* Paraméterként kapott alapanyag nevet keresi meg a tárolóban, ha megtalálta return true, másesetben false. */
bool alapanyag_tarolo::vanebenne(const std::string& nev){
    for (size_t i = 0; i < db; ++i) {
        /* Alapanyag megtalálva */
        if (anyagok[i]==nev)
            return true;
    }
    return false;
}

/* Paraméterként kapott alapanyagtárolót tekinti az elérhető alapanyagoknak.
 * Koktélokon végigmenve megnézi, hogy egy koktél összes alapanyaga rendelkezésre áll e a tárolóban, ha igen kiírja a koktél nevét. */
void koktel_tarolo::autokoktel(alapanyag_tarolo alaptarolo){
    std::cout<<"Az alabbi koktelokat tudja elkesziteni:\n";
    for (size_t i = 0; i < db; i++) {
        bool lehet=true;

        /* Az összes koktélt meg kell vizsgálni. */
        for (size_t j = 0; j < tar[i]->getDb(); ++j) {

            /* Van a tárolóban a paraméterként kapott alapnyag? */
            lehet=alaptarolo.vanebenne(tar[i]->operator[](j)->getNev());

            /* Ha egy alapanyag nem áll rendelkezésre fölösleges továbbnézni. */
            if (!lehet)
                break;
        }
        /* Ha lehetséges maradt akkor kiírjuk az alapanyagot. */
        if (lehet)
            std::cout <<tar[i]->getNev()<<std::endl;
    }
}

/* Teljes tároló felszabadítása. */
void koktel_tarolo::koktel_torles() {
    /* Amit törölni kell az a Koktél pointere, a Koktélnak az alapanyagai, Koktél alapanyagainak tömbje. */
    for (auto & i : tar) {
        for (size_t j = 0; j < i->getDb(); ++j) {
            delete i->operator[](j); /* Alapanyagok törlése */
        }
        i->tolro(); /* Alapanyag tömb felszabadítása */
        delete i; /* Koktélok törlése */
    }
}

void koktel_tarolo::del(size_t id) {

    /* Indexelési hiba esetén nincs teendő */
    if (id>=kapacitas || id>0)
        return;
    /* Alapanyagok törlése */
    for (size_t j = 0; j < tar[id]->getDb(); ++j) {
        delete tar[id]->operator[](j);
    }
    /* Koktél törlése */
    tar[id]->tolro();
    delete tar[id];

    /* Új lefoglalása */
    tar[id] = new Koktel("Alap",0);
    db--;
    for (size_t i = id; i < kapacitas-1; ++i) {
        Koktel *temp=tar[i];
        tar[i]=tar[i+1];
        tar[i+1]=temp;
    }
}

/* Hogyha talál egy üres helyet berakja az alapanyagot! Foglaltságiban átálítja igazra. */
void alapanyag_tarolo::add(const std::string& nev){
    for (size_t i = 0; i < max; ++i) {
        if (!van[i]){
            anyagok[i] = nev;
            van[i]=true;
            db++;
            break;
        }
    }
}

/* Azzal hogy az foglaltsági táblában false lesz, felülírható lesz. */
void alapanyag_tarolo::del(size_t i){
    van[i]=false;
    db--;
}