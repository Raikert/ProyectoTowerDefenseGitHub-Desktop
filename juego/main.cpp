#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "windows.h"
#include <iostream>
#include <cstdlib>
#include "Collision.hpp"
#include "Clases.h"
using namespace sf; ///para no poner sf::
using namespace std;
using namespace Collision; ///para no poner Collision::
#include "headers/Movimientos.h"
#include "headers/Colision_Danio.h"
#include "headers/Sprites.h"
#include "headers/Juego.h"

int main()
{
    ///puede devolver tanto un 0 si el programa termino bien, como otro valor
    ///xq sino nunca sabriamos si un archivo se cargo correctamente, que main mas chiquito ajajaj
    return juego();
}
