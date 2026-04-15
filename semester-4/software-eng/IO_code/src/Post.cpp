//
// Created by marling on 6/18/24.
//

#include "Post.h"

std::vector<Post*> Post::posty;

Post::Post(unsigned int ID, std::string tytul, std::string autor, std::string tresc, PostType typ, Date data)
: ID(ID), tytul(tytul), autor(autor), tresc(tresc), typ(typ), data(data) {
    posty.push_back(this);
}

Post::~Post() {
    auto it = std::find(posty.begin(), posty.end(), this);
    if (it != posty.end()) {
        posty.erase(it);
    }
}

const std::vector<Post*>& Post::getPosts() {
    return posty;
}


void Post::wyswietlPost() const {
    std::cout << "ID: " << ID << std::endl;
    std::cout << "Tytul: " << tytul << std::endl;
    std::cout << "Autor: " << autor << std::endl;
    std::cout << "Tresc: " << tresc << std::endl;
    std::cout << "Data: " << data.read() << std::endl;
}

