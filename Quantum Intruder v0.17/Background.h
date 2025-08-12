#pragma once

#include <SFML/Graphics.hpp>


class Background: public sf::Drawable{

    private:
        sf::Sprite _sprite;
        sf::Texture _texture;

    public:
        Background();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
