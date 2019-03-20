#include "analiza_szablonu.h"

using namespace std;
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

analiza_szablonu::analiza_szablonu()
{

}

void analiza_szablonu::ilNap(int ilnap)
{
    ilosc_napisowych=ilnap;
};

void analiza_szablonu::ilLicz(int illicz)
{
   ilosc_liczbowych=illicz;
};

void analiza_szablonu::ilZN(int ilzn)
{
    ilosc_znakowych=ilzn;
};

void analiza_szablonu::ilLog(int illog)
{
    ilosc_logicznych=illog;
};


//MAINOWE ZMIENNE GLOWA, string -> nazwa pliku z szablonem +

void analiza_szablonu::Analiza(string plik, int &Napis, int &Liczbowe, int &Znakowe, int &Logiczne)
{

ifstream pWe (plik.c_str());
if(!pWe.good())
{
    cout<<"Brak pliku z szablonem!\n";
    return; //ma wrocic do poczatku
}

string wiersz, reszta_wiersza, nazwa_podpola,

        pole_liczbowe="   \"0\";",
        pole_napisowe="  \"Napis\";",
        pole_logiczne="  \"?\";",
        pole_znakowe="  \"x\";";

int ilosc_liczbowych=0, ilosc_znakowych=0, ilosc_logicznych=0, ilosc_napisowych=0, ile_wierszy=0;

while (!pWe.eof())
{
    getline(pWe,wiersz);
    ile_wierszy++;
}
pWe.close();

pWe.open("C:/szablon.txt");
for(unsigned int i=0;i<ile_wierszy;i++) //analiza szablonu
{
    pWe>>nazwa_podpola;
    getline(pWe,reszta_wiersza);

    else if(reszta_wiersza==pole_napisowe)
    {
        ilosc_napisowych++;
    }
    if(reszta_wiersza==pole_liczbowe)
    {
        ilosc_liczbowych++;
    }
    else if(reszta_wiersza==pole_znakowe)
    {
        ilosc_znakowych++;
    }
    else if(reszta_wiersza==pole_logiczne)
    {
        ilosc_logicznych++;
    }

    else
    {
        cout<<"Blad w zapisie. Niezgodnosc z szablonem. Linijka numer: "<<i+1<<"\t";
        return;
    }
    if(nazwa_podpola.size()==0)
    {
        cout<<"Blad w nazwie podpola. Linijka numer: "<<i+1<<"\n";
        return;
    }
}
Znak=ilosc_znakowych;
Napis=ilosc_napisowych;
Logiczne=ilosc_logicznych;
Liczbowe=ilosc_liczbowych;
};
