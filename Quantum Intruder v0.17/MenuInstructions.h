#pragma once

#include <SFML/Graphics.hpp>
#include "BackgroundMenu.h"


class MenuInstructions{

    private:
        int _selectedItemIndex;

        sf::Font _font;

        sf::Text _tittle;

        sf::Text _paragraph;

        BackgroundMenu _background;

        std::vector<sf::Text> _menuItems;

        bool _enterPressed;

    public:
        MenuInstructions(float width, float height);

        void update(sf::RenderWindow& window, sf::Event event);

        void draw(sf::RenderWindow& window);

        int getSelectedItemIndex();

        bool isEnterPressed();
};
