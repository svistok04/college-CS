#include <iostream>
#include "Base.h"
#include "Klient.h"
#include "Grupa.h"
#include "Trener.h"
#include "Kierownik.h"

unsigned int Konto::ID_cnt = 0;
std::vector<Klient*> Klient::klienci;
std::vector<Wniosek*> Wniosek::wnioski;

int main()
{
    int i = 0;
    Kierownik K_KAMIL;
    Trener  T_MAR_A, T_BAR_K;
    Grupa grupa_1(1, "Grupa_A"), grupa_2(2, "Grupa_B");
    Klient C_JAN_N, C_TOM_K, C_KAM_K;

    ///Kierownik i klienci tworza konta
    K_KAMIL.stworzKonto("Kamil", "Kamil", "ul. Kierownicza 1", "Kamil@fakemail.com", "999 999 999", "KML", "****");
    C_JAN_N.stworzKonto("Jan", "Nowak", "ul. Mazowiecka 15", "Nowak.J@fakemail.com", "111 222 333", "Nowak2432523", "*********");
    C_TOM_K.stworzKonto("Tom", "Kier", "2015 Flower Ave.", "thomas.k@fakermail.com", "22 33 44 777", "TK2122", "********");
    C_KAM_K.stworzKonto("Kamil", "Bier", "ul. Zolnierska 111", "kamil.k@fakermail.com", "111 222 333", "KK2122", "********");

    ///Kierownik tworzy konta trenerow
    K_KAMIL.dodajPracownika(T_MAR_A, "Marcin", "Antoni", "ul. Bohaterow Warszawy 2", "marcin.mar@fakemail.com", "3333 22 11 00", "M_A", "*********");
    K_KAMIL.dodajPracownika(T_BAR_K, "Bartosz", "Kowalski", "ul. Orzechowska 2", "Bartosz.AAA@fakemail.com", "123 123 123", "B_K", "*********");

    ///Klienci wysylaja wnioski o dolaczenie do grup
    C_JAN_N.dolaczDoGrupy(1, "05", "06", "2024");
    C_KAM_K.dolaczDoGrupy(1, "04", "06", "2024");
    C_TOM_K.dolaczDoGrupy(2, "07", "06", "2024");

    ///Klient wysyla wniosek o uczestniczenie w treningach indywidualnych
    C_TOM_K.treningIndywidualny(T_MAR_A.getID(), "11", "06", "2024");

    ///Kierownik przypisuje trenerow do grup
    K_KAMIL.przypiszDoGrupy(T_MAR_A, grupa_1);
    K_KAMIL.przypiszDoGrupy(T_BAR_K, grupa_2);

    ///Trenerzy dodaja klientow do grup
    T_MAR_A.dodajDoGrupy(C_JAN_N, grupa_1);
    T_MAR_A.dodajDoGrupy(C_KAM_K, grupa_1);
    T_BAR_K.dodajDoGrupy(C_TOM_K, grupa_2);

    std::cout << "Grupa 1:" << std::endl;
    grupa_1.wyswietlListeKlientow();
    std::cout << "Grupa 2:" << std::endl;
    grupa_2.wyswietlListeKlientow();

    C_JAN_N.opuscGrupe(1, "08", "06", "2024");
    ///Trener usuwa klienta z grupy
    T_MAR_A.usun_z_grupy(C_JAN_N,grupa_1);
    std::cout << "--Janusz zostal usuniety z Grupy 1--" << std::endl;
    std::cout << "Grupa 1:" << std::endl;
    grupa_1.wyswietlListeKlientow();

    ///Trener dodaje klienta do listy na trening indywidualny
    T_MAR_A.treningIndywidualny(C_TOM_K);
    std::cout << "Lista na trening indywidualny trenera Marcina:" << std::endl;
    T_MAR_A.wyswietlListeNaTreningIndywidualny();

    ///Trener edytuje swoj harmonogram
    T_MAR_A.zmienHarmonogramTrenera("19", "02", "2024", "11:00", "1h");
    T_MAR_A.zmienHarmonogramTrenera("25", "02", "2024", "11:00", "1h");
    std::cout << "Harmonogram trenera Marcina:" << std::endl;
    T_MAR_A.wyswietlHarmonogram();

    ///Trener edytuje harmonogram
    T_MAR_A.zmienHarmonogramGrupy(grupa_1 ,"11", "02", "2024", "12:00", "1h");
    T_MAR_A.zmienHarmonogramGrupy(grupa_1 ,"12", "02", "2024", "12:00", "1h");
    T_MAR_A.zmienHarmonogramGrupy(grupa_1 ,"13", "02", "2024", "12:00", "1h");
    T_MAR_A.zmienHarmonogramGrupy(grupa_1 ,"14", "02", "2024", "12:00", "1h");
    T_MAR_A.zmienHarmonogramGrupy(grupa_1 ,"15", "02", "2024", "12:00", "1h");
    std::cout << "Harmonogram Grupy 1:" << std::endl;
    grupa_1.wyswietlHarmonogram();

    std::cout << "Dane trenera z grupy" << std::endl;
    grupa_1.readTrener();
    ///Alternatywna funkcja
    //    Trener** trn = grupa_1.accessTrainer();
    //    (*trn)->wyswietlDane();

    std::cout << "Blokowanie klienta Jan" << std::endl;
    K_KAMIL.zablokujKlienta(C_JAN_N);
    std::cout << "Jan: " << C_JAN_N.wypiszStatus() << " Tom: " << C_TOM_K.wypiszStatus() << std::endl;

    std::cout << "Grupa wniosek data" << std::endl;
    C_JAN_N.dolaczDoGrupy(1, "18", "06", "2024");
    std::vector<Wniosek>* w = C_JAN_N.getWniosek(); //-- this works
    std::cout << w->back().data_zlozenia.read() << std::endl;

    std::cout << "Ogloszenia" << std::endl;
    T_MAR_A.dodajOgloszenie(1, "Ogloszenie 1", "Lorem Ipsum", Date("01", "01", "2024"));
    K_KAMIL.dodajOgloszenie(2, "Ogloszenie 2", "dolor sit amet", Date("10", "01", "2024"));
    const auto& posts = Post::getPosts();
    if (!posts.empty()) {
        for (auto& post : posts) {
            post->wyswietlPost();
        }
    }

    return 0;
}
