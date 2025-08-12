#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Conversions.h"
#include "Collisionable.h"


class Block: public Collisionable{

    private:
        b2Body* _body;

        static float _width;

        static float _height;

        mutable sf::Sprite _sprite;

        static sf::Texture _texture;

        static bool _isTextureLoaded;

        void loadTexture();


    public:
        Block(b2World& world, float x, float y);

        void draw(sf::RenderTarget& target) const;

        virtual sf::FloatRect getBounds() const override;
};
