#include "stery.h"
#include <iostream>
#include <string>
using namespace std;
int Czyszczenie()
{
    int odp;
    cout<<"\nWyczyscic okno konsoli?"<<"\t";
    cin.clear();
    cin.sync();
    do
    {
        cin>>odp;

    }while(!(odp==1 || odp==0));
    return odp;
}
void Clear()
{
    system("cls");
    return;
}
int OdNowa()
{
    int odp;
    cout<<"\nOd nowa?"<<"\t";
    cin.clear();
    cin.sync();
    do
    {
        cin>>odp;

    }while(!(odp==1 || odp==0));
    return odp;
}
int Stworz()
{
    int odp;
    cout<<"\nStworzyc wlasna baze?"<<"\t";
    cin.clear();
    cin.sync();
    do
    {
        cin>>odp;

    }while(!(odp==1 || odp==0));
    return odp;
}
int Kolejny()
{
    int odp;
    cout<<"\nStworzyc kolejne podpole?"<<"\t";
    cin.clear();
    cin.sync();
    do
    {
        cin>>odp;

    }while(!(odp==1 || odp==0));
    return odp;
}
int Pokaz()
{
    int odp;
    cout<<"\nPokazac zapisana baze?"<<"\t";
    cin.clear();
    cin.sync();
    do
    {
        cin>>odp;

    }while(!(odp==1 || odp==0));
    return odp;
}
int Koniec()
{
    int odp;
    cout<<"\nZakonczyc dzialanie programu?"<<"\t";
    cin.clear();
    cin.sync();
    do
    {
        cin>>odp;

    }while(!(odp==1 || odp==0));
    return odp;
}
int Pomoc()
{
    int odp;
    cout<<"\nWyswietlic pomoc?"<<"\t";
    cin.clear();
    cin.sync();
    do
    {
        cin>>odp;

    }while(!(odp==1 || odp==0));
    return odp;
}
int Zapis()
{
    int odp;
    cout<<"\nZapisac baze?"<<"\t";
    cin.clear();
    cin.sync();
    do
    {
        cin>>odp;

    }while(!(odp==1 || odp==0));
    return odp;
}
int Odczyt()
{
    int odp;
    cout<<"\nCzy chcesz odczytac baze z wczesniej zapisanego pliku?"<<"\t";
    cin.clear();
    cin.sync();
    do
    {
        cin>>odp;

    }while(!(odp==1 || odp==0));
    return odp;
}
void Zakoncz()
{
    cout<<"\nKoniec programu.";
    return;
}
int Szukaj()
{
    int odp;
    cout<<"\nCzy chcesz znalezc konkretne pole?"<<"\t";
    cin.clear();
    cin.sync();
    do
    {
        cin>>odp;

    }while(!(odp==1 || odp==0));
    return odp;
}
int Ponow_probe()
{
    int odp;
    cout<<"\nCzy chcesz wyszukac jeszcze raz?"<<"\t";
    cin.clear();
    cin.sync();
    do
    {
        cin>>odp;

    }while(!(odp==1 || odp==0));
    return odp;
}
