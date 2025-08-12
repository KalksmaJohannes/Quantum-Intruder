#pragma once

#include <SFML/Graphics.hpp>
#include "BackgroundMenu.h"


class MenuWriteName {

    private:
        int _selectedItemIndex;

        sf::Font _font;

        sf::Text _tittle;

        sf::Text _prompt;

        sf::Text _nameText;

        BackgroundMenu _background;

        std::vector<sf::Text> _menuItems;

        bool _enterPressed;

        std::string _namePlayer;

        const int _maxLength = 5;

    public:
        MenuWriteName(float width, float height);

        void update(sf::RenderWindow& window, sf::Event event);

        void draw(sf::RenderWindow& window);

        int getSelectedItemIndex();

        std::string getName();

        void clearName();

        bool isEnterPressed();
};
