#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Conversions.h"
#include "Collisionable.h"


class Elevator: public Collisionable{

    private:
        b2Body* _body;

        static float _width;

        static float _height;

        mutable sf::Sprite _sprite;

        static sf::Texture _texture;

        static bool _isTextureLoaded;

        void loadTexture();

        bool _state = true;

        float _yUpperLimit;

        float _yDownLimit;

        float _speed;

        float _pauseDuration = 3.0f;

        bool _isPaused = false;

        sf::Clock _gameClock;




    public:
        Elevator(b2World& world, float x, float y, float upperLimit, float downLimit, float velocidad);

        void update();

        void draw(sf::RenderTarget& target) const;

        virtual sf::FloatRect getBounds() const override;

        void spawn(float x, float y);
};
