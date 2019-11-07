#ifndef SPRITES_H_INCLUDED
#define SPRITES_H_INCLUDED

using namespace std;
using namespace sf;
using namespace Collision;

void cargar_vector_sprites (Sprite *v,Sprite sprite,int cantidad_bichos)
{
    for (int i=0; i<=cantidad_bichos-1; i++)
    {
        v[i]=sprite;
    }
}

/** EJEMPLO DE LA CARGA DE BICHOS DIFERENTES CON UN FOR LLAMANDO A LA FUNCION
void cargar_vector_sprites (Sprite *v,int tipo, int pos)
{
    switch(tipo)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    }
    v[pos]=sprite;
}
*/

#endif // SPRITES_H_INCLUDED
