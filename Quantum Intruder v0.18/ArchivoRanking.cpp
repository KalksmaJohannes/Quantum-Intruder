#include "ArchivoRanking.h"


ArchivoRanking::ArchivoRanking(const char nombre[] = "ranking.dat"){

    strcpy(_nombre, nombre);

    if(contarRegistros() == -1){
        for(int i=0; i<5; i++){
            Ranking ranking("-----", sf::seconds(3599));

            grabarRegistro(ranking);
        }
    }

}

bool ArchivoRanking::crearDesdeCero(){

    FILE* ranking = fopen(_nombre, "wb");


    if (ranking == nullptr) return false;

    fclose(ranking);


    return true;

}


bool ArchivoRanking::grabarRegistro(Ranking registro){

    FILE *ranking;
    int escribio;


    ranking = fopen(_nombre, "ab");

    if (ranking == nullptr) return false;

    escribio = fwrite(&registro, _tamVar, 1, ranking);

    fclose(ranking);


    return escribio;
}

Ranking ArchivoRanking::leerRegistro(int posRegistro){

    Ranking registro;
    FILE *ranking;


    ranking = fopen(_nombre, "rb");

    if (ranking == nullptr) return registro;

    fseek(ranking, posRegistro*_tamVar, 0);

    fread(&registro, _tamVar, 1, ranking);

    fclose(ranking);


    return registro;
}

int ArchivoRanking::contarRegistros(){

    FILE *ranking;
    int cantBytes;


    ranking = fopen(_nombre, "rb");

    if(ranking == nullptr) return -1;

    fseek(ranking, 0, 2);

    cantBytes = ftell(ranking);

    fclose(ranking);


    return cantBytes / _tamVar;
}
