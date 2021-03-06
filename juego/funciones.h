#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <clocale>

using namespace std;

/*
setlocale(LC_ALL,"spanish");
*/

///Antiguas funciones de la cola tridimensional, fuera de uso,
///dada su incapacidad para recibir dinamicamente la cola.

/*
void inicializar_colas_torres_3d(int m[9][3][11],int valor)
{
    int f,c,x;

    for (f=0; f<9; f++)
    {
        for (c=0; c<3; c++)
        {
            m[f][c][10]=0;
            for (x=0; x<10; x++)
            {
                m[f][c][x]=valor;
            }
        }
    }
}
*/

/*
void ordenar_cola_3d(int m[9][3][11],int torre,int tipo,int enemigo_sacar,int cantidad_bichos)
{
    int pos_enemigo_siguiente,pos_enemigo_sacar;
    for (int i=0; i<cantidad_bichos; i++)
    {
        if (m[torre][tipo][i]==enemigo_sacar)
            pos_enemigo_sacar=i;
    }
    pos_enemigo_siguiente=pos_enemigo_sacar+1;
    for (int i=pos_enemigo_sacar ; i<cantidad_bichos; i++)
    {
        m[torre][tipo][i]=m[torre][tipo][pos_enemigo_siguiente];
        pos_enemigo_siguiente++;
    }
    m[torre][tipo][9]=-10000;
}
*/

/*
bool detectar_enemigo_cola3d (int m[9][3][11],int torre,int tipo,int enemigo_detectar,int cantidad_bichos)
{
    bool detector=false;
    for (int i=0; i<cantidad_bichos; i++)
    {
        if (m[torre][tipo][i]==enemigo_detectar)
            detector=true;
    }
    return detector;
}
*/

void DAR_VUELTA_LAS_BARRAS (char *cadena)
{
    for (int i=1; i<=100; i++)
    {
        if (cadena[i]!='\0')
        {
            if (cadena[i]==char(92))
                cadena[i]='/';
        }
    }
}

void escribir_cadena(char* cadena, const string & msj)
{
    /*
    char cadena2[100];
    strcpy(cadena2,msj.c_str());
    strcpy(cadena,cadena2);
    */
    strcpy(cadena,msj.c_str());
}

bool detectar_otro_menu_abierto (bool *v,int posiciones_torres)
{
    bool detector=true;
    for (int i=0; i<posiciones_torres; i++)
    {
        if (v[i]==true)
            detector=false;
    }
    return detector;
}

void inicializar_vector_entero (int *v,int tamanio,int valor)
{
    for (int i=0; i<tamanio; i++)
    {
        v[i]=valor;
    }
}

void inicializar_vector_bool (bool *v,int tamanio,bool valor)
{
    for (int i=0; i<tamanio; i++)
    {
        v[i]=valor;
    }
}

void inicializar_matriz_encolado(bool v[9][3],bool valor=false)
{
    int f,c;
    for (f=0; f<9; f++)
    {
        for (c=0; c<3; c++)
        {
            v[9][3]=valor;
        }
    }
}

#endif // FUNCIONES_H_INCLUDED
