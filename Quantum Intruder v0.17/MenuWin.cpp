#include "MenuWin.h"


MenuWin::MenuWin(float width, float height) : _selectedItemIndex(0), _enterPressed(false) {

    _font.loadFromFile("resources/Fonts/Robot Crush.ttf");

    _tittle.setFont(_font);
    _tittle.setString("GANASTE!!! Tu tiempo fue:");
    _tittle.setFillColor(sf::Color::Green);
    _tittle.setPosition(sf::Vector2f(width / 2, height / 10 * 1));
    _tittle.setCharacterSize(60);
    _tittle.setOrigin(_tittle.getLocalBounds().width / 2, _tittle.getLocalBounds().height / 2);

    _winInformation.setFont(_font);
    _winInformation.setString(timeScoreToString());
    _winInformation.setFillColor(sf::Color::Magenta);
    _winInformation.setPosition(sf::Vector2f(width / 2, height / 2));
    _winInformation.setCharacterSize(35);
    _winInformation.setOrigin(_winInformation.getLocalBounds().width / 2, _winInformation.getLocalBounds().height/2);

    sf::Text goBackMenu("Continuar", _font);
    goBackMenu.setFillColor(sf::Color::Red);
    goBackMenu.setPosition(sf::Vector2f(width / 2, height / 10 * 9));
    goBackMenu.setOrigin(goBackMenu.getLocalBounds().width / 2, goBackMenu.getLocalBounds().height/2);
    _menuItems.push_back(goBackMenu);

    //Inicializar sonidos
    _soundBuffer.loadFromFile("resources/Audios/select.wav");
    _sound.setBuffer(_soundBuffer);
    _sound.setVolume(10.0f);

}

void MenuWin::update(sf::RenderWindow& window, sf::Event event) {

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Return:
                _sound.play();

                _enterPressed = true;
            break;

            default:

            break;
        }
    }

}

void MenuWin::draw(sf::RenderWindow& window) {

    window.draw(_background);

    window.draw(_tittle);

    window.draw(_winInformation);

    for (auto& item : _menuItems) {
        window.draw(item);
    }

}

int MenuWin::getSelectedItemIndex() {

    return _selectedItemIndex;

}

void MenuWin::setTimeScore(sf::Time timeScore){

    _timeScore = timeScore;

    _winInformation.setString(timeScoreToString());

}

sf::Time MenuWin::getTimeScore(){

    return _timeScore;

}

bool MenuWin::isEnterPressed() {

    if (_enterPressed) {
        _enterPressed = false;

        return true;
    }


    return false;
}

std::string MenuWin::timeScoreToString(){

    std::string timeScore;

    int minutes, seconds;

    minutes = int(_timeScore.asSeconds()) / 60;
    seconds = int(_timeScore.asSeconds()) % 60;

    if (minutes < 10){
        timeScore += "0";
        timeScore += std::to_string(minutes);
        timeScore += ":";
    }
    else{
        timeScore += std::to_string(minutes);
        timeScore += ":";
    }

    if (seconds < 10){
        timeScore += "0";
        timeScore += std::to_string(seconds);
    }
    else{
        timeScore += std::to_string(seconds);
    }


    return timeScore;

}

void MenuWin::changeVolume(){

    if (_sound.getVolume() != 0.0f){
        _sound.setVolume(0.0f);
    }
    else{
        _sound.setVolume(10.0f);
    }

}
