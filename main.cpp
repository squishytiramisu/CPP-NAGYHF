

#include "menurendszer.h"
#include "alapanyag.h"

#include "gtest_lite.h"

/*TESZTELÉS, ki kell kommentelni itt és menurendszer.cpp-ben ha grafikusat szeretnénk. */
//#define SIM


int main() {

    setbuf(stdout, 0);
    setbuf(stderr, 0);


    #ifdef SIM

    /*COUT BACKUP*/
    std::streambuf* stream_buffer_cout = std::cout.rdbuf();

    std::ifstream in("standard_input.txt");
    std::cin.rdbuf(in.rdbuf());     // cin mostantól az in-ből olvas

    std::ostringstream kimenet;
    std::cout.rdbuf(kimenet.rdbuf());

    #endif


    fomenu();


    #ifdef SIM

    /*Ha a program jól fut le, ez az elvárt kimenet. */
    std::string elvart="A taroloban 0 koktel van.\nMi a koktel neve?: \nHany alapanyaga van?Mi az alapanyag tipusa?\n1.Liquor\n2.Mixer\n3.Garnish\nAdja meg a Liquor nevet: \nMennyisege(ml):\nAdja meg a Liquor tipusat: Alkohol %: ?\nEdes vagy sem? (true or false)Mi az alapanyag tipusa?\n1.Liquor\n2.Mixer\n3.Garnish\nAdja meg a Mixer nevet: \nMennyisege(ml):\nSzensavas vagy sem? (true or false)\nEdes vagy sem? (true or false)\nAllergen anyag vagy sem? (true or false)Mi az alapanyag tipusa?\n1.Liquor\n2.Mixer\n3.Garnish\nAdja meg a Garnish nevet: \nMennyisege(db):\nCitrusos vagy sem? (true or false)\nCsipos vagy sem? (true or false)\nDiszito anyag vagy sem? (true or false)Melyik alapanyagot szeretne torolni?\n0: Martini Henry\nAz alabbi koktelokat tudja elkesziteni:\nFAJL NEV: FAJL NEV: A taroloban 3 koktel van.\n\n\n\nKoktel neve:\n                 Gin :  100 ml\n             Nem Gin :  200 ml\nTulajdonsagok\n     Mennyiseg:300\n     Alkohol%: 4.23333\n     Edessegi szint: 2\n\n\nKoktel2:\n             EZ XDDD :  100 ml\n        EZ A MASODIK :  100 ml\n           Gigarnish :   10 ml\n               VIIIZ :  300 ml\nTulajdonsagok\n     Mennyiseg:510\n     Alkohol%: 1.76471\n     Edessegi szint: 3\n\n\nWhiskey cola:\n             WHiskey :  250 ml\n                Cola :  200 ml\nTulajdonsagok\n     Mennyiseg:450\n     Alkohol%: 22.2222\n     Edessegi szint: 2Melyiket toroljuk?\n0: Koktel neve\n1: Koktel2\n2: Whiskey cola\n";
    std::string actual=kimenet.str();


    /* COUT Visszairányítás */
    std::cout.rdbuf(stream_buffer_cout);


    TEST(TELJES,TEST){
        EXPECT_STREQ(elvart.c_str(),actual.c_str());
    }END

    if(elvart==actual)
        std::cout<<("\nTELJES PROGRAM SIKERESEN FUTOTT LE!\n");


    TEST(2,ALAPANYAG){
        Alapanyag egyik("Egyik",100);
        const Alapanyag& masik=egyik;
        EXPECT_TRUE(egyik==masik);
        EXPECT_FALSE(egyik!=masik);
    }END
    #endif


    return 0;


}
