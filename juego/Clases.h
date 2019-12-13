#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

using namespace std;
using namespace sf;
using namespace Collision;
/*
setlocale(LC_ALL,"spanish");
*/

/*
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
*/

class Textura
{
private:
    Texture textura;
public:
    Textura(const string& ruta, int tipo_carga=1)
    {
        if (tipo_carga==1)
        {
            if (!CreateTextureAndBitmask(textura,ruta))
                exit(-11111);
        }
        else
        {
            if (!textura.loadFromFile(ruta))
                exit(-11111);
        }
    }
    Textura () {}
    void cargar(const string& ruta, int tipo_carga=1)
    {
        if (tipo_carga==1)
        {
            if (!CreateTextureAndBitmask(textura,ruta))
                exit(-11111);
        }
        else
        {
            if (!textura.loadFromFile(ruta))
                exit(-11111);
        }
    }
    Texture &getTextura()
    {
        return textura;
    }
    void setSuavizado(bool eleccion)
    {
        textura.setSmooth(eleccion);
    }
};

class Letra
{
private:
    Font letra;
public:
    Letra (const string & ruta)
    {
        if (!letra.loadFromFile(ruta))
            exit(-5555);
    }
    Font &getFont ()
    {
        return letra;
    }

};

class Musica
{
private:
    Music musica;
public:
    Musica(const string & ruta)
    {
        if (!musica.openFromFile(ruta))
            exit(689);
    }
    Music & getMusica() {
    return musica;
    }
    void volumen (float v) {
    musica.setVolume(v);
    }
    void repeticion(bool eleccion) {
    musica.setLoop(eleccion);
    }
    void reproducir () {
    musica.play();
    }
    void pausar () {
    musica.pause();
    }
    void parar() {
    musica.stop();
    }
};

