#include "baza.h"
#include "stery.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
//getchar()
#include <string>
using namespace std;
//09.05. 19:30
Baza::Baza()
{
    ilosc_napisowych=0;
    ilosc_liczbowych=0;
    ilosc_znakowych=0;
    ilosc_logicznych=0;
    this->pierwotna=new Pole;
    this->glowa=new Pole;
    this->glowa->next=nullptr;
    this->pierwotna=glowa;
    this->suma=0;
    this->szerokosc_podpola=0;
}


//19.04 00:02
void Baza::wyswietl_opisowe()
{
    cout<<"\nPola:\n";
    unsigned int najdluzszy_wyraz = pierwotna->str[0].size();
    for(unsigned int i=0;i<suma;i++)
    {
        if(najdluzszy_wyraz < pierwotna->str[i].size())
        {
            najdluzszy_wyraz = pierwotna->str[i].size();
        }
    }
    for (unsigned int i=0; i<this->suma; i++)
    {
        cout<<setw(najdluzszy_wyraz + 5)<<left<<pierwotna->str[i];
    }
    cout<<"\n";
}



//20.04 00:20
void Baza::nazwa_p_zapisu()
{
    cout<<"\nWpisz sciezke do pliku z zapisem: ";
    string nazwa;
    cin.clear();
    cin.sync();
    cin>>nazwa;
    this->plik_zapisu=nazwa.c_str();
}



//20.04 00:23
void Baza::nazwa_plik_odczytu()
{
    cout<<"\nPodaj sciezke do pliku z wczesniej zapisana baza:";
    string nazwa;
    cin.clear();
    cin.sync();
    cin>>nazwa;
    this->plik_odczytu=nazwa;
}



//19.04 22:20
void Baza::nazwa_szablonu()
{
    string nazwa;
    cout<<"\nWpisz sciezke do szablonu: ";
    cin.clear();
    cin.sync();
    cin>>nazwa;
    this->szablon=nazwa.c_str();
}



