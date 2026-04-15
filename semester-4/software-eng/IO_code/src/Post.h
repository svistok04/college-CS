#pragma once
#include "Base.h"

enum class PostType {
    KIEROWNIK_POST,
    TRENER_POST
};

class Post {
private:
    unsigned int ID;
    std::string tytul;
    std::string autor;
    std::string tresc;
    PostType typ;
    Date data;
    static std::vector<Post*> posty;

public:
    Post(unsigned int ID, std::string tytul, std::string autor, std::string tresc, PostType typ, Date data);
    ~Post();
    static const std::vector<Post*>& getPosts();
    void wyswietlPost() const;
};

