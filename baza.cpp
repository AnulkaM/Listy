#include "baza.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
using namespace std;

Baza::Baza()
{
    ilosc_napisowych=0;
    ilosc_liczbowych=0;
    ilosc_znakowych=0;
    ilosc_logicznych=0;
    this->pierwotna=new Pole;
    this->glowa=new Pole;
    this->glowa->next=NULL;
    this->pierwotna=glowa;
    //this->glowa->ilosc_wyszukan=5;


}

void Baza::nazwa_p_zapisu()
{
    string nazwa;
    cin>>nazwa;
    this->plik_zapisu=nazwa.c_str();
}

void Baza::nazwa_plik_odczytu()
{
    string nazwa;
    cin>>nazwa;
    this->plik_odczytu=nazwa;
}
void Baza::nazwa_szablonu()
{
    string nazwa;
    cin>>nazwa;
    szablon=nazwa.c_str();
}
void Baza::analizuj_i_stworz_napisowe()
{
    ifstream pWe (szablon);
    if(!pWe.good())
    {
        cout<<"Brak pliku z szablonem!\n";
        return;
    }
    string wiersz, reszta_wiersza, nazwa_podpola;
    int ile_wierszy=0;
    const string
            pole_liczbowe="\t\"0\";",
            pole_napisowe="\t\"napis\";",
            pole_logiczne="\t\"?\";",
            pole_znakowe="\t\"x\";";

    while (!pWe.eof())
    {
        getline(pWe,wiersz);
        ile_wierszy++;
    }
    pWe.close();

    pWe.open(szablon);

    for(int i=0;i<ile_wierszy;i++)
    {
        pWe>>nazwa_podpola;
        getline(pWe,reszta_wiersza);
        if(reszta_wiersza==pole_napisowe)
        {
            this->ilosc_napisowych++;
        }
        else if(reszta_wiersza==pole_liczbowe)
        {
            this->ilosc_liczbowych++;
        }
        else if(reszta_wiersza==pole_znakowe)
        {
            this->ilosc_znakowych++;
        }
        else if(reszta_wiersza==pole_logiczne)
        {
            this->ilosc_logicznych++;
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
    pWe.close();

    if(ile_wierszy!= ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych + ilosc_logicznych)
    {
        cout<<"Cos jest nie tak z iloscia podpol w szablonie ( ilosc wierszy != ilosc podpol)."<<endl;
    }

    pWe.open(szablon);

       this->glowa->str=new string [ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych + ilosc_logicznych];

    for(int i=0;i<ile_wierszy;i++)
    {
        pWe>>nazwa_podpola;
        getline(pWe,reszta_wiersza);
        this->glowa->str[i]=nazwa_podpola;
    }

return;
}

void Baza::stworz_i_dodaj()
{
    Pole *nowy;
    nowy=new Pole;
    nowy->str=new string [ilosc_napisowych];
    nowy->num=new int [ilosc_liczbowych];
    nowy->ch=new char [ilosc_znakowych];
    nowy->log=new bool [ilosc_logicznych];
    //komunikat o kolejnosci wpisywania
    for(int i=0;i<ilosc_napisowych;i++)
    {
        cin>>nowy->str[i];
    }
    for(int i=0;i<ilosc_liczbowych;i++)
    {
        cin>>nowy->num[i];
    }
    for(int i=0;i<ilosc_znakowych;i++)
    {
        cin>>nowy->ch[i];
    }
    for(int i=0;i<ilosc_logicznych;i++)
    {
        cin>>nowy->log[i];
    }
    nowy->next=glowa;
    this->glowa=nowy;
}
int Baza::pobierzIloscWyszukiawn()
{
    return this->glowa->ilosc_wyszukan;
}

void Baza::zapis() //+ zapis ilosci wyszukan
{
    ofstream pWy (plik_zapisu.c_str());
    Pole *ogon;
    ogon = new Pole;
    ogon = glowa;

    pWy<<ilosc_napisowych<<"\t"<<ilosc_liczbowych<<"\t"<<ilosc_znakowych<<"\t"<<ilosc_logicznych<<"\t"; //przy odczycie bedzie wiadomo ile jest jakich pol;
       while(glowa->next!=NULL) //dochodzi do pola opisowego
       {
           for(int i=0;i<ilosc_napisowych;i++)
           {
               pWy<<glowa->str[i]<<endl;
           }
           for(int i=0;i<ilosc_liczbowych;i++)
           {
               pWy<<glowa->num[i]<<endl;
           }
           for(int i=0;i<ilosc_znakowych;i++)
           {
               pWy<<glowa->ch[i]<<endl;
           }
           for(int i=0;i<ilosc_logicznych;i++)
           {
               pWy<<glowa->log[i]<<endl;
           }
           this->glowa=glowa->next;
       }
       for (int i=0; i<ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych + ilosc_logicznych; i++)
       {
           pWy<<glowa->str[i]<<endl;
       }
       pWy.close();

       glowa = ogon;
       //usuwam dotychczasową listę
       Pole *stary;
       stary = new Pole;
       while(glowa->next!=NULL)
       {
           delete []glowa->str;
           delete []glowa->num;
           delete []glowa->ch;
           delete []glowa->log;
           stary = glowa;
           this->glowa=glowa->next;
           delete stary;
       }
       delete []glowa->str;

       return;
}
void Baza::odczyt() //odpowiednio spreparowany plik + odczyt ilosci wyszukan
{
    ifstream pWe (plik_odczytu);
    for(int i=0;i<4;i++)
    {
        pWe>>this->ilosc_napisowych>>this->ilosc_liczbowych>>this->ilosc_znakowych>>this->ilosc_logicznych;
    }
    int suma = ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych + ilosc_logicznych;

    /*
    for(int i=0;i<suma;i++)
    {
        pWe>>this->glowa->str[i];
    }
    */
    int ile_pol = suma / 4;

    Pole **wskaznik,*wczesniejszy;
    *wskaznik=new Pole [ile_pol];
    wczesniejszy=new Pole;

    this->glowa=(*wskaznik+ile_pol);

    for(int ile=0;ile<ile_pol;ile++)
    {
        for(int i=0;i<ilosc_napisowych;i++)
        {
            pWe>>(*wskaznik+ile)->str[i];
        }
        for(int i=0;i<ilosc_liczbowych;i++)
        {
            pWe>>(*wskaznik+ile)->num[i];
        }
        for(int i=0;i<ilosc_znakowych;i++)
        {
            pWe>>(*wskaznik+ile)->ch[i];
        }
        for(int i=0;i<ilosc_logicznych;i++)
        {
            pWe>>(*wskaznik+ile)->log[i];
        }
    }
    for(int i=ile_pol;i>0;i--)
    {
        wczesniejszy=(*wskaznik+ile_pol-1);
        wczesniejszy->next=(*wskaznik+ile_pol);
    }
    delete [] wczesniejszy;

    for(int i=0;i<suma;i++)
    {
        pWe>>this->glowa->str[i];
    }
    return;
}
void Baza::pokaz ()
{
    int suma = ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych + ilosc_logicznych;

    for(int i=0;i<suma+1;i++) // nie robi setw dla ostatniego pola + wywala
    {
        cout<<setw(10)<<pierwotna->str[i];
    }
    cout<<endl;

    while(glowa->next!=NULL)
    {
        for(int i=0;i<ilosc_napisowych;i++)
        {
            cout<<setw(10)<<glowa->str[i];
        }
        for(int i=0;i<ilosc_liczbowych;i++)
        {
            cout<<setw(10)<<glowa->num[i];
        }
        for(int i=0;i<ilosc_znakowych;i++)
        {
            cout<<setw(10)<<glowa->ch[i];
        }
        for(int i=0;i<ilosc_logicznych;i++)
        {
            cout<<setw(10)<<glowa->log[i];
        }
        cout<<endl;
    }
    cout<<"udalo sie!!!";
    return;
}
