#ifndef COLISION_DANIO_H_INCLUDED
#define COLISION_DANIO_H_INCLUDED

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
