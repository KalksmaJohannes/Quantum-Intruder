#pragma once


#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Conversions.h"
#include "Collisionable.h"


class Door: public Collisionable{

    private:
        b2Body* _body;

        mutable sf::Sprite _sprite;

        sf::Texture _texture;

        mutable sf::Sprite _doorSensorSprite;

        sf::Texture _doorSensorTexture;

        float _frames;

        bool _isKeyCollected;


    public:
        Door(b2World& world, float x, float y);

        void open();

        void close();

        void update();

        void draw(sf::RenderTarget& target) const;

        virtual sf::FloatRect getBounds() const override;

        sf::FloatRect getDoorSensorBounds() const;

        bool isDoorSensorCollision(const Collisionable& collisionable) const;
};
