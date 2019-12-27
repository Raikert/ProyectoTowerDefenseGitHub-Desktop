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

class Video
{
private:
    TcpSocket socket;
    char msj_recibido[100];
    char msj_anterior[100];
    char msj[200];
    size_t total_recibido;
    int msg_recibidos,delay;
    IpAddress ip;
    size_t bytes;
    char video_actual[200];
    PROCESS_INFORMATION processInfo_copia;
    bool encendido;
public:
    Video (int d=500) {
    delay=d;
    }
    void encender ()
    {
        STARTUPINFO startInfo= {0};
        PROCESS_INFORMATION processInfo = {0};
        BOOL bScucces = CreateProcess(TEXT("player++/bin/vidserv.exe"),
                                      NULL,NULL,NULL,FALSE,CREATE_NO_WINDOW,NULL,NULL,&startInfo,&processInfo);

        if (!bScucces)
            exit (98765);
        processInfo_copia=processInfo;
        msg_recibidos=0;
        encendido=true;
        socket.connect(ip.getLocalAddress(), 50001);
    }
    void apagar ()
    {
        TerminateProcess(processInfo_copia.hProcess,0);
        encendido=false;
    }
    void abrir (const string &ruta,RenderWindow &window)
    {
        if (encendido)
        {
            ///montado y contatenacion del comando
            ///open para la carga del video en funcion
            ///de la pantalla del usuario.
            char cadena_ruta[200];

            ///obtener la maldita ruta absoluta
            GetFullPathNameA(ruta.c_str(),200,cadena_ruta,NULL);
            DAR_VUELTA_LAS_BARRAS(cadena_ruta);
            ///---------------------------------

            char cadena[200]="open ";
            char espacio[2]=" ";
            char variable[10];
            strcat(cadena,cadena_ruta);
            strcat(cadena,espacio);
            itoa(window.getPosition().x+8, variable, 10);
            strcat(cadena,variable);
            strcat(cadena,espacio);
            itoa(window.getPosition().y+22, variable, 10);
            strcat(cadena,variable);
            strcat(cadena,espacio);
            string estatico="1024 608 Video";
            strcat(cadena,estatico.c_str());
            ///-------------
            escribir_cadena(msj,cadena);
            bytes=sizeof msj;
            if (socket.send(msj,bytes) != Socket::Done)
                exit (98765);
            /*
            if (strcmp(video_actual,msg.c_str())!= 0)
                escribir_cadena(video_actual,msg);
            */
            Sleep(delay);
            enviar("play");
        }
    }
    void enviar(const string &msg)
    {
        if (encendido)
        {
            escribir_cadena(msj,msg);
            bytes=sizeof msj;
            if (socket.send(msj,bytes) != Socket::Done)
                exit (98765);

            /*
            if (strcmp(video_actual,msg.c_str())!= 0)
                escribir_cadena(video_actual,msg);
            */
            Sleep(delay);
        }
    }

    void recibir (const string &comando)
    {
        if (encendido)
        {
            escribir_cadena(msj,comando);
            bytes=sizeof msj;
            if (socket.send(msj,bytes) != Socket::Done)
                exit (98765);

            Sleep(delay);
            socket.receive(msj_recibido,100,total_recibido);
            if (msg_recibidos==0)
                strcpy(msj_anterior,msj_recibido);

            msg_recibidos++;
            Sleep(delay);
        }
    }
    bool fin_video ()
    {
        if (encendido)
        {
            if (strcmp(msj_recibido,msj_anterior)==0&&msg_recibidos>1)
                return true;
            else
            {
                strcpy(msj_anterior,msj_recibido);
                return false;
            }
        }
    }
    void apagar_v ()
    {
        if (encendido)
        {
            enviar("closewindows");
        }
    }
    bool getEncendido() {
    return encendido;
    }
};

