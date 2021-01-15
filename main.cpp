#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <stdio.h>

using namespace std;

int ile;
clock_t start,stop;
double czas;

void sortowanie_grzebieniowe (int*tab, int n)
{
    int roz = n, zamiana = 0;   //roz=rozpietosc
    bool spr = true; //spr-zmienna sprawdzajaca czy  w danej iteracji zosta³y zamienione miejscami jakieœ dwa elementy
    while (roz > 1 || spr)
    {
        roz = roz*10/13;
        if(roz==0)
            roz=1;
        spr = false;
        for (int i=0; i + roz< n; ++i)
        {
            if (tab[i + roz] < tab[i])
            {
                zamiana = tab[i];
                tab[i] = tab[i + roz];
                tab[i + roz] = zamiana ;
                spr = true;
            }
        }
    }
}

void sortowanie_przez_wstawianie(int *tab, int n)
{
    int el, j;
    for (int i=2; i<n ; i++)
    {
        el=tab[i]; //wstawienie elementu w odpowiednie miejsce
        j=i-1;
        while ((j>0) && (el<tab[j]))//przesuwanie elementów wiêkszych od el
        {
            tab[j+1]=tab[j];
            j--;
        }
        tab[j+1]=el;//wstawienie el w odpowiednie miejsce
    }
}

