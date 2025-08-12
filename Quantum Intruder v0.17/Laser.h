#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Conversions.h"
#include "Collisionable.h"


class Laser: public Collisionable{

    private:
        b2Body* _body;

        static float _width;

        float _height;

        mutable sf::Sprite _sprite;

        static sf::Texture _texture;

        static bool _isTextureLoaded;

        void loadTexture();


    public:
        Laser(b2World& world, float x, float y, float height);

        void draw(sf::RenderTarget& target) const;

        virtual sf::FloatRect getBounds() const override;

        void spawn(b2Vec2 position);
};
