#ifndef POLE_H
#define POLE_H

using namespace std;
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

 struct Pole
 {
     string* str;
     int* num;
     char* ch;
     bool* log;
  /* int ilosc_wyszukan; */ //<------------------------------------------------------
     Pole* next;
 };

    void stworzNapisowe(Pole *&glowa, string plik); //tworzy nulla i napisowe pole (glowy)
    void stworz_i_dodaj(Pole *glowa); //dolacza do glowy
    void zapis (string plik, Pole *glowa, int ilosc_napisowych, int ilosc_liczbowych, int ilosc_znakowych, int ilosc_logicznych);
    void odczyt (string plik_wyj, Pole *glowa, int ilosc_napisowych, int ilosc_liczbowych, int ilosc_znakowych, int ilosc_logicznych);





#endif // POLE_H
