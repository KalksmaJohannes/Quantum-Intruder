#pragma once

#include <SFML/Graphics.hpp>


class BackgroundPause: public sf::Drawable{

    private:
        sf::Sprite _sprite;
        sf::Texture _texture;

    public:
        BackgroundPause();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
