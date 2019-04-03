#ifndef BAZA_H
#define BAZA_H

using namespace std;
#include <iostream>
#include <string>
struct Pole
{
    string* str;
    int* num;
    char* ch;
    bool* log;
    int ilosc_wyszukan;
    Pole* next;
};
class Baza
{
public:
    Baza();
    int ilosc_napisowych;
    int ilosc_liczbowych;
    int ilosc_znakowych;
    int ilosc_logicznych;
    string szablon, plik_zapisu, plik_odczytu;
private:
    Pole *glowa;
    Pole *pierwotna;
public:

    int pobierzIloscWyszukiawn();
    void nazwa_p_zapisu();
    void nazwa_szablonu();
    void analizuj_i_stworz_napisowe();
    void stworz_i_dodaj();
    void zapis ();
    void odczyt ();
    void pokaz ();
    void nazwa_plik_odczytu();

};


#endif // BAZA_H
