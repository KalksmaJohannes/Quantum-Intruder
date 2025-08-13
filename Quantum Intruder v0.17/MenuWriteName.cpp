#include "MenuWriteName.h"


MenuWriteName::MenuWriteName(float width, float height) : _selectedItemIndex(0), _enterPressed(false), _namePlayer(""){

    _font.loadFromFile("resources/Fonts/Robot Crush.ttf");

    _tittle.setFont(_font);
    _tittle.setString("Superaste un record!");
    _tittle.setFillColor(sf::Color::Green);
    _tittle.setPosition(sf::Vector2f(width / 2, height / 10 * 1));
    _tittle.setCharacterSize(60);
    _tittle.setOrigin(_tittle.getLocalBounds().width / 2, _tittle.getLocalBounds().height / 2);

    _prompt.setFont(_font);
    _prompt.setString("Escribe tu nombre para registrarlo en el ranking:");
    _prompt.setFillColor(sf::Color::Green);
    _prompt.setPosition(sf::Vector2f(width / 2, height / 3));
    _prompt.setCharacterSize(35);
    _prompt.setOrigin(_prompt.getLocalBounds().width / 2, _prompt.getLocalBounds().height / 2);

    _nameText.setFont(_font);
    _nameText.setString("_");
    _nameText.setFillColor(sf::Color::Cyan);
    _nameText.setPosition(sf::Vector2f(width / 2, height / 2));
    _nameText.setCharacterSize(50);
    _nameText.setOrigin(_nameText.getLocalBounds().width / 2, _nameText.getLocalBounds().height / 2);

    sf::Text goBackMenu("Continuar", _font);
    goBackMenu.setFillColor(sf::Color::Red);
    goBackMenu.setPosition(sf::Vector2f(width / 2, height / 10 * 9));
    goBackMenu.setOrigin(goBackMenu.getLocalBounds().width / 2, goBackMenu.getLocalBounds().height / 2);
    _menuItems.push_back(goBackMenu);

    //Inicializar sonidos
    _soundBufferNavigate.loadFromFile("resources/Audios/navigate.wav");
    _soundNavigate.setBuffer(_soundBufferNavigate);
    _soundNavigate.setVolume(10.0f);

    _soundBufferSelect.loadFromFile("resources/Audios/select.wav");
    _soundSelect.setBuffer(_soundBufferSelect);
    _soundSelect.setVolume(10.0f);

}

void MenuWriteName::update(sf::RenderWindow& window, sf::Event event){

    if (event.type == sf::Event::KeyPressed){
        switch (event.key.code){
            case sf::Keyboard::Return:
                _soundSelect.play();

                _enterPressed = true;
            break;

            default:

            break;
        }
    }

    if (event.type == sf::Event::TextEntered){
        if (event.text.unicode < 128){
            char enteredChar = static_cast<char>(event.text.unicode);

            if (enteredChar == 8 && !_namePlayer.empty()){
                _soundNavigate.play();

                _namePlayer.pop_back();
            }
            else if (enteredChar >= 32 && enteredChar <= 126 && static_cast<int>(_namePlayer.size()) < _maxLength){
                _soundNavigate.play();

                _namePlayer += enteredChar;
            }

            if (_namePlayer.empty()){
                _nameText.setString("_");
            }
            else{
                _nameText.setString(_namePlayer + "_");
            }

            _nameText.setOrigin(_nameText.getLocalBounds().width / 2, _nameText.getLocalBounds().height / 2);
        }
    }

}

void MenuWriteName::draw(sf::RenderWindow& window){

    window.draw(_background);
    window.draw(_tittle);
    window.draw(_prompt);
    window.draw(_nameText);

    for (auto& item : _menuItems){
        window.draw(item);
    }

}

int MenuWriteName::getSelectedItemIndex(){

    return _selectedItemIndex;

}

std::string MenuWriteName::getName(){

    return _namePlayer;

}

void MenuWriteName::clearName(){

    _namePlayer = "";

}

bool MenuWriteName::isEnterPressed(){

    if (_enterPressed){
        _enterPressed = false;

        return true;
    }


    return false;
}

void MenuWriteName::changeVolume(){

    if (_soundNavigate.getVolume() != 0.0f){
        _soundNavigate.setVolume(0.0f);
        _soundSelect.setVolume(0.0f);
    }
    else{
        _soundNavigate.setVolume(10.0f);
        _soundSelect.setVolume(10.0f);
    }

}