/// CLASE TEXTO
class Texto
{
private:
    Text texto;
    bool Borde;
    float x,y;
public:
    Texto (Font &letra,int variable,int tamanio,float posx,float posy,const Color& color=Color::Black,bool borde=false)
    {
        texto.setFont(letra);
        texto.setCharacterSize(tamanio);
        x=posx;
        y=posy;
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
    Texto () {}
    void setFormato_de_letra (Font &letra)
    {
        texto.setFont(letra);
    }
    Text getTexto()
    {
        return texto;
    }
    float getX ()
    {
        return x;
    }
    float getY ()
    {
        return y;
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
    void setPosicion (float posx,float posy)
    {
        x=posx;
        y=posy;
        texto.setPosition(x,y);
    }
    void setX(int posx)
    {
        x=posx;
        texto.setPosition(x,y);
    }
    void setY(int posy)
    {
        y=posy;
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

class Cinematica
{
    ///A raiz de que SFML no soporta video, y la extension SfeMovie para codeblocks
    ///es como querer enchufar un Iphone x en el toma inglesa de tu tia petunia, llego
    ///la clase Cinematica.

protected:

    ///Ahora bien, como funciona esta clase? , ¿Que es un Spritesheet? , ¿Que utilidad tendria IntRect en esto?
    /// ¿Que es una Cinematica? ¿Como hace la clase para calcular todo lo relacionado a ello?

    IntRect porcion_de_textura_cinematica;
    int frame_x,frame_y,limite_frames_x,limite_frames_y,tam_x,tam_y,tam_porcionx,tam_porciony;
    Sprite sprite_cinematica;
    Clock tiempo_cinematica;
    float fps,x,y;
    bool repeticion,estado;

public:

    ///Bien, para empezar , una cinematica es basicamente un pedazo de video, acompañado de audio, que anuncia
    ///algo del contenido en donde es mostrado de manera rapida y consisa, no es un video ni tan largo, ni
    ///tan corto, es suficiente como para mostrar una seccion de videojuego de manera que tenga un trasfondo
    ///audiovisual.

    ///Aclaro que la clase no maneja sonido, pero aun asi, intentare acoplarlo en ella.

    ///Segun Wikipedia :

    ///La cinemática (del griego kinéin 'mover, desplazar') es la rama de la mecánica que describe el
    ///movimiento de los objetos sólidos sin considerar las causas que lo originan (las fuerzas) y se limita,
    ///principalmente, al estudio de la trayectoria en función del tiempo. Para ello utiliza velocidades y
    ///aceleraciones, que describen cómo cambia la posición en función del tiempo. La velocidad se determina
    ///como el cociente entre el desplazamiento y el tiempo utilizado, mientras que la aceleración es el cociente
    ///entre el cambio de velocidad y el tiempo utilizado.

    ///Es decir, que el video ilusionado, depende de la cinematica de los frames contenidos en el Spritesheet, eso
    ///seria el desplazamiento, y que a su vez, tiene una velocidad, que lo marca el Clock, y asi poder reproducir video.
    ///Ese cociente que menciona es segundo/cantidad de frames = fps o fotogramas por segundo, que da como resultado el cociente
    ///de desplazamiento que marcan algunos de los condicionales de los if en el metodo de la clase actualizar_frame().
    ///La aceleracion quedara como algo extra que no supone mucha importancia realmente, tampoco somos Youtube viste.

    Cinematica (Texture &textura_cinematica,int tam_porcionx_p,int tam_porciony_p,bool fullscreen=false)
    {
        tam_porcionx=tam_porcionx_p;
        tam_porciony=tam_porciony_p;
        tam_x=textura_cinematica.getSize().x;
        tam_y=textura_cinematica.getSize().y;
        porcion_de_textura_cinematica=IntRect(0,0,tam_porcionx,tam_porciony);
        frame_x=frame_y=1;
        sprite_cinematica.setTexture(textura_cinematica);
        sprite_cinematica.setTextureRect(porcion_de_textura_cinematica);
        if (fullscreen)
            sprite_cinematica.scale(2.588,2.388);

        limite_frames_x=(tam_x/porcion_de_textura_cinematica.width);
        limite_frames_y=(tam_y/porcion_de_textura_cinematica.height);
        float fps_default=24;
        fps=1/fps_default;
        repeticion=true;
        estado=true;
    }
    Cinematica ()
    {
        frame_x=frame_y=1;
        float fps_default=24;
        fps=1/fps_default;
        repeticion=true;
        estado=true;
    }

    void Actualizar_frame(int,int);
    ///nombre_objeto.Actualizar_frame();  -----> actualiza el frame del Spritesheet.

    void Reicicio()
    ///nombre_objeto.Reinicio(); -------> se reproduce desde el principio.
    {
        porcion_de_textura_cinematica.left=0;
        porcion_de_textura_cinematica.top=0;
        frame_x=1;
        frame_y=1;
        tiempo_cinematica.restart();
        sprite_cinematica.setTextureRect(porcion_de_textura_cinematica);
    }

    Sprite getFrame()
    ///A modo de ejemplo, no significa que solo sirva para esto,pero es el uso mas general.
    ///window.draw(nombre_objeto_getFrame); -------> le envia al metodo window.draw, el frame actual a ser dibujado en pantalla.
    {
        return sprite_cinematica;
    }

    bool getEstado ()
    ///nombre_objeto.getEstado() -------> retorna el estado de reproduccion.
    {
        return estado;
    }
    bool getRepeticion()
    ///nombre_objeto.getEstado() --------> retorno booleano si el video es en bucle o no.
    {
        return repeticion;
    }
    float getX ()
    {
        return x;
    }
    float getY ()
    {
        return y;
    }
    void escalar(float escalax,float escalay)
    {
        sprite_cinematica.scale(escalax,escalay);
    }
    void setEstado(bool e)
    ///nombre_objeto.setEstado() -------> setea el estado de reproduccion a true o false;
    {
        estado=e;
    }
    void setPosicion (float posx,float posy)
    ///nombre_objeto.setPosicion (float x, float y) ------> cambia la posicion de los frames, tanto x como y.
    {
        x=posx;
        y=posy;
        sprite_cinematica.setPosition(x,y);
    }
    void setX (float posx)
    ///nombre_objeto.setX (float x) ------> cambia solo la posicion en x de los frames.
    {
        x=posx;
        sprite_cinematica.setPosition(x,y);
    }
    void setY (float posy)
    ///nombre_objeto.setY (float y) ------> cambia solo la posicion en y de los frames.
    {
        y=posy;
        sprite_cinematica.setPosition(x,y);
    }
    void setFps (float fps_par)
    ///nombre_objeto.setFps (float fps_par) --------> cambia la velocidad de reproduccion en frames por segundo.
    {
        fps=1/fps_par;
    }
    void setRepeticion(bool rep)
    ///nombre_objeto.setReproduccion(bool rep) -----> se cambia la opcion del video en bucle o no. Pd: viene en bucle por default.
    {
        repeticion=rep;
    }

    ///Ahora bien, que vendria a ser un Spritesheet?. Un Spritesheet es el lugar a donde se van a alojar todos
    ///los estados o frames que, en este caso la cinematica, va a tener, digo este caso, porque podria ser una
    ///animacion, que es distinto, dado que esta en si es un video, pero es tan corto, que se lo suele llamar
    ///Animacion,el Spritesheet se usa para todo aquello que requiera guardar mas de un estado sobre una imagen
    ///a la que se la quiere mostrar de forma continua. El formato del Spritesheet puede ser cualquiera de los
    ///mas conocidos, pero es recomendable usar los de mayor compresion, dado que a mas frames, mas grande sera
    ///la imagen, y por lo tanto , mayor sera su peso, sin contar la calidad con la que se quiere obtener el video.
};

///El IntRect juega el rol mas importante en nuestra clase, puesto que es nuestro filtro de frames para luego
///ser reproducidos de forma continua, y asi generar la ilusion de un video, y que ademas, a traves del parametro
///fps, que por defecto viene a 24 fps, que es valor estandar y minimo para tener fluidez en un video, se puede
///cambiar la velocidad a la que este es reproducido, puesto que a mas frames por segundo, mas rapido se vera todo.

void Cinematica::Actualizar_frame(int iniciox=0,int inicioy=0)
{
    ///La idea del funcionamiento es simple, a traves del tamaño del video en pixeles, y del tamaño de las particiones
    ///de video, tambien en pixeles, se puede saber que cantidad de frames posee la imagen de izquierda a derecha, de arriba
    ///hacia abajo. Una vez que la clase conoce sus limites, se hace un tira y afloje de frames desde el inicio hasta el fin
    ///de la imagen en el orden mencionado antes. Una vez que termina la reproduccion, esta vuelve a reproducirse desde el
    ///principio, salvo que agregue la booleana repeat, que daria la orden de si uno quisiera repetecion o no, ya lo implemento
    ///no se preocupen jajjaj, que se me acaba de ocurrir recien.
    if (estado)
    {
        if (frame_x<limite_frames_x&&tiempo_cinematica.getElapsedTime().asSeconds()>fps)
        {
            porcion_de_textura_cinematica.left+=tam_porcionx;
            frame_x++;
            tiempo_cinematica.restart();
        }
        else
        {
            if (frame_x==limite_frames_x&&tiempo_cinematica.getElapsedTime().asSeconds()>fps&&frame_y<limite_frames_y)
            {
                porcion_de_textura_cinematica.left=iniciox;
                porcion_de_textura_cinematica.top+=tam_porciony;
                frame_x=1;
                frame_y++;
                tiempo_cinematica.restart();
            }
            else if (frame_y==limite_frames_y&&tiempo_cinematica.getElapsedTime().asSeconds()>fps)
            {
                if (repeticion)
                {
                    porcion_de_textura_cinematica.left=iniciox;
                    porcion_de_textura_cinematica.top=inicioy;
                    frame_x=1;
                    frame_y=1;
                    tiempo_cinematica.restart();
                }
                else
                    estado=false;
            }
        }
        if (estado)
            sprite_cinematica.setTextureRect(porcion_de_textura_cinematica);
    }

    ///Por ultimo y no menos importante, algo que me habia olvidado de mencionar, el Clock es usado para el cambio de frames,
    ///por velocidad de fotogramas o fps, una vez que este supera el tiempo de espera para reproducir el siguiente, se reinicia
    ///y asi sucesivamente. Las Porciones de Sprite, por pixeles en x e y, van cambiando en cada actualizacion, en un sentido de
    ///acumuladores, que marcan la posicion superior izquierda de cada frame para luego ser mostrado.

    ///Y bueno ese seria el fin de la clase, me diverti mucho haciendolo, y espero que ustedes tambien usandola, o en su defecto,
    ///aprendiedo como hacerlo, ahhhh siii, lo olvidaba.

    /// ¿COMO SE HACE UNA SPRITESHEET?

    ///buena pregunta, joven padawan ,  la respuesta a esta pregunta del universo observable es un convertidor de video a gif y de
    ///gif a spritesheet, pero aun asi, creo q esta pagina que consegui tambien puede de video a spritesheet, tendria que probar.
    ///basicamente convierte lo que tengamos en un formato que SFML no puede leer que es formato de video, a una imagen de varias
    ///imagenes dentro de si misma, de modo que sea el mismo video, pero separado en frames, y asi, poder correrlo en Sfml.

    ///El link de la pagina es esta, si aun funciona - con la ruta al convertidor gif-spritesheet.
    ///Link: https://ezgif.com/gif-to-sprite
}

class Animacion: protected Cinematica
{
private:
    bool retorno;
    int x,y;
public:
    void cambiar_tipo(int);
    void cambiar_tira(int);
    void crear_Animacion_zombie(Texture &textura_cinematica,int tipo_zombie,int posx,int posy,float escalax,float escalay)
    {
        sprite_cinematica.setTexture(textura_cinematica);
        tam_porcionx=90;
        tam_porciony=90;
        frame_x=2;
        cambiar_tipo(tipo_zombie);
        sprite_cinematica.setTextureRect(porcion_de_textura_cinematica);
        sprite_cinematica.scale(escalax,escalay);
        setPosicion(posx,posy);
        setFps(5);
        setOpacidad(0);
    }
    void cambiar_frame (int estado)
    {
        if (tiempo_cinematica.getElapsedTime().asSeconds()>fps&&!retorno)
        {
            porcion_de_textura_cinematica.left+=tam_porcionx;
            frame_x++;
            tiempo_cinematica.restart();
            if (frame_x==3)
                retorno=true;
        }
        else
        {
            if (tiempo_cinematica.getElapsedTime().asSeconds()>fps&&retorno)
            {
                porcion_de_textura_cinematica.left-=tam_porcionx;
                frame_x--;
                tiempo_cinematica.restart();
                if (frame_x==1)
                    retorno=false;
            }
        }
        sprite_cinematica.setTextureRect(porcion_de_textura_cinematica);
    }
    Sprite getAnimacion ()
    {
        return getFrame();
    }
    float getPosx ()
    {
        return getX();
    }
    float getPosy ()
    {
        return getY();
    }
    bool getRetorno()
    {
        return retorno;
    }
    int getOpacidad()
    {
        return sprite_cinematica.getColor().a;
    }
    void setPosxy (float posx,float posy)
    {
        setPosicion(posx,posy);
    }
    void setPosx (float posx)
    {
        setX(posx);
    }
    void setPosy(float posy)
    {
        setY(posy);
    }
    void setColor(int rojo,int verde,int azul)
    {
        sprite_cinematica.setColor(Color(rojo,verde,azul,255));
    }
    void setOpacidad (int o)
    {
        sprite_cinematica.setColor(Color(255,255,255,o));
    }
    void setSprite (Sprite Animacion)
    {
        sprite_cinematica=Animacion;
    }
    void setRetorno (bool r)
    {
        retorno=r;
    }
};

void Animacion::cambiar_tipo(int tipo)
{
    switch (tipo)
    {
    case 1:
        x=90;
        y=90*2;
        break;
    case 2:
        x=90;
        y=90*6;
        break;
    case 3:
        x=90*7;
        y=90*6;
        break;
    case 4:
        x=90*10;
        y=90*6;
        break;
    case 5:
        x=90*4;
        y=90*2;
        break;
    case 6:
        x=90*4;
        y=90*6;
        break;
    case 7:
        x=90*7;
        y=90*2;
        break;
    case 8:
        x=90*10;
        y=90*2;
        break;
    default:
        break;
    }
    porcion_de_textura_cinematica=IntRect(x,y,tam_porcionx,tam_porciony);
}

void Animacion::cambiar_tira (int estado)
{
    switch (estado)
    {
    case 4:
        ///ANIMACION ARRIBA
        y=0;
        break;
    case 3:
    case 5:
    case 6:
        ///ANIMACION DERECHA
        y=90;
        break;
    case 0:
    case 2:
        ///ANIMACION ABAJO
        y=90*2;
        break;
    case 1:
        /// ANIMACION IZQUIERDA
        y=90*3;
        break;
    default:
        break;
    }
    porcion_de_textura_cinematica.top=y;
    sprite_cinematica.setTextureRect(porcion_de_textura_cinematica);
}

class Zombie
{
private:
    bool muerto,encolado[9][3];
    Animacion animacion_propiedad;
    int vida;
    float velocidad;
    int estado,intervalo_danio[3],danio_torre[3];
public:
    Zombie (Texture &textura_zombies,int tipo,float ve=0.5,float posx=295,float posy=0,float escalax=0.65,float escalay=0.65)///float ve=0.5,int opacida=0, int dinero=100,int vi=100)
    {

        animacion_propiedad.crear_Animacion_zombie(textura_zombies,tipo,posx,posy,escalax,escalay);
        vida=100;
        velocidad=ve;
        estado=0;
        muerto=false;
        inicializar_vector_entero(intervalo_danio,3,10000);
        inicializar_matriz_encolado(encolado);
    }
    Zombie () {}
    Sprite getZombie()
    {
        return animacion_propiedad.getAnimacion();
    }
    bool getMuerto()
    {
        return muerto;
    }
    bool getEncolado(int torre,int tipo)
    {
        return encolado[torre][tipo];
    }
    int getIntervalo_danio (int pos)
    {
        return intervalo_danio[pos];
    }
    int getEstado ()
    {
        return estado;
    }
    float getX ()
    {
        return animacion_propiedad.getPosx();
    }
    float getY ()
    {
        return animacion_propiedad.getPosy();
    }
    int getOpacidad()
    {
        return animacion_propiedad.getOpacidad();
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
    void setEncolado (int torre,int tipo,bool valor)
    {
        encolado[torre][tipo]=valor;
    }
    void setIntervalo_danio (int i,int pos)
    {
        intervalo_danio[pos]=i;
    }
    void setDanio_torre (int d,int pos)
    {
        danio_torre[pos]=d;
    }
    void setColor (int rojo,int verde,int azul)
    {
        animacion_propiedad.setColor(rojo,verde,azul);
    }
    void setX (float posx)
    {
        animacion_propiedad.setPosx(posx);
    }
    void setY (float posy)
    {
        animacion_propiedad.setPosy(posy);
    }
    void setPosicion(float posx,float posy)
    {
        animacion_propiedad.setPosxy(posx,posy);
    }
    void setOpacidad (int o)
    {
        animacion_propiedad.setOpacidad(o);
    }
    void setVida (int vi)
    {
        vida=vi;
    }
    void setVelocidad (float ve)
    {
        velocidad=ve;
    }
    void setZombie (Sprite &zombie_sprite_propiedad_asignar)
    {
        animacion_propiedad.setSprite(zombie_sprite_propiedad_asignar);
    }
    void setTira_mov()
    {
        animacion_propiedad.cambiar_tira(estado);
    }
    void cambiar_frame_sprite()
    {
        animacion_propiedad.cambiar_frame(estado);
    }
    void  reducir_vida(int pos_danio)
    {
        vida-=danio_torre[pos_danio];
    }
    void incrementar_opacidad (int incremento)
    {
        animacion_propiedad.setOpacidad(animacion_propiedad.getOpacidad()+incremento);
    }
    void decrementar_opacidad (int decremento)
    {
        animacion_propiedad.setOpacidad(animacion_propiedad.getOpacidad()-decremento);
    }
    void mover_abajo()
    {
        animacion_propiedad.setPosy(animacion_propiedad.getPosy()+velocidad);
    }
    void mover_izq()
    {
        animacion_propiedad.setPosx(animacion_propiedad.getPosx()-velocidad);
    }
    void mover_derecha()
    {
        animacion_propiedad.setPosx(animacion_propiedad.getPosx()+velocidad);
    }
    void mover_arriba()
    {
        animacion_propiedad.setPosy(animacion_propiedad.getPosy()-velocidad);
    }
};

/*
void reestablecer_color_zombies(Zombie *enemigo,int cantidad_bichos)
{
    for (int i=0; i<cantidad_bichos; i++)
    {
        enemigo[i].setColor(255,255,255);
    }
}
*/

/*
void Zombie::cambiar_frame_sprite()
{
    animacion_propiedad.cambiar_frame();
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
*/

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
