// Kolory.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <string>  
#include <fstream>
#include <vector>
#include <cassert>
#include <clocale>

using namespace std;

struct Gracz {
    string imie;
    int kasa = 0;
    int portfel = 0; //kasa z wygranych rund
};

struct Gracz gracze[3];

int kolejka = 0;

int Kolo[] = { -1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000 };
// -1 bankrut
// 0 strata kolejki


void textPlayers()
{
    int i;
    std::cout << "\n";
    for (i = 0; i < 3; i++) {
        if (i == kolejka) {
            cout << "\033[1;34m";
        }
        cout << gracze[i].imie << "\t" << gracze[i].kasa << "\n";
        cout << "\033[0m";

    }
    cout << "\n";
}

int jestSamogloska(char c)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y')
        return 1;
    else
        return 0;

}

char WczytajZnak()
{
    string letter;
    cin >> letter;
    
    while (letter.length() != 1)
    {
        cout << endl << "Type a single letter and press <enter>: ";
        cin >> letter;
    }

    for (auto& c : letter)  // & zapamietuje modyfikacje w petli & - referencja
        c = toupper(c);

    return letter[0];

}

char WczytajWybor()
{
    char wybor;
    wybor = WczytajZnak();

    while (wybor != '1' && wybor != '2')
    {
        cout << endl << "Wybierz [1-2]: ";
        cin >> wybor;
    }

    return wybor;

}


int main()
{
    int i;

    string haslo; // = "wielka antarktyda";
    string proba;
    char literka;
    int rozmiar;
    int maska[100];
    int suma = 0;
    int zgadl = 0;
    int sa_spolgloski = 0;
    int kwota = 0;
    char wybor;
    srand(time(NULL));
    string rezultat;
    vector<string> hasla;

    ifstream strum;
    strum.open("dane.txt");

    setlocale(LC_CTYPE, "Polish");

    while (!strum.eof())
    {
        string s;
        //strum >> s;
        getline(strum, s);
        //cout << s << endl;
        hasla.push_back(s);

    }

    strum.close();


    for(string item : hasla)
        cout << item << endl;

    

    cout << endl << endl;
    
    assert(hasla.size() > 0);
    int j = rand() % hasla.size(); // losujemy j-te haslo z przedzialu 0 ... size - 1
    //cout << hasla[j];

    haslo = hasla[j];
    rozmiar = haslo.size();

    gracze[0].imie = "Bryanusz";
    gracze[1].imie = "Jessica ";
    gracze[2].imie = "Nepomucen";

    for (i = 0; i < rozmiar; i++)
    {
        if (haslo[i] == ' ')
            maska[i] = 0;
        else
            maska[i] = 1;
    }




    do
    {
        cout << "\033[47m" << "\033[31m";
        for (i = 0; i < rozmiar; i++)
        {

            if (maska[i] == 1)
                cout << ".";
            else
                cout << haslo[i];
        }

        cout << "\033[0m";
        cout << endl;


        sa_spolgloski = 0;
        kwota = 0;

        for(i=0; i<rozmiar; i++)
            if ((!jestSamogloska(haslo[i])) && (maska[i]))
            {
                sa_spolgloski = 1;
                break;
            }

        if (sa_spolgloski)
            cout << " -- Spolgloski sa --" << endl;
         

        textPlayers();

        cout << "1. zgaduj haslo" << endl;
        cout << "2. krecenie kolem" << endl;

        // TODO tylko 1 i 2, nie mozna wprowadzac liter

        wybor = WczytajWybor();

        if (wybor == '1')
        {
            cout << "Podaj haslo" << endl;
            getline(cin >> ws, proba);  // wczytanie z klawiatury string z uwzgl. whitespa
            for (auto& c : proba)  // & zapamietuje modyfikacje w petli & - referencja
                c = toupper(c);
            if (haslo == proba) {
                cout << endl << " !!!!!!!!!! =======   WYGRANA ========== !!!!!!!!!!!!!" << endl;
                gracze[kolejka].portfel += gracze[kolejka].kasa;
                break;
            }
            else
            {
                kolejka = (kolejka + 1) % 3;
                suma = 1;
                cout << endl << " !!!!!!!!!! =======   ZLE ========== !!!!!!!!!!!!!" << endl;
                cout << endl << "=================================================" << endl;
                continue;


            }



        }


        rezultat = "";
        i = rand() % 15;
        if (Kolo[i] == 0)
            rezultat = "Strata kolejki";
        if (Kolo[i] == -1)
            rezultat = "Bankrut";
        if (rezultat != "")
           cout << "\033[1;31m" << rezultat << "\033[0m" << endl;
        else
        {
            cout << "\033[1;34m" << Kolo[i] << "\033[0m" << endl;
            kwota = Kolo[i];
        }

        // Strata kolejki i bankrut
        if ((Kolo[i] == 0) || (Kolo[i] == -1))
        {
            if (Kolo[i] == -1) // bankrut
                gracze[kolejka].kasa = 0;
            
            kolejka = (kolejka + 1) % 3;
            suma = 1;
            cout << endl << "=================================================" << endl;

            // TODO
            // sleep for
            // kupowanie samoglosek

            continue;

        }





        cout << gracze[kolejka].imie <<  ": Podaj litere" << endl;



        literka = WczytajZnak();
 

        zgadl = 0;

        if (jestSamogloska(literka))
            cout << "samogloska";
        else
            cout << "spolgloska";
        cout << endl;

        for (i = 0; i < rozmiar; i++)
        {
            if ((haslo[i] == literka) && (maska[i]==1)) {
                maska[i] = 0;
                zgadl++;
            }
        }

        if (zgadl)
        {
            cout << "OK";
            gracze[kolejka].kasa += kwota * zgadl;

            cout << endl << gracze[kolejka].imie << "\033[1;32m " << gracze[kolejka].kasa << "\033[0m";


        }
        else {
            cout << "Zle!";
            // strata kolejki
            kolejka = (kolejka + 1) % 3;
            cout << endl << "=================================================" << endl;
            suma = 1;
            continue;
        }

        


        cout << endl;



        suma = 0;

        for (i = 0; i < rozmiar; i++)
        {
            suma += maska[i];
        }

       

    } while (suma);
    cout << "BRAWO!";
    exit(0);

}