#ifndef COLISION_DANIO_H_INCLUDED
#define COLISION_DANIO_H_INCLUDED

/*
    /// Creacion de el texto vida ----------------------------------------
    Font tipo_texto_vida;
    if (!tipo_texto_vida.loadFromFile("tipos_de_texto/OpenSans-BoldItalic.ttf"))
        return -1;
    Text texto_vida[cantidad_bichos];
    for (i=0; i<cantidad_bichos; i++)
    {
        texto_vida[i].setFont(tipo_texto_vida);
    }

    ///vida de los monstruos-rango-daños
    float vida[cantidad_bichos];
    int vida_m[cantidad_bichos]= {1000};
    bool danio[cantidad_bichos];
    ponerEnCienVidas(vida, cantidad_bichos, 100);
    ponerEnFalso(danio, cantidad_bichos);

    ///vida flotante
    char vida_char[10];
    itoa(vida_m[0], vida_char, 10);
    string vida_string=string(vida_char);
    for (i=0; i<cantidad_bichos; i++)
    {
        texto_vida[i].setString(vida_string);
        texto_vida[i].setCharacterSize(13);
        texto_vida[i].setFillColor(Color::Black);
    }

    if (vida[d-1]>=0)
                    {
                        /// SI COLISIONA VE SI HAY ALGUIEN RECIBIENDO DAÑO, SINO, RECIBE DAÑO
                        if (PixelPerfectTest(v[d-1],rango_prueba))
                        {
                            v[d-1].setColor(Color(145,50,77,opacidad_bichos[d-1]));
                            /// Se encarga de verificar si hay alguien recibiendo daño
                            danio[d-1] = verificarDanio(danio, cantidad_bichos);
                            /// Si el monstruo esta recibiendo daño le saca vida
                            if (danio[d-1]==true)
                            {
                                vida[d-1]-=0.1;
                                if (tiempo%50==0)
                                {
                                    vida_m[d-1]-=2;
                                    itoa(vida_m[d-1],vida_char,10);
                                    vida_string = string(vida_char);
                                    texto_vida[d-1].setString(vida_string);
                                }
                            }
                        }
                        /// SI YA NO COLISIONA PONE EN FALSO EL RECIBIR DAÑO
                        else
                        {
                            v[d-1].setColor(Color(255,255,255,opacidad_bichos[d-1]));
                            danio[d-1]=false;
                        }

                        texto_vida[d-1].setPosition(v[d-1].getPosition().x+10, v[d-1].getPosition().y+25);
                        window.draw(v[d-1]);
                        window.draw(texto_vida[d-1]);
                    }
                    else
                    {
                        danio[d-1]=false;
                    }
                */

void ponerEnCienVidas(float *vidas, int cantidad_bichos, int tamanio)
{
    for (int x=0; x<cantidad_bichos; x++)
    {
        vidas[x]=tamanio;
    }
}

void ponerEnFalso(bool *danio, int cantidad_bichos)
{
    for (int x=0; x<cantidad_bichos; x++)
    {
        danio[x]=false;
    }
}

bool verificarDanio(bool *danio, int cantidad_bichos)
{
    for (int x=0; x<cantidad_bichos; x++)
    {
        if (danio[x]==true)
        {
            return false;
        }
    }
    return true;
}

#endif // COLISION_DANIO_H_INCLUDED
