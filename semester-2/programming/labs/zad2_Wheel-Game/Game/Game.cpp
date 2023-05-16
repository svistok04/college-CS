//
// Created by marling on 4/5/23.
//

#include "Game.hpp"

void Game::wczytacHaslo() {
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


    for(const string& item : hasla)
        cout << item << endl;



    cout << endl << endl;

    assert((int)hasla.size() > 0);
    int j = rand() % hasla.size(); // losujemy j-te haslo z przedzialu 0 ... size - 1
    //cout << hasla[j];

    haslo = hasla[j];
    rozmiar = (int)haslo.size();
}

int Game::jestSamogloska(char c)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y')
        return 1;
    else
        return 0;

}

char Game::WczytajZnak()
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


char Game::WczytajWybor()
{
    cout << "1. zgaduj haslo" << endl;
    cout << "2. krecenie kolem" << endl;
    char wybor;
    wybor = WczytajZnak();

    while (wybor != '1' && wybor != '2')
    {
        cout << endl << "Wybierz [1-2]: ";
        cin >> wybor;
    }

    return wybor;

}

void Game::textPlayers() {
    int i;
    std::cout << "\n";
    for (i = 0; i < 3; i++) {
        if (i == kolejka) {
            cout << "\033[1;34m";
        }
        cout << gracze[i]->getImie() << "\t" << gracze[i]->getKasa() << "\n";
        cout << "\033[0m";

    }
    cout << "\n";
}

void Game::turnTheWheel() {
    Wheel kolo;
    int i;
    rezultat = "";
    i = rand() % 15;
    if (kolo.getValue(i) == 0)
        rezultat = "Strata kolejki";
    if (kolo.getValue(i) == -1)
        rezultat = "Bankrut";
    if (!rezultat.empty())
        cout << "\033[1;31m" << rezultat << "\033[0m" << endl;
    else
    {
        cout << "\033[1;34m" << kolo.getValue(i) << "\033[0m" << endl;
        kwota = kolo.getValue(i);
    }

    // Strata kolejki i bankrut
    if ((kolo.getValue(i) == 0) || (kolo.getValue(i) == -1))
    {
        if (kolo.getValue(i) == -1) // bankrut
            gracze[kolejka]->setKasa(0);

        kolejka = (kolejka + 1) % 3;
        suma = 1;
        cout << endl << "=================================================" << endl;

    }
}

void Game::zgadacHaslo() {
    if (wybor == '1')
    {
        cout << "Podaj haslo" << endl;
        getline(cin >> ws, proba);  // wczytanie z klawiatury string z uwzgl. whitespa
        for (auto& c : proba)  // & zapamietuje modyfikacje w petli & - referencja
            c = toupper(c);
        if (haslo == proba) {
            cout << endl << " !!!!!!!!!! =======   WYGRANA ========== !!!!!!!!!!!!!" << endl;
            gracze[kolejka]->setPortfel(gracze[kolejka]->getPortfel() + gracze[kolejka]->getKasa()) ;
            exit(0);
        }
        else
        {
            kolejka = (kolejka + 1) % 3;
            suma = 1;
            cout << endl << " !!!!!!!!!! =======   ZLE ========== !!!!!!!!!!!!!" << endl;
            cout << endl << "=================================================" << endl;
        }
    }
}

void Game::zgadacLiterke() {
    cout << gracze[kolejka]->getImie() <<  ": Podaj litere" << endl;
    literka = WczytajZnak();
    zgadl = 0;
    int i;
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
        gracze[kolejka]->setKasa(gracze[kolejka]->getKasa() + kwota * zgadl);

        cout << endl << gracze[kolejka]->getImie() << "\033[1;32m " << gracze[kolejka]->getKasa() << "\033[0m";


    }
    else {
        cout << "Zle!";
        // strata kolejki
        kolejka = (kolejka + 1) % 3;
        cout << endl << "=================================================" << endl;
        suma = 1;
    }
}

Game::Game() {
    gracze[0] = new Player("Bryanusz");
    gracze[1] = new Player("Jessica");
    gracze[2] = new Player("Nepomucen");
}

Game::~Game() {
    for (int i = 0; i < 3; i++)
        delete gracze[i];

}

void Game::play() {

    srand(time(nullptr));

    int i;

    wczytacHaslo();

    for (i = 0; i < rozmiar; i++)
    {
        if (haslo[i] == ' ')
            maska[i] = 0;
        else
            maska[i] = 1;
    }




    do
    {
        cout << "\033[2J";

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

        wybor = WczytajWybor();

        zgadacHaslo();
/*
        rezultat = "";
        i = rand() % 15;
        if (kolo.getValue(i) == 0)
            rezultat = "Strata kolejki";
        if (kolo.getValue(i) == -1)
            rezultat = "Bankrut";
        if (rezultat != "")
            cout << "\033[1;31m" << rezultat << "\033[0m" << endl;
        else
        {
            cout << "\033[1;34m" << kolo.getValue(i) << "\033[0m" << endl;
            kwota = kolo.getValue(i);
        }

        // Strata kolejki i bankrut
        if ((kolo.getValue(i) == 0) || (kolo.getValue(i) == -1))
        {
            if (kolo.getValue(i) == -1) // bankrut
                gracze[kolejka]->setKasa(0);

            kolejka = (kolejka + 1) % 3;
            suma = 1;
            cout << endl << "=================================================" << endl;

            continue;

        }*/


        zgadacLiterke();

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