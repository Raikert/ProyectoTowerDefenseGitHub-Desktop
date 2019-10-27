#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "windows.h"
#include <iostream>
#include <cstdlib>
#include <clocale>
#include "Collision.hpp"

using namespace std;
using namespace sf;
using namespace Collision;
/*
setlocale(LC_ALL,"spanish");
*/

class Sprites
{
private:
    Texture camino_textura_propiedad;
    bool textura_cargada;
    Sprite  camino_sprite_propiedad;
public:
    Sprites (const string& nombre_imagen)
    {
        if(!CreateTextureAndBitmask(camino_textura_propiedad,nombre_imagen))
            textura_cargada=false;
        else
            textura_cargada=true;
        if (textura_cargada)
        {
            camino_sprite_propiedad.setTexture(camino_textura_propiedad);
            camino_sprite_propiedad.setColor(Color(255,255,255,0));
        }
    }
    Sprites (const string& nombre_imagen,float *opacidad_bicho,float x,float y)
    {

        if(!CreateTextureAndBitmask(camino_textura_propiedad,nombre_imagen))
            textura_cargada=false;
        else
            textura_cargada=true;
        if (textura_cargada)
        {
            camino_textura_propiedad.setSmooth(true);
            camino_sprite_propiedad.setTexture(camino_textura_propiedad);
            camino_sprite_propiedad.setColor(Color(255,255,255,opacidad_bicho[0]));
            camino_sprite_propiedad.setPosition(x,y);
        }
    }
    Sprite getSprite()
    {
        return camino_sprite_propiedad;
    }
    void setSprite(Sprite s)
    {
        camino_sprite_propiedad=s;
    }
    bool getConfirmacion()
    {
        return textura_cargada;
    }
};

class Monstruo
{
private:
    Sprite bicho;
    int vida,danio;
    float velocidad;
public:
    Sprite getBicho()
    {
        return bicho;
    }
    int getVida()
    {
        return vida;
    }
    int getDanio()
    {
        return danio;
    }
    float getVelocidad()
    {
        return velocidad;
    }
    void setVida (int v)
    {
        vida=v;
    }
    void setDanio (int d)
    {
        danio=d;
    }
    void setVelocidad (float ve)
    {
        velocidad=ve;
    }
    void setSprite (Sprite b)
    {
        bicho=b;
    }
};

class Boton
{
private:
    float esi[2],esd[2],eii[2],eid[2];
    RectangleShape boton;
public:
    Boton(float x,float y,float posx,float posy,int transparencia=0)
    {
        boton.setSize(Vector2f(x,y));
        boton.setPosition(posx,posy);
        esi[0]=boton.getPosition().x;
        esi[1]=boton.getPosition().y;
        esd[0]=boton.getPosition().x+(x-1);
        esd[1]=boton.getPosition().y;
        eii[0]=boton.getPosition().x;
        eii[1]=boton.getPosition().y+(y-1);
        eid[0]=boton.getPosition().x+(x-1);
        eid[1]=boton.getPosition().y+(y-1);
        boton.setFillColor(Color(255,255,255,transparencia));
    }
    int getEsix()
    {
        return esi[0];
    }
    int getEsdx()
    {
        return esd[0];
    }
    int getEiix()
    {
        return eii[0];
    }
    int getEidx()
    {
        return eid[0];
    }
    int getEsiy()
    {
        return esi[1];
    }
    int getEsdy()
    {
        return esd[1];
    }
    int getEiiy()
    {
        return eii[1];
    }
    int getEidy()
    {
        return eid[1];
    }
    RectangleShape getBoton()
    {
        return boton;
    }
    void setTransparencia(int t)
    {
        boton.setFillColor(Color(255,255,255,t));
    }
};

#endif // CLASES_H_INCLUDED
