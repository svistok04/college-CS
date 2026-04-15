#include "Kierownik.h"

void Kierownik::wyswietlDane()
{
    std::cout << "Kierownik: ";
    Konto::wyswietlDane();
}

void Kierownik::przypiszDoGrupy(Trener& trener, Grupa& grupa)
{
    Trener** trn = grupa.accessTrainer();
    *trn = &trener;
}


void Kierownik::dodajPracownika(Trener& trener, std::string imie, std::string nazwisko, std::string adres,
    std::string email, std::string numerTelefonu, std::string nazwaKonta, std::string haslo) {
    trener.stworzKonto(imie, nazwisko, adres,
    email, numerTelefonu, nazwaKonta, haslo);
}

void Kierownik::usunPracownika(Trener& trener) {
    std::string* status = trener.getAccStatus();
    *status = "removed";
}


void Kierownik::wyslijNaUrlop(Trener& trener) {
    std::string* status = trener.getAccStatus();
    *status = "on_vacation";
}

void Kierownik::zakonczUrlop(Trener& trener) {
    std::string* status = trener.getAccStatus();
    *status = "active";
}

void Kierownik::zablokujKlienta(Klient& klient) {
	std::string* status = klient.getAccStatus();
    *status = "blocked";
}

void Kierownik::wyswietlRaport() {
	// TODO - implement Kierownik::wyswietlRaport
	throw "Not yet implemented";
}

void Kierownik::zmienHarmonogramGrupy(Grupa& grupa, std::string day, std::string month, std::string year, std::string hour, std::string time) {
    Harmonogram* harmonogramGrupy = grupa.accessSchedule();
    harmonogramGrupy->dodajTermin(day, month, year, hour, time);
}

void Kierownik::dodajOgloszenie(unsigned int ID, const std::string& tytul, const std::string& tresc, const Date& data) {
    new Post(ID, tytul, this->imie + " " + this->nazwisko, tresc, PostType::KIEROWNIK_POST, data);
}

