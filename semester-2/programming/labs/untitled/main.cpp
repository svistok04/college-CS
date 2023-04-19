#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>
#include <locale.h>
using namespace std;

// klasa reprezentująca gracza
class Gracz {
    // pola klasy
    string imie; // nazwa gracza
    int kasa; // suma pieniędzy zgromadzonych przez gracza
    int portfel; // suma pieniędzy wygranych przez gracza
    bool kol; // flaga oznaczająca, czy gracz ma kolej

public:
    // konstruktor klasy
    Gracz(string n) {
        imie = n;
        kasa = 0;
        portfel = 0;
        kol = false;
    }

    // metody klasy
    string getImie() { // zwraca nazwę gracza
        return imie;
    }

    int getKasa() { // zwraca sumę pieniędzy zgromadzonych przez gracza
        return kasa;
    }

    int getPortfel() { // zwraca sumę pieniędzy wygranych przez gracza
        return portfel;
    }

    bool getKol() { // zwraca flagę oznaczającą, czy gracz ma kolej
        return kol;
    }

    void setKasa(int k) { // ustawia sumę pieniędzy zgromadzonych przez gracza
        kasa = k;
    }

    void setPortfel(int p) { // ustawia sumę pieniędzy wygranych przez gracza
        portfel = p;
    }

    void setKol(bool k) { // ustawia flagę oznaczającą, czy gracz ma kolej
        kol = k;
    }

    void txP() { // wypisuje nazwę i sumę pieniędzy zgromadzonych przez gracza
        if (kol) {
            cout << "\033[1;34m";
        }
        cout << imie << "\t" << kasa << "\n";
        cout << "\033[0m";
    }
};

// klasa reprezentująca koło fortuny
class Kolo {
protected: // pola chronione, dostępne dla klas pochodnych
    int wartosc; // wartość koła

public:
    // konstruktor klasy
    Kolo(int w) {
        wartosc = w;
    }

    // metody klasy
    int getWartosc() { // zwraca wartość koła
        return wartosc;
    }

    virtual string getRest() { // zwraca dodatkową informację o kole (może być nadpisana w klasach pochodnych)
        return "";
    }
};

// klasa dziedzicząca po klasie Kolo, reprezentująca koło specjalne
class KoloSpecjalne : public Kolo {
private: // pole prywatne, dostępne tylko dla tej klasy
    string rest; // dodatkowa informacja o kole

public:
    // konstruktor klasy
    KoloSpecjalne(int w, string r) : Kolo(w) {
        rest = r;
    }

    // metody klasy
    string getRest() override { // zwraca dodatkową informację o kole (nadpisuje metodę z klasy bazowej)
        return rest;
    }
};

// funkcja sprawdzająca, czy podany znak jest samogłoską
int jeS(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y')
        return 1;
    else
        return 0;
}

// funkcja wczytująca pojedynczy znak z klawiatury i zamieniająca go na wielką literę
char wcZ() {
    string lett;
    cin >> lett;
    while (lett.length() != 1) {
        cout << endl << "Type a single lett and press <enter>: ";
        cin >> lett;
    }
    for (auto& c : lett) c = toupper(c);
    return lett[0];
}

// funkcja wczytująca wybór gracza (1 lub 2) z klawiatury
char wcW() {
    char wybor;
    wybor = wcZ();
    while (wybor != '1' && wybor != '2') {
        cout << endl << "Wybierz [1-2]: ";
        cin >> wybor;
    }
    return wybor;
}