class Tiro
{
private:
    Sprite tiro;
    float x,y,x_inicial,y_inicial,diferenciax,diferenciay;
public:
    void cargar (float posx,float posy,Sprite &tiro_sprite)
    {
        x=posx;
        y=posy;
        x_inicial=x;
        y_inicial=y;
        tiro=tiro_sprite;
        tiro.setPosition(x,y);
    }
    Sprite getTiro()
    {
        return tiro;
    }
    void reset ()
    {
        x=x_inicial;
        y=y_inicial;
        tiro.setPosition(x,y);
    }
    void traza(float posx_zombie,float posy_zombie,float velocidad_zombie)
    {
        if (x<posx_zombie)
        {
            x+=velocidad_zombie;
            tiro.setPosition(x,y);
        }
        else
        {
            x-=velocidad_zombie;
            tiro.setPosition(x,y);
        }

        if (y<posy_zombie)
        {
            y+=velocidad_zombie;
            tiro.setPosition(x,y);
        }
        else
        {
            y-=velocidad_zombie;
            tiro.setPosition(x,y);
        }

        diferenciax=x-posx_zombie;
        diferenciay=y-posy_zombie;
        if (x<posx_zombie)
            diferenciax=-(diferenciax);
        if (y<posy_zombie)
            diferenciay=-(diferenciay);
        if (diferenciax<2&&diferenciay<2)
            reset();
    }
};

