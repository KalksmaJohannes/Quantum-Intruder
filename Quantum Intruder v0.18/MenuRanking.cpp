#include "MenuRanking.h"


MenuRanking::MenuRanking(float width, float height) : _selectedItemIndex(0), _enterPressed(false) {

    getRankingInformation();

    _font.loadFromFile("resources/Fonts/Robot Crush.ttf");

    _tittle.setFont(_font);
    _tittle.setString("Ranking:");
    _tittle.setFillColor(sf::Color::Green);
    _tittle.setPosition(sf::Vector2f(width / 2, height / 10 * 1));
    _tittle.setCharacterSize(40);
    _tittle.setOrigin(_tittle.getLocalBounds().width / 2, _tittle.getLocalBounds().height / 2);

    sf::Text rank1("[1] " + _rankingInformation[0], _font);
    rank1.setPosition(sf::Vector2f(width / 2, height / 10 * 3));
    rank1.setOrigin(rank1.getLocalBounds().width / 2, rank1.getLocalBounds().height/2);
    _rankingItems.push_back(rank1);

    sf::Text rank2("[2] " + _rankingInformation[1], _font);
    rank2.setPosition(sf::Vector2f(width / 2, height / 10 * 4));
    rank2.setOrigin(rank2.getLocalBounds().width / 2, rank2.getLocalBounds().height/2);
    _rankingItems.push_back(rank2);

    sf::Text rank3("[3] " + _rankingInformation[2], _font);
    rank3.setPosition(sf::Vector2f(width / 2, height / 10 * 5));
    rank3.setOrigin(rank3.getLocalBounds().width / 2, rank3.getLocalBounds().height/2);
    _rankingItems.push_back(rank3);

    sf::Text rank4("[4] " + _rankingInformation[3], _font);
    rank4.setPosition(sf::Vector2f(width / 2, height / 10 * 6));
    rank4.setOrigin(rank4.getLocalBounds().width / 2, rank4.getLocalBounds().height/2);
    _rankingItems.push_back(rank4);

    sf::Text rank5("[5] " + _rankingInformation[4], _font);
    rank5.setPosition(sf::Vector2f(width / 2, height / 10 * 7));
    rank5.setOrigin(rank5.getLocalBounds().width / 2, rank5.getLocalBounds().height/2);
    _rankingItems.push_back(rank5);

    sf::Text goBack("Atras", _font);
    goBack.setFillColor(sf::Color::Red);
    goBack.setPosition(sf::Vector2f(width / 2, height / 10 * 9));
    goBack.setOrigin(goBack.getLocalBounds().width / 2, goBack.getLocalBounds().height/2);
    _menuItems.push_back(goBack);

    //Inicializar sonidos
    _soundBuffer.loadFromFile("resources/Audios/select.wav");
    _sound.setBuffer(_soundBuffer);
    _sound.setVolume(10.0f);

}

void MenuRanking::update(sf::RenderWindow& window, sf::Event event) {

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

void MenuRanking::draw(sf::RenderWindow& window) {

    window.draw(_background);

    window.draw(_tittle);

    for(auto& item: _rankingItems){
        window.draw(item);
    }

    for (auto& item : _menuItems) {
        window.draw(item);
    }

}

int MenuRanking::getSelectedItemIndex() {

    return _selectedItemIndex;

}

bool MenuRanking::isEnterPressed() {

    if (_enterPressed) {
        _enterPressed = false;

        return true;
    }


    return false;
}

void MenuRanking::getRankingInformation(){

    ArchivoRanking archivo("ranking.dat");
    Ranking ranking;

    for(int i=0; i<5; i++){
        ranking = archivo.leerRegistro(i);

        _rankingInformation[i] = ranking.getRankInformation();
    }

}

bool MenuRanking::isNewRecord(sf::Time timeScore){

    ArchivoRanking archivo("ranking.dat");
    Ranking ranking;


    ranking = archivo.leerRegistro(4);

    if (timeScore < ranking.getTimeScore()){
        return true;
    }


    return false;
}

void MenuRanking::sortRanking(Ranking vec[], int tam) {

    Ranking auxiliar;

    for (int i = 0; i < tam; i++) {
        auxiliar.cargar(vec[i].getName(), vec[i].getTimeScore());

        for (int j = i + 1; j < tam; j++){
            if (vec[j].getTimeScore() < vec[i].getTimeScore()){
                auxiliar.cargar(vec[i].getName(), vec[i].getTimeScore());

                vec[i].setTimeScore(vec[j].getTimeScore());
                vec[i].setName(vec[j].getName());

                vec[j].setTimeScore(auxiliar.getTimeScore());
                vec[j].setName(auxiliar.getName());
            }
        }
    }

}


void MenuRanking::updateRankingInformation(Ranking ranking){

    ArchivoRanking archivo("ranking.dat");
    Ranking rankingg[5];

    for(int i=0; i<5; i++){
        rankingg[i] = archivo.leerRegistro(i);
    }

    rankingg[4] = ranking;

    sortRanking(rankingg, 5);

    archivo.crearDesdeCero();

    for(int i=0; i<5; i++){
        archivo.grabarRegistro(rankingg[i]);
    }

    updateStrings();

}

void MenuRanking::updateStrings(){

    getRankingInformation();

    _rankingItems[0].setString("[1] " + _rankingInformation[0]);
    _rankingItems[1].setString("[2] " + _rankingInformation[1]);
    _rankingItems[2].setString("[3] " + _rankingInformation[2]);
    _rankingItems[3].setString("[4] " + _rankingInformation[3]);
    _rankingItems[4].setString("[5] " + _rankingInformation[4]);

}

void MenuRanking::changeVolume(){

    if (_sound.getVolume() != 0.0f){
        _sound.setVolume(0.0f);
    }
    else{
        _sound.setVolume(10.0f);
    }

}