int main() {
    int i; // zmienna pomocnicza do pętli
    string haslo; // hasło do odgadnięcia
    string proba; // próba odgadnięcia hasła
    char litt; // litera podana przez gracza
    int n; // długość hasła
    int maska[100]; // tablica oznaczająca, które litery hasła zostały odkryte
    int suma = 0; // suma odkrytych liter hasła
    int zgadl = 0; // liczba zgadniętych liter w jednym ruchu
    int sa_s = 0; // flaga oznaczająca, czy w haśle są spółgłoski
    int kwota = 0; // kwota wylosowana z koła
    char wybor; // wybór gracza (1 lub 2)
    srand(time(NULL)); // inicjalizacja generatora liczb losowych
    string rest; // dodatkowa informacja o kole
    vector<string> hasla; // wektor przechowujący hasła wczytane z pliku
    int j; // indeks losowego hasła z wektora
    ifstream strum; // strumień do odczytu pliku
    strum.open("dane.txt"); // otwarcie pliku z hasłami
    setlocale(LC_CTYPE, "Polish"); // ustawienie polskiego kodowania znaków

    while (!strum.eof()) { // wczytywanie haseł z pliku do wektora
        string s;
        getline(strum, s);
        hasla.push_back(s);
    }

    strum.close(); // zamknięcie pliku

    for (string item: hasla) cout << item << endl; // wypisanie haseł na ekranie

    cout << endl << endl;

    assert(hasla.size() > 0); // sprawdzenie, czy wektor haseł nie jest pusty

    j = rand() % hasla.size(); // losowanie indeksu hasła z wektora

    haslo = hasla[j]; // przypisanie losowego hasła do zmiennej

    n = haslo.size(); // obliczenie długości hasła


// utworzenie trzech obiektów typu Gracz i przypisanie im nazw
    Gracz gracze[3] = {Gracz("Bryanusz"), Gracz("Jessica "), Gracz("Nepomucen")};

// ustawienie flagi kol na true dla pierwszego gracza
    gracze[0].setKol(true);

// utworzenie tablicy obiektów typu Kolo i KoloSpecjalne i przypisanie im wartości i informacji dodatkowych
    Kolo *kola[16] = {new KoloSpecjalne(-1, "Bankrut"), new Kolo(0), new Kolo(100), new Kolo(200), new Kolo(100),
                      new Kolo(200), new Kolo(100), new Kolo(200), new Kolo(500), new Kolo(500), new Kolo(1000),
                      new Kolo(1000), new Kolo(1500), new Kolo(2000), new Kolo(3000), new Kolo(5000)};

// inicjalizacja tablicy maska, która oznacza, które litery hasła zostały odkryte
    for (i = 0; i < n; i++) {
        if (haslo[i] == ' ') maska[i] = 0;
        else maska[i] = 1;
    }

    do { // główna pętla gry
        cout << "\033[47m" << "\033[31m"; // ustawienie koloru tekstu na czerwony na białym tle

        // wypisanie hasła z kropkami zamiast nieodkrytych liter
        for (i = 0; i < n; i++) {
            if (maska[i] == 1) cout << ".";
            else cout << haslo[i];
        }

        cout << "\033[0m"; // przywrócenie domyślnego koloru tekstu
        cout << endl;

        sa_s = 0; // zerowanie flagi oznaczającej, czy w haśle są spółgłoski

        kwota = 0; // zerowanie kwoty wylosowanej z koła

        // sprawdzenie, czy w haśle są spółgłoski
        for (i = 0; i < n; i++)
            if ((!jeS(haslo[i])) && (maska[i])) {
                sa_s = 1;
                break;
            }

        if (sa_s) cout << " -- Spolgloski sa --" << endl; // jeśli są spółgłoski, wypisanie informacji

        // wypisanie nazw i sum pieniędzy zgromadzonych przez graczy
        for (i = 0; i < 3; i++) {
            gracze[i].txP();
        }

        cout << "\n";

        // wypisanie opcji do wyboru przez gracza
        cout << "1. zgaduj haslo" << endl;
        cout << "2. krecenie kolem" << endl;

        wybor = wcW(); // wczytanie wyboru gracza

        if (wybor == '1') { // jeśli gracz wybrał zgadywanie hasła
            cout << "Podaj haslo" << endl;
            getline(cin >> ws, proba); // wczytanie próby odgadnięcia hasła
            for (auto &c: proba) c = toupper(c); // zamiana próby na wielkie litery

            if (haslo == proba) { // jeśli próba jest zgodna z hasłem
                cout << endl << " !!!!!!!!!! ======= WYGRANA ========== !!!!!!!!!!!!!"
                     << endl; // wypisanie informacji o wygranej
                for (i = 0; i < 3; i++) { // znalezienie gracza, który ma kolej
                    if (gracze[i].getKol()) {
                        gracze[i].setPortfel(gracze[i].getPortfel() +
                                             gracze[i].getKasa()); // dodanie sumy pieniędzy zgromadzonych przez gracza do jego portfela
                        break;
                    }
                }
                break; // zakończenie gry
            } else { // jeśli próba nie jest zgodna z hasłem
                for (i = 0; i < 3; i++) { // znalezienie gracza, który ma kolej
                    if (gracze[i].getKol()) {
                        gracze[i].setKol(false); // ustawienie flagi kol na false dla tego gracza
                        gracze[(i + 1) % 3].setKol(true); // ustawienie flagi kol na true dla następnego gracza
                        break;
                    }
                }
                suma = 1; // ustawienie sumy na wartość niezerową, aby kontynuować pętlę gry
                cout << endl << " !!!!!!!!!! ======= ZLE ========== !!!!!!!!!!!!!"
                     << endl; // wypisanie informacji o błędzie
                cout << endl << "=================================================" << endl;
                continue; // przejście do następnej iteracji pętli gry
            }
        }

        rest = ""; // zerowanie dodatkowej informacji o kole

        i = rand() % 16; // losowanie indeksu koła z tablicy

        rest = kola[i]->getRest(); // pobranie dodatkowej informacji o kole

        if (rest != "")
            cout << "\033[1;31m" << rest << "\033[0m"
                 << endl; // jeśli koło ma dodatkową informację, wypisanie jej na czerwono
        else {
            cout << "\033[1;34m" << kola[i]->getWartosc() << "\033[0m"
                 << endl; // jeśli koło nie ma dodatkowej informacji, wypisanie jego wartości na niebiesko
            kwota = kola[i]->getWartosc(); // przypisanie wartości koła do zmiennej kwota
        }

        if ((kola[i]->getWartosc() == 0) || (kola[i]->getWartosc() == -1)) { // jeśli koło ma wartość 0 lub -1
            for (i = 0; i < 3; i++) { // znalezienie gracza, który ma kolej
                if (gracze[i].getKol()) {
                    if (kola[i]->getWartosc() == -1)
                        gracze[i].setKasa(
                                0); // jeśli koło ma wartość -1, ustawienie sumy pieniędzy zgromadzonych przez gracza na 0
                    gracze[i].setKol(false); // ustawienie flagi kol na false dla tego gracza
                    gracze[(i + 1) % 3].setKol(true); // ustawienie flagi kol na true dla następnego gracza
                    break;
                }
            }
            suma = 1; // ustawienie sumy na wartość niezerową, aby kontynuować pętlę gry
            cout << endl << "=================================================" << endl;
            continue; // przejście do następnej iteracji pętli gry
        }

        for (i = 0; i < 3; i++) { // znalezienie gracza, który ma kolej
            if (gracze[i].getKol()) break;
        }

        cout << gracze[i].getImie() << ": Podaj litere" << endl; // wypisanie nazwy gracza i prośby o podanie litery

        litt = wcZ(); // wczytanie litery podanej przez gracza

        zgadl = 0; // zerowanie liczby zgadniętych liter w jednym ruchu

        if (jeS(litt)) cout << "samogloska"; // jeśli litera jest samogłoską, wypisanie informacji
        else cout << "spolgloska"; // jeśli litera jest spółgłoską, wypisanie informacji

        cout << endl;

        for (i = 0; i < n; i++) { // sprawdzenie, czy litera występuje w haśle i czy nie została już odkryta
            if ((haslo[i] == litt) && (maska[i] == 1)) {
                maska[i] = 0; // jeśli tak, ustawienie maski na 0 dla tej litery
                zgadl++; // zwiększenie liczby zgadniętych liter w jednym ruchu
            }
        }

        if (zgadl) { // jeśli gracz zgadł co najmniej jedną literę
            cout << "OK";
            gracze[i].setKasa(gracze[i].getKasa() + kwota *
                                                    zgadl); // dodanie do sumy pieniędzy zgromadzonych przez gracza iloczynu kwoty wylosowanej z koła i liczby zgadniętych liter
            cout << endl << gracze[i].getImie() << "\033[1;32m " << gracze[i].getKasa()
                 << "\033[0m"; // wypisanie nazwy gracza i sumy pieniędzy zgromadzonych przez gracza na zielono
        } else { // jeśli gracz nie zgadł żadnej litery
            cout << "Zle!";
            gracze[i].setKol(false); // ustawienie flagi kol na false dla tego gracza
            gracze[(i + 1) % 3].setKol(true); // ustawienie flagi kol na true dla następnego gracza
            cout << endl << "=================================================" << endl;
            suma = 1; // ustawienie sumy na wartość niezerową, aby kontynuować pętlę gry
            continue; // przejście do następnej iteracji pętli gry
        }

        cout << endl;

        suma = 0; // zerowanie sumy

        for (i = 0; i < n; i++) { // obliczenie sumy odkrytych liter hasła
            suma += maska[i];
        }

    } while (suma); // dopóki suma jest niezerowa, czyli dopóki są nieodkryte litery w haśle

    cout << "BRAWO!"; // wypisanie informacji o odgadnięciu hasła

    exit(0); // zakończenie programu

// wypisanie nazw i sum pieniędzy wygranych przez graczy
    for (i = 0; i < 3; i++) {
        gracze[i].txP();
    }


// zwolnienie pamięci zajmowanej przez obiekty typu Kolo i KoloSpecjalne
    for (i = 0; i < 16; i++) {
        delete kola[i];
    }
}