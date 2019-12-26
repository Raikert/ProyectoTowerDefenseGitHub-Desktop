#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "windows.h"
#include <iostream>
#include <cstdlib>
#include "Collision.hpp"
using namespace sf; //para no poner sf::
using namespace std;
using namespace Collision; //para no poner Collision::
#include "funciones.h"
#include "Clases.h"
#include "headers/Movimientos.h"
#include "headers/Colision_Danio.h"
#include "headers/Sprites.h"
#include "headers/Juego.h"

int main()
{
    //puede devolver tanto un 0 si el programa termino bien, como otro valor,
    //sino nunca sabriamos si un archivo se cargo correctamente, matamos todos los pajaros con un solo return jeje.
    return juego();
}

/// No tengo palabras, solo veo lo que hicimos hasta ahora ,
///estoy muy orgulloso de todos nosotros, la idea, el empeño
///que le ponemos cada dia a todo, y solo pienso en aquella idea
///de fede que comenzo todo este proyecto, que nos impulso a ser mas
///que unos simples programadores, jamas voy a olvidar esto,
///no esta a la altura de muchos tower defense pero, con tan solo ver como
///funciona todo, me hace sentir que el esfuerzo que todos hacemos a la larga
///vale la pena, y a pesar de que dejemos cosas para mas tarde, como es mi caso con Arso,
///no siento remordimientos cuando aprendo algo nuevo cada dia sobre este mundo tan maravilloso
///que es programar.
