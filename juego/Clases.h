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
    Cola () {}
    bool agregar(int);
    bool sacar(int &);
};

Cola::Cola(int t)
{
    tamanio=t;
    cola_dinamica=new int[tamanio];
    for (int i=0; i<tamanio; i++)
    {
        cola_dinamica[i]=10000;
    }
    if (cola_dinamica==NULL)
    {
        exit(1);
    }
    punto_inicio=punto_fin=0;
}

bool Cola::agregar(int x)
{
    if (punto_fin==tamanio)
        return false;
    cola_dinamica[punto_fin]=x;
    punto_fin++;
    return true;
}

bool Cola::sacar(int &x)
{
    if (punto_inicio==punto_fin)
        return false;
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
    bool Borde;
public:
    Texto (const string& letra,int variable,int tamanio,float x,float y,const Color& color=Color::Black,bool borde=false)
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
            if (borde)
            {
                texto.setOutlineThickness(2.f);
                Borde=true;
            }
            else
                Borde=false;
        }
    }
    Texto () {}
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
        texto.setFillColor(Color(texto.getFillColor().r,texto.getFillColor().g,texto.getFillColor().b,t));
        if (Borde)
        {
            texto.setOutlineColor(Color(texto.getOutlineColor().r,texto.getOutlineColor().g,texto.getOutlineColor().b,t));
        }
    }
    void setBorde_tamanio(float tamanio)
    {
        texto.setOutlineThickness(tamanio);
    }
    void setBorde_Color (const Color& color)
    {
        texto.setOutlineColor(color);
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

class Animacion
{
private:
    int num_frame;
    bool retorno;
public:
    Animacion()
    {
        num_frame=2;
        retorno=false;
    }
    int getNum_frame()
    {
        return num_frame;
    }
    bool getRetorno()
    {
        return retorno;
    }
    void setNum_frame(int f)
    {
        num_frame=f;
    }
    void setRetorno (bool r)
    {
        retorno=r;
    }
};

class Zombie
{
private:
    Texture zombie_textura_propiedad;
    bool textura_cargada;
    Sprite zombie_sprite_propiedad;
    float x,y;
    bool muerto,encolado;
    Animacion animacion_propiedad;
    IntRect porcion_de_imagen_propiedad;
    int opacidad;
    int vida,dinero_que_devuelve;
    float velocidad;
    int estado,intervalo_danio,danio_torre;
public:
    Zombie (const string& nombre_imagen,float posx,float posy,IntRect porcion_de_imagen,float ve=0.5,int opacida=0, int dinero=100,int vi=100)
    {

        if(!CreateTextureAndBitmask(zombie_textura_propiedad,nombre_imagen))
            textura_cargada=false;
        else
            textura_cargada=true;
        if (textura_cargada)
        {
            zombie_textura_propiedad.setSmooth(true);
            porcion_de_imagen_propiedad=porcion_de_imagen;
            zombie_sprite_propiedad.setTexture(zombie_textura_propiedad);
            zombie_sprite_propiedad.setTextureRect(porcion_de_imagen_propiedad);
            opacidad=opacida;
            zombie_sprite_propiedad.setColor(Color(255,255,255,opacidad));
            zombie_sprite_propiedad.setPosition(posx,posy);
            x=posx;
            y=posy;
            dinero_que_devuelve=dinero;
            vida=vi;
            velocidad=ve;
            estado=0;
            muerto=false;
            encolado=false;
        }
    }
    Zombie () {}
    Sprite getZombie()
    {
        return zombie_sprite_propiedad;
    }
    bool getMuerto()
    {
        return muerto;
    }
    bool getEncolado()
    {
        return encolado;
    }
    int getIntervalo_danio ()
    {
        return intervalo_danio;
    }
    int getDanio_torre ()
    {
        return danio_torre;
    }
    int getEstado ()
    {
        return estado;
    }
    float getX ()
    {
        return x;
    }
    float getY ()
    {
        return y;
    }
    int getOpacidad()
    {
        return opacidad;
    }
    int getVida()
    {
        return vida;
    }
    float getVelocidad()
    {
        return velocidad;
    }
    void setEstado (int e)
    {
        estado=e;
    }
    void setMuerto (bool m=true)
    {
        muerto=m;
    }
    void setEncolado (bool e)
    {
        encolado=e;
    }
    void setIntervalo_danio (int i)
    {
        intervalo_danio=i;
    }
    void setDanio_torre (int d)
    {
        danio_torre=d;
    }
    void setColor (int rojo,int verde,int azul,int opacida=255)
    {
        zombie_sprite_propiedad.setColor(Color(rojo,verde,azul,opacida));
    }
    void setX (float posx)
    {
        x=posx;
        zombie_sprite_propiedad.setPosition(x,y);
    }
    void setY (float posy)
    {
        y=posy;
        zombie_sprite_propiedad.setPosition(x,y);
    }
    void setPosicion(float posx,float posy)
    {
        x=posx;
        y=posy;
        zombie_sprite_propiedad.setPosition(x,y);
    }
    void setOpacidad (int o)
    {
        opacidad=o;
        zombie_sprite_propiedad.setColor(Color(255,255,255,opacidad));
    }
    void setVida (int vi)
    {
        vida=vi;
    }
    void setVelocidad (float ve)
    {
        velocidad=ve;
    }
    void setZombie (Sprite zombie_sprite_propiedad_asignar)
    {
        zombie_sprite_propiedad=zombie_sprite_propiedad_asignar;
    }
    bool getConfirmacion()
    {
        return textura_cargada;
    }
    void cambiar_frame_sprite(Clock&);
    void  reducir_vida()
    {
        vida-=danio_torre;
    }
    void incrementar_opacidad (int incremento)
    {
        opacidad+=incremento;
        zombie_sprite_propiedad.setColor(Color(255,255,255,opacidad));
    }
    void decrementar_opacidad (int decremento)
    {
        opacidad-=decremento;
        zombie_sprite_propiedad.setColor(Color(255,255,255,opacidad));
    }
    void mover_abajo()
    {
        y+=velocidad;
        setY(y);
    }
    void mover_izq()
    {
        x-=velocidad;
        setX(x);
    }
    void mover_derecha()
    {
        x+=velocidad;
        setX(x);
    }
    void mover_arriba()
    {
        y-=velocidad;
        setY(y);
    }
};

void Zombie::cambiar_frame_sprite(Clock &tiempo)
{
    switch (estado)
    {
    case 4:
///ANIMACION ARRIBA
        if (tiempo.getElapsedTime().asSeconds()>0.2f)
        {
            switch (animacion_propiedad.getNum_frame())
            {
            ///left es X
            ///top es Y
            ///width es ancho
            ///height es alto
            case 1:
                porcion_de_imagen_propiedad.left=0;
                porcion_de_imagen_propiedad.top=0;
                porcion_de_imagen_propiedad.width=30;
                porcion_de_imagen_propiedad.height=48;
                animacion_propiedad.setNum_frame(2);
                animacion_propiedad.setRetorno(false);
                break;
            case 2:
                porcion_de_imagen_propiedad.left=40;
                porcion_de_imagen_propiedad.top=0;
                porcion_de_imagen_propiedad.width=32;
                porcion_de_imagen_propiedad.height=48;
                if (animacion_propiedad.getRetorno())
                    animacion_propiedad.setNum_frame(1);
                else
                    animacion_propiedad.setNum_frame(3);
                break;
            case 3:
                porcion_de_imagen_propiedad.left=83;
                porcion_de_imagen_propiedad.top=0;
                porcion_de_imagen_propiedad.width=28;
                porcion_de_imagen_propiedad.height=49;
                animacion_propiedad.setNum_frame(2);
                animacion_propiedad.setRetorno(true);
                break;
            }
            zombie_sprite_propiedad.setTextureRect(porcion_de_imagen_propiedad);
            tiempo.restart();
        }
        break;
    case 3:
    case 5:
    case 6:
        ///ANIMACION DERECHA
        if (tiempo.getElapsedTime().asSeconds()>0.2f)
        {
            switch (animacion_propiedad.getNum_frame())
            {
            case 1:
                porcion_de_imagen_propiedad.left=0;
                porcion_de_imagen_propiedad.top=54;
                porcion_de_imagen_propiedad.width=30;
                porcion_de_imagen_propiedad.height=48;
                animacion_propiedad.setNum_frame(2);
                animacion_propiedad.setRetorno(false);
                break;
            case 2:
                porcion_de_imagen_propiedad.left=40;
                porcion_de_imagen_propiedad.top=54;
                porcion_de_imagen_propiedad.width=32;
                porcion_de_imagen_propiedad.height=48;
                if (animacion_propiedad.getRetorno())
                    animacion_propiedad.setNum_frame(1);
                else
                    animacion_propiedad.setNum_frame(3);
                break;
            case 3:
                porcion_de_imagen_propiedad.left=83;
                porcion_de_imagen_propiedad.top=54;
                porcion_de_imagen_propiedad.width=28;
                porcion_de_imagen_propiedad.height=49;
                animacion_propiedad.setNum_frame(2);
                animacion_propiedad.setRetorno(true);
                break;
            }
            zombie_sprite_propiedad.setTextureRect(porcion_de_imagen_propiedad);
            tiempo.restart();
        }
        break;
    case 0:
    case 2:
        ///ANIMACION ABAJO
        if (tiempo.getElapsedTime().asSeconds()>0.20f)
        {
            switch (animacion_propiedad.getNum_frame())
            {
            case 1:
                porcion_de_imagen_propiedad.left=0;
                porcion_de_imagen_propiedad.top=111;
                porcion_de_imagen_propiedad.width=30;
                porcion_de_imagen_propiedad.height=48;
                animacion_propiedad.setNum_frame(2);
                animacion_propiedad.setRetorno(false);
                break;
            case 2:
                porcion_de_imagen_propiedad.left=40;
                porcion_de_imagen_propiedad.top=111;
                porcion_de_imagen_propiedad.width=32;
                porcion_de_imagen_propiedad.height=48;
                if (animacion_propiedad.getRetorno())
                    animacion_propiedad.setNum_frame(1);
                else
                    animacion_propiedad.setNum_frame(3);
                break;
            case 3:
                porcion_de_imagen_propiedad.left=83;
                porcion_de_imagen_propiedad.top=111;
                porcion_de_imagen_propiedad.width=28;
                porcion_de_imagen_propiedad.height=49;
                animacion_propiedad.setNum_frame(2);
                animacion_propiedad.setRetorno(true);
                break;
            }
            zombie_sprite_propiedad.setTextureRect(porcion_de_imagen_propiedad);
            tiempo.restart();
        }
        break;
    case 1:
        /// ANIMACION IZQUIERDA

        if (tiempo.getElapsedTime().asSeconds()>0.2f)
        {
            switch (animacion_propiedad.getNum_frame())
            {
            case 1:
                porcion_de_imagen_propiedad.left=0;
                porcion_de_imagen_propiedad.top=166;
                porcion_de_imagen_propiedad.width=30;
                porcion_de_imagen_propiedad.height=48;
                animacion_propiedad.setNum_frame(2);
                animacion_propiedad.setRetorno(false);
                break;
            case 2:
                porcion_de_imagen_propiedad.left=40;
                porcion_de_imagen_propiedad.top=166;
                porcion_de_imagen_propiedad.width=32;
                porcion_de_imagen_propiedad.height=48;
                if (animacion_propiedad.getRetorno())
                    animacion_propiedad.setNum_frame(1);
                else
                    animacion_propiedad.setNum_frame(3);
                break;
            case 3:
                porcion_de_imagen_propiedad.left=80;
                porcion_de_imagen_propiedad.top=166;
                porcion_de_imagen_propiedad.width=28;
                porcion_de_imagen_propiedad.height=49;
                animacion_propiedad.setNum_frame(2);
                animacion_propiedad.setRetorno(true);
                break;
            }
            zombie_sprite_propiedad.setTextureRect(porcion_de_imagen_propiedad);
            tiempo.restart();
        }
        break;
    default:
        break;
    }
}

class Boton
{
private:
    float esi[2],esd[2],eii[2],eid[2];
    RectangleShape boton;
    int tamaniox,tamanioy,transparencia;
public:
    Boton(float x,float y,float posx,float posy,int Transparencia=0)
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
        transparencia=Transparencia;
        boton.setFillColor(Color(255,255,255,transparencia));
        tamaniox=x;
        tamanioy=y;
    }
    Boton () {}
    bool click(int *v)
    {
        if (v[0]>=esi[0]&&v[0]<=esd[0]&&v[1]>=esd[1]&&v[1]<=eid[1])
            return true;
        return false;
    }
    int getTransparencia ()
    {
        return transparencia;
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
        transparencia=t;
        boton.setFillColor(Color(255,255,255,transparencia));
    }
};

class Configuracion
{
private:
    bool sonido_menu;
public:
    Configuracion ()
    {
        FILE *p;
        p=fopen("Configuracion.dat","rb");
        if (p==NULL)
        {
            p=fopen("Configuracion.dat","ab");
            sonido_menu=true;
        }
        else
        {
            fread(this,sizeof this,1,p);
        }
        fclose(p);
    }
    bool getSonido_menu()
    {
        return sonido_menu;
    }
    void setSonido_menu(bool valor)
    {
        sonido_menu=valor;
        FILE *p;
        p=fopen("Configuracion.dat","rb+");
        fwrite(this,sizeof this,1,p);
        fclose(p);
    }
};

class Partida
{

private:
    int vidas;
    int dinero;
    int oleada;

public:
    int getvidas()
    {
        return vidas;
    }
    int getdinero()
    {
        return dinero;
    }
    int getoleada()
    {
        return oleada;
    }
    void setvidas(int x)
    {
        vidas=x;
    }
    void setdinero(int x)
    {
        dinero=x;
    }
    void setoleada(int x)
    {
        oleada=x;
    }
    bool leerendisco (int);
    void grabarendiso ();

};

#endif // CLASES_H_INCLUDED
