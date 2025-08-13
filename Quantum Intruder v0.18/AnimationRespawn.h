#pragma once

#include <SFML/Graphics.hpp>
#include "Conversions.h"


class AnimationRespawn{

    private:
        mutable sf::Sprite _sprite;

        sf::Texture _texture;

        float _frames;

        bool _isRespawning;

        float _x;

        float _y;


    public:
        AnimationRespawn();

        void respawn(float x, float y);

        void update();

        void draw(sf::RenderTarget& target) const;

        bool getIsRespawning();
};
