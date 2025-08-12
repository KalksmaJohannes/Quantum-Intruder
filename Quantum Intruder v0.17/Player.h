#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Conversions.h"
#include "Collisionable.h"


enum class PlayerState {
    Idle = 0,
    Moving
};


class Player: public Collisionable{

    private:
        b2Body* _body;

        mutable sf::Sprite _playerSprite;

        sf::Texture _playerTexture;

        mutable sf::Sprite _footSprite;

        sf::Texture _footTexture;

        float _frameIdle;

        float _frameMoving;

        PlayerState _state;

        float _moveSpeed;

        float _maxJumpForce;

        float _currentJumpForce;

        bool _jumpKeyReleased;

        bool _isJumping;

        bool _canJump;

        sf::Clock _jumpClock;


    public:
        Player(b2World& world, float x, float y);

        void cmd();

        void update();

        void draw(sf::RenderTarget& target) const;

        virtual sf::FloatRect getBounds() const override;

        sf::FloatRect getFootBounds() const;

        bool isFootCollision(const Collisionable& collisionable) const;

        b2Vec2 getPosition() const;

        void startContact();

        void endContact();

        void respawn(float x, float y);
};
