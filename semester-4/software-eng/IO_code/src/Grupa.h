#pragma once
#include "Base.h"
#include "Klient.h"
#include "Trener.h"
#include "Harmonogram.h"


class Grupa {
private:
    unsigned int ID;
    std::vector<Klient*> lista_klientow;
    Trener* trener_prowadzacy;
    Harmonogram harmonogramGrupy;
    std::string nazwa;
public:
    Grupa();

    Grupa(unsigned int ID, std::string nazwa);

    std::vector<Klient*>* accessList();

    Trener** accessTrainer();

    Harmonogram* accessSchedule();

    void readTrener();

    void wyswietlListeKlientow();

    unsigned int wyswietlID();

    void wyswietlHarmonogram();
};

