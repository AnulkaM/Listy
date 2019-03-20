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

//MAINOWE ZMIENNE GLOWA, string -> nazwa pliku z szablonem (2)
int stworzGlowe(string plik, Pole *glowa,int ilosc_napisowych,int ilosc_liczbowych, int ilosc_znakowych, int ilosc_logicznych) //zwraca adres adres nulla i napisow (glowy)
{
    glowa=new Pole;
    glowa->next=0;
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
void zapis (string plik, Pole *glowa, int ilosc_napisowych, int ilosc_liczbowych, int ilosc_znakowych, int ilosc_logicznych)
{
   ofstream pWy (plik.c_str());

}
