#pragma once
#include "Base.h"


class Harmonogram {
	private:
		std::vector<DateTime> dataStart;
    public:
        void dodajTermin(std::string day, std::string month, std::string year, std::string hour, std::string time);

        void wyswietlHarmonogram();
};

