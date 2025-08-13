#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Conversions.h"
#include "Collisionable.h"
#include <iostream>


class HealthImage{
    private:
        sf::Sprite _sprite;
        sf::Texture _texture;

    public:
        HealthImage();
        void draw(sf::RenderTarget& target) const ;
        void setTexture(std::string nameTexture);
};
