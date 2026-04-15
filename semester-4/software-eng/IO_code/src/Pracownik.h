#pragma once
#include "Base.h"
#include "Konto.h"
#include "Post.h"

class Pracownik : public Konto {

private:
    Date dataZatrudnienia;
    std::string wyksztalcenie;
    std::string numerKonta;
    std::vector<Post> posty;

public:
    void wyswietlListeKlientow();

    virtual void dodajOgloszenie(unsigned int ID, const std::string& tytul, const std::string& tresc, const Date& data) = 0;
    std::vector<Post>& getPosts() {
        return posty;
    }
};
