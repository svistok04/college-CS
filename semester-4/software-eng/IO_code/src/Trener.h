#pragma once
#include "Pracownik.h"
#include "Grupa.h"
#include "Klient.h"
#include "Harmonogram.h"

class Trener : public Pracownik {
private:
    Grupa* grupa;
    Harmonogram harmonogramTrenera;
    std::vector<Klient*> klienci_indywidualni;
public:
    Trener() {};

    void wyswietlDane() override;

    int cenaTreninguIndywidualnego;

    void dodajDoGrupy(Klient& klient, Grupa& grupa);

    void usun_z_grupy(Klient& klient, Grupa& grupa);

    void treningIndywidualny(Klient& klient);

    void wyswietlListeNaTreningIndywidualny();

    void zmienHarmonogramGrupy(Grupa& grupa, std::string day, std::string month, std::string year, std::string hour, std::string time);

    void zmienHarmonogramTrenera(std::string day, std::string month, std::string year, std::string hour, std::string time);

    void wyswietlHarmonogram();

    void dodajOgloszenie(unsigned int ID, const std::string& tytul, const std::string& tresc, const Date& data) override;

    friend class Kierownik;

};
