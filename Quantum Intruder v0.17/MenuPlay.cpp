#include "MenuPlay.h"


MenuPlay::MenuPlay(float width, float height) : _selectedItemIndex(0), _enterPressed(false) {

    _font.loadFromFile("resources/Fonts/Robot Crush.ttf");

    _tittle.setFont(_font);
    _tittle.setString("Seleccionar modo de juego:");
    _tittle.setFillColor(sf::Color::Green);
    _tittle.setPosition(sf::Vector2f(width / 2, height / 10 * 1));
    _tittle.setCharacterSize(40);
    _tittle.setOrigin(_tittle.getLocalBounds().width / 2, _tittle.getLocalBounds().height / 2);

    sf::Text timeTrialMode("Iniciar modo cronometrado", _font);
    timeTrialMode.setFillColor(sf::Color::Red);
    timeTrialMode.setPosition(sf::Vector2f(width / 2, height / 5 * 2));
    timeTrialMode.setOrigin(timeTrialMode.getLocalBounds().width / 2, timeTrialMode.getLocalBounds().height/2);
    _menuItems.push_back(timeTrialMode);

    sf::Text levelSelect("Seleccion de niveles libre", _font);
    levelSelect.setPosition(sf::Vector2f(width / 2, height / 5 * 3));
    levelSelect.setOrigin(levelSelect.getLocalBounds().width / 2, levelSelect.getLocalBounds().height/2);
    _menuItems.push_back(levelSelect);

    sf::Text goBack("Atras", _font);
    goBack.setPosition(sf::Vector2f(width / 2, height / 10 * 9));
    goBack.setOrigin(goBack.getLocalBounds().width / 2, goBack.getLocalBounds().height/2);
    _menuItems.push_back(goBack);

    //Inicializar sonidos
    _soundBufferNavigate.loadFromFile("resources/Audios/navigate.wav");
    _soundNavigate.setBuffer(_soundBufferNavigate);
    _soundNavigate.setVolume(10.0f);

    _soundBufferSelect.loadFromFile("resources/Audios/select.wav");
    _soundSelect.setBuffer(_soundBufferSelect);
    _soundSelect.setVolume(10.0f);

}

void MenuPlay::update(sf::RenderWindow& window, sf::Event event) {

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                moveUp();
            break;

            case sf::Keyboard::Down:
                moveDown();
            break;

            case sf::Keyboard::Return:
                _soundSelect.play();

                _enterPressed = true;
            break;

            default:

            break;
        }
    }

}

void MenuPlay::draw(sf::RenderWindow& window) {

    window.draw(_background);

    window.draw(_tittle);

    for (auto& item : _menuItems) {
        window.draw(item);
    }

}

int MenuPlay::getSelectedItemIndex() {

    return _selectedItemIndex;

}

bool MenuPlay::isEnterPressed() {

    if (_enterPressed) {
        _enterPressed = false;

        return true;
    }


    return false;
}

void MenuPlay::moveUp() {

    if (_selectedItemIndex - 1 >= 0) {
        _soundNavigate.play();

        _selectedItemIndex--;

        updateColors();
    }

}

void MenuPlay::moveDown() {

    if (_selectedItemIndex + 1 < static_cast<int>(_menuItems.size())) {
        _soundNavigate.play();

        _selectedItemIndex++;

        updateColors();
    }

}

void MenuPlay::updateColors(){

    for (int i = 0; i < static_cast<int>(_menuItems.size()); ++i){
        if (i == _selectedItemIndex){
            _menuItems[i].setFillColor(sf::Color::Red);
        }
        else{
            _menuItems[i].setFillColor(sf::Color::White);
        }
    }

}

void MenuPlay::resetSelection(){

    _selectedItemIndex = 0;

    updateColors();

}

void MenuPlay::changeVolume(){

    if (_soundNavigate.getVolume() != 0.0f){
        _soundNavigate.setVolume(0.0f);
        _soundSelect.setVolume(0.0f);
    }
    else{
        _soundNavigate.setVolume(10.0f);
        _soundSelect.setVolume(10.0f);
    }

}