//19.04 22:45
void Baza::analizuj_i_stworz_napisowe()
{
    string
            wiersz,
            reszta_wiersza,
            nazwa_podpola;

    unsigned int
            ile_wierszy=0,
            ile=0,
            i=0;

    const string
            pole_liczbowe=" ->\"0\";",
            pole_napisowe=" ->\"napis\";",
            pole_logiczne=" ->\"?\";",
            pole_znakowe=" ->\"x\";";

    ifstream pWe (szablon);
    while(!pWe.good())
    {
        cout<<"\nNieprawdidlowa sciezka! Wpisz ja jeszcze raz!\n";
        Baza::nazwa_szablonu();
        pWe.open(szablon);
    }
    //sprawdza czy szablon jest dobry i istnieje
    //otwarty

    while (!pWe.eof())
    {
        getline(pWe,wiersz);
        for(unsigned int i=0; i<wiersz.size(); i++)
        {
            if(wiersz[i]==' ' || wiersz[i]=='\t')
            {
                ile++;
            }
            else if(wiersz[i]=='\n')
            {
                ile++;
            }
        }
        if(ile!=wiersz.size())
            ile_wierszy++;
    }
    //jeśli są różne, to znaczy, że jest to prawidłowy wiersz
    //sprawdzam ilość pustych linijek w szablonie

    pWe.close();
    pWe.open(szablon);

    //otwiera
    //liczę ilość konkretnych podpól

    for(unsigned int i=0;i<ile_wierszy;i++)
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

        //jeśli nie wejdzie żaden z "else if-ów" to:

        else
        {
            cout<<"Blad w zapisie. Niezgodnosc z szablonem. Linijka numer: "<<i+1<<". Popraw szablon.";
            if(Pomoc())
            {
                cout<<"\nKazda jedna linijka tekstu znajdujaca sie w szablonie powinna byc postaci:\n\"nazwa podpola\" < znak bialy + \" ->\" > \"znak specjalny\";<znak bialy>\nZnaki specjalne:\n\"napis\" -> typ napisowy\n\"0\" -> typ liczbowy\n\"x\" -> typ znakowy\n\"?\" -> typ logiczny\n";
            }
            cout<<"\nWymuszenie zamkniecia programu!";
            EXIT_FAILURE;
        }
        //WYCHODZI

        if(nazwa_podpola.size()==1)
        {
            cout<<"Blad w nazwie podpola. Linijka numer: "<<i+1<<". Popraw szablon.";
            if(Pomoc())
            {
                cout<<"\nKazda jedna linijka tekstu znajdujaca sie w szablonie powinna byc postaci:\n\"nazwa podpola\" < znak bialy + \" ->\" > \"znak specjalny\";<znak bialy>\nZnaki specjalne:\n\"napis\" -> typ napisowy\n\"0\" -> typ liczbowy\n\"x\" -> typ znakowy\n\"?\" -> typ logiczny\n";
            }
            cout<<"\nWymuszenie zamkniecia programu!";
            EXIT_FAILURE;
        }
        //WYCHODZI
    }
    pWe.close();

    //zamknięty
    //jeśli wszystkie podpola zostały właściwie policzone to przechodzimy dalej:

    this->suma = ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych + ilosc_logicznych;

    if(ile_wierszy != suma)
    {
        cout<<"Cos jest nie tak z iloscia podpol w szablonie ( ilosc wierszy != ilosc podpol)."<<endl;
        EXIT_FAILURE;
    }
    this->glowa->str=new string [suma];

    //zaczynam ustawiać w kolejności: napisy, liczby, znaki, logi:

    //

    pWe.open(szablon);
    while(!pWe.eof())
    {
        pWe>>nazwa_podpola;
        //zbieram nazwę podpola
        getline(pWe,reszta_wiersza);
        //zbieram resztę wiersza
        if(reszta_wiersza==pole_napisowe)
        {
             this->glowa->str[i]=nazwa_podpola;
             i++;
        }
    }
    i=0;
    pWe.close();

    //napisowe

    pWe.open(szablon);
    while(!pWe.eof())
    {
        pWe>>nazwa_podpola;
        getline(pWe,reszta_wiersza);
        if(reszta_wiersza==pole_liczbowe)
        {
             this->glowa->str[i+ilosc_napisowych]=nazwa_podpola;
             i++;
        }
    }
    i=0;
    pWe.close();

    //liczbowe

    pWe.open(szablon);
    while(!pWe.eof())
    {
        pWe>>nazwa_podpola;
        getline(pWe,reszta_wiersza);
        if(reszta_wiersza==pole_znakowe)
        {
             this->glowa->str[i+ilosc_napisowych+ilosc_liczbowych]=nazwa_podpola;
             i++;
        }
    }
    i=0;
    pWe.close();//znakowe

    pWe.open(szablon);
    while(!pWe.eof())
    {
        pWe>>nazwa_podpola;
        getline(pWe,reszta_wiersza);
        if(reszta_wiersza==pole_logiczne)
        {
            this->glowa->str[i+ilosc_napisowych+ilosc_liczbowych+ ilosc_znakowych]=nazwa_podpola;
            i++;
        }
    }
    i=0;
    pWe.close();//logiczne

return;
}



void Baza::staty()
{
    cout<<ilosc_napisowych<<endl<<ilosc_liczbowych<<endl<<ilosc_znakowych<<endl<<ilosc_logicznych<<endl;
}



//19.04 23:40
void Baza::stworz_i_dodaj()
{
    cout<<"\nDodaj pole. Wpisz dane do kolejnych miejsc podpol:\n";
    Pole *nowy=new Pole;

    for(unsigned int i=0;i<suma;i++)
    {
        cout<<setw(szerokosc_podpola)<<right<<pierwotna->str[i];
    }

    nowy->str=new string [ilosc_napisowych];
    nowy->num=new int [ilosc_liczbowych];
    nowy->ch=new char [ilosc_znakowych];
    nowy->log=new bool [ilosc_logicznych];
    nowy->ilosc_wyszukan=new int;

    for(unsigned int i=0;i<ilosc_napisowych;i++)
    {
        cin.clear();
        cin.sync();
        cin>>nowy->str[i];
    }
    for(unsigned int i=0;i<ilosc_liczbowych;i++)
    {
        cin.clear();
        cin.sync();
        cin>>nowy->num[i];
    }
    for(unsigned int i=0;i<ilosc_znakowych;i++)
    {
        cin.clear();
        cin.sync();
        cin>>nowy->ch[i];
    }
    for(unsigned int i=0;i<ilosc_logicznych;i++)
    {
        cin.clear();
        cin.sync();
        cin>>nowy->log[i];
    }

    nowy->ilosc_wyszukan[0]=1;

    //czy można tak wyświetlać wpisywane nazwy, aby były obok siebie?

    nowy->next=glowa;
    this->glowa=nowy;

return;
}