int main()
{
    fstream plik, wyniki;
    plik.open("tablica.txt",ios::in); // Otwarcie/utworzenie pliku, z którego pobierana bedzie tablica
    wyniki.open("wyniki.txt",ios::out); // Otwarcie/utworzenie pliku, do którego zapisywany bêdzie wynik


    cout<<"Program sortujacy grzbieniowo oraz przez wstawianie, porownujacy dzialanie obu metod"<<endl;

    int x;
    cout<<"Jesli chcesz posortowac dowolna tablice obiema metodami wpisz 1 "<<endl;
    cout<<"Jesli chcesz porownac czas dzialania obu metod wpisz 2 "<<endl;
    cout<<"Jesli chcesz odczytac tablice z pliku wpisz 3"<<endl;
    cin >> x;

    while((x!=1)&&(x!=2)&&(x!=3))//jezeli x nie jest rowny 1,2 lub 3 postepuj zgodnie z petla
    {
        cout<<"Wprowadz liczbe 1, 2 lub 3! " <<endl;
        cin>>x;
    }

    if(x==1)
    {
        cout << "Program sortujacy grzebieniowo i przez wstawianie" << endl<<endl;

        cout<<"Ile losowych liczb w tablicy: ";
        cin>>ile;

        int *tablica; //dynamiczna alokacja tablicy
        tablica=new int [ile];

        int *tablica2;
        tablica2=new int [ile];

        srand(time(NULL));    //inicjowanie generatora

        for(int i=0; i<ile; i++)     //wczytywanie losowych liczb do tablicy
        {
            tablica[i] = rand()%100000+1;
        }
        for(int i=0; i<ile; i++) //przepisanie tablicy do tablicy2
        {
            tablica2[i]=tablica[i];
        }

        cout<<"Przed posortowaniem: "<<endl;
        wyniki<<"Przed posortowaniem: "<<endl;
        for(int i=0; i<ile; i++)
        {
            cout<<tablica[i]<<" ";
            wyniki<<tablica[i]<<" ";
        }

        cout<<endl<<endl<<"Sortuje grzebieniowo."<<endl;
        sortowanie_grzebieniowe (tablica,ile);

        cout<<"Po posortowaniu grzebieniowym: "<<endl;
        wyniki <<"\n"<< "Po posortowaniu grzebieniowym: "<<endl; //wczytywanie tablicy do pliku
        for(int i=0; i<ile; i++)
        {
            cout<<tablica[i]<<" ";
            wyniki<< tablica[i] <<" "; //wczytywanie tablicy do pliku
        }

        cout<<endl<<endl<<"Sortuje przez wstawianie."<<endl;
        sortowanie_przez_wstawianie (tablica2,ile);

        cout<<"Po posortowaniu przez wstawianie: "<<endl;
        wyniki <<"\n"<< "Po posortowaniu przez wstawianie: "<<endl;
        for(int i=0; i<ile; i++)
        {
            cout<<tablica[i]<<" ";
            wyniki<< tablica[i] <<" ";
        }

        cout<<endl;
        delete [] tablica;
        delete [] tablica2;
    }

    if (x==2)
    {
        int liczba_testow=20;

        for(int i=0; i<liczba_testow; i++)
        {
            cout<<endl<<"Ile losowych liczb w tablicy: ";
            cin>>ile;

            int *tablica; //dynamiczna alokacja tablicy
            tablica=new int [ile];
            int *tablica2;
            tablica2=new int [ile];

            srand(time(NULL));    //inicjowanie generatora

            for(int i=0; i<ile; i++)     //wczytywanie losowych liczb do tablicy
            {
                tablica[i] = rand()%100000+1;
            }
            for(int i=0; i<ile; i++) //przepisanie tablicy do tablicy2
            {
                tablica2[i]=tablica[i];
            }

            //testowe wypisanie losowo wygenerowanej tablicy
            /*    cout<<"Przed posortowaniem: "<<endl;
                 wyniki<<"Przed posortowaniem: "<<endl;
                for(int i=0; i<ile; i++)
                 {
                     cout<<tablica[i]<<" ";   //mozliwosc zmiany na tablica2[i] w celu sprawdzenia poprawnoœci sortowania metoda przez wstawianie
                     wyniki<<tablica[i]<<" ";

                 }
            /*testy algorytmu sortowania grzebieniowego*/
            cout<<endl<<endl<<"Sortuje grzebieniowo."<<endl;
            start = clock();
            sortowanie_grzebieniowe (tablica,ile);
            stop = clock();
            czas = (double)(stop-start) / CLOCKS_PER_SEC;
            cout<<"Ilosc danych w tablicy: "<<ile<<endl;
            cout<<"Czas sortowania grzebieniowego: "<<czas<<" s"<<endl;
            wyniki<<"\n"<<endl<<"Czas sortowania grzebieniowego: "<<czas<<" s"<<endl;

            /*testy algorytmu sortowania przez wstawianie*/
            cout<<endl<<endl<<"Sortuje przez wstawianie."<<endl;
            start = clock();
            sortowanie_przez_wstawianie (tablica2,ile);
            stop = clock();
            czas = (double)(stop-start) / CLOCKS_PER_SEC;
            cout<<"Ilosc danych w tablicy: "<<ile<<endl;
            cout<<"Czas sortowania przez wstawianie: "<<czas<<" s"<<endl;
            wyniki<<endl<<"Czas sortowania przez wstawianie: "<<czas<<" s"<<endl;

            //testowe wypisanie posortowanej, losowo wygenerowanej tablicy
            /*   cout<<"Po posortowaniu: "<<endl;
               wyniki<<"\n"<<"Po posortowaniu: "<<endl;
                   for(int i=0; i<ile; i++)
                   {
                       cout<<tablica[i]<<" ";   //mozliwosc zmiany na tablica2[i] w celu sprawdzenia poprawnoœci sortowania metoda przez wstawianie
                       wyniki<<tablica[i]<<" ";
                   }
            */
        }
    }

    if(x==3)
    {
        int ile=100;  //liczba elementow w pliku
        int tablica[ile];  //zadeklarowanie dwoch tablic
        int tablica2[ile];

        for(int i=0; i<ile; i++) //petla wpisujaca elementy z pliku do tablicy
        {
            plik>>tablica[i];
        }
        /*      cout<<"Przed posortowaniem: "<<endl;
              wyniki<<"Przed posortowaniem: "<<endl;
              for (int i=0; i < ile; i++)
              {
                  cout << tablica[i] << " ";
                  wyniki<<tablica[i]<<" ";
              }
        */
        cout<<endl<<endl<<"Sortuje grzebieniowo."<<endl;
        start = clock();
        sortowanie_grzebieniowe (tablica,ile);
        stop = clock();
        czas = (double)(stop-start) / CLOCKS_PER_SEC;
        cout<<"Ilosc danych w tablicy: "<<ile<<endl;
        cout<<"Czas sortowania grzebieniowego: "<<czas<<" s"<<endl;
        wyniki<<"\n"<<endl<<"Czas sortowania grzebieniowego: "<<czas<<" s"<<endl;

        /*testy algorytmu sortowania przez wstawianie*/
        cout<<endl<<endl<<"Sortuje przez wstawianie."<<endl;
        start = clock();
        sortowanie_przez_wstawianie (tablica2,ile);
        stop = clock();
        czas = (double)(stop-start) / CLOCKS_PER_SEC;
        cout<<"Ilosc danych w tablicy: "<<ile<<endl;
        cout<<"Czas sortowania przez wstawianie: "<<czas<<" s"<<endl;
        wyniki<<endl<<"Czas sortowania przez wstawianie: "<<czas<<" s"<<endl<<endl;

        //zapisanie do pliku
        /*    cout<<"Po posortowaniu: "<<endl;
            wyniki<<"\n"<<"Po posortowaniu: "<<endl;
            for (int i=0; i < ile; i++)
            {
                cout<<tablica[i]<<" ";
                wyniki<< tablica[i] << " ";
            }
        */
        plik.close();
        wyniki.close();
    }
    return 0;
}
