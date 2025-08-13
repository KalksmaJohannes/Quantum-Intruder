#pragma once

#include <vector>
#include "Player.h"
#include "PlayerDead.h"
#include "Block.h"
#include "Ramp.h"
#include "Spike.h"
#include "Button.h"
#include "Laser.h"
#include "Elevator.h"
#include "Key.h"
#include "Door.h"
#include "DebugDraw.h"
#include "BlockBackground.h"
#include "HealthImage.h"
#include "LevelImage.h"

class Scene2: public sf::Drawable{

    private:
        b2World _world;

        std::vector<Block> _blocks;

        std::vector<Ramp> _ramps;

        std::vector<Spike> _spikes;

        std::vector<Button> _buttons;

        std::vector<Laser> _lasers;

        std::vector<Elevator> _elevators;

        std::vector<Key> _key;

        std::vector<Door> _door;

        std::vector<PlayerDead> _playersDead;

        std::vector<BlockBackground> _blocksBackground;

        HealthImage _healthImage;

        LevelImage _levelImage;

        Player _player;

        b2Vec2 _buttonOriginalPosition;

        b2Vec2 _laserOriginalPosition;

        b2Vec2 _keyOriginalPosition;

        int _deathsCount;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        bool _isSceneClear;


    public:
        Scene2();

        void update();

        void createMap();

        b2World& getWorld();

        void resetScene();

        bool getSceneClear();

        void changeVolume();

        ~Scene2();
};
