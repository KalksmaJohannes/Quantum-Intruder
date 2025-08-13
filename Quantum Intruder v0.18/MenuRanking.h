#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BackgroundMenu.h"
#include "Ranking.h"
#include "ArchivoRanking.h"


class MenuRanking{

    private:
        int _selectedItemIndex;

        sf::Font _font;

        sf::Text _tittle;

        BackgroundMenu _background;

        std::vector<sf::Text> _menuItems;

        std::vector<sf::Text> _rankingItems;

        std::string _rankingInformation[5];

        bool _enterPressed;

        sf::Sound _sound;

        sf::SoundBuffer _soundBuffer;

    public:
        MenuRanking(float width, float height);

        void update(sf::RenderWindow& window, sf::Event event);

        void draw(sf::RenderWindow& window);

        int getSelectedItemIndex();

        bool isEnterPressed();

        void getRankingInformation();

        bool isNewRecord(sf::Time timeScore);

        void sortRanking(Ranking vec[], int tam);

        void updateRankingInformation(Ranking ranking);

        void updateStrings();

        void changeVolume();
};
