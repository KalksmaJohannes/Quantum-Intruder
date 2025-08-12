#include "MenuOptions.h"


MenuOptions::MenuOptions(float width, float height) : _selectedItemIndex(0), _enterPressed(false) {

    _font.loadFromFile("resources/Fonts/Robot Crush.ttf");

    _musicActive = 1;
    _sfxActive = 1;

    _tittle.setFont(_font);
    _tittle.setString("Opciones:");
    _tittle.setFillColor(sf::Color::Green);
    _tittle.setPosition(sf::Vector2f(width / 2, height / 10 * 1));
    _tittle.setCharacterSize(40);
    _tittle.setOrigin(_tittle.getLocalBounds().width / 2, _tittle.getLocalBounds().height / 2);

    sf::Text music("Music: ON", _font);
    music.setFillColor(sf::Color::Red);
    music.setPosition(sf::Vector2f(width / 2, height / 10 * 4));
    music.setOrigin(music.getLocalBounds().width / 2, music.getLocalBounds().height/2);
    _menuItems.push_back(music);

    sf::Text sfx("SFX: ON", _font);
    sfx.setPosition(sf::Vector2f(width / 2, height / 10 * 5));
    sfx.setOrigin(sfx.getLocalBounds().width / 2, sfx.getLocalBounds().height/2);
    _menuItems.push_back(sfx);

    sf::Text deleteData("Eliminar datos de ranking", _font);
    deleteData.setPosition(sf::Vector2f(width / 2, height / 10 * 6));
    deleteData.setOrigin(deleteData.getLocalBounds().width / 2, deleteData.getLocalBounds().height/2);
    _menuItems.push_back(deleteData);

    sf::Text goBack("Atras", _font);
    goBack.setPosition(sf::Vector2f(width / 2, height / 10 * 9));
    goBack.setOrigin(goBack.getLocalBounds().width / 2, goBack.getLocalBounds().height/2);
    _menuItems.push_back(goBack);

}

void MenuOptions::update(sf::RenderWindow& window, sf::Event event) {

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
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

void MenuOptions::draw(sf::RenderWindow& window) {

    window.draw(_background);

    window.draw(_tittle);

    for (auto& item : _menuItems) {
        window.draw(item);
    }

}

int MenuOptions::getSelectedItemIndex() {

    return _selectedItemIndex;

}

bool MenuOptions::isEnterPressed() {

    if (_enterPressed) {
        _enterPressed = false;

        return true;
    }


    return false;
}

void MenuOptions::moveUp() {

    if (_selectedItemIndex - 1 >= 0) {
        _selectedItemIndex--;

        updateColors();
    }

}

void MenuOptions::moveDown() {

    if (_selectedItemIndex + 1 < static_cast<int>(_menuItems.size())) {
        _selectedItemIndex++;

        updateColors();
    }

}

void MenuOptions::updateColors(){

    for (int i = 0; i < static_cast<int>(_menuItems.size()); ++i){
        if (i == _selectedItemIndex){
            _menuItems[i].setFillColor(sf::Color::Red);
        }
        else{
            _menuItems[i].setFillColor(sf::Color::White);
        }
    }

}

void MenuOptions::resetSelection(){

    _selectedItemIndex = 0;

    updateColors();

}

void MenuOptions::setMusicActive(){

    _musicActive *= -1;

    if (_musicActive > 0){
        _menuItems[0].setString("Music: ON");
    }
    else{
        _menuItems[0].setString("Music: OFF");
    }

}

void MenuOptions::setSfxActive(){

    _sfxActive *= -1;

    if (_sfxActive > 0){
        _menuItems[1].setString("SFX: ON");
    }
    else{
        _menuItems[1].setString("SFX: OFF");
    }

}

void MenuOptions::deleteData(){

    ArchivoRanking archivo("ranking.dat");
    Ranking ranking;


    archivo.crearDesdeCero();

    ranking.setName("-----");
    ranking.setTimeScore(sf::seconds(3599));

    for (int i=0; i<5; i++){
        archivo.grabarRegistro(ranking);
    }

}
