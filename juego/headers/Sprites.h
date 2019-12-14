#ifndef SPRITES_H_INCLUDED
#define SPRITES_H_INCLUDED

void cargar_vector_sprites (Zombie *v,Zombie &tipo,int cantidad_bichos,int oleada=1,int nivel=1)
{
    int r;
    for (int i=0; i<cantidad_bichos; i++)
    {
        switch(nivel)
        {
        case 1:
            r=rand()% (4)+1;
            break;
        case 2:
            r=rand()% (5)+1;
            break;
        case 3:
            r=rand()% (6)+1;
            break;
        case 4:
            r=rand()% (7)+1;
            break;
        case 5:
            r=rand()% (8)+1;
            break;
        default:
            break;
        }
        tipo.cambiar_zombie(r);
        switch (r)
        {
        case 1:
            tipo.setVida(100);
            tipo.setVelocidad(0.8);
            break;
        case 2:
            tipo.setVida(150);
            tipo.setVelocidad(1.5);
            break;
        case 3:
            tipo.setVida(100);
            tipo.setVelocidad(1);
            break;
        case 4:
            tipo.setVida(100);
            tipo.setVelocidad(1.3);
            break;
        case 5:
            tipo.setVida(200);
            tipo.setVelocidad(0.8);
            break;
        case 6:
            tipo.setVida(300);
            tipo.setVelocidad(0.7);
            break;
        case 7:
            tipo.setVida(400);
            tipo.setVelocidad(0.6);
            break;
        case 8:
            tipo.setVida(500);
            tipo.setVelocidad(0.5);
            break;
        default:
            break;
        }
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
