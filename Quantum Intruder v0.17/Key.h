#pragma once


#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Conversions.h"
#include "Collisionable.h"


class Key: public Collisionable{

    private:
        b2Body* _body;

        mutable sf::Sprite _sprite;

        sf::Texture _texture;

        float _frames;


    public:
        Key(b2World& world, float x, float y);

        void update();

        void draw(sf::RenderTarget& target) const;

        virtual sf::FloatRect getBounds() const override;

        void spawn(b2Vec2 position);
};