class Textura
{
private:
    Texture textura;
public:
    void setSuavizado(bool eleccion)
    {
        textura.setSmooth(eleccion);
    }
    Textura(const string& ruta, int con_colision=1,bool suavizado=false)
    {
        if (con_colision==1)
        {
            if (!CreateTextureAndBitmask(textura,ruta))
                exit(-11111);
        }
        else
        {
            if (!textura.loadFromFile(ruta))
                exit(-11111);
        }
        if (suavizado)
            setSuavizado(true);
    }
    Textura () {}
    void cargar(const string& ruta, int tipo_carga=1,bool suavizado=false)
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
        if (suavizado)
            setSuavizado(true);
    }
    Texture &getTextura()
    {
        return textura;
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
    Music & getMusica()
    {
        return musica;
    }
    void volumen (float v)
    {
        musica.setVolume(v);
    }
    void repeticion(bool eleccion)
    {
        musica.setLoop(eleccion);
    }
    void reproducir ()
    {
        musica.play();
    }
    void pausar ()
    {
        musica.pause();
    }
    void parar()
    {
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
    int frame_x,frame_y,limite_frames_x,limite_frames_y,tam_x,tam_y,tam_porcionx,tam_porciony,ignore;
    Sprite sprite_cinematica;
    Clock tiempo_cinematica;
    float fps,x,y;
    bool repeticion,estado,retorno,balanceo;

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

    Cinematica (Texture &textura_cinematica,int tam_porcionx_p,int tam_porciony_p,bool regresar=false)
    {
        tam_porcionx=tam_porcionx_p;
        tam_porciony=tam_porciony_p;
        tam_x=textura_cinematica.getSize().x;
        tam_y=textura_cinematica.getSize().y;
        porcion_de_textura_cinematica=IntRect(0,0,tam_porcionx,tam_porciony);
        frame_x=frame_y=1;
        sprite_cinematica.setTexture(textura_cinematica);
        sprite_cinematica.setTextureRect(porcion_de_textura_cinematica);
        limite_frames_x=(tam_x/porcion_de_textura_cinematica.width);
        limite_frames_y=(tam_y/porcion_de_textura_cinematica.height);
        float fps_default=24;
        fps=1/fps_default;
        repeticion=false;
        estado=true;
        balanceo=regresar;
        retorno=false;
    }
    Cinematica ()
    {
        frame_x=frame_y=1;
        float fps_default=24;
        fps=1/fps_default;
        repeticion=true;
        estado=true;
    }

    void Actualizar_frame();
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
    void setIgnore(int frames_ignorados)
    {
        ignore=frames_ignorados;
    }
    void setColor (Color color)
    {
        sprite_cinematica.setColor(color);
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

void Cinematica::Actualizar_frame()
{
    ///La idea del funcionamiento es simple, a traves del tamaño del video en pixeles, y del tamaño de las particiones
    ///de video, tambien en pixeles, se puede saber que cantidad de frames posee la imagen de izquierda a derecha, de arriba
    ///hacia abajo. Una vez que la clase conoce sus limites, se hace un tira y afloje de frames desde el inicio hasta el fin
    ///de la imagen en el orden mencionado antes. Una vez que termina la reproduccion, esta vuelve a reproducirse desde el
    ///principio, salvo que agregue la booleana repeat, que daria la orden de si uno quisiera repetecion o no, ya lo implemento
    ///no se preocupen jajjaj, que se me acaba de ocurrir recien.
    if (estado)
    {
        if (!retorno)
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
                    porcion_de_textura_cinematica.left=0;
                    porcion_de_textura_cinematica.top+=tam_porciony;
                    frame_x=1;
                    frame_y++;
                    tiempo_cinematica.restart();
                    if (frame_y==limite_frames_y&&ignore!=0)
                        limite_frames_x-=ignore;
                }
                else
                {
                    if (frame_y==limite_frames_y&&tiempo_cinematica.getElapsedTime().asSeconds()>fps)
                    {
                        if (balanceo)
                        {
                            retorno=true;
                            tiempo_cinematica.restart();
                        }

                        if (repeticion)
                        {
                            porcion_de_textura_cinematica.left=0;
                            porcion_de_textura_cinematica.top=0;
                            frame_x=1;
                            frame_y=1;
                            tiempo_cinematica.restart();
                        }
                        else if (!balanceo)
                            estado=false;
                    }
                }
            }
        }

        if (retorno)
        {
            if (ignore!=0)
                limite_frames_x=(tam_x/porcion_de_textura_cinematica.width);

            if (frame_x>1&&tiempo_cinematica.getElapsedTime().asSeconds()>fps)
            {
                porcion_de_textura_cinematica.left-=tam_porcionx;
                frame_x--;
                tiempo_cinematica.restart();
            }
            else
            {
                if (frame_x==1&&tiempo_cinematica.getElapsedTime().asSeconds()>fps&&frame_y>1)
                {
                    porcion_de_textura_cinematica.left=tam_x-tam_porcionx;
                    porcion_de_textura_cinematica.top-=tam_porciony;
                    frame_x=limite_frames_x;
                    frame_y--;
                    tiempo_cinematica.restart();
                }
                else
                {
                    if (frame_y==1&&tiempo_cinematica.getElapsedTime().asSeconds()>fps)
                    {
                        retorno=false;
                        tiempo_cinematica.restart();
                    }
                }
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
    int sectorx,sectory,iniciox,inicioy;
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
        sectorx=90;
        sectory=90*2;
        iniciox=sectorx;
        inicioy=sectory;
        break;
    case 2:
        sectorx=90;
        sectory=90*6;
        iniciox=sectorx;
        inicioy=sectory;
        break;
    case 3:
        sectorx=90*7;
        sectory=90*6;
        iniciox=sectorx;
        inicioy=sectory;
        break;
    case 4:
        sectorx=90*10;
        sectory=90*6;
        iniciox=sectorx;
        inicioy=sectory;
        break;
    case 5:
        sectorx=90*4;
        sectory=90*2;
        iniciox=sectorx;
        inicioy=sectory;
        break;
    case 6:
        sectorx=90*4;
        sectory=90*6;
        iniciox=sectorx;
        inicioy=sectory;
        break;
    case 7:
        sectorx=90*7;
        sectory=90*2;
        iniciox=sectorx;
        inicioy=sectory;
        break;
    case 8:
        sectorx=90*10;
        sectory=90*2;
        iniciox=sectorx;
        inicioy=sectory;
        break;
    default:
        break;
    }
    porcion_de_textura_cinematica=IntRect(sectorx,sectory,tam_porcionx,tam_porciony);
}

void Animacion::cambiar_tira (int estado)
{
    switch (estado)
    {
    case 4:
        ///ANIMACION ARRIBA
        sectory=inicioy-90*2;
        break;
    case 3:
    case 5:
    case 6:
        ///ANIMACION DERECHA
        sectory=inicioy-90;
        break;
    case 0:
    case 2:
        ///ANIMACION ABAJO
        sectory=inicioy;
        break;
    case 1:
        /// ANIMACION IZQUIERDA
        sectory=inicioy+90;
        break;
    default:
        break;
    }
    porcion_de_textura_cinematica.top=sectory;
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
    Zombie (Texture &textura_zombies,int tipo=1,float ve=0.5,float posx=295,float posy=0,float escalax=0.65,float escalay=0.65)///float ve=0.5,int opacida=0, int dinero=100,int vi=100)
    {

        animacion_propiedad.crear_Animacion_zombie(textura_zombies,tipo,posx,posy,escalax,escalay);
        vida=0;
        velocidad=ve;
        estado=0;
        muerto=false;
        inicializar_vector_entero(intervalo_danio,3,10000);
        inicializar_matriz_encolado(encolado);
    }
    Zombie () {}
    void cambiar_zombie(int tipo)
    {
        animacion_propiedad.cambiar_tipo(tipo);
    }
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
    bool encendido;
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
        encendido=false;
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
    bool getEncendido()
    {
        return encendido;
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
    void setEncendido(bool e)
    {
        encendido=e;
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
    bool pos_torres[9];
    int niv_torres[9];
    int tipo_torres[9];

public:

    Partida()
    {
        vidas=1000;
        dinero=5000;
        oleada=0;

    }

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
    int getniv_torres(int pos)
    {
        return niv_torres[pos];
    }
    int gettipo_torres(int pos)
    {
        return tipo_torres[pos];
    }
    bool getpos_torres(int pos)
    {
        return pos_torres[pos];
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
    bool leerendisco ();
    bool grabarendiso ();
    void setpos_torre(int pos,bool ocu)
    {

        pos_torres[pos]=ocu;

    }
    void settipo_torre(int pos,int tipo)
    {

        tipo_torres[pos]=tipo;
    }
    void setniv_torres(int pos, int niv)
    {

        niv_torres[pos]=niv;
    }



};

bool Partida::leerendisco()
{
    FILE *p;
    p=fopen("partida.dat","rb");
    if(p==NULL)
        return false;
    if(fread(this,sizeof *this,1,p)==1)
    {
        fclose(p);
        return true;
    }
    fclose(p);
    return false;



}

bool Partida::grabarendiso()
{
    FILE *p;
    p=fopen("partida.dat","wb");
    if(p==NULL)
        return false;
    if(fwrite(this,sizeof *this,1,p)==1)
    {
        fclose(p);
        return true;
    }
    fclose(p);
    return false;

}


/// CLASE TORRE

class Torre
{
private:
    int tipo;
    int nivel;
    int precio;
    int danio;
    int intervalo;
    Sprite cuerpoS;
    Sprite rangoS;
    Tiro tiro_torre;
public:
    Torre(int tip=0, int niv=0)
    {
        tipo=tip;
        nivel=niv;
    }

    void setTipoNivel()
    {
        tipo=0;
        nivel=0;
        rangoS.setPosition(1000,600);
    }
    void cambiar_traza (float x_zombie,float y_zombie,float velocidad=1)
    {
        tiro_torre.traza(x_zombie,y_zombie,velocidad);
    }
    void resetear_tiro ()
    {
        tiro_torre.reset();
    }
    Sprite get_Tiro ()
    {
        return tiro_torre.getTiro();
    }
    void setTipoNivel(int t, int n,Texture &cuerpoT,Texture &rangoT)
    {
        tipo=t;
        nivel=n;
        switch(tipo)
        {
        case 1: /// ROJO
            switch(nivel)
            {
            case 1:
                precio=300;
                danio=6;
                intervalo=5;
                cuerpoS.setTexture(cuerpoT);
                rangoS.setTexture(rangoT);
                break;
            case 2:
                precio=900;
                danio=10;
                intervalo=5;
                cuerpoS.setTexture(cuerpoT);
                rangoS.setTexture(rangoT);
                break;
            case 3:
                precio=2100;
                danio=14;
                intervalo=5;
                cuerpoS.setTexture(cuerpoT);
                rangoS.setTexture(rangoT);
                break;
            }
            rangoS.setColor(Color(255,0,0,100));
            break;
        case 2: /// GRIS
            switch(nivel)
            {
            case 1:
                precio=400;
                danio=25;
                intervalo=15;
                cuerpoS.setTexture(cuerpoT);
                rangoS.setTexture(rangoT);
                break;
            case 2:
                precio=1200;
                danio=60;
                intervalo=15;
                cuerpoS.setTexture(cuerpoT);
                rangoS.setTexture(rangoT);
                break;
            case 3:
                precio=3600;
                danio=85;
                intervalo=15;
                cuerpoS.setTexture(cuerpoT);
                rangoS.setTexture(rangoT);
                break;
            }
            rangoS.setColor(Color(0,255,200,100));
            break;
        case 3: /// VERDE
            switch(nivel)
            {
            case 1:
                precio=500;
                danio=80;
                intervalo=50;
                cuerpoS.setTexture(cuerpoT);
                rangoS.setTexture(rangoT);
                break;
            case 2:
                precio=1500;
                danio=140;
                intervalo=50;
                cuerpoS.setTexture(cuerpoT);
                rangoS.setTexture(rangoT);
                break;
            case 3:
                precio=4500;
                danio=230;
                intervalo=50;
                cuerpoS.setTexture(cuerpoT);
                rangoS.setTexture(rangoT);
                break;

            }
            rangoS.setColor(Color(0,255,0,100));
            break;
        default:
            precio=0;
            danio=0;
            intervalo=0;
            cuerpoS.setTexture(cuerpoT);
            rangoS.setTexture(rangoT);

            cuerpoS.setPosition(10000,0);
            rangoS.setPosition(10000,0);
            break;
        }
    }

    void setTipoNivel(int n,Texture &cuerpoT)
    {
        nivel=n;
        switch(tipo)
        {
        case 1: /// ROJO
            switch(nivel)
            {
            case 1:
                precio=300;
                danio=6;
                intervalo=5;
                cuerpoS.setTexture(cuerpoT);
                break;
            case 2:
                precio=900;
                danio=10;
                intervalo=5;
                cuerpoS.setTexture(cuerpoT);
                break;
            case 3:
                precio=2100;
                danio=14;
                intervalo=5;
                cuerpoS.setTexture(cuerpoT);
                break;
            }
            break;
        case 2: /// GRIS
            switch(nivel)
            {
            case 1:
                precio=400;
                danio=25;
                intervalo=15;
                cuerpoS.setTexture(cuerpoT);
                break;
            case 2:
                precio=1200;
                danio=60;
                intervalo=15;
                cuerpoS.setTexture(cuerpoT);
                break;
            case 3:
                precio=3600;
                danio=85;
                intervalo=15;
                cuerpoS.setTexture(cuerpoT);
                break;
            }
            break;
        case 3: /// VERDE
            switch(nivel)
            {
            case 1:
                precio=500;
                danio=80;
                intervalo=50;
                cuerpoS.setTexture(cuerpoT);
                break;
            case 2:
                precio=1500;
                danio=140;
                intervalo=50;
                cuerpoS.setTexture(cuerpoT);
                break;
            case 3:
                precio=4500;
                danio=230;
                intervalo=50;
                cuerpoS.setTexture(cuerpoT);
                break;
            }
            break;
        }
    }

    void setPosicionTorre(float x, float y,Sprite &tiro_sprite)
    {
        cuerpoS.setPosition(x,y);
        tiro_torre.cargar(x+24,y+19,tiro_sprite);
    }

    void setEscalaTorre(float fx, float fy)
    {
        cuerpoS.setScale(fx,fy);
    }

    void setPosicionRango(float x, float y)
    {
        rangoS.setPosition(x,y);
    }

    void setEscalaRango(float fx, float fy)
    {
        rangoS.setScale(fx,fy);
    }
    Sprite getSpriteCuerpo()
    {
        return cuerpoS;
    }
    Sprite getSpriteRango()
    {
        return rangoS;
    }

    int getTipo()
    {
        return tipo;
    }

    int getDanio()
    {
        return danio/3;
    }

    int getIntervalo()
    {
        return intervalo;
    }

    int getPrecio()
    {
        return precio/2;
    }

    void subirNivel(Texture &cuerpoT)
    {
        setTipoNivel(nivel+1,cuerpoT);
    }

    int getNivel()
    {
        return nivel;
    }

};

#endif // CLASES_H_INCLUDED
