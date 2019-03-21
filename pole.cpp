using namespace std;
#include "pole.h"
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

/*
 struct Pole
 {
     string* str;
     int* num;
     char* ch;
     bool* log;
     int ilosc_wyszukan;
     Pole* next;
 };
 */

//MAINOWE ZMIENNE GLOWA, string -> nazwa pliku z szablonem (2) + nazwa pliku wyjsciowego do zapisu

int stworzNapisowe(string plik, Pole *glowa,int ilosc_napisowych,int ilosc_liczbowych, int ilosc_znakowych, int ilosc_logicznych) //zwraca adres adres nulla i napisow (glowy)
{
    glowa=new Pole;
    glowa->next=nullptr;
    int iloscpol = ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych + ilosc_logicznych;
    glowa->str=new string [iloscpol];

    ifstream pWe (plik.c_str());
    if(!pWe.good())
    {
        cout<<"Zly plik!\n";
        //powrot
    }
    //zbiera nazwy
    string wiersz;
    for(int i=0;i<iloscpol;i++)
    {
        pWe>>glowa->str[i];
        getline(pWe,wiersz);
    }
    pWe.close();//-----------------------------------------------> pozamykaj w reszcie miejsc
    //powrot
    return 0;
}
void stworz_i_dodaj (Pole *&glowa,int ilosc_napisowych,int ilosc_liczbowych, int ilosc_znakowych, int ilosc_logicznych) //dolacza do glowy
{
    Pole *nowy;
    nowy=new Pole;
    //nadam wartosci i dodam do glowy

    nowy->str=new string [ilosc_napisowych];
    nowy->num=new int [ilosc_liczbowych];
    nowy->ch=new char [ilosc_znakowych];
    nowy->log=new bool [ilosc_logicznych];

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
    glowa=nowy;
}

//uzytkownik sam podaje nazwe pliku

void zapis (string plik_wyj, Pole *glowa, int ilosc_napisowych, int ilosc_liczbowych, int ilosc_znakowych, int ilosc_logicznych)
{
   int suma= ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych + ilosc_logicznych;
   ofstream pWy (plik_wyj.c_str());

   pWy<<ilosc_napisowych<<"\t"<<ilosc_liczbowych<<"\t"<<ilosc_znakowych<<"\t"<<ilosc_logicznych;//przy odczycie bedzie wiadomo ile jest jakich pol;

   while(glowa->next!=nullptr) //dochodzi do pola opisowego
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
       glowa=glowa->next;
   }
   for (int i=0;i<suma;i++)
   {
       pWy<<glowa->str[i]<<endl;
   }
   return; //<---- 4ry pierwsze odczyty dają nam "a,b,c,d", potem tworzę pola, ale nie łączę ich ze sobą. W tablicy dynamicznej trzymam
   //kolejne adresy komórek. Na końcu łączę od ostatniego, bo przecież pola są ustawione od końca.
}


void odczyt (string plik_wyj, Pole *&glowa, int ilosc_napisowych, int ilosc_liczbowych, int ilosc_znakowych, int ilosc_logicznych)
{
    ifstream pWe (plik_wyj.c_str());
    if(!pWe.good())
    {
        cout<<"Zla nazwa pliku z baza!"<<endl;
        return;
    }
    for(int i=0;i<4;i++)//odczyt ilości określonych typów podpól
    {
        pWe>>ilosc_napisowych>>ilosc_liczbowych>>ilosc_znakowych>>ilosc_logicznych;
    }

    int licznik_pol=0;
    string pacman;
    while(!pWe.eof())
    {
        pWe>>pacman;
        licznik_pol++;
    } //wiemy ile jest pól

    Pole **adres;
    adres=new Pole* [licznik_pol]; //tablica przechowująca adresy pól

    Pole *nowy;
    nowy=new Pole [licznik_pol];//stworzenie odpowiedniej ilości pól

    for(int k=0; k<licznik_pol; k++)
    {

        nowy[k].str=new string[ilosc_napisowych]; //nie działa zapis typu: nowy[k]->...
        nowy[k].num=new int [ilosc_liczbowych];
        nowy[k].ch=new char[ilosc_znakowych];
        nowy[k].log=new bool[ilosc_logicznych];

        for(int i=0;i<ilosc_napisowych;i++)
        {
            pWe>>nowy[k].str[i];
        }
        for(int i=0;i<ilosc_liczbowych;i++)
        {
            pWe>>nowy[k].num[i];
        }
        for(int i=0;i<ilosc_znakowych;i++)
        {
            pWe>>nowy[k].ch[i];
        }
        for(int i=0;i<ilosc_logicznych;i++)
        {
            pWe>>nowy[k].log[i];
        }
        //gotowe jedno pole. Zbieram adres i wrzucam do tablicy;
        *(adres+k)=(nowy+k);
    }

    for(int k=0; k<licznik_pol-1; k++) //+1 bo jest jeszcze pole napisowe
    {
        (*(adres+k))->next = *(adres+k+1);
    }
    delete []adres;

    //dodanie pola z nazwami

    Pole *napisy;
    napisy=new Pole;
    napisy->str=new string [ilosc_napisowych+ilosc_liczbowych+ilosc_znakowych+ilosc_logicznych];

    for(int i=0;i<licznik_pol;i++)
    {
        pWe>>napisy->str[i];
    }

    //dołączam resztę do "napisów"

    (*(adres+licznik_pol+1))->next=napisy;



}
















