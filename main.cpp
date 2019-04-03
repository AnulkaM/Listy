   using namespace std;
#include <iostream>
#include "baza.h"

int main()
{
    bool kolejny=1, again=1;
    Baza baza;

    while(again)
    {

        cout<<"x"<<endl;
        baza.nazwa_szablonu();
        cout<<"x"<<endl;
        baza.analizuj_i_stworz_napisowe();

        cout<<"x"<<endl;
        while(kolejny)
        {
            baza.stworz_i_dodaj();
            cout<<"Stworzyc kolejne podpole? Wpisz 1 lub 0."<<endl;
            cin>>kolejny;
        }

        baza.pokaz();

        break;

        cout<<"x"<<endl;

        baza.nazwa_p_zapisu();

        cout<<"x"<<endl;

        baza.zapis();

        cout<<"x"<<endl;

        baza.nazwa_plik_odczytu();

        cout<<"x"<<endl;

        baza.odczyt();

        cout<<"x"<<endl;

        baza.pokaz();

        cout<<"Ponawiamy procedure dzialania programu od nowa? Wpisz 1 lub 0."<<endl;
    }



    return 0;
}
