#pragma once

#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>


class Ranking{

    private:
        char _namePlayer[6];

        sf::Time _timeScore;


    public:
        Ranking();

        Ranking(const char namePlayer[], sf::Time timeScore);

        void cargar(std::string namePlayer, sf::Time timeScore);

        std::string getRankInformation();

        std::string getName();

        void setTimeScore(sf::Time timeScore);

        void setName(std::string name);

        sf::Time getTimeScore();
};
