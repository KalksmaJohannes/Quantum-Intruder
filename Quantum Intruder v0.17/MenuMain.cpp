#include "MenuMain.h"


MenuMain::MenuMain(float width, float height) : _selectedItemIndex(0), _enterPressed(false){

    _font.loadFromFile("resources/Fonts/Robot Crush.ttf");

    _tittle.setFont(_font);
    _tittle.setString("Quantum Intruder");
    _tittle.setFillColor(sf::Color::White);
    _tittle.setPosition(sf::Vector2f(width / 2, height / 10 * 1));
    _tittle.setCharacterSize(90);
    _tittle.setOrigin(_tittle.getLocalBounds().width / 2, _tittle.getLocalBounds().height / 2);

    sf::Text play("Iniciar Juego", _font);
    play.setFillColor(sf::Color::Red);
    play.setPosition(sf::Vector2f(width / 2, height / 10 * 4));
    play.setCharacterSize(40);
    play.setOrigin(play.getLocalBounds().width / 2, play.getLocalBounds().height/2);
    _menuItems.push_back(play);

    sf::Text ranking("Ranking", _font);
    ranking.setPosition(sf::Vector2f(width / 2, height / 10 * 5));
    ranking.setCharacterSize(40);
    ranking.setOrigin(ranking.getLocalBounds().width / 2, ranking.getLocalBounds().height/2);
    _menuItems.push_back(ranking);

    sf::Text instructions("Instrucciones", _font);
    instructions.setPosition(sf::Vector2f(width / 2, height / 10 * 6));
    instructions.setCharacterSize(40);
    instructions.setOrigin(instructions.getLocalBounds().width / 2, instructions.getLocalBounds().height/2);
    _menuItems.push_back(instructions);

    sf::Text options("Opciones", _font);
    options.setPosition(sf::Vector2f(width / 2, height / 10 * 7));
    options.setCharacterSize(40);
    options.setOrigin(options.getLocalBounds().width / 2, options.getLocalBounds().height/2);
    _menuItems.push_back(options);

    sf::Text exit("Salir", _font);
    exit.setPosition(sf::Vector2f(width / 2, height / 10 * 8));
    exit.setCharacterSize(40);
    exit.setOrigin(exit.getLocalBounds().width / 2, exit.getLocalBounds().height/2);
    _menuItems.push_back(exit);

}

void MenuMain::update(sf::RenderWindow& window, sf::Event event){

    if (event.type == sf::Event::KeyPressed){
        switch (event.key.code){
            case sf::Keyboard::Up:
                moveUp();
            break;

            case sf::Keyboard::Down:
                moveDown();
            break;

            case sf::Keyboard::Return:
                _enterPressed = true;
            break;

            default:

            break;
        }
    }

}

void MenuMain::draw(sf::RenderWindow& window){

    window.draw(_background);

    window.draw(_tittle);

    for (auto& item : _menuItems){
        window.draw(item);
    }

}

int MenuMain::getSelectedItemIndex(){

    return _selectedItemIndex;

}

bool MenuMain::isEnterPressed(){

    if (_enterPressed) {
        _enterPressed = false;

        return true;
    }


    return false;
}

void MenuMain::moveUp(){

    if (_selectedItemIndex - 1 >= 0) {
        _selectedItemIndex--;

        updateColors();
    }

}

void MenuMain::moveDown(){

    if (_selectedItemIndex + 1 < static_cast<int>(_menuItems.size())){
        _selectedItemIndex++;

        updateColors();
    }

}

void MenuMain::updateColors(){

    for (int i = 0; i < static_cast<int>(_menuItems.size()); ++i){
        if (i == _selectedItemIndex){
            _menuItems[i].setFillColor(sf::Color::Red);
        }
        else{
            _menuItems[i].setFillColor(sf::Color::White);
        }
    }

}

void MenuMain::resetSelection(){

    _selectedItemIndex = 0;

    updateColors();

}
