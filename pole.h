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
     int ilosc_wyszukan;
     Pole* next;
 };

    void stworzGlowe(Pole *&glowa, string plik); //zwraca adres adres nulla i napisow (glowy)
    void stworz_i_dodaj(Pole *glowa); //dolacza do glowy






#endif // POLE_H
