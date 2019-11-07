#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

using namespace std;
using namespace sf;
using namespace Collision;
/*
setlocale(LC_ALL,"spanish");
*/

/// CLASE COLA --------------------------------------------------------------
class Cola
{
private:
    int punto_inicio, punto_fin, tamanio;
    int *cola_dinamica;
public:
    Cola(int);
    ~Cola()
    {
        delete cola_dinamica;
    }
    bool agregar(int);
    bool sacar(int &);
};

Cola::Cola(int t=0)
{
    tamanio=t;
    cola_dinamica=new int[tamanio];
    if (cola_dinamica==NULL)
    {
        exit(1);
    }
    punto_inicio=punto_fin=0;
}

bool Cola::agregar(int x)
{
    if (punto_fin=tamanio)
        return false;
    cola_dinamica[punto_fin]=x;
    punto_fin++;
    return true;
}

bool Cola::sacar(int &x)
{
    if (punto_inicio==punto_fin) return false;
    x=cola_dinamica[punto_inicio];
    punto_inicio++;
    return true;
}
/// ------------------------------------------------------------------------------------


/// CLASE TEXTO
class Texto
{
private:
    Font formato_de_letra;
    Text texto;
    bool formato_cargado;
public:
    Texto (const string& letra="tipos_de_texto/OpenSans-BoldItalic.ttf",int variable=0,int tamanio=0,float x=0,float y=0,const Color& color=Color(0,0,0,0))
    {
        if (!formato_de_letra.loadFromFile(letra))
            formato_cargado=false;
        else
            formato_cargado=true;

        if (formato_cargado)
        {
            texto.setFont(formato_de_letra);
            texto.setCharacterSize(tamanio);
            texto.setPosition(x,y);
            char variable_char[10];
            itoa(variable, variable_char, 10);
            string variable_string = string(variable_char);
            texto.setString(variable_string);
            texto.setFillColor(color);
        }
    }
    void setFormato_de_letra (const string& letra)
    {
        if (!formato_de_letra.loadFromFile(letra))
            formato_cargado=false;
        else
            formato_cargado=true;
    }
    bool getConfirmacion()
    {
        return formato_cargado;
    }
    Text getTexto()
    {
        return texto;
    }

    void setVariable (int variable)
    {
        char variable_char[10];
        itoa(variable, variable_char, 10);
        string variable_string = string(variable_char);
        texto.setString(variable_string);
    }
    void setColor(const Color& color)
    {
        texto.setFillColor(color);
    }
    void setPosicion (float x,float y)
    {
        texto.setPosition(x,y);
    }
    void setTransparencia(float t)
    {
        texto.setFillColor(Color(0,0,0,t));
    }
};

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

/*

class Coordenada{
    float x, y;
    public:


};

Coordenada si, sd, ii, id;
si.getX()

*/
class Boton
{
private:
    float esi[2],esd[2],eii[2],eid[2];
    RectangleShape boton;
    int tamaniox,tamanioy;
public:
    Boton(float x=0,float y=0,float posx=0,float posy=0,int transparencia=0)
    {
        boton.setSize(Vector2f(x,y));
        esi[0]=posx;
        esi[1]=posy;
        esd[0]=posx+(x-1);
        esd[1]=posy;
        eii[0]=posx;
        eii[1]=posy+(y-1);
        eid[0]=posx+(x-1);
        eid[1]=posy+(y-1);
        boton.setPosition(posx,posy);
        boton.setFillColor(Color(255,255,255,transparencia));
        tamaniox=x;
        tamanioy=y;
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
