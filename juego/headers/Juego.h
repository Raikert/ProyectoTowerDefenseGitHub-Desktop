#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

using namespace std;
using namespace sf;
using namespace Collision;

int juego()
{
    ///variables de los for, dados los multiples conflictos por declaraciones seguidas en los ciclos.
    int i,x,te,d,o;

    ///variables de la ventana del juego
    int tamx,tamy,tamx_actual=1000,tamy_actual=600;
    Vector2f pixeles_convertidos;
    ///---------------------------------

    ///vida del la base
    const int const_vida_juego=1000;
    ///-------------

    const int cantidad_bichos=10;
    Zombie enemigo[cantidad_bichos];
    Clock tiempo_zombies[cantidad_bichos];
    IntRect porcion_de_sprite(0,0,36,50);
    Zombie aldeano("img/zombie.png",285,0,porcion_de_sprite,2);
    if (!aldeano.getConfirmacion())
        return -10;
    Texto vidas_texto[cantidad_bichos];
    Texto vidas_texto_variable("tipos_de_texto/OpenSans-BoldItalic.ttf",aldeano.getVida(),15,aldeano.getX()+13,aldeano.getY()+48);
    if (!vidas_texto_variable.getConfirmacion())
        return -10;
    for (i=0; i<cantidad_bichos; i++)
    {
        vidas_texto[i]=vidas_texto_variable;
    }
    Zombie aldeano_menu("img/zombie.png",668,317,porcion_de_sprite,2,255);
    Clock tiempo_aldeano_menu;
    if (!aldeano_menu.getConfirmacion())
        return -10;
    cargar_vector_sprites(enemigo,aldeano,cantidad_bichos);

    bool menu_principal=true,oleada_fin,fin_juego=false;
    /** /// VARIABLES DE MONSTRUOS
    int monstruos_lvl_1=2;
    int monstruos_lvl_2=2;
    int monstruos_lvl_3=2;

    /// VARIABLE QUE CUENTA LOS MONSTRUOS
    int monstruos_en_juego=0;
    */

    /// PRUEBA CON LA CLASE COLA
    Cola Cola_Torre[9];
    for (o=0; o<9; o++)
    {
        Cola_Torre[o]=Cola(10);
    }

    ///------Animaciones de los zombies-------
    ///Explicacion del IntRect o rectangulo de una imagen.

    ///Imaginen que tienen un cuadro vacio, y a su vez tienen
    ///la pintura en un pa�o de lana al que quieren poner en ese
    ///cuadro, pero q tambien ustedes pretenden mostrar solo una
    ///parte de ese pa�o. Si lo asociamos con esto seria asi:
    ///El Sprite es el cuadro.
    ///La textura es el pa�o o imagen.
    ///lo que quieren mostrar es la variable de tipo IntRect.

    ///ahora, una vez q montaron todo, lo que quieren hacer es
    ///recortar el pa�o al cual montaron al cuadro, entonces como
    ///se hace?
    ///Primero crean una variable de tip� IntRect, que significa
    ///rectangulo interior o zona de recorte. Ahora bien, que
    ///significan todas esas coordenadas?.
    ///Las primeras 2: tanto el 15 y el 34 es la posicion en donde
    ///va a empezar ese rectangulo, igual q la posicion de los sprites
    ///en la esquina izquierda superior, y los otros 2 son el ancho y
    ///el alto de su rectangulo o recorte, el orden para las primeras
    ///dos es igual a la q veniamos usando, primero en X, despues en Y
    ///las otras 2 es primero el ancho, despues el alto.

    ///Hasta ahora todo bien no?, eso espero xddd

    ///Si se fijan mas abajo van a ver una variable nueva que se llama
    ///Clock o tiempo, es una variable q desde q es declarada
    ///cuenta tiempo, ya sea en segundos, minutos, lo q sea.
    ///pero lo q usariamos nosotros seria mas q nada los segundos
    ///asi q para obtener la cantidad de seg q tiene el CLock
    ///hay q usar el metodo GetElapsedTime() pero q a su vez
    ///nos entregue el tiempo en segundos entonces le agregamos
    ///AsSeconds(), y asi obtendriamos el tiempo en seg q tiene
    ///actualmente nuestro juego, sin contar los minutos obvio.
    ///pero q me imagino q tambien se podra almacenar en otra variable
    ///de tipo int y podriamos armar un relojito para el juego.

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


    ///---------------------------------------

    ///definicion de la ventana del juego
    RenderWindow window(VideoMode(tamx_actual,tamy_actual), "Tower Defense - La defensa del fuerte Nicomando");

    ///Setea el framerate a 60 fps, comentar para mas velocidad,seteado para ver la velocidad real del juego
    ///bugeo de los sprites solucionado seteando el Smooth de los Sprites en True.
    window.setFramerateLimit(60);
    ///Sector de Incializacion y generacion de Sprites y vectores de Sprites
    /*
    Sprites bicho("img/bicho_reside_circulo.png",opacidad_bichos,285,0);

    if (!bicho.getConfirmacion())
        return -10;
        */

    ///Camino lvl1 para modificaciones de colision por error de colisiones con los bichos - comentado

    /*
    Sprites camino1("img/caminolvl1.png")
    if (!camino1.getConfirmacion())
        return -10;
    */

    Texture textura_mapa,textura_menu,textura_rango,textura_derrota;

    if (!textura_mapa.loadFromFile("img/008 - copia.png"))
        return -1;
    if (!textura_menu.loadFromFile("img/006.jpg"))
        return -1;
    if (!textura_rango.loadFromFile("img/rango.png"))
        return -1;
    if (!textura_derrota.loadFromFile("img/derrota.jpg"))
        return -11;
    textura_rango.setSmooth(true);
    textura_menu.setSmooth(true);
    textura_mapa.setSmooth(true);
    textura_derrota.setSmooth(true);
    ///Zona de texto
    Font tipo_de_texto;

    /// ------------------------------------------------------------------
    /** if (!tipo_de_texto.loadFromFile("tipos_de_texto/OpenSans-Bold.ttf"))
        return -1;
    Text texto_prueba;
    texto_prueba.setFont(tipo_de_texto);
    texto_prueba.setString("GENTESSS EDITION");
    texto_prueba.setCharacterSize(24);   */
    ///-------------------------------------------------------------------
    Sprite mapa,menu,derrota;
    mapa.setTexture(textura_mapa);
    menu.setTexture(textura_menu);
    derrota.setTexture(textura_derrota);
    int mousexy[2];
    for (i=0; i<2; i++)
    {
        mousexy[i]=0;
    }
    Texto mousex("tipos_de_texto/OpenSans-BoldItalic.ttf",mousexy[0],18,627,545,Color::White);
    if (!mousex.getConfirmacion())
        return -1;
    Texto mousey("tipos_de_texto/OpenSans-BoldItalic.ttf",mousexy[1],18,693,549,Color::White);
    if (!mousey.getConfirmacion())
        return -1;

    ///Si gente, le puse MUSICA WEEEEE
    Music musica_menu,musica_juego,musica_derrota;
    if (!musica_menu.openFromFile("musica/menu_song.ogg"))
        return -1;
    if (!musica_juego.openFromFile("musica/lvl1_song.ogg"))
        return -1;
    if (!musica_derrota.openFromFile("musica/derrota.ogg"))
        return -113;
    ///volumen de la musica del menu
    musica_menu.setVolume(50.f);
    // musica_menu.setPlayingOffset(seconds(62.5f));
    musica_menu.play();
    musica_menu.setLoop(true);
    musica_juego.setVolume(50.f);
    musica_juego.setLoop(true);
    musica_derrota.setLoop(true);
    musica_derrota.setVolume(50.f);
    bool boolmusica=false,boolmusicajuego=true,habilitacionmouse=true,boolmusicaderrota=false;

    ///con esta variable se cambia la cantidad de monstruos en el mundo

    ///Para un futuro en donde pongamos a los 3 sprites de los 8 tipos de monstruos q consegui-veanlo en la carpeta de img

    /*
    Sprite enemigo[cantidad_objetos][3];
    */

    ///objeto boton de la nueva clase de botones_rectangulo, 5 Parametros:
    ///Tama�o en Float X, Tama�o en Float Y, Posicion de la pantalla en Float X, Posicion de la pantalla en Float Y
    ///el Quinto parametro es transparencia q se pone en 0,osea invisible, por parametro por omision.
    ///Util para ver en q posicion de la pantalla se ubica el boton.

    Boton nueva_partida(237,38,351,316),cargar_partida_boton(237,38,351,377,255),salir(237,38,351,437),sonido(55,50,872,487);
    Boton nueva_oleada(49,45,823,433,255);
    Boton guardar_partida(152,44,824,545,255);
    Boton pausa(49,45,875,433);
    Boton reanudar(49,45,927,433);

    ///*/////////////////////////////////////////////-------------ZONA DE TORRES -------------////////////////////////////////////////////////////////////////////////////////////////////////
    ///-----Cantidad de torres-----
    const int cantidad_torres=3;

    ///-----Intervalo de da�o de las torres-----
    int intervalo_danio[cantidad_torres];
    intervalo_danio[2]=50;
    intervalo_danio[0]=50;
    intervalo_danio[1]=50;

    ///-----Da�o de las torres-----
    int danio_torre[cantidad_torres];
    danio_torre[2]=30; /// Primer torre
    danio_torre[0]=1;  /// Segunda torre
    danio_torre[1]=70; /// Tercer torre

    ///-----Valor de las torres-----
    int compra[3];
    compra[2]=100;
    compra[0]=150;
    compra[1]=200;

    ///-----Dinero de juego-----
    int dinero;
    dinero=1000;
    Texto dinero_texto("tipos_de_texto/OpenSans-BoldItalic.ttf",dinero,20,940,117,Color::Black);

    ///-----Vida de juego-----
    int vida_juego;
    vida_juego=const_vida_juego;
    Texto vida_juego_texto("tipos_de_texto/OpenSans-BoldItalic.ttf",vida_juego,20,940,138,Color::Black);

    /// Estados
    bool menu_abierto=false;
    bool mouse_afuera=false;

    /// Variables para la verificacion de clicks y demas
    int posicion_clickeada;
    int contador_de_clicks=0;
    int contador_de_clicks_fuera=0;
    /// Definicion de los espacios para las torres ----------------------------------------------------------------------------
    const int tam_torres = 9;
    int coordenadas_X_Y_torres[2]; /// X=0 Y=1
    int coordenadas_X_Y_torres_tipo[cantidad_torres][2];
    /*
    int coordenadas_X_Y_torres_t1[2]; /// X=0 Y=1
    int coordenadas_X_Y_torres_t2[2]; /// X=0 Y=1
    int coordenadas_X_Y_torres_t3[2]; /// X=0 Y=1
    */
    int coordenadas_X_Y_equis[2]; /// X=0 Y=1
    int coordenadas_X_Y_vender[2]; /// X=0 Y=1
    int coordenadas_X_Y_subirlvl[2]; /// X=0 Y=1
    int coordenadas_X_Y_mejorar[2]; /// X=0 Y=1
    Boton torres[tam_torres];
    Boton torres_tipo[cantidad_torres][tam_torres];
    /*
    Boton torres_t1[tam_torres];
    Boton torres_t2[tam_torres];
    Boton torres_t3[tam_torres];
    */
    Boton torres_equis[tam_torres];
    Boton torres_vender[tam_torres];
    Boton torres_subirlvl[tam_torres];
    Boton torres_mejorar[tam_torres];
    /// Posiciones de cada boton
    for (i=0; i<tam_torres; i++)
    {
        switch (i)
        {
        case 0:
            /// Espacio para la torre
            coordenadas_X_Y_torres[0]=236;
            coordenadas_X_Y_torres[1]=114;
            /// Torre 1 del menu
            coordenadas_X_Y_torres_tipo[0][0]=coordenadas_X_Y_torres[0]-74;
            coordenadas_X_Y_torres_tipo[0][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 2 del menu
            coordenadas_X_Y_torres_tipo[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_tipo[1][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 3 del menu
            coordenadas_X_Y_torres_tipo[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_tipo[2][1]=coordenadas_X_Y_torres[1]-72;
            /// Cruz para cerrar el menu
            coordenadas_X_Y_equis[0]=339;
            coordenadas_X_Y_equis[1]=74;
            /// Boton para vender del menu
            coordenadas_X_Y_vender[0]=339;
            coordenadas_X_Y_vender[1]=92;
            /// Boton para cambiar el menu por el menu de nivel+1
            coordenadas_X_Y_subirlvl[0]=339;
            coordenadas_X_Y_subirlvl[1]=110;
            /// Boton para mejorar la torre
            coordenadas_X_Y_mejorar[0]=339;
            coordenadas_X_Y_mejorar[1]=129;
            break;
        case 1:
            /// Espacio para la torre
            coordenadas_X_Y_torres[0]=98;
            coordenadas_X_Y_torres[1]=245;
            /// Torre 1 del menu
            coordenadas_X_Y_torres_tipo[0][0]=coordenadas_X_Y_torres[0]-74;
            coordenadas_X_Y_torres_tipo[0][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 2 del menu
            coordenadas_X_Y_torres_tipo[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_tipo[1][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 3 del menu
            coordenadas_X_Y_torres_tipo[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_tipo[2][1]=coordenadas_X_Y_torres[1]-72;
            /// Cruz para cerrar el menu
            coordenadas_X_Y_equis[0]=339;
            coordenadas_X_Y_equis[1]=74;
            /// Boton para vender del menu
            coordenadas_X_Y_vender[0]=339;
            coordenadas_X_Y_vender[1]=92;
            /// Boton para cambiar el menu por el menu de nivel+1
            coordenadas_X_Y_subirlvl[0]=339;
            coordenadas_X_Y_subirlvl[1]=110;
            /// Boton para mejorar la torre
            coordenadas_X_Y_mejorar[0]=339;
            coordenadas_X_Y_mejorar[1]=129;
            break;
        case 2:
            /// Espacio para la torre
            coordenadas_X_Y_torres[0]=98;
            coordenadas_X_Y_torres[1]=420;
            /// Torre 1 del menu
            coordenadas_X_Y_torres_tipo[0][0]=coordenadas_X_Y_torres[0]-74;
            coordenadas_X_Y_torres_tipo[0][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 2 del menu
            coordenadas_X_Y_torres_tipo[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_tipo[1][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 3 del menu
            coordenadas_X_Y_torres_tipo[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_tipo[2][1]=coordenadas_X_Y_torres[1]-72;
            /// Cruz para cerrar el menu
            coordenadas_X_Y_equis[0]=339;
            coordenadas_X_Y_equis[1]=74;
            /// Boton para vender del menu
            coordenadas_X_Y_vender[0]=339;
            coordenadas_X_Y_vender[1]=92;
            /// Boton para cambiar el menu por el menu de nivel+1
            coordenadas_X_Y_subirlvl[0]=339;
            coordenadas_X_Y_subirlvl[1]=110;
            /// Boton para mejorar la torre
            coordenadas_X_Y_mejorar[0]=339;
            coordenadas_X_Y_mejorar[1]=129;
            break;
        case 3:
            /// Espacio para la torre
            coordenadas_X_Y_torres[0]=194;
            coordenadas_X_Y_torres[1]=331;
            /// Torre 1 del menu
            coordenadas_X_Y_torres_tipo[0][0]=coordenadas_X_Y_torres[0]-74;
            coordenadas_X_Y_torres_tipo[0][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 2 del menu
            coordenadas_X_Y_torres_tipo[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_tipo[1][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 3 del menu
            coordenadas_X_Y_torres_tipo[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_tipo[2][1]=coordenadas_X_Y_torres[1]-72;
            /// Cruz para cerrar el menu
            coordenadas_X_Y_equis[0]=339;
            coordenadas_X_Y_equis[1]=74;
            /// Boton para vender del menu
            coordenadas_X_Y_vender[0]=339;
            coordenadas_X_Y_vender[1]=92;
            /// Boton para cambiar el menu por el menu de nivel+1
            coordenadas_X_Y_subirlvl[0]=339;
            coordenadas_X_Y_subirlvl[1]=110;
            /// Boton para mejorar la torre
            coordenadas_X_Y_mejorar[0]=339;
            coordenadas_X_Y_mejorar[1]=129;
            break;
        case 4:
            /// Espacio para la torre
            coordenadas_X_Y_torres[0]=242;
            coordenadas_X_Y_torres[1]=419;
            /// Torre 1 del menu
            coordenadas_X_Y_torres_tipo[0][0]=coordenadas_X_Y_torres[0]-74;
            coordenadas_X_Y_torres_tipo[0][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 2 del menu
            coordenadas_X_Y_torres_tipo[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_tipo[1][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 3 del menu
            coordenadas_X_Y_torres_tipo[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_tipo[2][1]=coordenadas_X_Y_torres[1]-72;
            /// Cruz para cerrar el menu
            coordenadas_X_Y_equis[0]=339;
            coordenadas_X_Y_equis[1]=74;
            /// Boton para vender del menu
            coordenadas_X_Y_vender[0]=339;
            coordenadas_X_Y_vender[1]=92;
            /// Boton para cambiar el menu por el menu de nivel+1
            coordenadas_X_Y_subirlvl[0]=339;
            coordenadas_X_Y_subirlvl[1]=110;
            /// Boton para mejorar la torre
            coordenadas_X_Y_mejorar[0]=339;
            coordenadas_X_Y_mejorar[1]=129;
            break;
        case 5:
            /// Espacio para la torre
            coordenadas_X_Y_torres[0]=339;
            coordenadas_X_Y_torres[1]=419;
            /// Torre 1 del menu
            coordenadas_X_Y_torres_tipo[0][0]=coordenadas_X_Y_torres[0]-74;
            coordenadas_X_Y_torres_tipo[0][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 2 del menu
            coordenadas_X_Y_torres_tipo[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_tipo[1][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 3 del menu
            coordenadas_X_Y_torres_tipo[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_tipo[2][1]=coordenadas_X_Y_torres[1]-72;
            /// Cruz para cerrar el menu
            coordenadas_X_Y_equis[0]=339;
            coordenadas_X_Y_equis[1]=74;
            /// Boton para vender del menu
            coordenadas_X_Y_vender[0]=339;
            coordenadas_X_Y_vender[1]=92;
            /// Boton para cambiar el menu por el menu de nivel+1
            coordenadas_X_Y_subirlvl[0]=339;
            coordenadas_X_Y_subirlvl[1]=110;
            /// Boton para mejorar la torre
            coordenadas_X_Y_mejorar[0]=339;
            coordenadas_X_Y_mejorar[1]=129;
            break;
        case 6:
            /// Espacio para la torre
            coordenadas_X_Y_torres[0]=434;
            coordenadas_X_Y_torres[1]=419;
            /// Torre 1 del menu
            coordenadas_X_Y_torres_tipo[0][0]=coordenadas_X_Y_torres[0]-74;
            coordenadas_X_Y_torres_tipo[0][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 2 del menu
            coordenadas_X_Y_torres_tipo[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_tipo[1][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 3 del menu
            coordenadas_X_Y_torres_tipo[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_tipo[2][1]=coordenadas_X_Y_torres[1]-72;
            /// Cruz para cerrar el menu
            coordenadas_X_Y_equis[0]=339;
            coordenadas_X_Y_equis[1]=74;
            /// Boton para vender del menu
            coordenadas_X_Y_vender[0]=339;
            coordenadas_X_Y_vender[1]=92;
            /// Boton para cambiar el menu por el menu de nivel+1
            coordenadas_X_Y_subirlvl[0]=339;
            coordenadas_X_Y_subirlvl[1]=110;
            /// Boton para mejorar la torre
            coordenadas_X_Y_mejorar[0]=339;
            coordenadas_X_Y_mejorar[1]=129;
            break;
        case 7:
            /// Espacio para la torre
            coordenadas_X_Y_torres[0]=482;
            coordenadas_X_Y_torres[1]=90;
            /// Torre 1 del menu
            coordenadas_X_Y_torres_tipo[0][0]=coordenadas_X_Y_torres[0]-74;
            coordenadas_X_Y_torres_tipo[0][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 2 del menu
            coordenadas_X_Y_torres_tipo[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_tipo[1][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 3 del menu
            coordenadas_X_Y_torres_tipo[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_tipo[2][1]=coordenadas_X_Y_torres[1]-72;
            /// Cruz para cerrar el menu
            coordenadas_X_Y_equis[0]=339;
            coordenadas_X_Y_equis[1]=74;
            /// Boton para vender del menu
            coordenadas_X_Y_vender[0]=339;
            coordenadas_X_Y_vender[1]=92;
            /// Boton para cambiar el menu por el menu de nivel+1
            coordenadas_X_Y_subirlvl[0]=339;
            coordenadas_X_Y_subirlvl[1]=110;
            /// Boton para mejorar la torre
            coordenadas_X_Y_mejorar[0]=339;
            coordenadas_X_Y_mejorar[1]=129;
            break;
        case 8:
            /// Espacio para la torre
            coordenadas_X_Y_torres[0]=535;
            coordenadas_X_Y_torres[1]=224;
            /// Torre 1 del menu
            coordenadas_X_Y_torres_tipo[0][0]=coordenadas_X_Y_torres[0]-74;
            coordenadas_X_Y_torres_tipo[0][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 2 del menu
            coordenadas_X_Y_torres_tipo[1][0]=coordenadas_X_Y_torres[0]-15;
            coordenadas_X_Y_torres_tipo[1][1]=coordenadas_X_Y_torres[1]-72;
            /// Torre 3 del menu
            coordenadas_X_Y_torres_tipo[2][0]=coordenadas_X_Y_torres[0]+44;
            coordenadas_X_Y_torres_tipo[2][1]=coordenadas_X_Y_torres[1]-72;
            /// Cruz para cerrar el menu
            coordenadas_X_Y_equis[0]=339;
            coordenadas_X_Y_equis[1]=74;
            /// Boton para vender del menu
            coordenadas_X_Y_vender[0]=339;
            coordenadas_X_Y_vender[1]=92;
            /// Boton para cambiar el menu por el menu de nivel+1
            coordenadas_X_Y_subirlvl[0]=339;
            coordenadas_X_Y_subirlvl[1]=110;
            /// Boton para mejorar la torre
            coordenadas_X_Y_mejorar[0]=339;
            coordenadas_X_Y_mejorar[1]=129;
            break;
        }
        torres[i]=Boton(49,90,coordenadas_X_Y_torres[0],coordenadas_X_Y_torres[1]);
        torres_tipo[0][i]=Boton(58,71,coordenadas_X_Y_torres_tipo[1][0],coordenadas_X_Y_torres_tipo[1][1]);
        torres_tipo[1][i]=Boton(58,71,coordenadas_X_Y_torres_tipo[2][0],coordenadas_X_Y_torres_tipo[2][1]);
        torres_tipo[2][i]=Boton(58,71,coordenadas_X_Y_torres_tipo[0][0],coordenadas_X_Y_torres_tipo[0][1]);
        /*
        torres_t3[i]=Boton(59,71,coordenadas_X_Y_torres_t1[0],coordenadas_X_Y_torres_t1[1]);
        torres_t1[i]=Boton(57,71,coordenadas_X_Y_torres_t2[0],coordenadas_X_Y_torres_t2[1]);
        torres_t2[i]=Boton(59,71,coordenadas_X_Y_torres_t3[0],coordenadas_X_Y_torres_t3[1]);
        */
        torres_equis[i]=Boton(19,18,coordenadas_X_Y_equis[0],coordenadas_X_Y_equis[1]);
    }

    /// Declaracion del vector de menues de torres
    bool menu_torre[tam_torres], spawn_torre[tam_torres][3], spawnear[tam_torres], Ocupado[tam_torres];
    for (i=0; i<tam_torres; i++)
    {
        for (te=0; te<3; te++)
        {
            spawn_torre[i][te]=false;
        }
    }
    ponerEnFalso(menu_torre, tam_torres);
    ponerEnFalso(spawnear, tam_torres);
    ponerEnFalso(Ocupado, tam_torres);

    /// Texturas
    Texture textura_menu_torre, textura_torre_tipo[cantidad_torres], /*textura_torre_1, textura_torre_2, textura_torre_3,*/ rango_torre;
    /// MENU DE TORRES
    if (!textura_menu_torre.loadFromFile("img/Menu_Torres.png"))
        return -1;
    textura_menu_torre.setSmooth(true);
    /// TORRE 1
    if (!textura_torre_tipo[0].loadFromFile("img/T1-1.png"))
        return -1;
    textura_torre_tipo[0].setSmooth(true);
    /// TORRE 2
    if (!textura_torre_tipo[1].loadFromFile("img/T2-1.png"))
        return -1;
    textura_torre_tipo[1].setSmooth(true);
    /// TORRE 3
    if (!textura_torre_tipo[2].loadFromFile("img/T3-1.png"))
        return -1;
    textura_torre_tipo[2].setSmooth(true);
    /// RANGO TORRE
    if (!rango_torre.loadFromFile("img/rango.png"))
        return -1;
    rango_torre.setSmooth(true);

    /// Sprites
    Sprite Sprite_menu_torre[tam_torres], Sprite_torre_tipo[cantidad_torres][tam_torres] /*Sprite_torre_1[tam_torres], Sprite_torre_2[tam_torres], Sprite_torre_3[tam_torres]*/;
    Sprite Sprite_rango_torre_tipo[cantidad_torres][tam_torres];
    /*Sprite_rango_torre_t1[tam_torres], Sprite_rango_torre_t2[tam_torres], Sprite_rango_torre_t3[tam_torres]*/;
    for (x=0; x<tam_torres; x++)
    {
        ///menu
        Sprite_menu_torre[x].setTexture(textura_menu_torre);
        Sprite_menu_torre[x].setPosition(torres[x].getEsix()-75,torres[x].getEsiy()-72);

        for(int f=0; f<cantidad_torres; f++)
        {
            Sprite_torre_tipo[f][x].setTexture(textura_torre_tipo[f]);
            Sprite_torre_tipo[f][x].setPosition(torres[x].getEsix(),torres[x].getEsiy());

            Sprite_rango_torre_tipo[f][x].setTexture(rango_torre);
            Sprite_rango_torre_tipo[f][x].scale(1,1.22);
            Sprite_rango_torre_tipo[f][x].setPosition(1000,600);
            Sprite_rango_torre_tipo[f][x].setColor(Color(255,255,255,100));
        }
        /*
        ///torre 1
        Sprite_torre_tipo[0][x].setTexture(textura_torre_tipo[0]);
        Sprite_torre_tipo[0][x].setPosition(torres[x].getEsix(),torres[x].getEsiy());
        ///torre 2
        Sprite_torre_tipo[1][x].setTexture(textura_torre_tipo[1]);
        Sprite_torre_tipo[1][x].setPosition(torres[x].getEsix(),torres[x].getEsiy());
        ///torre 3
        Sprite_torre_tipo[2][x].setTexture(textura_torre_tipo[2]);
        Sprite_torre_tipo[2][x].setPosition(torres[x].getEsix(),torres[x].getEsiy());
        ///rango de da�o T1
        Sprite_rango_torre_t1[x].setTexture(rango_torre);
        Sprite_rango_torre_t1[x].scale(1,1.22);
        Sprite_rango_torre_t1[x].setPosition(1000,600);
        Sprite_rango_torre_t1[x].setColor(Color(255,255,255,100));
        ///rango de da�o T2
        Sprite_rango_torre_t2[x].setTexture(rango_torre);
        Sprite_rango_torre_t2[x].scale(1,1.22);
        Sprite_rango_torre_t2[x].setPosition(1000,600);
        Sprite_rango_torre_t2[x].setColor(Color(1,1,255,50));
        ///rango de da�o T3
        Sprite_rango_torre_t3[x].setTexture(rango_torre);
        Sprite_rango_torre_t3[x].scale(1,1.22);
        Sprite_rango_torre_t3[x].setPosition(1000,600);
        Sprite_rango_torre_t3[x].setColor(Color(100,100,100,100));
        */
    }
    int a = 0;
    /// ----------------------------------------------------------------------------------------------------------------------
    ///*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// VARIABLES PARA LA SIGUIENTE OLEADA
    int bichos_muertos=0;
    bool siguiente_oleada=false;
    int vida_aumentada=100;
    int contador_oleadas=0;



    /*
    Rect<jojo>::Rect(200,200,50,50);
    */
//vidas
    float opacidad_menu=0; ///transparencia del objeto 255=100% porciento

    for (i=0; i<=cantidad_bichos-1; i++)
    {
        ///Seria un corte de control donde por cada vuelta de J se cargara un frame de un tipo de bicho, faltaria la forma
        ///dinamica de indicar a cual tipo de monstruo cargar en cada fila de la matriz
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

    int objetos=1;
    int tiempo=1;

    ///Todo lo que se necesita para crear un texto son 2 lineas de codigo, Nueva Clase Texto, Parametros:

    ///1)Formato de texto: ruta donde esta alojado el tipo de texto.
    ///2)variable a convertir, debe ser int, proximamente constructor para texto plano.
    ///3)Tama�o del texto, similar al word cuando pones el tama�o de la letra.
    ///4)Posicion de la pantalla en coordenadas de pixeles en X.
    ///5)Posicion de la pantalla en coordenadas de pixeles en Y.
    ///6)Color: Se debe anteponer Color:: y despues el color dentro de los contenidos por Sfml,

    ///Podriamos agregar using namespace Color, pero seria demasiado exagerado, posiblemente agrege
    ///un constructor para colores en RGB y transparencia, pero mas adelante.

    ///El objeto texto junto con el pasaje de variable a string se hacen simultaneamente.
    ///para cambiar el string, se usa el metodo setVariable(variable), que explico mas abajo con la variable tiempo.

    ///Para todo tipo de carga de archivos se debe verificar la carga con un metodo de confirmacion, que devuelve un verdadero
    ///o falso, en caso de una carga incorrecta el programa se detendra para la visibilidad del error, el constructor no puede
    ///hacerlo por si mismo, dado que no puede devolver ningun valor, es cosa nuestra asegurarlo.

    ///-------------------------
    Texto tiempo_texto("tipos_de_texto/OpenSans-BoldItalic.ttf",tiempo,25,600,300,Color::Black);
    if (!tiempo_texto.getConfirmacion())
        return -1;
    ///-------------------------

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        ///Animaciones de los zombies ----

        /*
        for(i=1; i<cantidad_bichos; i++)
        {
            for (a=0; a<cantidad_bichos; a++)
            {

            }
        }

        ///---------
        */
        ///La magia de las resoluciones y conversion de los pixeles por defecto a pixeles customizados-------------
        tamx=window.getSize().x;
        tamy=window.getSize().y;
        if (tamx!=tamx_actual||tamy!=tamy_actual)
        {
            pixeles_convertidos=window.mapPixelToCoords(Vector2i(Mouse::getPosition(window).x,Mouse::getPosition(window).y));
            mousexy[0]=pixeles_convertidos.x;
            mousexy[1]=pixeles_convertidos.y;
        }
        ///---------------------------------------------------------------------------------------------------------
        else
        {
            mousexy[0]=Mouse::getPosition(window).x;
            mousexy[1]=Mouse::getPosition(window).y;
        }
        mousex.setVariable(mousexy[0]);
        mousey.setVariable(mousexy[1]);
        ///Configuracion de los botones dentro del juego

        window.clear();

        ///  COMIENZA EL JUEGO

        if (vida_juego<=0)
        {
            fin_juego=true;
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                fin_juego=false;
                menu_principal=true;

                vida_juego=const_vida_juego;
                vida_juego_texto.setVariable(vida_juego);
                cargar_vector_sprites(enemigo,aldeano,cantidad_bichos);
                for(int o=0; o<cantidad_bichos; o++)
                {
                    vidas_texto[o].setVariable(enemigo[o].getVida());
                }
                dinero=1000;
                dinero_texto.setVariable((dinero));
                tiempo=1;
                objetos=1;
                musica_derrota.stop();
                musica_menu.play();
                opacidad_menu=0;
                boolmusicaderrota=false;

                for(int l=0; l<tam_torres; l++)
                {
                    /// TORRES -------------------------------------
                    spawn_torre[l][0]=false;
                    spawn_torre[l][1]=false;
                    spawn_torre[l][2]=false;
                    Ocupado[l]=false;

                    /// RANGOS -------------------------------------
                    for(int f=0; f<cantidad_torres; f++)
                    {
                        Sprite_rango_torre_tipo[f][l].setPosition(10000,0);
                    }
                }
            }
        }
        if (fin_juego)
        {
            window.draw(derrota);
            if (!boolmusicaderrota)
            {
                musica_juego.stop();
                musica_derrota.play();
                boolmusicaderrota=true;
            }
        }
        else
        {
            if (menu_principal)
            {
                menu.setColor(Color(255,255,255,opacidad_menu));
                window.draw(menu);
                /// window.draw(texto_prueba);
                window.draw(aldeano_menu.getZombie());
                window.draw(mousex.getTexto());
                window.draw(mousey.getTexto());

                if (opacidad_menu<255)
                {
                    opacidad_menu+=5;
                }
                else
                {
                    ///Configuracion de los botones en el menu principal
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {

                        ///Nueva partida
                        if (nueva_partida.click(mousexy))
                        {
                            /*
                            volumen_menu-=0.1;
                            musica_menu.setVolume(volumen_menu);
                                */
                            musica_menu.stop();
                            musica_juego.play();

                            mousex.setColor(Color::Black);
                            mousey.setColor(Color::Black);

                            menu_principal=false;
                        }
                        ///Cargar Partida
                        if (cargar_partida_boton.click(mousexy))
                        {
                            musica_menu.stop();
                            musica_juego.play();

                        }
                        ///Salir
                        if (salir.click(mousexy))
                        {
                            musica_menu.stop();
                            window.close();

                        }

                    }
                }
                aldeano_menu.cambiar_frame_sprite(tiempo_aldeano_menu);

            }
            else
            {
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    if (habilitacionmouse)
                    {
                        ///pausa del juego
                        if (pausa.click(mousexy))
                        {
                            musica_juego.pause();
                            while (true)
                            {
                                while (window.pollEvent(event))
                                {
                                    if (event.type == Event::Closed)
                                    {
                                        window.close();
                                        return 0;
                                    }
                                }
                                tamx=window.getSize().x;
                                tamy=window.getSize().y;
                                if (tamx!=tamx_actual||tamy!=tamy_actual)
                                {
                                    pixeles_convertidos=window.mapPixelToCoords(Vector2i(Mouse::getPosition(window).x,Mouse::getPosition(window).y));
                                    mousexy[0]=pixeles_convertidos.x;
                                    mousexy[1]=pixeles_convertidos.y;
                                }
                                ///---------------------------------------------------------------------------------------------------------
                                else
                                {
                                    mousexy[0]=Mouse::getPosition(window).x;
                                    mousexy[1]=Mouse::getPosition(window).y;
                                }
                                mousex.setVariable(mousexy[0]);
                                mousey.setVariable(mousexy[1]);
                                if (Mouse::isButtonPressed(Mouse::Left))
                                {
                                    if (reanudar.click(mousexy))
                                    {
                                        musica_juego.play();
                                        break;
                                    }
                                }
                            }
                        }
                        ///sonido
                        if (sonido.click(mousexy))
                        {
                            if (boolmusicajuego)
                            {
                                musica_juego.setVolume(0.f);
                                boolmusicajuego=false;
                            }
                            else
                            {
                                musica_juego.setVolume(50.f);
                                boolmusicajuego=true;
                            }
                        }
                        ///Oleada
                        if (nueva_oleada.click(mousexy))
                        {
                            musica_juego.stop();
                            for (i=0; i<cantidad_bichos; i++)
                            {
                                if (enemigo[i].getVida()<0)
                                {
                                    oleada_fin=true;
                                }
                                else
                                    oleada_fin=false;
                            }
                            if (oleada_fin)
                            {
                                ///oleada.incrementar(v);
                            }
                        }
                        /// Torres
                        for (i=0; i<tam_torres; i++)
                        {
                            if (torres[i].click(mousexy))
                            {
                                ///SE ABRE EL MENU DE TORRES
                                menu_torre[i]=true;
                                spawnear[i]=true;
                                habilitacionmouse=false;
                                posicion_clickeada=i;
                                contador_de_clicks++;
                            }
                            else
                            {
                                ///SE CIERRA EL MENU DE TORRES
                                menu_torre[i]=false;
                                if (contador_de_clicks>1)
                                {
                                    //spawnear[i]=false;
                                }
                                contador_de_clicks++;

                                /// Este for se encarga de cerrar la posibilidad de spawneo a los otros lugares que
                                /// no sea el que se clickeo anteriormente
                                for(int k=0; k<tam_torres; k++)
                                {
                                    if (k != posicion_clickeada)
                                    {
                                        spawnear[k]=false;
                                    }
                                }
                            }
                            if (habilitacionmouse)
                            {
                                for(x=0; x<tam_torres; x++)
                                {
                                    if (Ocupado[i]==false&&spawnear[i]==true)
                                    {
                                        for(int u=0; u<cantidad_torres; u++)
                                        {
                                            if(dinero>=compra[u]&&torres_tipo[u][i].click(mousexy))
                                            {
                                                ///Se spawnea la torre U
                                                spawn_torre[i][u]=true;
                                                /// El espacio de la torre 1 esta siendo ocupado por la torre 1
                                                Ocupado[i]=true;
                                                dinero-=compra[u];
                                                dinero_texto.setVariable(dinero);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        ///mientras el mouse este presionado no repetira ninguna accion en bucle hasta q se suelte el click izquierdo
                        habilitacionmouse=false;
                    }
                }
                else
                {
                    ///una vez que se solto el mouse, recien se habilita para una nueva accion
                    habilitacionmouse=true;
                }

                for (i=1; i<=objetos; i++)
                {
                    /// MAPA DEL JUEGO
                    window.draw(mapa);

                    /// COORDENADAS DEL MOUSE - MOMENTANEO
                    window.draw(mousex.getTexto());
                    window.draw(mousey.getTexto());
                    /// VARIABLE TIEMPO - MOMENTANEO
                    window.draw(tiempo_texto.getTexto());

                    /// VIDA DEL JUEGO
                    window.draw(vida_juego_texto.getTexto());
                    /// DINERO DEL JUEGO
                    window.draw(dinero_texto.getTexto());

                    /// REPRODUCTOR DE MUSICA
                    if (!boolmusica)
                    {
                        musica_juego.play();
                        boolmusica=true;
                    }
///*///////////////////////////////////////////////////////////- Spawnear torres -///////////////////////////////////////////////////////////////////////////
                    for (x=0; x<tam_torres; x++)
                    {
                        for(int y=0; y<3; y++)
                        {
                            if (spawn_torre[x][y]==true)
                            {
                                Sprite_rango_torre_tipo[y][x].setPosition(torres[x].getEsix()-92,torres[x].getEsiy()-50);
                                window.draw(Sprite_rango_torre_tipo[y][x]);
                                window.draw(Sprite_torre_tipo[y][x]);
                                /*
                                switch (y)
                                {
                                case 0:
                                    Sprite_rango_torre_t1[x].setPosition(torres[x].getEsix()-92,torres[x].getEsiy()-50);
                                    window.draw(Sprite_rango_torre_t1[x]);
                                    window.draw(Sprite_torre_1[x]);
                                    break;
                                case 1:
                                    Sprite_rango_torre_t2[x].setPosition(torres[x].getEsix()-92,torres[x].getEsiy()-50);
                                    window.draw(Sprite_rango_torre_t2[x]);
                                    window.draw(Sprite_torre_2[x]);
                                    break;
                                case 2:
                                    Sprite_rango_torre_t3[x].setPosition(torres[x].getEsix()-92,torres[x].getEsiy()-50);
                                    window.draw(Sprite_rango_torre_t3[x]);
                                    window.draw(Sprite_torre_3[x]);
                                    break;
                                }
                                */
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
                        else if (!enemigo[d-1].getMuerto()&& enemigo[d-1].getEstado()!=7)
                        {
                            dinero+=100;
                            dinero_texto.setVariable(dinero);
                            enemigo[d-1].setMuerto();
                        }
                        ///esto serian los mini-estados de los sprites, 3 cases por ser 3 frames o mini-sprites
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
                    for (x=0; x<tam_torres; x++)
                    {
                        if (menu_torre[x]==true)
                        {
                            window.draw(Sprite_menu_torre[x]);
                        }
                    }

                    for (x=0; x<tam_torres; x++)
                    {
                        for(int f=0; f<cantidad_torres; f++)
                        {
                            /// Si el enemigo colisiona con el sprite (invisible o no) hace da�o
                            if (PixelPerfectTest(enemigo[i-1].getZombie(),Sprite_rango_torre_tipo[f][x]))
                            {
                                if (tiempo%intervalo_danio[f]==0)
                                {
                                    enemigo[i-1].reducir_vida(danio_torre[f]);
                                    vidas_texto[i-1].setVariable(enemigo[i-1].getVida());
                                    enemigo[i-1].setColor(50,50,77);
                                }
                                else
                                {
                                    enemigo[i-1].setColor(255,255,255);
                                }
                            }
                        }
                    }
                    if (enemigo[i-1].getVida()>0)
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
                    enemigo[i-1].cambiar_frame_sprite(tiempo_zombies[i-1]);

                    ///Peque�a maquina de estados
                    switch (enemigo[i-1].getEstado())
                    {
                    case 0:
                        ///el pixelperfectTest del mapa colisionable reemplazara a la tecnica del paint y el limite de pixeles
                        ///mientras cambio los limites colisionables sobre el mapa del lvl1, seguimos con los pixeles.
                        if (/*PixelPerfectTest(enemigo[i-1],camino1.getSprite())*/enemigo[i-1].getY()<199&&enemigo[i-1].getX()==285)
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
                        break;
                    case 1:
                        if (enemigo[i-1].getX()>47)
                        {
                            enemigo[i-1].mover_izq();
                        }
                        else
                            enemigo[i-1].setEstado(2);
                        break;
                    case 2:
                        if (enemigo[i-1].getY()<500)
                        {
                            enemigo[i-1].mover_abajo();
                        }
                        else
                            enemigo[i-1].setEstado(3);
                        break;
                    case 3:
                        if (enemigo[i-1].getX()<485)
                        {
                            enemigo[i-1].mover_derecha();
                        }
                        else
                            enemigo[i-1].setEstado(4);
                        break;
                    case 4:
                        if (enemigo[i-1].getY()>177)
                        {
                            enemigo[i-1].mover_arriba();
                        }
                        else
                            enemigo[i-1].setEstado(5);
                        break;
                    case 5:
                        if (enemigo[i-1].getX()<700)
                        {
                            enemigo[i-1].mover_derecha();
                        }
                        else
                            enemigo[i-1].setEstado(6);
                        break;
                    case 6:
                        if (enemigo[i-1].getOpacidad()!=0)
                        {
                            enemigo[i-1].decrementar_opacidad(5);
                            vidas_texto[i-1].setTransparencia(enemigo[i-1].getOpacidad());
                            enemigo[i-1].mover_derecha();
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

                        ///movimientos en diagonal
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
                if (tiempo%150==0)
                {
                    if (objetos<cantidad_bichos)
                    {
                        objetos++;
                    }
                }
                tiempo++;
                ///Metodo de clase Texto, para modificar el string porque la variable cambio de valor.

                ///--------
                tiempo_texto.setVariable(tiempo);
                ///--------

                /// SIGUIENTE OLEADA
                for(int h=0; h<cantidad_bichos; h++)
                {
                    if(enemigo[h].getVida()<=0)
                    {
                        bichos_muertos++;
                    }
                    if(bichos_muertos==cantidad_bichos)
                    {
                        siguiente_oleada=true;
                        vida_aumentada+=100;
                        aldeano.setVida(vida_aumentada);
                        for(int p=0; p<cantidad_bichos; p++)
                        {
                            vidas_texto[p].setVariable(vida_aumentada);
                        }
                        bichos_muertos=0;
                    }
                }
                if(siguiente_oleada==true)
                {
                    objetos=1;
                    tiempo=1;
                    cargar_vector_sprites(enemigo,aldeano,cantidad_bichos);
                    siguiente_oleada=false;
                }
                else
                {
                    bichos_muertos=0;
                }

            }
        }
        ///Pruebas iniciales con circulos
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
        /// FIN DEL ELSE
        window.display();
    }
    return 0;
}


#endif // JUEGO_H_INCLUDED