//20.04 00:12
void Baza::zapis()
{
    nazwa_p_zapisu();
    ofstream pWy (plik_zapisu.c_str());
    Pole *ogon = glowa;

    pWy<<ilosc_napisowych<<"\t"<<ilosc_liczbowych<<"\t"<<ilosc_znakowych<<"\t"<<ilosc_logicznych<<"\n";

       while(glowa->next!=nullptr) //dochodzi do pola opisowego
       {
           for(unsigned int i=0;i<ilosc_napisowych;i++)
           {
               pWy<<glowa->str[i]<<endl;
           }
           for(unsigned int i=0;i<ilosc_liczbowych;i++)
           {
               pWy<<glowa->num[i]<<endl;
           }
           for(unsigned int i=0;i<ilosc_znakowych;i++)
           {
               pWy<<glowa->ch[i]<<endl;
           }
           for(unsigned int i=0;i<ilosc_logicznych;i++)
           {
               pWy<<glowa->log[i]<<endl;
           }
           this->glowa=glowa->next;
       }
       for (unsigned int i=0; i<suma; i++) //samo pole opisowe
       {
           pWy<<glowa->str[i]<<endl;
       }
       pWy.close();

       glowa = ogon;

       Pole *stary;

       cout<<"\nCzyszczenie pamieci. Zapis listy...";
       //dochodzimy do opisowego
       while(glowa->next!=nullptr)
       {
           stary = glowa;
           delete []glowa->str;
           delete []glowa->num;
           delete []glowa->ch;
           delete []glowa->log;
           delete glowa->ilosc_wyszukan;

           this->glowa=glowa->next;
           delete stary;
       }

       delete []glowa->str;
       cout<<"\nLista zapisana.";
       return;
}



//20.04 00:30
void Baza::odczyt()
{
    int
            k=0;
    string
            wiersz;

    ifstream pWe (plik_odczytu);

    while(!pWe.good())
    {
        cout<<"\nBrak pliku z baza! Wpisz sciezke jeszcze raz!";
        Baza::nazwa_plik_odczytu();
        pWe.open(plik_odczytu);
    }
    while(!pWe.eof())
    {
        getline(pWe,wiersz);
        k++;
    }
    pWe.close();

    //'k' liczy wiersze

    pWe.open(plik_odczytu);

    pWe>>this->ilosc_napisowych>>this->ilosc_liczbowych>>this->ilosc_znakowych>>this->ilosc_logicznych;

    this->suma=ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych + ilosc_logicznych;

    pWe.close();

    unsigned int ile_pol = ((k-1)/suma);
    //razem z opisowym

    Pole *adres= new Pole [ile_pol];
    //+1 opisowe
    pWe.open(plik_odczytu);
    for(unsigned int i=0;i<4;i++)
    {
        pWe>>wiersz;
    }
    //tworzy po kolei pola i podpola
    for(unsigned int j=0;j<ile_pol-1;j++)
    {
        adres[j].str=new string [ilosc_napisowych];
        adres[j].num=new int [ilosc_napisowych];
        adres[j].ch=new char [ilosc_napisowych];
        adres[j].log=new bool [ilosc_napisowych];
        adres[j].next=new Pole;

        adres[j].ilosc_wyszukan=new int;
        adres[j].ilosc_wyszukan[0]=0;

        for(unsigned int i=0;i<ilosc_napisowych;i++)
        {
            pWe>>adres[j].str[i];
        }
        for(unsigned int i=0;i<ilosc_liczbowych;i++)
        {
            pWe>>adres[j].num[i];
         }
        for(unsigned int i=0;i<ilosc_znakowych;i++)
        {
            pWe>>adres[j].ch[i];
        }
        for(unsigned int i=0;i<ilosc_logicznych;i++)
        {
            pWe>>adres[j].log[i];
        }
    }
    //tworzenie opisowego
    adres[ile_pol-1].str=new string [suma];

    for(unsigned int i=0;i<suma;i++)
    {
        pWe>>adres[ile_pol-1].str[i];
    }
    //zbieram opisowe
    pWe.close();

    for(unsigned int i=ile_pol-1;i>0;i--)
    {
       adres[i-1].next=&adres[i];
    }
    this->pierwotna=&adres[ile_pol-1];
    //^opisowe
    this->glowa=&adres[0];
    this->pierwotna->next=nullptr;
    return;
}



