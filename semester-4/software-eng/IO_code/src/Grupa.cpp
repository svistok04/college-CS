#include "Grupa.h"

Grupa::Grupa(unsigned int ID, std::string nazwa)
{
    this->ID = ID;
    this->nazwa = nazwa;
}

std::vector<Klient*>* Grupa::accessList()
{
    return &lista_klientow;
}

Trener** Grupa::accessTrainer()
{
    return &trener_prowadzacy;
}

void Grupa::readTrener()
{
    this->trener_prowadzacy->wyswietlDane();
}

void Grupa::wyswietlListeKlientow()
{
    if (lista_klientow.empty())
        return;
    for (auto item : lista_klientow)
        item->wyswietlDane();
}

 unsigned int Grupa::wyswietlID()
 {
     return ID;
 }

 Harmonogram* Grupa::accessSchedule()
 {
    return &harmonogramGrupy;
 }

 void Grupa::wyswietlHarmonogram()
{
    harmonogramGrupy.wyswietlHarmonogram();
}
