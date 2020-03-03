#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "windows.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
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



///Mensaje para los que quieren adentrarse en este proyecto, primero que nada, este es un proyecto
///compartido, es decir, que no lo hice solo, un compañero muy especial llamado Nicolas Rodriguez
///me ayudo mucho en gran parte del escenario creativo y el backstague de cosas muy complicadas que
///sin su gran capacidad de imaginacion, cosas como las torres, menues , y graficas no existirian
///o al menos no serian lo que son, la idea no es de ninguno de nosotros dos, es de un tercer compañero,
///que lamentablemente no pudo participar mucho en lo que concierne a lo que es desarrollo de codigo,
///no es para culpar a nadie, es para que los que se adentren en este proyecto tengan en cuenta, que hacer
///algo de esta envergadura no es tarea sencilla y requiere de mucha voluntad para llevarse a cabo, aun asi
///todo puede lograrse si uno se siente capaz de lograrlo, como yo con muchas cosas que si se animan a leer
///veran que fueron todos pequeños descubrimientos que fuimos haciendo a medida que trabajabamos en ello.
///Para los que sean muy expertos en este tema de la programacion, les propongo echarle un ojo y juzgar a su criterio
///que hicimos bien, mal y que ojala les llegue a sorprender algo de esto dado que somos de los mas creidos en saber
///que codeamos demasiado bien, mas cuando nos enfocamos en resumir codigo. Asi que no se queden atras, hagan volar
///sus alas de la mente y den rienda suelta a sus mas profundos deseos de lograr algo en codigo, que se que lo van a lograr
///porque yo lo logre con este proyecto.

///Quiero seguir en el anonimato a pesar de que ya muchos sabran quien escribe pero, es todo mejor cuando el que te lo narra,
///es alguien que indirectamente te hace pensar que nunca estuvo ahi, pero que siempre lo estara dejando comentarios como estos.
///saludos, y suerte a todo aquel que intente nadar por las profundas aguas de nuestro mundo.
