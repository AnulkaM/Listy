using namespace std;
#include <iostream>
#include "baza.h"
#include "stery.h"
int main()
{
    Baza baza;
     do
     {
        if(Stworz())
        {
            baza.nazwa_szablonu();
            baza.analizuj_i_stworz_napisowe();
            do
            {
                baza.wyswietl_opisowe();
                baza.stworz_i_dodaj();
            }
            while(Kolejny());

            if(Czyszczenie())
            {
                Clear();
            }

            if(Pokaz())
            {
                baza.pokaz();
            }
            if(Szukaj())
            {
                baza.szukaj();
            }

            if(Czyszczenie())
            {
                Clear();
            }

            if(Zapis())
            {
                baza.zapis();
            }

            if(Koniec())
            {
                return 0;
            }
        }
        if(Odczyt())
        {
            baza.nazwa_plik_odczytu();
            baza.odczyt();
            baza.pokaz();

            if(Kolejny())
            {
                baza.stworz_i_dodaj();
            }
            if(Szukaj())
            {
                baza.szukaj();
            }
            if(Czyszczenie())
            {
                Clear();
            }

            if(Pokaz())
            {
                baza.pokaz();
            }

            if(Czyszczenie())
            {
                Clear();
            }

            if(Zapis())
            {
                baza.zapis();
            }

            if(Koniec())
            {
                return 0;
            }
        }


    }
    while(OdNowa());
    Zakoncz();

    return 0;
}


