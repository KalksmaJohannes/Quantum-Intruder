#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Conversions.h"
#include "Collisionable.h"


class Ramp: public Collisionable{

    private:
        b2Body* _body;

        static float _width;

        static float _height;

        mutable sf::Sprite _sprite;

        static sf::Texture _texture;

        static bool _isTextureLoaded;

        void loadTexture();


    public:
        Ramp(b2World& world, float x, float y, float facingRight, float facingUp);

        void draw(sf::RenderTarget& target) const;

        virtual sf::FloatRect getBounds() const override;
};
