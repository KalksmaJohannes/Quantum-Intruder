#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Loading: public sf::Drawable{

    private:
        sf::Sprite _sprite;

        sf::Texture _texture;

        float _frames;

        bool _isLoading;

        sf::Sound _sound;

        sf::SoundBuffer _soundBuffer;


    public:
        Loading();

        void load();

        void update();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void changeVolume();
};
