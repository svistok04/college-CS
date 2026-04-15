#include "Trener.h"

void Trener::wyswietlDane()
{
    std::cout << "Trener: ";
    Konto::wyswietlDane();
}

void Trener::dodajDoGrupy(Klient& klient, Grupa& grupa) {
    Trener** trn = grupa.accessTrainer();
    if (*trn != this)
        return;

    auto vec = grupa.accessList();
    std::vector<Wniosek>* wnioski = klient.getWniosek();

    for (unsigned int i = 0; i < wnioski->size(); i++)
        if ((*wnioski)[i].typ == DODANIE_DO_GRUPY && (*wnioski)[i].grupa_ID == grupa.wyswietlID())
        {
            vec->push_back(&klient);
            (*wnioski).erase(wnioski->begin() + i);
            break;
        }
}

void Trener::treningIndywidualny(Klient& klient) {
    std::vector<Wniosek>* wnioski = klient.getWniosek();

    for (unsigned int i = 0; i < wnioski->size(); i++)
        if ((*wnioski)[i].typ == ZAPISANIE_NA_TRENING && (*wnioski)[i].grupa_ID == ID_konta)
        {
            klienci_indywidualni.push_back(&klient);
            (*wnioski).erase(wnioski->begin() + i);
            break;
        }
}

void Trener::usun_z_grupy(Klient& klient, Grupa& grupa)
{
    Trener** trn = grupa.accessTrainer();
    if (*trn != this)
        return;
    std::vector<Wniosek>* wnioski = klient.getWniosek();

    for (unsigned int i = 0; i < wnioski->size(); i++)
        if ((*wnioski)[i].typ == USUNIECIE_Z_GRUPY && (*wnioski)[i].grupa_ID == ID_konta)
        {
            (*wnioski).erase(wnioski->begin() + i);
            break;
        }
    std::vector<Klient*>* vec = grupa.accessList();
    for (unsigned int i = 0; i < vec->size(); i++)
    {
        if ((*vec)[i] == &klient)
            (*vec).erase((*vec).begin() + i);
        break;
    }

}

void Trener::wyswietlListeNaTreningIndywidualny()
{
    if (klienci_indywidualni.empty())
        return;
    for (auto item : klienci_indywidualni)
        item->wyswietlDane();
}

void Trener::zmienHarmonogramGrupy(Grupa& grupa, std::string day, std::string month, std::string year, std::string hour, std::string time) {
    Harmonogram* harmonogramGrupy = grupa.accessSchedule();
    Trener** trn = grupa.accessTrainer();
    if (*trn != this)
        return;
    harmonogramGrupy->dodajTermin(day, month, year, hour, time);
}

void Trener::wyswietlHarmonogram()
{
    harmonogramTrenera.wyswietlHarmonogram();
}

void Trener::zmienHarmonogramTrenera(std::string day, std::string month, std::string year, std::string hour, std::string time) {
    harmonogramTrenera.dodajTermin(day, month, year, hour, time);
}

void Trener::dodajOgloszenie(unsigned int ID, const std::string& tytul, const std::string& tresc, const Date& data) {
    new Post(ID, tytul, this->imie + " " + this->nazwisko, tresc, PostType::TRENER_POST, data);
}