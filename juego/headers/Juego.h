#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include<stdlib.h>
#include<time.h>

using namespace std;
using namespace sf;
using namespace Collision;

int juego()
{
    /// ZONA RANDOM
    srand(time(NULL));
    /// -----------
    bool tiempo_inicial=true;
    //variables de los for, dados los multiples conflictos por declaraciones seguidas en los ciclos.
    int i,x,te,d,o,l,f,c,debug,z,p,y,h;

    //variables de la ventana del juego
    int tamx,tamy,tamx_actual=1000,tamy_actual=600;
    Vector2f pixeles_convertidos;
    View vista_del_juego(FloatRect(0.f,0.f,1000.f,600.f));
    ///por lo raro que paresca, la siguiente linea logra que se pueda ver en fullscreen, si se lo comenta
    ///se ve una franja negra en el lado izquierdo, pero no entiendo xq.
    Vector2f caca=vista_del_juego.getCenter();

    //Constantes practicas
    const int const_vida_juego=1000;
    bool primer_enemigo=false;
    int tiempo_spawn=500;
    const int cantidad_bichos=10;
    const float velocidad_bichos=0.8;

    //Objetos Archivo-----------
    Configuracion reg_config;
    bool primer_carga=false;

    //Vector dinamico de zombies--------
    Zombie *enemigo = new Zombie[cantidad_bichos];

    ///Objeto de tipo Zombie, nuevo diseño.-----------

    ///Contructor :

    ///1) Textura por puntero, hacer un getTextura() del objeto Textura creado.
    ///2) Tipo de Zombie (1 al 8).
    ///3) Velocidad del zombie.

    Textura textura_zombies ("img/Zombies.png");

    Zombie aldeano(textura_zombies.getTextura());

    cargar_vector_sprites(enemigo,aldeano,cantidad_bichos);

    ///------------------------------------------------------

    Letra font_texto1("tipos_de_texto/letra_pintura.ttf");

    Texto vidas_texto[cantidad_bichos];
    Texto vidas_texto_variable(font_texto1.getFont(),enemigo[0].getVida(),17,aldeano.getX()+13,aldeano.getY()+48,Color::Transparent,true);

    vidas_texto_variable.setBorde_Color(Color(255,0,255,0));
    vidas_texto_variable.setBorde_tamanio(0.5);
    for (i=0; i<cantidad_bichos; i++)
    {
        vidas_texto[i]=vidas_texto_variable;
        vidas_texto[i].setVariable(enemigo[i].getVida());
    }

    /// CANTIDAD DE ENEMIGOS MUERTOS

    int enemigos_muertos=0;

    //Texto oleada_texto("tipos_de_texto/OpenSans-BoldItalic.ttf",oleada,20,940)

    // VARIABLES DE MONSTRUOS
    //int monstruos_lvl_1=2;
    //int monstruos_lvl_2=2;
    //int monstruos_lvl_3=2;

    // VARIABLE QUE CUENTA LOS MONSTRUOS
    //int monstruos_en_juego=0;


    // PRUEBA CON LA CLASE COLA
    //Cola Cola_Torre[9];
    //for (o=0; o<9; o++)
    //{
    //   Cola_Torre[o]=Cola(10);
    //}

    ///------Animaciones de los zombies-------

    //Explicacion del IntRect o rectangulo de una imagen.

    //Imaginen que tienen un cuadro vacio, y a su vez tienen
    //la pintura en un paño de lana al que quieren poner en ese
    //cuadro, pero q tambien ustedes pretenden mostrar solo una
    //parte de ese paño. Si lo asociamos con esto seria asi:
    //El Sprite es el cuadro.
    //La textura es el paño o imagen.
    //lo que quieren mostrar es la variable de tipo IntRect.

    //Ahora, una vez q montaron todo, lo que quieren hacer es
    //recortar el paño al cual montaron al cuadro, entonces como se hace?

    //Primero crean una variable de tipó IntRect, que significa
    //rectangulo interior o zona de recorte. Ahora bien, que significan todas esas coordenadas?.

    //Las primeras 2: tanto el 15 y el 34 es la posicion en donde
    //va a empezar ese rectangulo, igual q la posicion de los sprites
    //en la esquina izquierda superior, y los otros 2 son el ancho y
    //el alto de su rectangulo o recorte, el orden para las primeras
    //dos es igual a la q veniamos usando, primero en X, despues en Y
    //las otras 2 es primero el ancho, despues el alto.

    //Hasta ahora todo bien no?, eso espero xddd

    //Si se fijan mas abajo van a ver una variable nueva que se llama
    //Clock o tiempo, es una variable q desde q es declarada
    //cuenta tiempo, ya sea en segundos, minutos, lo q sea.
    //pero lo q usariamos nosotros seria mas q nada los segundos
    //asi q para obtener la cantidad de seg q tiene el CLOCK
    //hay q usar el metodo GetElapsedTime() pero q a su vez
    //nos entregue el tiempo en segundos entonces le agregamos
    //AsSeconds(), y asi obtendriamos el tiempo en seg q tiene
    //actualmente nuestro juego, sin contar los minutos obvio.
    //pero q me imagino q tambien se podra almacenar en otra variable
    //de tipo int y podriamos armar un relojito para el juego.

    /*
        Texture sprites;
        if (!sprites.loadFromFile("img/zombie2.png"))
            return -1;
        IntRect porcion_de_sprite(0,0,36,50);
        Sprite animacion_abajo(sprites,porcion_de_sprite),animacion_muestra_menu;
        //--solo para mostrarlo en el menu jeje
        animacion_muestra_menu=animacion_abajo;
        animacion_muestra_menu.setPosition(668,317);
        //-------
        animacion_abajo.setPosition(285,0);
        animacion_abajo.setColor(Color::Transparent);
        animacion_abajo.setScale(0.5,0.5);
        int num_sprite[cantidad_bichos];
        for (i=0; i<cantidad_bichos; i++)
        {
            num_sprite[i]=2;
        }
        bool retorno[cantidad_bichos];
        ponerEnFalso(retorno,cantidad_bichos);
        Clock animaciones[cantidad_bichos];

    */

    //Sector de Incializacion y generacion de Sprites y vectores de Sprites

    /*
    Sprites bicho("img/bicho_reside_circulo.png",opacidad_bichos,285,0);

    if (!bicho.getConfirmacion())
        return -10;
        */

    //Camino lvl1 para modificaciones de colision por error de colisiones con los bichos - comentado

    /*
    Sprites camino1("img/caminolvl1.png")
    if (!camino1.getConfirmacion())
        return -10;
    */

    ///Efectos de sonido - breve explicacion

    ///Segun Sfml: Sounds (and music) are played in a separate thread.
    ///This means that you are free to do whatever you want after calling play()
    ///(except destroying the sound or its data, of course), the sound will continue
    ///to play until it's finished or explicitly stopped.

    ///Los sonidos, a diferencia de los objetos music, trabajan de la misma forma que los sprites.
    ///tienen un soundbuffer, que seria lo mismo que una textura, y un sound que seria lo mismo que
    ///un sprite.

    SoundBuffer buffer,buffer2;
    buffer.loadFromFile("musica/FX/select_menu.wav");
    buffer2.loadFromFile("musica/FX/building.ogg");

    ///Se carga el buffer, como una textura.

    Sound fx,fx2;
    fx.setBuffer(buffer);
    fx.setVolume(12);
    fx2.setBuffer(buffer2);
    fx2.setVolume(12);

    ///se carga el sound ,  como un sprite.

    ///las mecanicas de los sprites, son iguales para los soundbuffer y los sound, uno puede cargar
    ///diferentes objetos sound con el mismo soundbuffer.

    bool fx_bool=true;
    ///-----------------------------------------------------------

    ///Reproductor de Video

    Video reproductor;

    Textura textura_mapa("img/008.png",0),textura_menu("img/fondo_menu_nuevo.jpg",0),textura_derrota("img/derrota.jpg",0);

    textura_menu.setSuavizado(true);
    textura_mapa.setSuavizado(true);
    textura_derrota.setSuavizado(true);

    ///clase partida
    Partida game;

    //Zona de texto---------------------------
    /*
    Font tipo_de_texto;
    */
    // ------------------------------------------------------------------
    // if (!tipo_de_texto.loadFromFile("tipos_de_texto/OpenSans-Bold.ttf"))
    //    return -1;
    //Text texto_prueba;
    //texto_prueba.setFont(tipo_de_texto);
    //texto_prueba.setString("GENTESSS EDITION");
    //texto_prueba.setCharacterSize(24);   */
    //-------------------------------------------------------------------

    ///Nueva clase : Cinematica------------------------------------

    ///Constructor - parametros :

    ///1) Textura del Spritesheet cargado como objeto, mandarlo con el metodo getTextura().
    ///2) Ancho del gif - X
    ///3) Alto del gif - Y
    ///4) Por omision True, Modo Fullscreen True/False.

    ///Si el tamaño de los frames en el Spritesheet se modifico del tamaño del gif
    ///2) Ancho de los frames - X
    ///3) Alto de los frames - Y

    ///La explicacion de que es un Spritesheet, el uso de IntRect y
    ///el uso de los metodos se encuentran donde esta declarada la clase Cinematica.

    ///Es la clase a la que mas explicacion le he dedicado, dado que es todo una ciencia
    ///es uso y reproduccion de video, que llega a sorprender de la manera en la que todo
    ///termina funcionando para ser solo una ilusion optica, y como todo puede llegar a
    ///ser Programable.

    ///Y si, es una sola linea.
    /*
        Textura gif_prueba("img/cinematicas/gif_prueba.jpg",0);

        Textura viejo ("img/cinematicas/viejo_gif.jpg",0);

        Textura pasto_tex("img/cinematicas/pasto_verde_final.png",0,true);

        Cinematica test1(gif_prueba.getTextura(),386,251);  ///tamaño del gif
        Cinematica viejo_test(viejo.getTextura(),400,226);
        Cinematica pasto(pasto_tex.getTextura(),337,480,true);

        pasto.setIgnore(4);
        pasto.escalar(0.25,0.25);
        pasto.setColor(Color(Color::Green));

        ///pero no para los metodos, jeje.

        test1.setRepeticion(false);
        test1.setEstado(false);

        viejo_test.setEstado(false);
        viejo_test.setFps(10);
        */

    ///El draw de esta cinematica esta debajo de todo solo por esta vez, dado que sino los demas
    ///draws lo superponen y no se lo puede ver. Para ver esta clase en accion ,con la Tecla A
    ///y en cualquier estado del juego se lo puede activar, si es que aun esta activo este ejemplo
    ///que hice, deberia verse un fragmento de video de Age of Empires.

    ///------------------------------------------------------------------------------------

    ///Animaciones con mecanismo de Cinematicas - dada su alta simplicidad - aun en proceso.

    ///Cinematica fuego("img/fuego.jpg",IntRect(0,0,820,858),4100,2574);

    ///-------------------------------------------------------------------------------------

    Sprite mapa,menu,derrota;
    mapa.setTexture(textura_mapa.getTextura());
    menu.setTexture(textura_menu.getTextura());
    derrota.setTexture(textura_derrota.getTextura());
    int mousexy[2];
    bool teclado=false;
    for (i=0; i<2; i++)
    {
        mousexy[i]=0;
    }
    Letra font_texto2("tipos_de_texto/letra_increible_con_borde.ttf");

    Texto mousex (font_texto2.getFont(),mousexy[0],18,628,540);

    Texto mousey (font_texto2.getFont(),mousexy[1],18,700,540);

    Texto muertos_texto(font_texto2.getFont(),enemigos_muertos,40,940,284,Color::Yellow,true);

    //Si gente, le puse MUSICA WEEEEE


    Musica musica_menu("musica/menu_song.ogg"),musica_juego("musica/musica2_juego.ogg"),musica_derrota("musica/derrota.ogg");

    //volumen de la musica del menu

    musica_menu.volumen(3);
    // musica_menu.setPlayingOffset(seconds(62.5f));
    musica_menu.repeticion(true);
    musica_juego.volumen(3);
    musica_juego.repeticion(true);
    musica_derrota.repeticion(true);
    musica_derrota.volumen(30);
    bool boolmusica=false,boolmusicajuego=true,habilitacionmouse=true,boolmusicaderrota=false;

    //Para un futuro en donde pongamos a los 3 sprites de los 8 tipos de monstruos q consegui-veanlo en la carpeta de img

    /*
    Sprite enemigo[cantidad_objetos][3];
    */

    ///CLASE BOTON

    //objeto boton de la nueva clase de botones_rectangulo, 5 Parametros:
    //Tamaño en Float X, Tamaño en Float Y, Posicion de la pantalla en Float X, Posicion de la pantalla en Float Y
    //el Quinto parametro es transparencia q se pone en 0,osea invisible, por parametro por omision.
    //Util para ver en q posicion de la pantalla se ubica el boton.

    Boton nueva_partida(237,38,727,111),cargar_partida_boton(237,38,728,205,255),salir(161,38,742,456),sonido(55,50,872,487);
    Boton nueva_oleada(49,45,823,433,255), derrota_boton(1000,600,0,0), guardar_partida(152,44,824,545,255), pausa(49,45,875,433);
    Boton reanudar(49,45,927,433), sonido_menu(62,46,32,362),pantalla_completa(64,52,24,433);

    /// ---------------------------------- MENSAJES --------------------------------------------

    /// MENSAJE POST OLEADA
    /*
    Font MensajePostOleadaF;
    if (!MensajePostOleadaF.loadFromFile("tipos_de_texto/OpenSans-Bold.ttf"))
        return -1;
    Text MensajePostOleadaT;
    MensajePostOleadaT.setFont(MensajePostOleadaF);
    MensajePostOleadaT.setString("¡Una horda de zombies se aproxima, defiende el castillo!");
    MensajePostOleadaT.setCharacterSize(28);
    MensajePostOleadaT.setColor(Color(0,200,0,255));
    MensajePostOleadaT.setPosition(15,250);
    */



    /// MENSAJE TERMINA LA OLEADA PARA GUARDAR
    int Opacidad_Mensaje_guardar=255;
    bool guardar_f=false;

    Texture mensaje_guardar;
    mensaje_guardar.loadFromFile("img/Mensaje_Guardar.png");
    mensaje_guardar.setSmooth(true);

    Sprite mensajee_guardar;
    mensajee_guardar.setTexture(mensaje_guardar);
    mensajee_guardar.setPosition(110,160);
    mensajee_guardar.setScale(0.7,0.7);




    /// MENSAJE POST PARTIDA

    int Opacidad_Mensaje_Partida=255;

    Texture mensaje_post_partida_T;
    mensaje_post_partida_T.loadFromFile("img/Mensaje_Partida.png");
    mensaje_post_partida_T.setSmooth(true);

    Sprite mensaje_post_partida_S;
    mensaje_post_partida_S.setTexture(mensaje_post_partida_T);
    mensaje_post_partida_S.setPosition(110,160);
    mensaje_post_partida_S.setScale(0.7,0.7);

    /// MENSAJE DE DINERO INSUFICIENTE

    bool dinero_insuficiente[9]= {false};
    int Opacidad_Mensaje_Dinero[9]= {255};

    Texture mensaje_dinero_t;
    mensaje_dinero_t.loadFromFile("img/Mensaje_Dinero.png");
    mensaje_dinero_t.setSmooth(true);

    Sprite mensaje_dinero_s[9];
    for(x=0; x<9; x++)
    {
        mensaje_dinero_s[x].setTexture(mensaje_dinero_t);
        mensaje_dinero_s[x].setScale(0.7,0.7);
    }


    /// ----------------------------------------------------------------------------------------

///*/////////////////////////////////////////////-------------ZONA DE TORRES -------------////////////////////////////////////////////////////////////////////////////////////////////////

    ///-----Cantidad de posiciones para las torres
    const int posiciones_torres=9;

    ///-----Cantidad de torres-----
    const int cantidad_torres=3;

    ///-----Niveles de las torres-----
    int torre_nivel[posiciones_torres];
    inicializar_vector_entero(torre_nivel,posiciones_torres,0);


    ///-----Cantidad de niveles de las torres-----
    const int niveles_torres=3;

    ///-----Cantidad de niveles del menu de torres-----
    const int niveles_menu=3;

    /// NIVELES DE LOS MENUS
    int nivel_del_menu[posiciones_torres];
    inicializar_vector_entero(nivel_del_menu,posiciones_torres,0);

    ///-------------Tiros---------------------
    Textura tiro_balin("img/tiro.png",0);
    Textura tiro_rayo("img/rayo.png",0);
    Sprite carcasa_escalada;
    carcasa_escalada.scale(0.1875,0.1875);
    bool prioridad_dibujo[posiciones_torres];
    inicializar_vector_bool(prioridad_dibujo,posiciones_torres,false);
    /// Estado del menu

    bool menu_abierto[posiciones_torres];
    ponerEnFalso(menu_abierto, posiciones_torres);

    ///-----Dinero de juego-----

    int dinero;
    dinero=300;
    Texto dinero_texto(font_texto2.getFont(),dinero,25,937,147,Color(4,174,21,255),true);

    ///-----Vida de juego-----

    int vida_juego;
    vida_juego=const_vida_juego;
    Texto vida_juego_texto(font_texto2.getFont(),vida_juego,25,874,110,Color(241,65,91,255),true);

    /// Variables para la verificacion de clicks y demas

    int posicion_clickeada;
    int contador_de_clicks=0;
    int contador_de_clicks_fuera=0;

    /// Definicion de los espacios para las torres ----------------------------------------------------------------------------

    /// Posiciones para las torres
    int coordenadas_X_Y_torres[2]; /// X=0 Y=1
    /// Posicion del menu completo
    int coordenadas_X_Y_menu[2];
    /// Posiciones para seleccionar torres
    int coordenadas_X_Y_torres_lvl_1[cantidad_torres][2];
    /// Posicion del boton para cerrar el menu
    int coordenadas_X_Y_equis[2]; /// X=0 Y=1
    /// Posicion del boton para vender
    int coordenadas_X_Y_vender[2]; /// X=0 Y=1
    /// Posicion del boton para cambiar el menu por el menu+1
    int coordenadas_X_Y_subirlvl[2]; /// X=0 Y=1
    /// Posicion del boton para mejorar la torre
    int coordenadas_X_Y_mejorar[2]; /// X=0 Y=1

    Boton torres_menu_area[posiciones_torres];

    Boton torres[posiciones_torres];

    Boton torres_tipo[cantidad_torres][posiciones_torres];

    Boton torres_equis[posiciones_torres];

    Boton torres_vender[posiciones_torres];

    Boton torres_subirlvl[posiciones_torres];

    Boton torres_mejorar[posiciones_torres];

    /// Posiciones de cada boton----------------------------------

    for (i=0; i<posiciones_torres; i++)
    {
        switch (i)
        {
        case 0:

            /// Espacio para la torre

            coordenadas_X_Y_torres[0]=121;
            coordenadas_X_Y_torres[1]=45;

            /// Espacio para el menu

            coordenadas_X_Y_menu[0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_menu[1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 1 del menu

            coordenadas_X_Y_torres_lvl_1[0][0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_torres_lvl_1[0][1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 2 del menu

            coordenadas_X_Y_torres_lvl_1[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_lvl_1[1][1]=coordenadas_X_Y_torres[1]-72;

            /// Torre 3 del menu

            coordenadas_X_Y_torres_lvl_1[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_lvl_1[2][1]=coordenadas_X_Y_torres[1]-72;

            /// Cruz para cerrar el menu

            coordenadas_X_Y_equis[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_equis[1]=coordenadas_X_Y_torres[1]-73;

            /// Boton para vender del menu

            coordenadas_X_Y_vender[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_vender[1]=coordenadas_X_Y_torres[1]-52;

            /// Boton para cambiar el menu por el menu de nivel+1

            coordenadas_X_Y_subirlvl[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_subirlvl[1]=coordenadas_X_Y_torres[1]-19;

            /// Boton para mejorar la torre

            coordenadas_X_Y_mejorar[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_mejorar[1]=coordenadas_X_Y_torres[1]-35;
            break;

        case 1:

            /// Espacio para la torre

            coordenadas_X_Y_torres[0]=118;
            coordenadas_X_Y_torres[1]=200;

            /// Espacio para el menu

            coordenadas_X_Y_menu[0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_menu[1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 1 del menu

            coordenadas_X_Y_torres_lvl_1[0][0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_torres_lvl_1[0][1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 2 del menu

            coordenadas_X_Y_torres_lvl_1[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_lvl_1[1][1]=coordenadas_X_Y_torres[1]-72;

            /// Torre 3 del menu

            coordenadas_X_Y_torres_lvl_1[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_lvl_1[2][1]=coordenadas_X_Y_torres[1]-72;

            /// Cruz para cerrar el menu

            coordenadas_X_Y_equis[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_equis[1]=coordenadas_X_Y_torres[1]-73;

            /// Boton para vender del menu

            coordenadas_X_Y_vender[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_vender[1]=coordenadas_X_Y_torres[1]-52;

            /// Boton para cambiar el menu por el menu de nivel+1

            coordenadas_X_Y_subirlvl[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_subirlvl[1]=coordenadas_X_Y_torres[1]-19;

            /// Boton para mejorar la torre

            coordenadas_X_Y_mejorar[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_mejorar[1]=coordenadas_X_Y_torres[1]-35;
            break;

        case 2:

            /// Espacio para la torre

            coordenadas_X_Y_torres[0]=120;
            coordenadas_X_Y_torres[1]=368;

            /// Espacio para el menu

            coordenadas_X_Y_menu[0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_menu[1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 1 del menu

            coordenadas_X_Y_torres_lvl_1[0][0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_torres_lvl_1[0][1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 2 del menu

            coordenadas_X_Y_torres_lvl_1[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_lvl_1[1][1]=coordenadas_X_Y_torres[1]-72;

            /// Torre 3 del menu

            coordenadas_X_Y_torres_lvl_1[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_lvl_1[2][1]=coordenadas_X_Y_torres[1]-72;

            /// Cruz para cerrar el menu

            coordenadas_X_Y_equis[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_equis[1]=coordenadas_X_Y_torres[1]-73;

            /// Boton para vender del menu

            coordenadas_X_Y_vender[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_vender[1]=coordenadas_X_Y_torres[1]-52;

            /// Boton para cambiar el menu por el menu de nivel+1

            coordenadas_X_Y_subirlvl[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_subirlvl[1]=coordenadas_X_Y_torres[1]-19;

            /// Boton para mejorar la torre

            coordenadas_X_Y_mejorar[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_mejorar[1]=coordenadas_X_Y_torres[1]-35;
            break;

        case 3:

            /// Espacio para la torre

            coordenadas_X_Y_torres[0]=267;
            coordenadas_X_Y_torres[1]=368;

            /// Espacio para el menu

            coordenadas_X_Y_menu[0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_menu[1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 1 del menu

            coordenadas_X_Y_torres_lvl_1[0][0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_torres_lvl_1[0][1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 2 del menu

            coordenadas_X_Y_torres_lvl_1[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_lvl_1[1][1]=coordenadas_X_Y_torres[1]-72;

            /// Torre 3 del menu

            coordenadas_X_Y_torres_lvl_1[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_lvl_1[2][1]=coordenadas_X_Y_torres[1]-72;

            /// Cruz para cerrar el menu

            coordenadas_X_Y_equis[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_equis[1]=coordenadas_X_Y_torres[1]-73;

            /// Boton para vender del menu

            coordenadas_X_Y_vender[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_vender[1]=coordenadas_X_Y_torres[1]-52;

            /// Boton para cambiar el menu por el menu de nivel+1

            coordenadas_X_Y_subirlvl[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_subirlvl[1]=coordenadas_X_Y_torres[1]-19;

            /// Boton para mejorar la torre

            coordenadas_X_Y_mejorar[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_mejorar[1]=coordenadas_X_Y_torres[1]-35;
            break;

        case 4:

            /// Espacio para la torre

            coordenadas_X_Y_torres[0]=293;
            coordenadas_X_Y_torres[1]=200;

            /// Espacio para el menu

            coordenadas_X_Y_menu[0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_menu[1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 1 del menu

            coordenadas_X_Y_torres_lvl_1[0][0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_torres_lvl_1[0][1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 2 del menu

            coordenadas_X_Y_torres_lvl_1[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_lvl_1[1][1]=coordenadas_X_Y_torres[1]-72;

            /// Torre 3 del menu

            coordenadas_X_Y_torres_lvl_1[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_lvl_1[2][1]=coordenadas_X_Y_torres[1]-72;

            /// Cruz para cerrar el menu

            coordenadas_X_Y_equis[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_equis[1]=coordenadas_X_Y_torres[1]-73;

            /// Boton para vender del menu

            coordenadas_X_Y_vender[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_vender[1]=coordenadas_X_Y_torres[1]-52;

            /// Boton para cambiar el menu por el menu de nivel+1

            coordenadas_X_Y_subirlvl[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_subirlvl[1]=coordenadas_X_Y_torres[1]-19;

            /// Boton para mejorar la torre

            coordenadas_X_Y_mejorar[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_mejorar[1]=coordenadas_X_Y_torres[1]-35;
            break;

        case 5:

            /// Espacio para la torre

            coordenadas_X_Y_torres[0]=414;
            coordenadas_X_Y_torres[1]=135;

            /// Espacio para el menu

            coordenadas_X_Y_menu[0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_menu[1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 1 del menu

            coordenadas_X_Y_torres_lvl_1[0][0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_torres_lvl_1[0][1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 2 del menu

            coordenadas_X_Y_torres_lvl_1[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_lvl_1[1][1]=coordenadas_X_Y_torres[1]-72;

            /// Torre 3 del menu

            coordenadas_X_Y_torres_lvl_1[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_lvl_1[2][1]=coordenadas_X_Y_torres[1]-72;

            /// Cruz para cerrar el menu

            coordenadas_X_Y_equis[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_equis[1]=coordenadas_X_Y_torres[1]-73;

            /// Boton para vender del menu

            coordenadas_X_Y_vender[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_vender[1]=coordenadas_X_Y_torres[1]-52;

            /// Boton para cambiar el menu por el menu de nivel+1

            coordenadas_X_Y_subirlvl[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_subirlvl[1]=coordenadas_X_Y_torres[1]-19;

            /// Boton para mejorar la torre

            coordenadas_X_Y_mejorar[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_mejorar[1]=coordenadas_X_Y_torres[1]-35;
            break;

        case 6:

            /// Espacio para la torre

            coordenadas_X_Y_torres[0]=414;
            coordenadas_X_Y_torres[1]=268;

            /// Espacio para el menu

            coordenadas_X_Y_menu[0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_menu[1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 1 del menu

            coordenadas_X_Y_torres_lvl_1[0][0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_torres_lvl_1[0][1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 2 del menu

            coordenadas_X_Y_torres_lvl_1[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_lvl_1[1][1]=coordenadas_X_Y_torres[1]-72;

            /// Torre 3 del menu

            coordenadas_X_Y_torres_lvl_1[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_lvl_1[2][1]=coordenadas_X_Y_torres[1]-72;

            /// Cruz para cerrar el menu

            coordenadas_X_Y_equis[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_equis[1]=coordenadas_X_Y_torres[1]-73;

            /// Boton para vender del menu

            coordenadas_X_Y_vender[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_vender[1]=coordenadas_X_Y_torres[1]-52;

            /// Boton para cambiar el menu por el menu de nivel+1

            coordenadas_X_Y_subirlvl[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_subirlvl[1]=coordenadas_X_Y_torres[1]-19;

            /// Boton para mejorar la torre

            coordenadas_X_Y_mejorar[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_mejorar[1]=coordenadas_X_Y_torres[1]-35;
            break;

        case 7:

            /// Espacio para la torre

            coordenadas_X_Y_torres[0]=414;
            coordenadas_X_Y_torres[1]=402;

            /// Espacio para el menu

            coordenadas_X_Y_menu[0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_menu[1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 1 del menu

            coordenadas_X_Y_torres_lvl_1[0][0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_torres_lvl_1[0][1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 2 del menu

            coordenadas_X_Y_torres_lvl_1[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_lvl_1[1][1]=coordenadas_X_Y_torres[1]-72;

            /// Torre 3 del menu

            coordenadas_X_Y_torres_lvl_1[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_lvl_1[2][1]=coordenadas_X_Y_torres[1]-72;

            /// Cruz para cerrar el menu

            coordenadas_X_Y_equis[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_equis[1]=coordenadas_X_Y_torres[1]-73;

            /// Boton para vender del menu

            coordenadas_X_Y_vender[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_vender[1]=coordenadas_X_Y_torres[1]-52;

            /// Boton para cambiar el menu por el menu de nivel+1

            coordenadas_X_Y_subirlvl[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_subirlvl[1]=coordenadas_X_Y_torres[1]-19;

            /// Boton para mejorar la torre

            coordenadas_X_Y_mejorar[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_mejorar[1]=coordenadas_X_Y_torres[1]-35;
            break;

        case 8:

            /// Espacio para la torre

            coordenadas_X_Y_torres[0]=562;
            coordenadas_X_Y_torres[1]=370;

            /// Espacio para el menu

            coordenadas_X_Y_menu[0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_menu[1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 1 del menu

            coordenadas_X_Y_torres_lvl_1[0][0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_torres_lvl_1[0][1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 2 del menu

            coordenadas_X_Y_torres_lvl_1[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_lvl_1[1][1]=coordenadas_X_Y_torres[1]-72;

            /// Torre 3 del menu

            coordenadas_X_Y_torres_lvl_1[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_lvl_1[2][1]=coordenadas_X_Y_torres[1]-72;

            /// Cruz para cerrar el menu

            coordenadas_X_Y_equis[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_equis[1]=coordenadas_X_Y_torres[1]-73;

            /// Boton para vender del menu

            coordenadas_X_Y_vender[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_vender[1]=coordenadas_X_Y_torres[1]-52;

            /// Boton para cambiar el menu por el menu de nivel+1

            coordenadas_X_Y_subirlvl[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_subirlvl[1]=coordenadas_X_Y_torres[1]-19;

            /// Boton para mejorar la torre

            coordenadas_X_Y_mejorar[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_mejorar[1]=coordenadas_X_Y_torres[1]-35;
            break;

            case 9:

            /// Espacio para la torre

            coordenadas_X_Y_torres[0]=559;
            coordenadas_X_Y_torres[1]=236;

            /// Espacio para el menu

            coordenadas_X_Y_menu[0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_menu[1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 1 del menu

            coordenadas_X_Y_torres_lvl_1[0][0]=coordenadas_X_Y_torres[0]-75;
            coordenadas_X_Y_torres_lvl_1[0][1]=coordenadas_X_Y_torres[1]-73;

            /// Torre 2 del menu

            coordenadas_X_Y_torres_lvl_1[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_lvl_1[1][1]=coordenadas_X_Y_torres[1]-72;

            /// Torre 3 del menu

            coordenadas_X_Y_torres_lvl_1[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_lvl_1[2][1]=coordenadas_X_Y_torres[1]-72;

            /// Cruz para cerrar el menu

            coordenadas_X_Y_equis[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_equis[1]=coordenadas_X_Y_torres[1]-73;

            /// Boton para vender del menu

            coordenadas_X_Y_vender[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_vender[1]=coordenadas_X_Y_torres[1]-52;

            /// Boton para cambiar el menu por el menu de nivel+1

            coordenadas_X_Y_subirlvl[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_subirlvl[1]=coordenadas_X_Y_torres[1]-19;

            /// Boton para mejorar la torre

            coordenadas_X_Y_mejorar[0]=coordenadas_X_Y_torres[0]+102;
            coordenadas_X_Y_mejorar[1]=coordenadas_X_Y_torres[1]-35;
            break;

        }

        torres[i]=Boton(49,90,coordenadas_X_Y_torres[0],coordenadas_X_Y_torres[1]);
        torres_tipo[0][i]=Boton(58,71,coordenadas_X_Y_torres_lvl_1[1][0],coordenadas_X_Y_torres_lvl_1[1][1]);
        torres_tipo[1][i]=Boton(58,71,coordenadas_X_Y_torres_lvl_1[2][0],coordenadas_X_Y_torres_lvl_1[2][1]);
        torres_tipo[2][i]=Boton(58,71,coordenadas_X_Y_torres_lvl_1[0][0],coordenadas_X_Y_torres_lvl_1[0][1]);
        torres_equis[i]=Boton(19,18,coordenadas_X_Y_equis[0],coordenadas_X_Y_equis[1]);
        torres_mejorar[i]=Boton(19,16,coordenadas_X_Y_mejorar[0],coordenadas_X_Y_mejorar[1]);
        torres_vender[i]=Boton(19,16,coordenadas_X_Y_vender[0],coordenadas_X_Y_vender[1]);
        torres_menu_area[i]=Boton(196,72,coordenadas_X_Y_menu[0],coordenadas_X_Y_menu[1]);
        torres_subirlvl[i]=Boton(19,17,coordenadas_X_Y_subirlvl[0],coordenadas_X_Y_subirlvl[1]);

        mensaje_dinero_s[i].setPosition(coordenadas_X_Y_torres[0]-85,coordenadas_X_Y_torres[1]);
        mensaje_dinero_s[i].setScale(0.5,0.5);
    }

    /// Declaracion del vector de menues de torres------------------------------
    bool Ocupado[posiciones_torres];

    /// Vector de niveles de los menues
    int nivel_de_torre[posiciones_torres];
    inicializar_vector_entero(nivel_de_torre,posiciones_torres,0);

    ponerEnFalso(Ocupado, posiciones_torres);

    /// Texturas----------------------------------

    /// CANTIDAD DE MENUES
    const int menus=3;

    Textura textura_menu_torre[menus];
    /// MENU DE TORRES 1
    textura_menu_torre[0].cargar("img/Menu_Torres_1.png",0,true);
    /// MENU DE TORRES 2
    textura_menu_torre[1].cargar("img/Menu_Torres_2.png",0,true);
    /// MENU DE TORRES 3
    textura_menu_torre[2].cargar("img/Menu_Torres_3.png",0,true);

    /// MATRIZ DE CLASE TORRE TIPO X NIVEL

    Textura rango_torres_textura("img/rango.png");
    Textura texturas_torres[3][3];

    for (i=0; i<3; i++)
    {
        switch (i)
        {
        case 0:
            texturas_torres[i][0].cargar("img/T1-1.png",0,true);
            texturas_torres[i][1].cargar("img/T1-2.png",0,true);
            texturas_torres[i][2].cargar("img/T1-3.png",0,true);
            break;
        case 1:
            texturas_torres[i][0].cargar("img/T2-1.png",0,true);
            texturas_torres[i][1].cargar("img/T2-2.png",0,true);
            texturas_torres[i][2].cargar("img/T2-3.png",0,true);
            break;
        case 2:
            texturas_torres[i][0].cargar("img/T3-1.png",0,true);
            texturas_torres[i][1].cargar("img/T3-2.png",0,true);
            texturas_torres[i][2].cargar("img/T3-3.png",0,true);
            break;
        default:
            break;
        }
    }

    Torre vec_torres[posiciones_torres];
    Torre aux_torre;

    for(x=0; x<posiciones_torres; x++)
    {
        vec_torres[x]=Torre(0,0);
    }
    aux_torre=Torre(0,0);

    /// Sprites-------------

    Sprite Sprite_menu_torre[menus][posiciones_torres];
    for (x=0; x<posiciones_torres; x++)
    {
        ///menues------------

        for(int t=0; t<3; t++)
        {
            Sprite_menu_torre[t][x].setTexture(textura_menu_torre[t].getTextura());
            Sprite_menu_torre[t][x].setPosition(torres[x].getEsix()-75,torres[x].getEsiy()-72);
        }
    }
    int a = 0;

    // ----------------------------------------------------------------------------------------------------------------------
    //*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // VARIABLES PARA LA SIGUIENTE OLEADA

    int bichos_muertos=0;
    int vida_aumentada=0;
    int oleada=1;
    Texto oleada_texto(font_texto2.getFont(),oleada,17,843,202,Color::Yellow,true);



    /*
    Rect<jojo>::Rect(200,200,50,50);
    */
//vidas
    float opacidad_menu=0; //transparencia del objeto 255=100% porciento

    for (i=0; i<=cantidad_bichos-1; i++)
    {
        //Seria un corte de control donde por cada vuelta de J se cargara un frame de un tipo de bicho, faltaria la forma
        //dinamica de indicar a cual tipo de monstruo cargar en cada fila de la matriz
        /*
        for (int j=0;j++<=2;j++) {*/
        /*
        enemigo[i][j]...
        enemigo[i][j]...
        enemigo[i][j]...
        */
        /*
        enemigo[i]=CircleShape(25.f);
        */

        /*
        enemigo[i].setTexture(textura_bicho);
        enemigo[i].setColor(Color(255,255,255,opacidad_objetos[i]));
        enemigo[i].setPosition(285,0);
        */
        /*
        }*/
    }

    int objetos=0;
    int tiempo=1;
    int estado_juego=2;

    //Todo lo que se necesita para crear un texto son 2 lineas de codigo, Nueva Clase Texto, Parametros:

    //1)Formato de texto: ruta donde esta alojado el tipo de texto.
    //2)variable a convertir, debe ser int, proximamente constructor para texto plano.
    //3)Tamaño del texto, similar al word cuando pones el tamaño de la letra.
    //4)Posicion de la pantalla en coordenadas de pixeles en X.
    //5)Posicion de la pantalla en coordenadas de pixeles en Y.
    //6)Color: Se debe anteponer Color:: y despues el color dentro de los contenidos por Sfml,

    //Podriamos agregar using namespace Color, pero seria demasiado exagerado, posiblemente agrege
    //un constructor para colores en RGB y transparencia, pero mas adelante.

    //El objeto texto junto con el pasaje de variable a string se hacen simultaneamente.
    //para cambiar el string, se usa el metodo setVariable(variable), que explico mas abajo con la variable tiempo.

    //Para todo tipo de carga de archivos se debe verificar la carga con un metodo de confirmacion, que devuelve un verdadero
    //o falso, en caso de una carga incorrecta el programa se detendra para la visibilidad del error, el constructor no puede
    //hacerlo por si mismo, dado que no puede devolver ningun valor, es cosa nuestra asegurarlo.

    //-------------------------

    Texto tiempo_texto(font_texto2.getFont(),tiempo,25,667,500);

    //-------------------------

    //Sistema de colas para las torres

    ///y si gente, es un new de una tridimensional, sorprendidos no?

    int (*colas_torres_3d) [cantidad_torres][cantidad_bichos+1] = new int[posiciones_torres][cantidad_torres][cantidad_bichos+1];

    ///para entender esto, o al menos saber con se declaran, porque ni yo entendi un cuerno, les dejo el link donde lo
    ///explican con el titulo §5  Asignar el valor devuelto, con la linea : int (* mptr3)[10][2] = new int[3][10][2];
    ///Link: https://www.zator.com/Cpp/E4_9_20c.htm

    ///Inicializador dinamico de la cola-----------------
    int valor=-10000;
    for (f=0; f<posiciones_torres; f++)
    {
        for (c=0; c<cantidad_torres; c++)
        {
            colas_torres_3d[f][c][cantidad_bichos]=0;
            for (x=0; x<cantidad_bichos; x++)
            {
                colas_torres_3d[f][c][x]=valor;
            }
        }
    }
    ///---------------------------------------------------

    int prioridad,pos_enemigo_siguiente,pos_enemigo_sacar;
    bool detector=false;
    //-------------------------------------------

    //definicion de la ventana del juego---------------------
    RenderWindow window(VideoMode(tamx_actual,tamy_actual), "Tower Defense - La defensa del fuerte Nicomando");
    //Setea el framerate a 60 fps, comentar para mas velocidad,seteado para ver la velocidad real del juego
    //bugeo de los sprites solucionado seteando el Smooth de los Sprites en True.
    window.setFramerateLimit(60);
    //metodo para que no se tome en cuenta las repeticiones al presionar una tecla, similar a la booleana habilitacion_mouse
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);
    Textura puntero("img/puntero.png",0,true);
    Sprite puntero1(puntero.getTextura());
    puntero1.scale(0.4,0.4);
    while (window.isOpen())
    {

        Event event;
        //Zona de estados del juego-------------------------------------------
        while (window.pollEvent(event))
        {

            //si la ventana se cierra-------------
            if (event.type == Event::Closed)
            {
                window.close();
            }
            //------------------------------------


            //La magia de las resoluciones y conversion de los pixeles por defecto a pixeles customizados------------

            if (event.type != Event::LostFocus)
            {
                tamx=window.getSize().x;
                tamy=window.getSize().y;
                if (tamx!=1000||tamy!=600)
                {
                    pixeles_convertidos=window.mapPixelToCoords(Vector2i(Mouse::getPosition(window).x,Mouse::getPosition(window).y));
                    mousexy[0]=pixeles_convertidos.x;
                    mousexy[1]=pixeles_convertidos.y;
                }

                else
                {
                    mousexy[0]=Mouse::getPosition(window).x;
                    mousexy[1]=Mouse::getPosition(window).y;
                }
                mousex.setVariable(mousexy[0]);
                mousey.setVariable(mousexy[1]);
                //fin resoluciones---------------------------------------------------------------------------------------

                if (Mouse::isButtonPressed(Mouse::Left)&&estado_juego==2)
                {
                    //Pantalla Completa

                    if (pantalla_completa.click(mousexy))
                    {
                        if (!pantalla_completa.getEncendido())
                        {
                            window.create(VideoMode(tamx_actual,tamy_actual),"Tower Defense - La defensa del fuerte Nicomando",Style::Fullscreen);
                            pantalla_completa.setEncendido(true);
                            window.setView(vista_del_juego);
                            window.setFramerateLimit(60);
                            window.setKeyRepeatEnabled(false);
                            window.setMouseCursorVisible(false);
                        }
                        else
                        {
                            window.create(VideoMode(tamx_actual,tamy_actual),"Tower Defense - La defensa del fuerte Nicomando");
                            pantalla_completa.setEncendido(false);
                            window.setView(vista_del_juego);
                            window.setFramerateLimit(60);
                            window.setKeyRepeatEnabled(false);
                            window.setMouseCursorVisible(false);
                        }
                    }

                }
            }
            //-------------------------------------------

            //EVENTO SI UNA TECLA ES PRESIONADA

            if (event.type == Event::KeyPressed)
            {
                //debug del juego------------tecla d---------

                if (Keyboard::isKeyPressed(Keyboard::D))
                {

                    if (!teclado)
                        teclado=true;
                    else
                    {
                        teclado=false;
                    }
                }
                //--------------------------------------------

                //Salir del juego al menu principal------tecla escape-------------

                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    estado_juego=2;
                    vida_juego=const_vida_juego;
                    vida_juego_texto.setVariable(vida_juego);
                    aldeano.setVida(0);
                    vida_aumentada=0;
                    cargar_vector_sprites(enemigo,aldeano,cantidad_bichos);
                    for(o=0; o<cantidad_bichos; o++)
                    {
                        vidas_texto[o].setVariable(enemigo[o].getVida());
                        vidas_texto[o].setPosicion(aldeano.getX()+13,aldeano.getY()+48);
                        vidas_texto[o].setTransparencia(0);
                    }
                    enemigos_muertos=0;
                    muertos_texto.setVariable(enemigos_muertos);
                    dinero=300;
                    dinero_texto.setVariable(dinero);
                    tiempo=1;
                    objetos=0;
                    oleada=1;
                    oleada_texto.setVariable(oleada);
                    musica_juego.parar();
                    primer_carga=false;
                    opacidad_menu=0;
                    boolmusicajuego=false;
                    for(l=0; l<posiciones_torres; l++)
                    {
                        /// TORRES -------------------------------------
                        Ocupado[l]=false;
                        vec_torres[l].setTipoNivel();
                        /// RANGOS -------------------------------------
                        /*
                        for(int f=0; f<posiciones_torres; f++)
                        {
                            vec_torres[f].setPosicionTorre(10000,0);
                            vec_torres[f].setPosicionRango(10000,0);
                        }
                        */
                    }
                    for (f=0; f<posiciones_torres; f++)
                    {
                        for (c=0; c<cantidad_torres; c++)
                        {
                            colas_torres_3d[f][c][cantidad_bichos]=0;
                            for (x=0; x<cantidad_bichos; x++)
                            {
                                colas_torres_3d[f][c][x]=valor;
                            }
                        }
                    }
                }

                /*
                ///Primer cinematica del juego - testeos
                if (Keyboard::isKeyPressed(Keyboard::A))
                {
                    if (!test1.getRepeticion())
                        test1.setEstado(true);

                    else
                    {
                        if (!test1.getEstado())
                            test1.setEstado(true);
                        else
                            test1.setEstado(false);
                    }
                    test1.Reicicio();
                }

                if (Keyboard::isKeyPressed(Keyboard::F))
                {
                    if (!viejo_test.getRepeticion())
                        viejo_test.setEstado(true);

                    else
                    {
                        if (!viejo_test.getEstado())
                            viejo_test.setEstado(true);
                        else
                            viejo_test.setEstado(false);
                    }
                    viejo_test.Reicicio();
                }
                */
                //--------------------------------------------------------------
            }
        }
        //fin de la zona de estados del juego------------------------------------

        //Animaciones de los zombies ----

        /*
        for(i=1; i<cantidad_bichos; i++)
        {
            for (a=0; a<cantidad_bichos; a++)
            {

            }
        }

        ///---------
        */

        window.clear();

        ///testeos con los bichos--Descomentar para usar--cantidad de bichos especifica por pantalla para realizar tests.

        /*
        if (tiempo%150==0)   ///cantidad de bichos hasta que el tiempo_spawn es cambiado,acorde al tiempo_spawn inicial.
        {
            tiempo_spawn=500;  ///poner un absurdo o un numero grande, para que asi solo entren la cantidad de zombies deseada
        }                       ///para el testeo
        */

        // Estados del Juego-----------------------------------

        switch (estado_juego)
        {
        case 0:  // Cuando el juego esta en pausa, solo se dibuja, no se modifican las variables.

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if (reanudar.click(mousexy))
                {
                    musica_juego.reproducir();
                    estado_juego=3;
                }
            }

            // MAPA DEL JUEGO

            window.draw(mapa);


            // DEBUG

            if (teclado)
            {
                // COORDENADAS DEL MOUSE

                window.draw(mousex.getTexto());
                window.draw(mousey.getTexto());
                // VARIABLE TIEMPO

                window.draw(tiempo_texto.getTexto());
            }

            // VIDA DEL JUEGO
            window.draw(vida_juego_texto.getTexto());
            // DINERO DEL JUEGO

            window.draw(dinero_texto.getTexto());
            // OLEADA

            window.draw(oleada_texto.getTexto());

            // TORRES Y SUS AREAS

            for (x=0; x<posiciones_torres; x++)
            {
                if(vec_torres[x].getTipo()!=0)
                {
                    window.draw(vec_torres[x].getSpriteCuerpo());
                    window.draw(vec_torres[x].getSpriteRango());
                }
                if (prioridad_dibujo[x])
                {
                    window.draw(vec_torres[x].get_Tiro());
                }
            }

            // ZOMBIES Y SUS VIDAS

            for (d=1; d<=objetos; d++)
            {
                if (enemigo[d-1].getVida()>0)
                {
                    window.draw(enemigo[d-1].getZombie());
                    window.draw(vidas_texto[d-1].getTexto());
                }
            }

            //Cantidad de zombies muertos

            window.draw(muertos_texto.getTexto());

            //

            /// MENU DE LAS TORRES

            for (x=0; x<posiciones_torres; x++)
            {
                if (menu_abierto[x]==true)
                {
                    switch(nivel_del_menu[x]+1)
                    {
                    case 1:
                        window.draw(Sprite_menu_torre[0][x]);
                        break;
                    case 2:
                        window.draw(Sprite_menu_torre[1][x]);
                        break;
                    case 3:
                        window.draw(Sprite_menu_torre[2][x]);
                        break;
                    }
                }
            }

            break;  // fin de estado pausa del juego

        case 1:  // ESTADO DERROTADO---------------------------

            if (!reproductor.getEncendido())
            {
                musica_juego.parar();
                reproductor.encender();
                reproductor.abrir("img/cinematicas/derrota.mp4",window);
            }
            /*
            window.draw(derrota);
            if (!boolmusicaderrota)
            {
                musica_juego.parar();
                musica_derrota.reproducir();
                boolmusicaderrota=true;
            }
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if (derrota_boton.click(mousexy))
                {
                */
            if (reproductor.fin_video())
            {
                reproductor.apagar();
                estado_juego=2;
                vida_juego=const_vida_juego;
                vida_juego_texto.setVariable(vida_juego);
                aldeano.setVida(0);
                vida_aumentada=0;
                cargar_vector_sprites(enemigo,aldeano,cantidad_bichos);
                for(o=0; o<cantidad_bichos; o++)
                {
                    vidas_texto[o].setVariable(enemigo[o].getVida());
                    vidas_texto[o].setPosicion(aldeano.getX()+13,aldeano.getY()+48);
                    vidas_texto[o].setTransparencia(0);
                }
                enemigos_muertos=0;
                muertos_texto.setVariable(enemigos_muertos);
                dinero=300;
                dinero_texto.setVariable((dinero));
                tiempo=1;
                objetos=0;
                oleada=1;
                oleada_texto.setVariable(oleada);
                ///musica_derrota.parar();
                primer_carga=false;
                opacidad_menu=0;
                boolmusicaderrota=false;
                for(l=0; l<posiciones_torres; l++)
                {
                    // TORRES -------------------------------------
                    vec_torres[l].setTipoNivel();
                    Ocupado[l]=false;
                }
                for (f=0; f<posiciones_torres; f++)
                {
                    for (c=0; c<cantidad_torres; c++)
                    {
                        colas_torres_3d[f][c][cantidad_bichos]=0;
                        for (x=0; x<cantidad_bichos; x++)
                        {
                            colas_torres_3d[f][c][x]=valor;
                        }
                    }
                }
            }
            /*
            }
            }
            */
            break; // fin del estado derrotado

        case 2:  // ESTADO MENU PRINCIPAL-----------------------------------

            if (reg_config.getSonido_menu()&&!primer_carga)
            {
                musica_menu.reproducir();
                primer_carga=true;
            }

            menu.setColor(Color(255,255,255,opacidad_menu));
            window.draw(menu);
            // window.draw(texto_prueba);
            if (opacidad_menu<255)
            {
                opacidad_menu+=5;
            }
            else
            {
                if (reproductor.getEncendido())
                {
                    if (reproductor.fin_video())
                    {
                        estado_juego=3;
                        buffer.loadFromFile("musica/FX/dead_effect2.ogg");
                        fx.setBuffer(buffer);
                        reproductor.apagar();
                        musica_juego.reproducir();
                    }
                }

                if (nueva_partida.click(mousexy)||cargar_partida_boton.click(mousexy)||salir.click(mousexy)||
                        sonido_menu.click(mousexy)||pantalla_completa.click(mousexy))
                {
                    if (fx_bool)
                    {
                        fx.play();
                        fx_bool=false;
                    }
                }
                else
                {
                    fx_bool=true;
                }

                //Configuracion de los botones en el menu principal-----------

                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    if (habilitacionmouse)
                    {

                        // Nueva partida

                        if (nueva_partida.click(mousexy))
                        {
                            /*
                            volumen_menu-=0.1;
                            musica_menu.setVolume(volumen_menu);
                                */
                            if (!reproductor.getEncendido())
                            {
                                musica_menu.parar();
                                reproductor.encender();
                                reproductor.abrir("img/cinematicas/intro.mp4",window);
                            }
                        }

                        // Cargar Partida

                        if (cargar_partida_boton.click(mousexy))
                        {
                            game.leerendisco();

                            vida_juego=game.getvidas();
                            vida_juego_texto.setVariable(vida_juego);
                            aldeano.setVida(0+(100*game.getoleada()-100));
                            vida_aumentada=0+(100*game.getoleada()-100);
                            cargar_vector_sprites(enemigo,aldeano,cantidad_bichos);
                            for(o=0; o<cantidad_bichos; o++)
                            {
                                vidas_texto[o].setVariable(enemigo[o].getVida());
                                vidas_texto[o].setPosicion(aldeano.getX()+13,aldeano.getY()+48);
                                vidas_texto[o].setTransparencia(0);
                            }
                            dinero=game.getdinero();
                            dinero_texto.setVariable(dinero);
                            tiempo=1;
                            objetos=0;
                            oleada=game.getoleada();
                            oleada_texto.setVariable(oleada);
                            musica_menu.parar();

                            primer_carga=false;
                            opacidad_menu=0;
                            boolmusicajuego=false;
                            /*
                            for(int x=0; x<posiciones_torres; x++)
                            {
                                Ocupado[x]=game.getpos_torres(x);
                                vec_torres[x].setTipoNivel(game.gettipo_torres(x),game.getniv_torres(x),texturas_torres[game.gettipo_torres(x)][game.getniv_torres(x)].getTextura() ,rango_torres_textura.getTextura());
                            }
                            */
                            for (f=0; f<posiciones_torres; f++)
                            {
                                for (c=0; c<cantidad_torres; c++)
                                {
                                    colas_torres_3d[f][c][cantidad_bichos]=0;
                                    for (x=0; x<cantidad_bichos; x++)
                                    {
                                        colas_torres_3d[f][c][x]=valor;
                                    }
                                }
                            }

                            estado_juego=3;
                            estado_juego=0;

                        }

                        //Salir

                        if (salir.click(mousexy))
                        {
                            musica_menu.parar();
                            window.close();
                        }

                        //Sonido

                        if (sonido_menu.click(mousexy))
                        {
                            if (reg_config.getSonido_menu())
                            {
                                reg_config.setSonido_menu(false);
                                musica_menu.volumen(0);
                            }
                            else
                            {
                                reg_config.setSonido_menu(true);
                                musica_menu.volumen(3);
                            }

                        }

                        habilitacionmouse=false;
                    }

                }
                else
                    habilitacionmouse=true;

            }
            break;  // fin estado menu principal

        case 3:   // ESTADO JUEGO------------------------------------

            // Cuando se pierde se cambia a estado derrota------
            if (vida_juego<=0)
            {
                estado_juego=1;

            }
            // ------------------------------------------------

            ///  COMIENZA EL JUEGO

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if (habilitacionmouse)
                {
                    /// PAUSA DEL JUEGO

                    if (pausa.click(mousexy))
                    {
                        musica_juego.pausar();
                        estado_juego=0;
                    }


                    if(guardar_partida.click(mousexy)&& bichos_muertos==10)
                    {
                        game.setdinero(dinero);
                        game.setvidas(vida_juego);
                        game.setoleada(oleada+1);

                        /// ---- GUARDADO DE TORRES ------

                        for(x=0; x<posiciones_torres; x++)
                        {
                            game.setpos_torre(x,Ocupado[x]);
                            game.settipo_torre(x,vec_torres[x].getTipo());
                            game.setniv_torres(x,vec_torres[x].getNivel());
                        }

                        /// ------------------------------

                        game.grabarendiso();

                        estado_juego=2;
                        vida_juego=const_vida_juego;
                        vida_juego_texto.setVariable(vida_juego);
                        aldeano.setVida(0);
                        vida_aumentada=0;
                        cargar_vector_sprites(enemigo,aldeano,cantidad_bichos);
                        for(o=0; o<cantidad_bichos; o++)
                        {
                            vidas_texto[o].setVariable(enemigo[o].getVida());
                            vidas_texto[o].setPosicion(aldeano.getX()+13,aldeano.getY()+48);
                            vidas_texto[o].setTransparencia(0);
                        }
                        dinero=300;
                        dinero_texto.setVariable(dinero);
                        tiempo=1;
                        objetos=0;
                        oleada=1;
                        oleada_texto.setVariable(oleada);
                        musica_juego.parar();
                        primer_carga=false;
                        opacidad_menu=0;
                        boolmusicajuego=false;
                        for(l=0; l<posiciones_torres; l++)
                        {
                            /// TORRES -------------------------------------
                            Ocupado[l]=false;
                            vec_torres[l].setTipoNivel();
                            /// RANGOS -------------------------------------
                            /*
                            for(int f=0; f<posiciones_torres; f++)
                            {
                                vec_torres[f].setPosicionTorre(10000,0);
                                vec_torres[f].setPosicionRango(10000,0);
                            }
                            */
                        }
                        for (f=0; f<posiciones_torres; f++)
                        {
                            for (c=0; c<cantidad_torres; c++)
                            {
                                colas_torres_3d[f][c][cantidad_bichos]=0;
                                for (x=0; x<cantidad_bichos; x++)
                                {
                                    colas_torres_3d[f][c][x]=valor;
                                }
                            }
                        }


                    }


                    // nueva oleada

                    if (nueva_oleada.click(mousexy)&&bichos_muertos==10)
                    {
                        vida_aumentada+=100;
                        aldeano.setVida(vida_aumentada);
                        cargar_vector_sprites(enemigo,aldeano,cantidad_bichos,oleada);
                        for(p=0; p<cantidad_bichos; p++)
                        {
                            vidas_texto[p].setVariable(enemigo[p].getVida());
                        }
                        bichos_muertos=0;
                        oleada++;
                        oleada_texto.setVariable(oleada);
                        objetos=0;
                        tiempo=1;

                        /// INFORMAR SOBRE UNA NUEVA OLEADA
                    }

                    // sonido

                    if (sonido.click(mousexy))
                    {
                        if (boolmusicajuego)
                        {
                            musica_juego.volumen(0);
                            boolmusicajuego=false;
                        }
                        else
                        {
                            musica_juego.volumen(3);
                            boolmusicajuego=true;
                        }
                    }

                    /// ---------------------------- TORRES ---------------------------- ///

                    for(x=0; x<posiciones_torres; x++)
                    {
                        if(habilitacionmouse==true && menu_abierto[x]==true)
                        {

                            /// CIERRE DEL MENU
                            if(torres_equis[x].click(mousexy))
                            {
                                menu_abierto[x]=false;
                            }

                            /// SUBIR NIVEL TORRE POR MENOS DE PRECIO
                            if(Ocupado[x]==true && torres_mejorar[x].click(mousexy) && vec_torres[x].getNivel()<3)
                            {
                                aux_torre=vec_torres[x];
                                aux_torre.subirNivel(texturas_torres[aux_torre.getTipo()-1][aux_torre.getNivel()].getTextura());
                                if(dinero>=(aux_torre.getPrecio()*2))
                                {
                                    dinero-=(aux_torre.getPrecio()*2);
                                    dinero_texto.setVariable(dinero);
                                    vec_torres[x].subirNivel(texturas_torres[vec_torres[x].getTipo()-1][vec_torres[x].getNivel()].getTextura());
                                }
                            }

                            /// VENDE LA TORRE Y TE DEVUELVE EL PRECIO DEL NIVEL ACTUAL (pero en int)
                            if(Ocupado[x]==true && torres_vender[x].click(mousexy))
                            {
                                Ocupado[x]=false;
                                dinero+=(vec_torres[x].getPrecio()*2);
                                dinero_texto.setVariable(dinero);
                                vec_torres[x].setTipoNivel();
                            }

                            /// SPAWNEO DE TORRES
                            for(y=0; y<3; y++)
                            {
                                if(Ocupado[x]==false && torres_tipo[y][x].click(mousexy))
                                {
                                    if (fx2.getPlayingOffset().asMilliseconds()>1000||fx2.getPlayingOffset().asSeconds()==0)
                                        fx2.play();

                                    vec_torres[x].setTipoNivel(y+1,nivel_del_menu[x]+1,texturas_torres[y][nivel_del_menu[x]].getTextura(),rango_torres_textura.getTextura());
                                    switch (y)
                                    {
                                    case 0:
                                        carcasa_escalada.setTexture(tiro_balin.getTextura());
                                        break;
                                    case 1:
                                        carcasa_escalada.setTexture(tiro_balin.getTextura());
                                        break;
                                    case 2:
                                        carcasa_escalada.setTexture(tiro_rayo.getTextura());
                                        break;
                                    default:
                                        break;
                                    }
                                    vec_torres[x].setPosicionTorre(torres[x].getEsix(),torres[x].getEsiy(),carcasa_escalada);
                                    vec_torres[x].setPosicionRango(torres[x].getEsix()-93,torres[x].getEsiy()-52);
                                    vec_torres[x].setEscalaRango(1,1.22);
                                    Ocupado[x]=true;
                                    dinero-=vec_torres[x].getPrecio();
                                    dinero_texto.setVariable(dinero);

                                    if(dinero>=vec_torres[x].getPrecio())
                                    {
                                        dinero-=vec_torres[x].getPrecio();
                                        dinero_texto.setVariable(dinero);
                                    }
                                    else
                                    {
                                        dinero+=vec_torres[x].getPrecio();
                                        dinero_texto.setVariable(dinero);
                                        Ocupado[x]=false;
                                        dinero_insuficiente[x]=true;
                                        Opacidad_Mensaje_Dinero[x]=255;
                                        vec_torres[x].setTipoNivel();
                                    }
                                }
                            }
                        }

                        /// HABILITACION DEL MENU
                        if(torres[x].click(mousexy)&&detectar_otro_menu_abierto(menu_abierto,posiciones_torres))
                        {
                            menu_abierto[x]=true;
                        }
                        else
                        {
                            if(torres_menu_area[x].click(mousexy))
                            {
                                /// NIVEL DEL MENU
                                if(torres_subirlvl[x].click(mousexy))
                                {
                                    nivel_del_menu[x]++;
                                    if(nivel_del_menu[x]>2)
                                    {
                                        nivel_del_menu[x]=0;
                                    }
                                }
                            }
                            else
                            {
                                menu_abierto[x]=false;
                                nivel_del_menu[x]=0;
                            }
                        }
                    }
                    // mientras el mouse este presionado no repetira ninguna accion en bucle hasta q se suelte el click izquierdo
                    habilitacionmouse=false;
                }
            }
            else
            {
                // una vez que se solto el mouse, recien se habilita para una nueva accion
                habilitacionmouse=true;
            }

///--------------------------Sector de Dibujado-------------------------------------------------------------------

            // MAPA DEL JUEGO
            /*
                        for (i=1; i<=8; i++)
                        {
                            for (z=1; z<=10; z++)
                            {
                                window.draw(pasto.getFrame());
                                pasto.setX(pasto.getX()+84);
                            }
                            pasto.setX(0);
                            pasto.setY(pasto.getY()+80);
                        }
                        pasto.setPosicion(0,-40);
                        pasto.Actualizar_frame();
            */
            window.draw(mapa);

            if(guardar_f==true && Opacidad_Mensaje_guardar>0)
            {
                guardar_f=false;


                Opacidad_Mensaje_guardar--;
                mensajee_guardar.setColor(Color(255,255,255,Opacidad_Mensaje_Partida));
                window.draw(mensajee_guardar);


            }


            // VIDA DEL JUEGO
            window.draw(vida_juego_texto.getTexto());
            // DINERO DEL JUEGO
            window.draw(dinero_texto.getTexto());
            // OLEADA
            window.draw(oleada_texto.getTexto());

            if (teclado)
            {
                // COORDENADAS DEL MOUSE
                window.draw(mousex.getTexto());
                window.draw(mousey.getTexto());
                // VARIABLE TIEMPO
                window.draw(tiempo_texto.getTexto());
            }



            for(x=0; x<posiciones_torres; x++)
            {
                if(dinero_insuficiente[x]==true)
                {
                    Opacidad_Mensaje_Dinero[x]--;
                    mensaje_dinero_s[x].setColor(Color(255,255,255,Opacidad_Mensaje_Dinero[x]));
                    window.draw(mensaje_dinero_s[x]);

                    if(Opacidad_Mensaje_Dinero[x]<=0)
                    {
                        dinero_insuficiente[x]=false;
                        Opacidad_Mensaje_Dinero[x]=255;
                    }
                }
            }

            window.draw(muertos_texto.getTexto());



///*///////////////////////////////////////////////////////////- Spawnear torres -///////////////////////////////////////////////////////////////////////////

            for (x=0; x<posiciones_torres; x++)
            {
                if(vec_torres[x].getTipo()!=0)
                {
                    window.draw(vec_torres[x].getSpriteCuerpo());
                    if(menu_abierto[x]==true)
                    {
                        window.draw(vec_torres[x].getSpriteRango());
                    }
                }
            }
///*///////////////////////////////////////////////////////////------------------///////////////////////////////////////////////////////////////////////////

            for (d=1; d<=objetos; d++)
            {
                if (enemigo[d-1].getVida()>0)
                {
                    window.draw(enemigo[d-1].getZombie());
                    window.draw(vidas_texto[d-1].getTexto());
                }
                else if (!enemigo[d-1].getMuerto()&&enemigo[d-1].getEstado()!=7)
                {
                    if (fx.getPlayingOffset().asMilliseconds()>4000||fx.getPlayingOffset().asSeconds()==0)
                        fx.play();

                    enemigo[d-1].setMuerto();
                    enemigos_muertos++;
                    muertos_texto.setVariable(enemigos_muertos);
                }

                // esto serian los mini-estados de los sprites, 3 cases por ser 3 frames o mini-sprites

                /*
                switch(mini_estados) {
                case 1:
                break;
                case 2:---------
                break;
                case 3:
                break;
                }
                */
            }

            for (x=0; x<posiciones_torres; x++)
            {
                if (menu_abierto[x]==true)
                {
                    window.draw(Sprite_menu_torre[nivel_del_menu[x]][x]);
                }
                if (prioridad_dibujo[x])
                {
                    window.draw(vec_torres[x].get_Tiro());
                    prioridad_dibujo[x]=false;
                }
            }

            if(tiempo>=200 && Opacidad_Mensaje_Partida>0)
            {
                tiempo_inicial=false;
                Opacidad_Mensaje_Partida-=2;
                if(Opacidad_Mensaje_Partida<0)
                {
                    Opacidad_Mensaje_Partida=0;
                }
                mensaje_post_partida_S.setColor(Color(255,255,255,Opacidad_Mensaje_Partida));
                window.draw(mensaje_post_partida_S);
            }
            else
            {
                if (tiempo_inicial==true)
                {
                    window.draw(mensaje_post_partida_S);
                }
            }

///----------------------Fin Sector Dibujado-------------------------------------------------

            for (i=1; i<=objetos; i++)
            {
                enemigo[i-1].cambiar_frame_sprite();

                // Spot para detener el debug por tiempo,sin importancia------------

                if (tiempo%300==0)
                {
                    debug=0;
                }
                // --------------------------------------

                // COLAS DE LAS TORRES-----matriz tridimensional---------

                for (x=0; x<posiciones_torres; x++)
                {
                    for(f=0; f<cantidad_torres; f++)
                    {
                        //// Si el enemigo colisiona con el rango de una torre, este le hace daño segun sus caracteristicas,
                        ////si se muere, su posicion se mueve a (0,0), para que su sprite no estorbe en la caja de colisiones.

                        if (PixelPerfectTest(enemigo[i-1].getZombie(),vec_torres[x].getSpriteRango()))
                        {
                            ////el enemigo es encolado, si solo si, nunca fue encolado en la cola de una torre, por su tipo,
                            ////si esa cola no esta llena y por ultimo si este no esta muerto.

                            if (!enemigo[i-1].getEncolado(x,f)&&colas_torres_3d[x][f][cantidad_bichos]<10&&!enemigo[i-1].getMuerto())
                            {
                                colas_torres_3d[x][f][colas_torres_3d[x][f][cantidad_bichos]]=i-1;
                                colas_torres_3d[x][f][cantidad_bichos]++;
                                enemigo[i-1].setEncolado(x,f,true);
                                enemigo[i-1].setIntervalo_danio(vec_torres[x].getIntervalo(),f);
                                enemigo[i-1].setDanio_torre(vec_torres[x].getDanio(),f);
                            }
                        }
                        else
                        {
                            for (z=0; z<cantidad_bichos; z++)
                            {
                                if (colas_torres_3d[x][f][z]==i-1)
                                    detector=true;
                            }

                            if (colas_torres_3d[x][f][cantidad_bichos]>0&&detector)
                            {
                                enemigo[i-1].setEncolado(x,f,false);
                                enemigo[i-1].setColor(255,255,255);
                                colas_torres_3d[x][f][cantidad_bichos]--;
                                vec_torres[x].resetear_tiro();

                                ///Ordenador de la cola de manera dinamica---------------

                                for (z=0; z<cantidad_bichos; z++)
                                {
                                    if (colas_torres_3d[x][f][z]==i-1)
                                        pos_enemigo_sacar=z;
                                }

                                pos_enemigo_siguiente=pos_enemigo_sacar+1;

                                for (z=pos_enemigo_sacar ; z<cantidad_bichos; z++)
                                {
                                    colas_torres_3d[x][f][z]=colas_torres_3d[x][f][pos_enemigo_siguiente];
                                    pos_enemigo_siguiente++;
                                }
                                colas_torres_3d[x][f][cantidad_bichos-1]=-10000;

                                ///------------------------------------------------------
                            }
                            detector=false;
                        }

                        prioridad=colas_torres_3d[x][f][0];

                        if (prioridad==i-1&&prioridad!=-10000)
                        {
                            enemigo[i-1].setIntervalo_danio(vec_torres[x].getIntervalo(),f);
                            enemigo[i-1].setDanio_torre(vec_torres[x].getDanio(),f);
                            vec_torres[x].cambiar_traza(enemigo[prioridad].getX(),enemigo[prioridad].getY(),enemigo[prioridad].getVelocidad());
                            prioridad_dibujo[x]=true;

                            if (enemigo[prioridad].getIntervalo_danio(f)!=10000)
                            {
                                if (tiempo%enemigo[prioridad].getIntervalo_danio(f)==0)
                                {
                                    enemigo[prioridad].reducir_vida(f);
                                    vidas_texto[prioridad].setVariable(enemigo[prioridad].getVida());
                                    enemigo[prioridad].setColor(50,50,77);

                                    if (enemigo[i-1].getVida()<=0)
                                    {
                                        enemigo[i-1].setEncolado(x,f,false);
                                        colas_torres_3d[x][f][cantidad_bichos]--;
                                        vec_torres[x].resetear_tiro();

                                        ///Ordenador de la cola de manera dinamica---------------

                                        for (z=0; z<cantidad_bichos; z++)
                                        {
                                            if (colas_torres_3d[x][f][z]==i-1)
                                                pos_enemigo_sacar=z;
                                        }

                                        pos_enemigo_siguiente=pos_enemigo_sacar+1;

                                        for (z=pos_enemigo_sacar ; z<cantidad_bichos; z++)
                                        {
                                            colas_torres_3d[x][f][z]=colas_torres_3d[x][f][pos_enemigo_siguiente];
                                            pos_enemigo_siguiente++;
                                        }
                                        colas_torres_3d[x][f][cantidad_bichos-1]=-10000;

                                        ///------------------------------------------------------

                                        dinero+=20;
                                        dinero_texto.setVariable(dinero);
                                    }
                                }
                                else
                                {
                                    enemigo[prioridad].setColor(255,255,255);
                                }

                            }
                        }
                    }
                }

                // FIN COLAS TORRES-------------------------------------

                if (!enemigo[i-1].getMuerto())
                {
                    vidas_texto[i-1].setPosicion(enemigo[i-1].getX()+13,enemigo[i-1].getY()+48);
                }
                else
                {
                    vidas_texto[i-1].setPosicion(aldeano.getX()+13,aldeano.getY()+48);
                    vidas_texto[i-1].setTransparencia(0);
                }



                /*
                switch (estados[i-1])
                {
                case 4:
                    ///ANIMACION ARRIBA
                    if (animaciones[i-1].getElapsedTime().asSeconds()>0.100f)
                    {
                        switch (num_sprite[i-1])
                        {
                        ///left es X
                        ///top es Y
                        ///width es ancho
                        ///height es alto
                        case 1:
                            porcion_de_sprite.left=22;
                            porcion_de_sprite.top=13;
                            porcion_de_sprite.width=45;
                            porcion_de_sprite.height=70;
                            num_sprite[i-1]=2;
                            retorno[i-1]=false;
                            break;
                        case 2:
                            porcion_de_sprite.left=88;
                            porcion_de_sprite.top=13;
                            porcion_de_sprite.width=45;
                            porcion_de_sprite.height=70;
                            if (retorno[i-1])
                                num_sprite[i-1]=1;
                            else
                                num_sprite[i-1]=3;
                            break;
                        case 3:
                            porcion_de_sprite.left=155;
                            porcion_de_sprite.top=13;
                            porcion_de_sprite.width=45;
                            porcion_de_sprite.height=70;
                            num_sprite[i-1]=2;
                            retorno[i-1]=true;
                            break;
                        }
                        animacion_muestra_menu.setTextureRect(porcion_de_sprite);
                        enemigo[i-1].setTextureRect(porcion_de_sprite);
                        animaciones[i-1].restart();
                    }
                    break;
                case 3:
                case 5:
                case 6:
                    ///ANIMACION DERECHA
                    if (animaciones[i-1].getElapsedTime().asSeconds()>0.100f)
                    {
                        switch (num_sprite[i-1])
                        {
                        case 1:
                            porcion_de_sprite.left=23;
                            porcion_de_sprite.top=101;
                            porcion_de_sprite.width=45;
                            porcion_de_sprite.height=70;
                            num_sprite[i-1]=2;
                            retorno[i-1]=false;
                            break;
                        case 2:
                            porcion_de_sprite.left=91;
                            porcion_de_sprite.top=98;
                            porcion_de_sprite.width=45;
                            porcion_de_sprite.height=72;
                            if (retorno[i-1])
                                num_sprite[i-1]=1;
                            else
                                num_sprite[i-1]=3;
                            break;
                        case 3:
                            porcion_de_sprite.left=157;
                            porcion_de_sprite.top=101;
                            porcion_de_sprite.width=45;
                            porcion_de_sprite.height=70;
                            num_sprite[i-1]=2;
                            retorno[i-1]=true;
                            break;
                        }
                        animacion_muestra_menu.setTextureRect(porcion_de_sprite);
                        enemigo[i-1].setTextureRect(porcion_de_sprite);
                        animaciones[i-1].restart();
                    }
                    break;
                case 0:
                case 2:
                case -1:
                    ///ANIMACION ABAJO
                    if (animaciones[i-1].getElapsedTime().asSeconds()>0.100f)
                    {
                        switch (num_sprite[i-1])
                        {
                        case 1:
                            porcion_de_sprite.left=22;
                            porcion_de_sprite.top=191;
                            porcion_de_sprite.width=45;
                            porcion_de_sprite.height=70;
                            num_sprite[i-1]=2;
                            retorno[i-1]=false;
                            break;
                        case 2:
                            porcion_de_sprite.left=88;
                            porcion_de_sprite.top=189;
                            porcion_de_sprite.width=45;
                            porcion_de_sprite.height=70;
                            if (retorno[i-1])
                                num_sprite[i-1]=1;
                            else
                                num_sprite[i-1]=3;
                            break;
                        case 3:
                            porcion_de_sprite.left=155;
                            porcion_de_sprite.top=190;
                            porcion_de_sprite.width=45;
                            porcion_de_sprite.height=70;
                            num_sprite[i-1]=2;
                            retorno[i-1]=true;
                            break;
                        }
                        animacion_muestra_menu.setTextureRect(porcion_de_sprite);
                        enemigo[i-1].setTextureRect(porcion_de_sprite);
                        animaciones[i-1].restart();
                    }
                    break;
                case 1:
                    /// ANIMACION IZQUIERDA

                    if (animaciones[i-1].getElapsedTime().asSeconds()>0.100f)
                    {
                        switch (num_sprite[i-1])
                        {
                        case 1:
                            porcion_de_sprite.left=17;
                            porcion_de_sprite.top=277;
                            porcion_de_sprite.width=45;
                            porcion_de_sprite.height=70;
                            num_sprite[i-1]=2;
                            retorno[i-1]=false;
                            break;
                        case 2:
                            porcion_de_sprite.left=83;
                            porcion_de_sprite.top=275;
                            porcion_de_sprite.width=45;
                            porcion_de_sprite.height=70;
                            if (retorno[i-1])
                                num_sprite[i-1]=1;
                            else
                                num_sprite[i-1]=3;
                            break;
                        case 3:
                            porcion_de_sprite.left=149;
                            porcion_de_sprite.top=276;
                            porcion_de_sprite.width=45;
                            porcion_de_sprite.height=70;
                            num_sprite[i-1]=2;
                            retorno[i-1]=true;
                            break;
                        }
                        animacion_muestra_menu.setTextureRect(porcion_de_sprite);
                        enemigo[i-1].setTextureRect(porcion_de_sprite);
                        animaciones[i-1].restart();
                    }
                    break;
                default:
                    break;
                }


                */
                if (!enemigo[i-1].getMuerto())
                {
                    // Pequeña maquina de estados
                    switch (enemigo[i-1].getEstado())
                    {
                    case 0:

                        // el pixelperfectTest del mapa colisionable reemplazara a la tecnica del paint y el limite de pixeles
                        // mientras cambio los limites colisionables sobre el mapa del lvl1, seguimos con los pixeles.

                        if (enemigo[i-1].getY()<130/*PixelPerfectTest(enemigo[i-1],camino1.getSprite()) */ )
                        {
                            if(enemigo[i-1].getOpacidad()<255)
                            {
                                enemigo[i-1].incrementar_opacidad(5);
                                vidas_texto[i-1].setTransparencia(enemigo[i-1].getOpacidad());
                            }
                            enemigo[i-1].mover_abajo();
                        }
                        else
                            enemigo[i-1].setEstado(1);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 1:
                        if (enemigo[i-1].getX()>69)
                        {
                            enemigo[i-1].mover_izq();
                        }
                        else
                            enemigo[i-1].setEstado(2);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 2:
                        if (enemigo[i-1].getY()<340)
                        {
                            enemigo[i-1].mover_abajo();
                        }
                        else
                            enemigo[i-1].setEstado(3);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 3:
                        if (enemigo[i-1].getX()<199)
                        {
                            enemigo[i-1].mover_derecha();
                        }
                        else
                            enemigo[i-1].setEstado(31);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 31:
                        if (enemigo[i-1].getY()<460)
                        {
                            enemigo[i-1].mover_abajo();
                        }
                        else
                            enemigo[i-1].setEstado(32);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 32:
                        if (enemigo[i-1].getX()<370)
                        {
                            enemigo[i-1].mover_derecha();
                        }
                        else
                            enemigo[i-1].setEstado(4);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 4:
                        if (enemigo[i-1].getY()>227)
                        {
                            enemigo[i-1].mover_arriba();
                        }
                        else
                            enemigo[i-1].setEstado(5);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 5:
                        if (enemigo[i-1].getX()<491)
                        {
                            enemigo[i-1].mover_derecha();
                        }
                        else
                            enemigo[i-1].setEstado(51);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 51:
                        if (enemigo[i-1].getY()<459)
                        {
                            enemigo[i-1].mover_abajo();
                        }
                        else
                            enemigo[i-1].setEstado(52);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 52:
                        if (enemigo[i-1].getX()<670)
                        {
                            enemigo[i-1].mover_derecha();
                        }
                        else
                            enemigo[i-1].setEstado(53);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 53:
                        if (enemigo[i-1].getY()>189)
                        {
                            enemigo[i-1].mover_arriba();
                        }
                        else
                            enemigo[i-1].setEstado(54);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 54:
                        if (enemigo[i-1].getX()>614)
                        {
                            enemigo[i-1].mover_izq();
                        }
                        else
                            enemigo[i-1].setEstado(55);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 55:
                        if (enemigo[i-1].getY()>125)
                        {
                            enemigo[i-1].mover_arriba();
                        }
                        else
                            enemigo[i-1].setEstado(6);
                        enemigo[i-1].setTira_mov();
                        break;
                    case 6:
                        if (enemigo[i-1].getOpacidad()!=0)
                        {
                            enemigo[i-1].decrementar_opacidad(5);
                            vidas_texto[i-1].setTransparencia(enemigo[i-1].getOpacidad());
                            enemigo[i-1].mover_arriba();
                        }
                        else
                        {
                            enemigo[i-1].setEstado(7);
                            if(enemigo[i-1].getVida()>0)
                            {
                                vida_juego-=100;
                                vida_juego_texto.setVariable(vida_juego);
                                dinero+=50;
                                dinero_texto.setVariable(dinero);
                            }
                            enemigo[i-1].setVida(0);
                        }
                        break;
                    case 7:
                        break;

                        //movimientos en diagonal

                        /*
                        case 1:
                            if (circulo1.getPosition().y>171&&circulo1.getPosition().x>35)
                            {
                                mov_diagonal_izq_abajo(&circulo1,0.1,0.038);

                            }
                            else
                                estado=2;
                            break;glorious morning
                        case 2:
                            if (circulo1.getPosition().x<35&&circulo1.getPosition().y<429)
                            {
                        glorious morning           mov_obj_abajo(enemigo,objetos,0.1);

                            }
                            else
                                estado=10;
                            break;
                        case 10:
                            if (circulo1.getPosition().y>429&&circulo1.getPosition().y<500)
                            {
                                mov_diagonal_der_abajo(&circulo1,0.1,0.1);
                            }
                            else
                                estado=3;
                            break;
                        case 3:
                            break;
                        case 4:
                            if (circulo1.getPosition().x>292&&circulo1.getPosition().x<570)
                            {
                                mov_diagonal_der_arriba(&circulo1,0.1,0.1);
                            }
                            else
                                estado=5;
                            break;
                        case 5:
                            if(circulo1.getPosition().x<637)
                            {
                                mov_derecha(&circulo1,0.1);
                            }
                            else
                                estado=6;
                            break;
                        case 6:
                            if (circulo1.getPosition().x>637&&circulo1.getPosition().x<700)
                            {
                                mov_derecha(&circulo1,0.1);
                                if(opacidad>0)
                                {
                                    opacidad-=0.4;
                                    circulo1.setFillColor(Color(255,255,255,opacidad));
                                }
                            }
                            else
                            {
                                circulo1.setPosition(290,0);
                                estado=0;
                            }
                            break;
                        */
                    }
                }

                /*

                for(int x=0; x<10;x++){
                 switch (x)
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    break;


                }






                */
            }

            if (tiempo%tiempo_spawn==0)
            {
                if (objetos<cantidad_bichos)
                {
                    objetos++;
                }
            }

            /// INTERVALO DE SPAWNEO DE LOS ENEMIGOS
            switch(objetos)
            {
            case 0:
                if(oleada==1)
                {
                    tiempo_spawn=500;
                }
                else
                {
                    tiempo_spawn=200;
                }
                break;
            case 1:
                tiempo_spawn=250;
                break;
            case 2:
                tiempo_spawn=200;
                break;
            case 3:
                tiempo_spawn=150;
                break;
            case 4:
                tiempo_spawn=100;
                break;
            case 6:
                tiempo_spawn=50;
                break;
            }

            /// MENSAJE POST OLEADA



            tiempo++;

            //Metodo de clase Texto, para modificar el string porque la variable cambio de valor.

            //--------
            tiempo_texto.setVariable(tiempo);
            //--------

            // SIGUIENTE OLEADA

            for(h=0; h<cantidad_bichos; h++)
            {
                if(enemigo[h].getVida()<=0&&bichos_muertos<cantidad_bichos)
                {
                    bichos_muertos++;
                }
            }
            if (bichos_muertos!=cantidad_bichos)
                bichos_muertos=0;

            //Pruebas iniciales con circulos

            /*
            window.draw(circulo1);
            if (circulo1.getPosition().x<600&&circulo1.getPosition().y<=0) {
            x=circulo1.getPosition().x+.1;
            circulo1.setPosition(x,circulo1.getPosition().y);
            }
            if (circulo1.getPosition().x>600&&circulo1.getPosition().y<400) {
            y=circulo1.getPosition().y+.1;
            circulo1.setPosition(circulo1.getPosition().x,y);
            }
            if (circulo1.getPosition().x>0&&circulo1.getPosition().y>400) {
            x=circulo1.getPosition().x-.1;
            circulo1.setPosition(x,circulo1.getPosition().y);
            }
            if (circulo1.getPosition().x<0&&circulo1.getPosition().y>0) {
            y=circulo1.getPosition().y-.1;
            circulo1.setPosition(circulo1.getPosition().x,y);
            }
            */

            break;  // fin del estado juego

        default:
            break;

        }   // fin del switch(estado_juego)

        ///cinematica,draw, test-----------------
        /*
                if (test1.getEstado())
                {
                    window.draw(test1.getFrame());

                    test1.Actualizar_frame();
                }

                if (viejo_test.getEstado())
                {
                    window.draw(viejo_test.getFrame());

                    viejo_test.Actualizar_frame();
                }
        */
        ///-------------------------------------

        ///Intentando acoplar el mecanismo de cinematica a las animaciones
        ///dada su simplicidad para reproducir frames.----------------------
        /*
        if (Keyboard::isKeyPressed(Keyboard::F))
        {
            window.draw(fuego.getFrame());

            fuego.actualizar_frame();

        }
        ///--------------------------------
        */
        ///-----------------------------------------------
        puntero1.setPosition(mousexy[0],mousexy[1]);
        window.draw(puntero1);

        window.display();

    }   // fin del while(window.IsOpen())

    ///Liberacion de memoria
    delete enemigo;
    delete colas_torres_3d;

    if (reproductor.getEncendido())
        reproductor.apagar();

    return 0;

}  // Fin de la funcion juego();


#endif // JUEGO_H_INCLUDED
