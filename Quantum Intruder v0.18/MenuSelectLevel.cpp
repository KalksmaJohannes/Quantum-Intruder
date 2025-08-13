#include "MenuSelectLevel.h"


MenuSelectLevel::MenuSelectLevel(float width, float height) : _selectedItemIndex(0), _enterPressed(false) {

    _font.loadFromFile("resources/Fonts/Robot Crush.ttf");

    _tittle.setFont(_font);
    _tittle.setString("Seleccionar Nivel:");
    _tittle.setFillColor(sf::Color::Green);
    _tittle.setPosition(sf::Vector2f(width / 2, height / 12 * 1));
    _tittle.setCharacterSize(40);
    _tittle.setOrigin(_tittle.getLocalBounds().width / 2, _tittle.getLocalBounds().height / 2);

    sf::Text level1("Nivel 1", _font);
    level1.setFillColor(sf::Color::Red);
    level1.setPosition(sf::Vector2f(width / 2, height / 14 * 3));
    level1.setOrigin(level1.getLocalBounds().width / 2, level1.getLocalBounds().height/2);
    _menuItems.push_back(level1);

    sf::Text level2("Nivel 2", _font);
    level2.setPosition(sf::Vector2f(width / 2, height / 14 * 4));
    level2.setOrigin(level2.getLocalBounds().width / 2, level2.getLocalBounds().height/2);
    _menuItems.push_back(level2);

    sf::Text level3("Nivel 3", _font);
    level3.setPosition(sf::Vector2f(width / 2, height / 14 * 5));
    level3.setOrigin(level3.getLocalBounds().width / 2, level3.getLocalBounds().height/2);
    _menuItems.push_back(level3);

    sf::Text level4("Nivel 4", _font);
    level4.setPosition(sf::Vector2f(width / 2, height / 14 * 6));
    level4.setOrigin(level4.getLocalBounds().width / 2, level4.getLocalBounds().height/2);
    _menuItems.push_back(level4);

    sf::Text level5("Nivel 5", _font);
    level5.setPosition(sf::Vector2f(width / 2, height / 14 * 7));
    level5.setOrigin(level5.getLocalBounds().width / 2, level5.getLocalBounds().height/2);
    _menuItems.push_back(level5);

    sf::Text level6("Nivel 6", _font);
    level6.setPosition(sf::Vector2f(width / 2, height / 14 * 8));
    level6.setOrigin(level6.getLocalBounds().width / 2, level2.getLocalBounds().height/2);
    _menuItems.push_back(level6);

    sf::Text level7("Nivel 7", _font);
    level7.setPosition(sf::Vector2f(width / 2, height / 14 * 9));
    level7.setOrigin(level7.getLocalBounds().width / 2, level7.getLocalBounds().height/2);
    _menuItems.push_back(level7);

    sf::Text level8("Nivel 8", _font);
    level8.setPosition(sf::Vector2f(width / 2, height / 14 * 10));
    level8.setOrigin(level8.getLocalBounds().width / 2, level8.getLocalBounds().height/2);
    _menuItems.push_back(level8);

    sf::Text level9("Nivel 9", _font);
    level9.setPosition(sf::Vector2f(width / 2, height / 14 * 11));
    level9.setOrigin(level9.getLocalBounds().width / 2, level9.getLocalBounds().height/2);
    _menuItems.push_back(level9);

    sf::Text goBack("Atras", _font);
    goBack.setPosition(sf::Vector2f(width / 2, height / 12 * 11));
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

void MenuSelectLevel::update(sf::RenderWindow& window, sf::Event event) {

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

void MenuSelectLevel::draw(sf::RenderWindow& window) {

    window.draw(_background);

    window.draw(_tittle);

    for (auto& item : _menuItems) {
        window.draw(item);
    }

}

int MenuSelectLevel::getSelectedItemIndex() {

    return _selectedItemIndex;

}

bool MenuSelectLevel::isEnterPressed() {

    if (_enterPressed) {
        _enterPressed = false;

        return true;
    }


    return false;
}

void MenuSelectLevel::moveUp() {

    if (_selectedItemIndex - 1 >= 0) {
        _soundNavigate.play();

        _selectedItemIndex--;

        updateColors();
    }

}

void MenuSelectLevel::moveDown() {

    if (_selectedItemIndex + 1 < static_cast<int>(_menuItems.size())) {
        _soundNavigate.play();

        _selectedItemIndex++;

        updateColors();
    }

}

void MenuSelectLevel::updateColors(){

    for (int i = 0; i < static_cast<int>(_menuItems.size()); ++i){
        if (i == _selectedItemIndex){
            _menuItems[i].setFillColor(sf::Color::Red);
        }
        else{
            _menuItems[i].setFillColor(sf::Color::White);
        }
    }

}

void MenuSelectLevel::resetSelection(){

    _selectedItemIndex = 0;

    updateColors();

}

void MenuSelectLevel::changeVolume(){

    if (_soundNavigate.getVolume() != 0.0f){
        _soundNavigate.setVolume(0.0f);
        _soundSelect.setVolume(0.0f);
    }
    else{
        _soundNavigate.setVolume(10.0f);
        _soundSelect.setVolume(10.0f);
    }

}
