#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "windows.h"
#include <iostream>
#include <cstdlib>
///para no poner sf::

using namespace sf;
using namespace std;

class boton_rectangulo {
private:
    float esi[2],esd[2],eii[2],eid[2];
    RectangleShape boton;
    public:
        boton_rectangulo(float x,float y,float posx,float posy) {
        boton.setSize(Vector2f(x,y));
        esi[0]=posx;
        esi[1]=posy;
        esd[0]=posx+(x-1);
        esd[1]=posy;
        eii[0]=posx;
        eii[1]=posy+(y-1);
        eid[0]=posx+(x-1);
        eid[1]=posy+(y-1);
        boton.setPosition(esi[0],esi[1]);
        }
        int getEsix(){return esi[0];}
        int getEsdx(){return esd[0];}
        int getEiix(){return eii[0];}
        int getEidx(){return eid[0];}
        int getEsiy(){return esi[1];}
        int getEsdy(){return esd[1];}
        int getEiiy(){return eii[1];}
        int getEidy(){return eid[1];}
        RectangleShape getBoton() {return boton;}
};

///funciones hibridas con objetos

void mov_obj_abajo(CircleShape v[],int objeto,float velocidad_y)
{
    float y;
    y=v[objeto].getPosition().y+velocidad_y;
    v[objeto].setPosition(v[objeto].getPosition().x,y);
}

void mov_diagonal_izq_abajo(CircleShape *circulo,float velocidad_x, float velocidad_y)
{
    float x,y;
    x=circulo->getPosition().x-velocidad_x;
    y=circulo->getPosition().y+velocidad_y;
    circulo->setPosition(x,y);
}

void mov_obj_derecha(CircleShape v[],int objeto,float velocidad_x)
{
    float x;
    x=v[objeto].getPosition().x+velocidad_x;
    v[objeto].setPosition(x,v[objeto].getPosition().y);
}

void mov_diagonal_der_arriba (CircleShape *circulo,float velocidad_x,float velocidad_y)
{
    float x,y;
    x=circulo->getPosition().x+velocidad_x;
    y=circulo->getPosition().y-velocidad_y;
    circulo->setPosition(x,y);
}

void mov_derecha(CircleShape *v,int objeto,float velocidad_x)
{
    float x;
    x=v[objeto].getPosition().x+velocidad_x;
    v[objeto].setPosition(x,v[objeto].getPosition().y);
}

void mov_diagonal_der_abajo(CircleShape *circulo,float velocidad_x,float velocidad_y)
{
    float x,y;
    x=circulo->getPosition().x+velocidad_x;
    y=circulo->getPosition().y+velocidad_y;
    circulo->setPosition(x,y);
}

void mov_obj_izq(CircleShape v[],int objeto,float velocidad_x)
{
    float x;
    x=v[objeto].getPosition().x-velocidad_x;
    v[objeto].setPosition(x,v[objeto].getPosition().y);
}

void mov_obj_arriba(CircleShape *v,int objeto,float velocidad_y)
{
    float y;
    y=v[objeto].getPosition().y-velocidad_y;
    v[objeto].setPosition(v[objeto].getPosition().x,y);
}

