#pragma once
#include "Base.h"
#include "Konto.h"

enum typ_wniosku
{
    DODANIE_DO_GRUPY,
    ZAPISANIE_NA_TRENING,
    USUNIECIE_Z_GRUPY
};

struct Wniosek
{
    bool init = false;
    typ_wniosku typ;
    unsigned int klient_ID;
    unsigned int grupa_ID;
    Date data_zlozenia;
    static std::vector<Wniosek*> wnioski;

    Wniosek() {}

    Wniosek(typ_wniosku typ, unsigned int klient_ID, unsigned int grupa_ID, Date data_zlozenia)
    {
        this->typ = typ;
        this->klient_ID = klient_ID;
        this->grupa_ID = grupa_ID;
        this->data_zlozenia = data_zlozenia;
        init = true;
        wnioski.push_back(this);
    }

};

class Klient : public Konto {
private:
    float limitKredytowy;
    Grupa *grupa = NULL;
    std::string status;
    std::vector<Wniosek> wnioski_klienta;
    static std::vector<Klient*> klienci;
public:

    static void wyswietlListeKlientow();

    void wyswietlDane() override;

    void stworzKonto(std::string imie, std::string nazwisko, std::string adres,
    std::string email, std::string numerTelefonu, std::string nazwaKonta, std::string haslo) override;

    void dolaczDoGrupy(unsigned int ID_grupy, std::string d, std::string m, std::string y);

    std::vector<Wniosek>* getWniosek();

    void opuscGrupe(unsigned int ID_grupy, std::string d, std::string m, std::string y);

    void treningIndywidualny(unsigned int ID_trenera, std::string d, std::string m, std::string y);

    void zlozSkarge();

    void wyswietlRachunki();
};



