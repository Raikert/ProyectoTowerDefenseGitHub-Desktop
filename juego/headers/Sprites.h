#ifndef SPRITES_H_INCLUDED
#define SPRITES_H_INCLUDED

void cargar_vector_sprites (Sprite *v,Sprite sprite,int cantidad_bichos)
{
    for (int i=0; i<=cantidad_bichos-1; i++)
    {
        v[i]=sprite;
    }
}

#endif // SPRITES_H_INCLUDED
