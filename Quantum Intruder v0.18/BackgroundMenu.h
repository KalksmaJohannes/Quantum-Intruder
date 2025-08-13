#pragma once

#include <SFML/Graphics.hpp>


class BackgroundMenu: public sf::Drawable{

    private:
        sf::Sprite _sprite;
        sf::Texture _texture;

    public:
        BackgroundMenu();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
