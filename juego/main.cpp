#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "windows.h"
#include <iostream>
#include <cstdlib>
///para no poner sf::

using namespace sf;
using namespace std;

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

    RenderWindow window(VideoMode(800, 600), "TOWER DEFENSE");
    Texture textura,texturacirculo,texturamenu;
    if (!textura.loadFromFile("img/007.png"))
        return EXIT_FAILURE;
    if (!texturacirculo.loadFromFile("img/004.jpg"))
        return EXIT_FAILURE;
    if (!texturamenu.loadFromFile("img/006.jpg"))
        return EXIT_FAILURE;
    Sprite sprite,sprite1;
    sprite.setTexture(textura);
    sprite1.setTexture(texturamenu);
    ///Si gente, le puse MUSICA WEEEEE
    Music music;
    if (!music.openFromFile("musica/halo musica.ogg")) return -1;
    music.play();
    ///con esta variable se cambia la cantidad de mounstruos en el mundo
    int cantidad_objetos=10;
    CircleShape v[cantidad_objetos];
    float opacidad_objetos[cantidad_objetos]={0};
    int estados[cantidad_objetos]= {0};
    estados[0]=-1;
    float opacidad_menu=0; ///transparencia del objeto 255=100% porciento
    for (int i=0; i<=cantidad_objetos-1; i++)
    {
        v[i]=CircleShape(25.f);
        v[i].setTexture(&texturacirculo);
        v[i].setFillColor(Color(255,255,255,opacidad_objetos[i]));
        v[i].setPosition(285,0);
    }
    int objetos=1;
    int tiempo=1;
    float x=0,y=0;
    ///Setea el framerate a 60 fps, comentado para mas velocidad,se setea para q no haya lag
    /*
    window.setFramerateLimit(60);
    */
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();

        for (int i=1; i<=objetos; i++)
        {
            if (estados[i-1]!=-1)
            {
                window.draw(sprite);
                for (int d=1; d<=objetos; d++)
                {
                    window.draw(v[d-1]);
                }
            }
            ///Pequeña maquina de estados
            switch (estados[i-1])
            {
            case -1:
                sprite1.setColor(Color(255,255,255,opacidad_menu));
                window.draw(sprite1);
                if (opacidad_menu<255)
                {
                    opacidad_menu+=5;
                }
                else
                {
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        if (Mouse::getPosition(window).x>=281&&Mouse::getPosition(window).x<=469&&Mouse::getPosition(window).y>=316&&Mouse::getPosition(window).y<=353)
                            estados[0]=0;
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

    ///debug de variables en la terminal-no darle bola al warning
    cout<<x<<endl;
    cout<<y<<endl;
    system("pause");
    return 0;
}
