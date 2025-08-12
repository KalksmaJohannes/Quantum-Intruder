#pragma once

#include <string.h>
#include "Ranking.h"


class ArchivoRanking{

    private:
        char _nombre[50];

        int _tamVar = sizeof(Ranking);


    public:
        ArchivoRanking(const char nombre[]);

        bool crearDesdeCero();

        bool grabarRegistro(Ranking registro);

        bool listarRegistros();

        int buscarLegajo(int legajo);

        Ranking leerRegistro(int posRegistro);

        int contarRegistros();
};
