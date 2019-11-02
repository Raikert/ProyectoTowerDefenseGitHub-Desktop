#ifndef MOVIMIENTOS_H_INCLUDED
#define MOVIMIENTOS_H_INCLUDED

using namespace std;
using namespace sf;
using namespace Collision;

///funciones hibridas con objetos

void mov_obj_abajo(Sprite v[],int objeto,float velocidad_y)
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

void mov_derecha(Sprite *v,int objeto,float velocidad_x)
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

void mov_obj_izq(Sprite v[],int objeto,float velocidad_x)
{
    float x;
    x=v[objeto].getPosition().x-velocidad_x;
    v[objeto].setPosition(x,v[objeto].getPosition().y);
}

void mov_obj_arriba(Sprite *v,int objeto,float velocidad_y)
{
    float y;
    y=v[objeto].getPosition().y-velocidad_y;
    v[objeto].setPosition(v[objeto].getPosition().x,y);
}

#endif // MOVIMIENTOS_H_INCLUDED