int main()
{
    ///carga del mundo

    RenderWindow window(VideoMode(1000, 600), "Tower Defense - La defensa del fuerte nicomando");
    Texture textura_mapa,textura_circulo,textura_menu;
    if (!textura_mapa.loadFromFile("img/008.png"))
        return -1;
    if (!textura_circulo.loadFromFile("img/004.jpg"))
        return -1;
    if (!textura_menu.loadFromFile("img/006.jpg"))
        return -1;

    ///Zona de texto
    Font tipo_de_texto,tipo_de_texto1;
    if (!tipo_de_texto.loadFromFile("tipos_de_texto/OpenSans-Bold.ttf"))
        return -1;
    if (!tipo_de_texto1.loadFromFile("tipos_de_texto/OpenSans-BoldItalic.ttf"))
        return -1;
    Text texto_prueba,texto_variable;
    texto_prueba.setFont(tipo_de_texto);
    texto_prueba.setString("Imprimimos texto GENTEEE");
    texto_prueba.setCharacterSize(24);
    texto_variable.setFont(tipo_de_texto1);
    ///Zona de texto

    Sprite mapa,menu;
    mapa.setTexture(textura_mapa);
    menu.setTexture(textura_menu);
    int mousexy[2];
    ///Si gente, le puse MUSICA WEEEEE
    Music musica_menu,musica_juego;
    if (!musica_menu.openFromFile("musica/halo musica.ogg"))
        return -1;
    if (!musica_juego.openFromFile("musica/musica juego.ogg"))
        return -1;
    ///volumen de la musica del menu
    musica_menu.setVolume(15.f);
    musica_menu.setPlayingOffset(seconds(62.5f));
    musica_menu.play();
    musica_juego.setVolume(5.f);
    bool boolmusica=false;
    ///con esta variable se cambia la cantidad de monstruos en el mundo
    const int cantidad_objetos=1000;
    CircleShape v[cantidad_objetos];
    boton_rectangulo nueva_partida(237,38,351,316);
    ///vida de los monstruos-rango-daños
    int vidas[cantidad_objetos]={100};
    float opacidad_objetos[cantidad_objetos]= {0};
    CircleShape rango_prueba(150.f);
    rango_prueba.setFillColor(Color(24,81,213,100));
    rango_prueba.setPosition(130,378);
    int estados[cantidad_objetos]= {0};
    estados[0]=-1;
    float opacidad_menu=0; ///transparencia del objeto 255=100% porciento
    for (int i=0; i<=cantidad_objetos-1; i++)
    {
        v[i]=CircleShape(25.f);
        v[i].setTexture(&textura_circulo);
        v[i].setFillColor(Color(255,255,255,opacidad_objetos[i]));
        v[i].setPosition(285,0);
    }
    int objetos=1;
    int tiempo=1;

    ///Convertir una variable en un string, variable tiempo
    char tiempo_char[10];
    itoa(tiempo,tiempo_char,10);
    string tiempo_string = string(tiempo_char);
    texto_variable.setString(tiempo_string);
    texto_variable.setCharacterSize(25);
    texto_variable.setPosition(600,300);
    texto_variable.setFillColor(Color::Black);
    ///Setea el framerate a 60 fps, comentar para mas velocidad,seteado para ver la velocidad real del juego

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                musica_menu.stop();
                window.close();
            }
        }

        window.clear();

        for (int i=1; i<=objetos; i++)
        {
            if (estados[i-1]!=-1)
            {
                window.draw(mapa);
                window.draw(texto_variable);
                window.draw(rango_prueba);
                if (!boolmusica)
                {
                    musica_juego.play();
                    boolmusica=true;
                }
                for (int d=1; d<=objetos; d++)
                {
                    window.draw(v[d-1]);
                }
            }
            ///Pequeña maquina de estados
            switch (estados[i-1])
            {
            case -1:
                menu.setColor(Color(255,255,255,opacidad_menu));
                window.draw(menu);
                window.draw(texto_prueba);
                window.draw(nueva_partida.getBoton());
                if (opacidad_menu<255)
                {
                    opacidad_menu+=5;
                }
                else
                {
                    ///Configuracion de los botones en el menu principal
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        mousexy[0]=Mouse::getPosition(window).x;
                        mousexy[1]=Mouse::getPosition(window).y;
                        ///Nueva partida
                        if (mousexy[0]>=nueva_partida.getEsix()&&mousexy[0]<=nueva_partida.getEsdx()&&mousexy[1]>=nueva_partida.getEsdy()&&mousexy[1]<=nueva_partida.getEidy())
                        {
                            /*
                            volumen_menu-=0.1;
                            musica_menu.setVolume(volumen_menu);
                                */
                            musica_menu.stop();
                            estados[0]=0;
                        }
                        ///Cargar Partida
                        if (mousexy[0]>=281&&mousexy[0]<=469&&mousexy[1]>=377&&mousexy[1]<=414)
                        {

                        }
                        ///Salir
                        if (mousexy[0]>=281&&mousexy[0]<=469&&mousexy[1]>=437&&mousexy[1]<=474)
                        {
                            musica_menu.stop();
                            window.close();
                        }

                    }
                }
                break;
            case 0:
                if (v[i-1].getPosition().y<199&&v[i-1].getPosition().x==285)
                {
                    if(opacidad_objetos[i-1]<255)
                    {
                        opacidad_objetos[i-1]+=5;
                        v[i-1].setFillColor(Color(255,255,255,opacidad_objetos[i-1]));
                    }
                    mov_obj_abajo(v,i-1,0.5);
                }
                else
                    estados[i-1]=1;
                break;

            case 1:
                if (v[i-1].getPosition().x>47)
                {
                    mov_obj_izq(v,i-1,0.5);
                }
                else
                    estados[i-1]=2;
                break;
            case 2:
                if (v[i-1].getPosition().y<500)
                {
                    mov_obj_abajo(v,i-1,0.5);
                }
                else
                    estados[i-1]=3;
                break;
            case 3:
                if (v[i-1].getPosition().x<485)
                {
                    mov_derecha(v,i-1,0.5);
                }
                else
                    estados[i-1]=4;
                break;
            case 4:
                if (v[i-1].getPosition().y>177)
                {
                    mov_obj_arriba(v,i-1,0.5);
                }
                else
                    estados[i-1]=5;
                break;
            case 5:
                if (v[i-1].getPosition().x<700)
                {
                    mov_derecha(v,i-1,0.5);
                }
                else
                    estados[i-1]=6;
                break;
            case 6:
                if (opacidad_objetos[i-1]!=0)
                {
                    opacidad_objetos[i-1]-=5;
                    v[i-1].setFillColor(Color(255,255,255,opacidad_objetos[i-1]));
                    mov_derecha(v,i-1,0.5);
                }
                else
                    estados[i-1]=0;
                break;

                ///movimientos en diagonal
                /*
                case 1:
                    if (circulo1.getPosition().y>171&&circulo1.getPosition().x>35)
                    {
                        mov_diagonal_izq_abajo(&circulo1,0.1,0.038);

                    }
                    else
                        estado=2;
                    break;
                case 2:
                    if (circulo1.getPosition().x<35&&circulo1.getPosition().y<429)
                    {
                        mov_obj_abajo(v,objetos,0.1);

                    }
                    else
                        estado=10;
                    break;
                case 10:
                    if (circulo1.getPosition().y>429&&circulo1.getPosition().y<500)
                    {
                        mov_diagonal_der_abajo(&circulo1,0.1,0.1);
                    }
                    else
                        estado=3;
                    break;
                case 3:
                    break;
                case 4:
                    if (circulo1.getPosition().x>292&&circulo1.getPosition().x<570)
                    {
                        mov_diagonal_der_arriba(&circulo1,0.1,0.1);
                    }
                    else
                        estado=5;
                    break;
                case 5:
                    if(circulo1.getPosition().x<637)
                    {
                        mov_derecha(&circulo1,0.1);
                    }
                    else
                        estado=6;
                    break;
                case 6:
                    if (circulo1.getPosition().x>637&&circulo1.getPosition().x<700)
                    {
                        mov_derecha(&circulo1,0.1);
                        if(opacidad>0)
                        {
                            opacidad-=0.4;
                            circulo1.setFillColor(Color(255,255,255,opacidad));
                        }
                    }
                    else
                    {
                        circulo1.setPosition(290,0);
                        estado=0;
                    }
                    break;
                */
            }
        }
        if (tiempo%500==0)
        {
            if (objetos<cantidad_objetos)
            {
                objetos++;
                tiempo=1;
            }
        }
        if (estados[0]!=-1)
        {
            tiempo++;

            ///cada vez que se actualiza la variable se tiene que actualizar el string
            itoa(tiempo,tiempo_char,10);
            string tiempo_string = string(tiempo_char);
            texto_variable.setString(tiempo_string);
        }
        ///Pruebas iniciales con circulos
        /*
        window.draw(circulo1);
        if (circulo1.getPosition().x<600&&circulo1.getPosition().y<=0) {
        x=circulo1.getPosition().x+.1;
        circulo1.setPosition(x,circulo1.getPosition().y);
        }
        if (circulo1.getPosition().x>600&&circulo1.getPosition().y<400) {
        y=circulo1.getPosition().y+.1;
        circulo1.setPosition(circulo1.getPosition().x,y);
        }
        if (circulo1.getPosition().x>0&&circulo1.getPosition().y>400) {
        x=circulo1.getPosition().x-.1;
        circulo1.setPosition(x,circulo1.getPosition().y);
        }
        if (circulo1.getPosition().x<0&&circulo1.getPosition().y>0) {
        y=circulo1.getPosition().y-.1;
        circulo1.setPosition(circulo1.getPosition().x,y);
        }
        */
        window.display();
    }
    return 0;
}
