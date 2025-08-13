#include "MenuInstructions.h"


MenuInstructions::MenuInstructions(float width, float height) : _selectedItemIndex(0), _enterPressed(false) {

    _font.loadFromFile("resources/Fonts/Robot Crush.ttf");

    _tittle.setFont(_font);
    _tittle.setString("Instrucciones:");
    _tittle.setFillColor(sf::Color::Green);
    _tittle.setPosition(sf::Vector2f(width / 2, 50));
    _tittle.setCharacterSize(40);
    _tittle.setOrigin(_tittle.getLocalBounds().width / 2, _tittle.getLocalBounds().height / 2);

    _paragraph.setFont(_font);
    _paragraph.setString("En Quantum Intruder, controlas a nanobots encargados de hackear distintas \n\nterminales en busca de informacion valiosa. Estas terminales se encuentran llenas de \n\nobstaculos gracias a su sofisticado antivirus. Pero no te preocupes, ya que contaras con 3 \n\nnanobots en cada nivel, de los cuales solo podras usar uno a la vez. Cada vez que un \n\nnanobot muera, aparecera un nuevo nanobot dispuesto a continuar la mision de su \n\nantecesor. A pesar de que perder un nanobot pueda sonar malo, realmente es una gran \n\nventaja para los proximos nanobots, ya que podran usar a los nanobots ca¡dos como \n\nnuevas plataformas, y de esa forma llegar a lugares que hubieran sido imposibles \n\nde alcanzar de no ser por los nanobots que se sacrificaron.");
    _paragraph.setFillColor(sf::Color::Yellow);
    _paragraph.setPosition(sf::Vector2f(width / 2, 340));
    _paragraph.setCharacterSize(25);
    _paragraph.setOrigin(_paragraph.getLocalBounds().width / 2, _paragraph.getLocalBounds().height/2);

    sf::Text goBack("Atras", _font);
    goBack.setFillColor(sf::Color::Red);
    goBack.setPosition(sf::Vector2f(width / 2, height / 4 * 3.5));
    goBack.setOrigin(goBack.getLocalBounds().width / 2, goBack.getLocalBounds().height/2);
    _menuItems.push_back(goBack);

    //Inicializar sonido
    _soundBuffer.loadFromFile("resources/Audios/select.wav");
    _sound.setBuffer(_soundBuffer);
    _sound.setVolume(10.0f);

}

void MenuInstructions::update(sf::RenderWindow& window, sf::Event event) {

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

void MenuInstructions::draw(sf::RenderWindow& window) {

    window.draw(_background);

    window.draw(_tittle);

    window.draw(_paragraph);

    for (auto& item : _menuItems) {
        window.draw(item);
    }

}

int MenuInstructions::getSelectedItemIndex() {

    return _selectedItemIndex;

}

bool MenuInstructions::isEnterPressed() {

    if (_enterPressed) {
        _enterPressed = false;

        return true;
    }


    return false;
}

void MenuInstructions::changeVolume(){

    if (_sound.getVolume() != 0.0f){
        _sound.setVolume(0.0f);
    }
    else{
        _sound.setVolume(10.0f);
    }

}
