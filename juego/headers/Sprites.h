#ifndef SPRITES_H_INCLUDED
#define SPRITES_H_INCLUDED

void cargar_vector_sprites (Zombie *v,Zombie &tipo,int cantidad_bichos)
{
    for (int i=0; i<cantidad_bichos; i++)
    {
        v[i]=tipo;
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