//20.04 00:12
int Baza::szerokosc()
{
    Pole
            *ogon=glowa;

    string
            rzutowanie = to_string(glowa->num[0]);

    unsigned int
            najdluzszy_wyraz = (glowa->str[0]).size(),
            najdluzsza_liczba = 0;

    //głowa dochodzi do pola napisowego, ale szukamy największej wartości wśród wszystkich podpól wszystkich pól,
    //więc druga funkcja niżej przeszukuje opisowe

    while(glowa->next!=nullptr)
    {
        for(unsigned int i=0;i<ilosc_napisowych;i++)
        {
            if((glowa->str[i]).size() > najdluzszy_wyraz)
            {
                najdluzszy_wyraz = (glowa->str[i]).size();
            }
        }
        for(unsigned int i=0;i<ilosc_liczbowych;i++)
        {
            rzutowanie = to_string(glowa->num[i]);
            if(rzutowanie.size() > najdluzsza_liczba)
            {
               najdluzsza_liczba = rzutowanie.size();
            }
        }
        this->glowa = glowa->next;
    }

    //jesteśmy na polu opisowym

    for(unsigned int i=0;i<suma;i++)
    {
        if((glowa->str[i]).size() > najdluzszy_wyraz)
        {
            najdluzszy_wyraz = (glowa->str[i]).size();
        }
    }
    this->glowa=ogon;
    this->szerokosc_podpola = (max(najdluzszy_wyraz,najdluzsza_liczba)) + 5;
    return szerokosc_podpola;
}
    //szukam najdłuższego z wyrazów/liczb

