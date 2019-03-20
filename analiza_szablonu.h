#ifndef ANALIZA_SZABLONU_H
#define ANALIZA_SZABLONU_H

using namespace std;
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>


class analiza_szablonu
{
public:
    analiza_szablonu();

    int ilosc_napisowych, ilosc_liczbowych, ilosc_znakowych, ilosc_logicznych;


    void Analiza(string nazPliku, int &Napis,int &Liczbowe, int &Znak,int &Logiczne);
    void ilNap(int ilnap);
    void ilLog(int illog);
    void ilZN (int ilzn);
    void ilLicz(int illicz);
};

#endif // ANALIZA_SZABLONU_H
