#pragma once

#include <SFML/Graphics.hpp>
#include "BackgroundMenu.h"
#include "ArchivoRanking.h"


class MenuOptions{

    private:
        int _selectedItemIndex;

        sf::Font _font;

        sf::Text _tittle;

        BackgroundMenu _background;

        std::vector<sf::Text> _menuItems;

        bool _enterPressed;

        int _musicActive;

        int _sfxActive;

        void moveUp();

        void moveDown();

        void updateColors();

    public:
        MenuOptions(float width, float height);

        void update(sf::RenderWindow& window, sf::Event event);

        void draw(sf::RenderWindow& window);

        int getSelectedItemIndex();

        bool isEnterPressed();

        void resetSelection();

        void setMusicActive();

        void setSfxActive();

        void deleteData();
};