//09.05 19:30
void Baza::pokaz()
{
    Pole
            *ogon=glowa;
    unsigned int
            k=1;
    //wybór szerokości podpola ^
    //podpola są uszeregowane

    szerokosc();

    for(unsigned int i=0;i<suma;i++)
    {
        cout<<setw(szerokosc_podpola)<<right<<pierwotna->str[i];
    }
    cout<<endl;
    while(glowa->next!=nullptr)
    {
        cout<<k<<". ";
        for(unsigned int i=0;i<ilosc_napisowych;i++)
        {
            cout<<setw(szerokosc_podpola)<<right<<glowa->str[i];
        }
        for(unsigned int i=0;i<ilosc_liczbowych;i++)
        {
            cout<<setw(szerokosc_podpola)<<right<<glowa->num[i];
        }
        for(unsigned int i=0;i<ilosc_znakowych;i++)
        {
            cout<<setw(szerokosc_podpola)<<right<<glowa->ch[i];
        }
        for(unsigned int i=0;i<ilosc_logicznych;i++)
        {
            cout<<setw(szerokosc_podpola)<<right<<glowa->log[i];
        }
        cout<<endl;
        this->glowa=glowa->next;
        k++;
    }
    this->glowa=ogon;
    return;
}
//09.05 18:00
void Baza::szukaj()
{
    Pole
            *ogon = glowa,
            **pom;
    unsigned int
            numer = 0,
            numer_pola = 0,
            szukana_liczba=0,
            ile=0;
    char
            szukany_znak;
    string
            szukany_napis;
    bool
            szukany_bol;


    for(unsigned int i=0;i<suma;i++)
    {
        cout<<endl<<i+1<<". "<<pierwotna->str[i];
    }
    cout<<"\nWybierz obszar poszukiwan. Wprowadz liczbe od 1. do "<<suma<<".\n";
    cin.clear();
    cin.sync();
    //wybrał tag, po którym będzie szukał
    do
    {
        cin>>numer;
        if(numer > suma)
        {
            cout<<"\nPodany zly numer. Wpisz jeszcze raz!";
            break;
        }

        if(numer<=ilosc_napisowych)//wybrał napisy
        {
            cout<<"\nNapis";
            do
            {
                cout<<"\nDobrze. Teraz wpisz szukane wyrazenie: ";
                cin.clear();
                cin.sync();
                cin>>szukany_napis;

               // this->glowa=ogon;
                while(glowa->next!=nullptr)
                {
                    if(glowa->str[numer-1]==szukany_napis)
                    {
                        cout<<"\nLiczy!";
                        ile++;
                    }
                    this->glowa=glowa->next;
                    //ilość dobrych pól
                }
                cout<<"\nIle:"<<ile;

                if(ile==0)
                {
                    cout<<"\nBlad! Procedura szukania rozpoczeta od nowa!";
                    break;
                }
                pom = new Pole *[ile];

                ile=0;

                cout<<"\nStworzono pomocnicza tablice.";

                this->glowa=ogon;
                while(glowa->next!=nullptr)
                {
                    if(glowa->str[numer-1]==szukany_napis)
                    {
                        ile++;
                        cout<<ile;
                        cout<<endl;
                        pom[ile] = glowa;
                        //pom ma w sobie adres pola
                        //jeśli mamy jeden znaleziony wynik to pokazuje pierwotną
                        if(ile==1)
                        {
                            for(unsigned int i=0;i<suma;i++)
                            {
                                cout<<setw(szerokosc_podpola)<<right<<pierwotna->str[i];
                            }
                        }
                        //Pokazuje konkretne pole:
                        cout<<endl<<ile<<". ";
                        for(unsigned int i=0;i<ilosc_napisowych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->str[i];
                        }
                        for(unsigned int i=0;i<ilosc_liczbowych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->num[i];
                        }
                        for(unsigned int i=0;i<ilosc_znakowych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->ch[i];
                        }
                        for(unsigned int i=0;i<ilosc_logicznych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->log[i];
                        }
                        cout<<endl;
                   }
                   this->glowa=glowa->next;
               }
               //Wiemy ile jest identycznych danych i są wypisane

               cout<<"\nWybierz szukane pole sposrod wypisanych: ";
               this->glowa=ogon;
               do
               {
                   cin.clear();
                   cin.sync();
                   cin>>numer_pola;
               }
               while(numer_pola > ile || numer_pola <= 0);
               //wybrane pole -> teraz trzeba do konkretnego pola dodać punkcik wyszukiwania
               cout<<"\nPrzed dodaniem";
               *((pom[numer_pola - 1])->ilosc_wyszukan)+=1;
               cout<<"\nPo dodaniu";
               cout<<endl<<glowa->str[0]<<endl<<glowa->ilosc_wyszukan[0];
               delete []pom;
            }
            while(Ponow_probe());
        }







        else if(numer<=ilosc_napisowych + ilosc_liczbowych)//wybrał liczbę
        {
            do
            {
                cout<<"\nLiczba";
                cout<<"\nDobrze. Teraz wpisz szukane wyrazenie: ";
                cin.clear();
                cin.sync();
                cin>>szukana_liczba;

                this->glowa=ogon;
                while(glowa->next!=nullptr)
                {
                    if(glowa->num[ilosc_napisowych - numer - 1]==szukana_liczba)
                    {
                        ile++;
                    }
                    this->glowa=glowa->next;
                    //ilość dobrych pól
                }
                pom = new Pole *[ile];
                ile=0;
                this->glowa=ogon;
                while(glowa->next!=nullptr)
                {
                    if(glowa->num[ilosc_napisowych - numer - 1]==szukana_liczba)
                    {
                        ile++;
                        pom[ile] = glowa;
                        //jeśli mamy jeden znaleziony wynik to pokazuje pierwotną
                        if(ile==1)
                        {
                            for(unsigned int i=0;i<suma;i++)
                            {
                                cout<<setw(szerokosc_podpola)<<right<<pierwotna->str[i];
                            }
                        }
                        //Pokazuje konkretne pole:
                        cout<<endl<<ile<<". ";
                        for(unsigned int i=0;i<ilosc_napisowych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->str[i];
                        }
                        for(unsigned int i=0;i<ilosc_liczbowych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->num[i];
                        }
                        for(unsigned int i=0;i<ilosc_znakowych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->ch[i];
                        }
                        for(unsigned int i=0;i<ilosc_logicznych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->log[i];
                        }
                        cout<<endl;
                    }
                    this->glowa->next=glowa->next;
               }
               //Wiemy ile jest identycznych danych i są wypisane
               cout<<"\nWybierz szukane pole sposrod wypisanych: ";
               this->glowa=ogon;
               do
               {
                   cin.clear();
                   cin.sync();
                   cin>>numer_pola;
               }
               while(numer_pola > ile || numer_pola <= 0);
               //wybrane pole -> teraz trzeba do konkretnego pola dodać punkcik wyszukiwania

               *(pom[numer_pola])->ilosc_wyszukan+=1;
               delete []pom;
            }
            while(Ponow_probe());
        }







        else if(numer<=ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych)//wybrał znak
        {
            do
            {
                cout<<"\nZnak";
                cout<<"\nDobrze. Teraz wpisz szukane wyrazenie: ";
                cin.clear();
                cin.sync();
                cin>>szukany_znak;

                this->glowa=ogon;
                while(glowa->next!=nullptr)
                {
                    if(glowa->ch[ilosc_napisowych + ilosc_liczbowych - numer - 1]==szukana_liczba)
                    {
                        ile++;
                    }
                    this->glowa=glowa->next;
                    //ilość dobrych pól
                }
                pom = new Pole *[ile];
                ile=0;
                this->glowa=ogon;
                while(glowa->next!=nullptr)
                {
                    if(glowa->ch[ilosc_napisowych + ilosc_liczbowych - numer - 1]==szukana_liczba)
                    {
                        ile++;
                        pom[ile] = glowa;
                        //jeśli mamy jeden znaleziony wynik to pokazuje pierwotną
                        if(ile==1)
                        {
                            for(unsigned int i=0;i<suma;i++)
                            {
                                cout<<setw(szerokosc_podpola)<<right<<pierwotna->str[i];
                            }
                        }
                        //Pokazuje konkretne pole:
                        cout<<endl<<ile<<". ";
                        for(unsigned int i=0;i<ilosc_napisowych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->str[i];
                        }
                        for(unsigned int i=0;i<ilosc_liczbowych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->num[i];
                        }
                        for(unsigned int i=0;i<ilosc_znakowych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->ch[i];
                        }
                        for(unsigned int i=0;i<ilosc_logicznych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->log[i];
                        }
                        cout<<endl;
                    }
                    this->glowa->next=glowa->next;
               }
               //Wiemy ile jest identycznych danych i są wypisane
               cout<<"\nWybierz szukane pole sposrod wypisanych: ";
               this->glowa=ogon;
               do
               {
                   cin.clear();
                   cin.sync();
                   cin>>numer_pola;
               }
               while(numer_pola > ile || numer_pola <= 0);
               //wybrane pole -> teraz trzeba do konkretnego pola dodać punkcik wyszukiwania

               *(pom[numer_pola])->ilosc_wyszukan+=1;
               delete []pom;
            }
            while(Ponow_probe());
        }









        else if(numer<=ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych + ilosc_logicznych)//wybrał bool
        {
            do
            {
                cout<<"\nBool";
                cout<<"\nDobrze. Teraz wpisz szukane wyrazenie: ";
                cin.clear();
                cin.sync();
                cin>>szukany_bol;

                this->glowa=ogon;
                while(glowa->next!=nullptr)
                {
                    if(glowa->log[ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych - numer - 1]==szukany_bol)
                    {
                        ile++;
                    }
                    this->glowa=glowa->next;
                    //ilość dobrych pól
                }
                pom = new Pole *[ile];
                ile=0;
                this->glowa=ogon;
                while(glowa->next!=nullptr)
                {
                    if(glowa->log[ilosc_napisowych + ilosc_liczbowych + ilosc_znakowych - numer - 1]==szukany_bol)
                    {
                        ile++;
                        pom[ile] = glowa;
                        //jeśli mamy jeden znaleziony wynik to pokazuje pierwotną
                        if(ile==1)
                        {
                            for(unsigned int i=0;i<suma;i++)
                            {
                                cout<<setw(szerokosc_podpola)<<right<<pierwotna->str[i];
                            }
                        }
                        //Pokazuje konkretne pole:
                        cout<<endl<<ile<<". ";
                        for(unsigned int i=0;i<ilosc_napisowych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->str[i];
                        }
                        for(unsigned int i=0;i<ilosc_liczbowych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->num[i];
                        }
                        for(unsigned int i=0;i<ilosc_znakowych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->ch[i];
                        }
                        for(unsigned int i=0;i<ilosc_logicznych;i++)
                        {
                            cout<<setw(szerokosc_podpola)<<right<<glowa->log[i];
                        }
                        cout<<endl;
                    }
                    this->glowa->next=glowa->next;
                }
                //Wiemy ile jest identycznych danych i są wypisane
                cout<<"\nWybierz szukane pole sposrod wypisanych: ";
                this->glowa=ogon;
                do
                {
                    cin.clear();
                    cin.sync();
                    cin>>numer_pola;
                }
                while(numer_pola > ile || numer_pola <= 0);
                //wybrane pole -> teraz trzeba do konkretnego pola dodać punkcik wyszukiwania

                *(pom[numer_pola])->ilosc_wyszukan+=1;
                delete []pom;
            }
            while(Ponow_probe());




    while(numer<=0 || numer > suma);

}

        else
        {
            cout<<"\nNumer jest niepoprawny. Wprowadz go jeszcze raz: ";
            break;
        }
    }
    while(numer > suma);
    return;
}
























