#include "Ranking.h"


Ranking::Ranking(){}

Ranking::Ranking(const char namePlayer[], sf::Time timeScore){

    strcpy(_namePlayer, namePlayer);
    _timeScore = timeScore;

}

void Ranking::setTimeScore(sf::Time timeScore){

    _timeScore = timeScore;

}

void Ranking::setName(std::string name){

    strcpy(_namePlayer, name.c_str());

}

sf::Time Ranking::getTimeScore(){

    return _timeScore;

}

std::string Ranking::getName(){

    return _namePlayer;

}

void Ranking::cargar(std::string namePlayer, sf::Time timeScore){

    strcpy(_namePlayer, namePlayer.c_str());

    setTimeScore(timeScore);

}

std::string Ranking::getRankInformation(){

    std::string rankName = std::string(_namePlayer), rankTimeScore = "      ";

    int minutes, seconds;

    minutes = int(_timeScore.asSeconds()) / 60;
    seconds = int(_timeScore.asSeconds()) % 60;

    if (minutes < 10){
        rankTimeScore += "0";
        rankTimeScore += std::to_string(minutes);
        rankTimeScore += ":";
    }
    else{
        rankTimeScore += std::to_string(minutes);
        rankTimeScore += ":";
    }

    if (seconds < 10){
        rankTimeScore += "0";
        rankTimeScore += std::to_string(seconds);
    }
    else{
        rankTimeScore += std::to_string(seconds);
    }


    return rankName + rankTimeScore;

}
