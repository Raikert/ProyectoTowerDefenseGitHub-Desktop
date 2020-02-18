#ifndef SPRITES_H_INCLUDED
#define SPRITES_H_INCLUDED

void cargar_vector_sprites (Zombie *v,Zombie &tipo,int cantidad_bichos,int oleada=1,int nivel=1,int vida_aumentada=0)
{
    int r;
    for (int i=0; i<cantidad_bichos; i++)
    {
        if (oleada<4)                     //sistema de dificultad por oleadas
            r=rand()% (2)+1;
        else
        {
            if (oleada<8)
                r=rand()% (3)+1;
            else
            {
                if (oleada<12)
                    r=rand()% (4)+1;
                else
                {
                    if (oleada<16)
                        r=rand()% (5)+1;
                    else
                    {
                        if (oleada<20)
                            r=rand()% (6)+1;
                        else
                        {
                            if (oleada<24)
                                r=rand()% (7)+1;
                            else
                            {
                                r=rand()% (8)+1;
                            }
                        }
                    }
                }
            }
        }

        /* ///sistema de dificultad por niveles.

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

        */

        tipo.cambiar_zombie(r);
        v[i]=tipo;
        switch (r)
        {
        case 1:
            v[i].setVida(tipo.getVida()+100);
            v[i].setVelocidad(0.8);
            break;
        case 2:
            v[i].setVida(tipo.getVida()+150);
            v[i].setVelocidad(1.5);
            break;
        case 3:
            v[i].setVida(tipo.getVida()+100);
            v[i].setVelocidad(1);
            break;
        case 4:
            v[i].setVida(tipo.getVida()+100);
            v[i].setVelocidad(1.3);
            break;
        case 5:
            v[i].setVida(tipo.getVida()+200);
            v[i].setVelocidad(0.8);
            break;
        case 6:
            v[i].setVida(tipo.getVida()+300);
            v[i].setVelocidad(0.7);
            break;
        case 7:
            v[i].setVida(tipo.getVida()+400);
            v[i].setVelocidad(0.6);
            break;
        case 8:
            v[i].setVida(tipo.getVida()+500);
            v[i].setVelocidad(0.5);
            break;
        default:
            break;
        }
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
