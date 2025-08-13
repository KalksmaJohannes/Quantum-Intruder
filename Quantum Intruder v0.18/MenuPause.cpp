#include "MenuPause.h"


MenuPause::MenuPause(float width, float height) : _selectedItemIndex(0), _enterPressed(false) {

    _font.loadFromFile("resources/Fonts/Robot Crush.ttf");

    _musicActive = 1;
    _sfxActive = 1;

    _tittle.setFont(_font);
    _tittle.setString("opciones");
    _tittle.setFillColor(sf::Color::White);
    _tittle.setPosition(sf::Vector2f(width / 2, height / 10 * 3.3f));
    _tittle.setCharacterSize(40);
    _tittle.setOrigin(_tittle.getLocalBounds().width / 2, _tittle.getLocalBounds().height / 2);

    sf::Text music("music: on", _font);
    music.setFillColor(sf::Color::Red);
    music.setPosition(sf::Vector2f(width / 2, height / 10 * 4.3f));
    music.setOrigin(music.getLocalBounds().width / 2, music.getLocalBounds().height/2);
    _menuItems.push_back(music);

    sf::Text sxf("sfx: on", _font);
    sxf.setPosition(sf::Vector2f(width / 2, height / 10 * 5.3f));
    sxf.setOrigin(sxf.getLocalBounds().width / 2, sxf.getLocalBounds().height/2);
    _menuItems.push_back(sxf);

    sf::Text goBack("Volver al Menu", _font);
    goBack.setPosition(sf::Vector2f(width / 2, height / 10 * 6.3f));
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

void MenuPause::update(sf::RenderWindow& window, sf::Event event) {

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

void MenuPause::draw(sf::RenderWindow& window) {

    window.draw(_background);

    window.draw(_tittle);

    for (auto& item : _menuItems) {
        window.draw(item);
    }

}

int MenuPause::getSelectedItemIndex() {

    return _selectedItemIndex;

}

bool MenuPause::isEnterPressed() {

    if (_enterPressed) {
        _enterPressed = false;

        return true;
    }


    return false;
}

void MenuPause::moveUp() {

    if (_selectedItemIndex - 1 >= 0) {
        _soundNavigate.play();

        _selectedItemIndex--;

        updateColors();
    }

}

void MenuPause::moveDown() {

    if (_selectedItemIndex + 1 < static_cast<int>(_menuItems.size())) {
        _soundNavigate.play();

        _selectedItemIndex++;

        updateColors();
    }

}

void MenuPause::updateColors(){

    for (int i = 0; i < static_cast<int>(_menuItems.size()); ++i){
        if (i == _selectedItemIndex){
            _menuItems[i].setFillColor(sf::Color::Red);
        }
        else{
            _menuItems[i].setFillColor(sf::Color::White);
        }
    }

}

void MenuPause::resetSelection(){

    _selectedItemIndex = 0;

    updateColors();

}

void MenuPause::setMusicActive(){

    _musicActive *= -1;

    if (_musicActive > 0){
        _menuItems[0].setString("music: on");
    }
    else{
        _menuItems[0].setString("music: off");
    }

}

void MenuPause::setSfxActive(){

    _sfxActive *= -1;

    if (_sfxActive > 0){
        _menuItems[1].setString("sfx: on");
    }
    else{
        _menuItems[1].setString("sfx: off");
    }

}

void MenuPause::changeVolume(){

    if (_soundNavigate.getVolume() != 0.0f){
        _soundNavigate.setVolume(0.0f);
        _soundSelect.setVolume(0.0f);
    }
    else{
        _soundNavigate.setVolume(10.0f);
        _soundSelect.setVolume(10.0f);
    }

}
