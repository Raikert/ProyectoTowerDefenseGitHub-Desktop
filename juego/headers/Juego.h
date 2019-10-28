#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

int juego()
{
    ///carga del mundo

    RenderWindow window(VideoMode(1000, 600), "Tower Defense - La defensa del fuerte nicomando");

    ///Setea el framerate a 60 fps, comentar para mas velocidad,seteado para ver la velocidad real del juego
    ///bugeo de los sprites solucionado: ver linea 152;

    window.setFramerateLimit(60);

    ///Sector de Incializacion y generacion de Sprites y vectores de Sprites
    const int cantidad_bichos=10;
    float opacidad_bichos[cantidad_bichos]= {0};
    Sprites bicho("img/bicho_reside_circulo.png",opacidad_bichos,285,0);

    if (!bicho.getConfirmacion())
        return -10;

    Sprite v[cantidad_bichos];
    cargar_vector_sprites(v,bicho.getSprite(),cantidad_bichos);

    ///Camino lvl1 para modificaciones de colision por error de colisiones con los bichos - comentado

    /*
    Sprites camino1("img/caminolvl1.png")
    if (!camino1.getConfirmacion())
        return -10;
    */

    Texture textura_mapa,textura_bicho,textura_menu,textura_rango;

    if (!textura_mapa.loadFromFile("img/008.png"))
        return -1;
    if (!textura_menu.loadFromFile("img/006.jpg"))
        return -1;
    if (!textura_rango.loadFromFile("img/rango_torres.png"))
        return -1;

    textura_bicho.setSmooth(true);
    textura_rango.setSmooth(true);
    textura_menu.setSmooth(true);
    textura_mapa.setSmooth(true);

    ///Zona de texto
    Font tipo_de_texto,tipo_de_texto1;

    /// Variables en texto de las posiciones del mouse -------------------
    Font tipo_texto_mouse;
    if (!tipo_texto_mouse.loadFromFile("tipos_de_texto/OpenSans-BoldItalic.ttf"))
        return -1;
    Text texto_mousex,texto_mousey;
    texto_mousex.setFont(tipo_texto_mouse);
    texto_mousey.setFont(tipo_texto_mouse);
    texto_mousex.setCharacterSize(18);
    texto_mousey.setCharacterSize(18);
    texto_mousex.setPosition(627,545);
    texto_mousey.setPosition(693,549);
    ///-------------------------------------------------------------------

    /// Creacion de el texto vida ----------------------------------------
    Font tipo_texto_vida;
    if (!tipo_texto_vida.loadFromFile("tipos_de_texto/OpenSans-BoldItalic.ttf"))
        return -1;
    Text texto_vida[cantidad_bichos];
    for (int i=0; i<cantidad_bichos; i++)
    {
        texto_vida[i].setFont(tipo_texto_vida);
    }
    /// ------------------------------------------------------------------
    if (!tipo_de_texto.loadFromFile("tipos_de_texto/OpenSans-Bold.ttf"))
        return -1;
    if (!tipo_de_texto1.loadFromFile("tipos_de_texto/OpenSans-BoldItalic.ttf"))
        return -1;
    Text texto_prueba,texto_variable;
    texto_prueba.setFont(tipo_de_texto);
    texto_prueba.setString("GENTESSS EDITION");
    texto_prueba.setCharacterSize(24);
    texto_variable.setFont(tipo_de_texto1);

    ///Zona de texto

    Sprite mapa,menu;
    mapa.setTexture(textura_mapa);
    menu.setTexture(textura_menu);
    int mousexy[2];

    ///Si gente, le puse MUSICA WEEEEE
    Music musica_menu,musica_juego;
    if (!musica_menu.openFromFile("musica/song_sneaky_driver.ogg"))
        return -1;
    if (!musica_juego.openFromFile("musica/glorious morning.ogg"))
        return -1;

    ///volumen de la musica del menu
    musica_menu.setVolume(50.f);
    // musica_menu.setPlayingOffset(seconds(62.5f));
    musica_menu.play();
    musica_menu.setLoop(true);
    musica_juego.setVolume(50.f);
    musica_juego.setLoop(true);
    bool boolmusica=false,boolmusicajuego=true,habilitacionmouse=true;

    ///con esta variable se cambia la cantidad de monstruos en el mundo

    ///Para un futuro en donde pongamos a los 3 sprites de los 8 tipos de monstruos q consegui-veanlo en la carpeta de img

    /*
    Sprite v[cantidad_objetos][3];
    */

    ///objeto boton de la nueva clase de botones_rectangulo, 5 Parametros:
    ///Tamaño en Float X, Tamaño en Float Y, Posicion de la pantalla en Float X, Posicion de la pantalla en Float Y
    ///el Quinto parametro es transparencia q se pone en 0,osea invisible, por parametro por omision.
    ///Util para ver en q posicion de la pantalla se ubica el boton.

    Boton nueva_partida(237,38,351,316),cargar_partida(237,38,351,377),salir(237,38,351,437),sonido(55,50,872,487);

    /// Definicion de los espacios para las torres ----------------------------------------------------------------------------
    const int tam_torres = 9;
    /// Posiciones de cada torre
    Boton torre1(49,77,236,114),torre2(49,77,98,245),torre3(49,77,98,420),torre4(49,77,194,331),torre5(49,77,242,419);
    Boton torre6(49,77,339,419),torre7(49,77,434,419),torre8(49,77,482,90),torre9(49,77,535,224);
    /// Poiciones de la X para cerrar el menu de torre
    Boton cerrarTorre1(49,77,236,114),cerrarTorre2(49,77,98,245),cerrarTorre3(49,77,98,420),cerrarTorre4(49,77,194,331);
    Boton cerrarTorre5(49,77,242,419),cerrarTorre6(49,77,339,419),cerrarTorre7(49,77,434,419);
    Boton cerrarTorre8(49,77,482,90),cerrarTorre9(49,77,535,224);
    /// Submenu torre 1
    Boton torre1_t1(59,72,161,74),torre1_t2(59,72,220,74),torre1_t3(59,72,279,74);
    /// Declaracion del vector de menues de torres
    bool menu_torre[tam_torres];
    ponerEnFalso(menu_torre, tam_torres);
    /// Declaracion de las torres del menu de torres
    bool menu_torre_elegir[tam_torres];
    ponerEnFalso(menu_torre_elegir, tam_torres);
    /// Textura del menu de torres
    Texture textura_menu_torre;
    if (!textura_menu_torre.loadFromFile("img/Menu_Torres.png"))
        return -1;
    textura_menu_torre.setSmooth(true);
    /// Hacerlo un sprite
    Sprite Sprite_menu_torre[tam_torres];
    for (int x=0; x<tam_torres; x++)
    {
        Sprite_menu_torre[x].setTexture(textura_menu_torre);
    }
    Sprite_menu_torre[0].setPosition(torre1.getEsix()-75,torre1.getEsiy()-40);
    Sprite_menu_torre[1].setPosition(torre2.getEsix()-75,torre2.getEsiy()-40);
    Sprite_menu_torre[2].setPosition(torre3.getEsix()-75,torre3.getEsiy()-40);
    Sprite_menu_torre[3].setPosition(torre4.getEsix()-75,torre4.getEsiy()-40);
    Sprite_menu_torre[4].setPosition(torre5.getEsix()-75,torre5.getEsiy()-40);
    Sprite_menu_torre[5].setPosition(torre6.getEsix()-75,torre6.getEsiy()-40);
    Sprite_menu_torre[6].setPosition(torre7.getEsix()-75,torre7.getEsiy()-40);
    Sprite_menu_torre[7].setPosition(torre8.getEsix()-75,torre8.getEsiy()-40);
    Sprite_menu_torre[8].setPosition(torre9.getEsix()-75,torre9.getEsiy()-40);
    /// ----------------------------------------------------------------------------------------------------------------------

    ///Zona de declaracion de variables tipo rango-torres
    Sprite rango_prueba;
    rango_prueba.setTexture(textura_rango);
    rango_prueba.setColor(Color(24,81,213,100));
    rango_prueba.setPosition(130,378);

    /*
    Rect<jojo>::Rect(200,200,50,50);
    */

    int estados[cantidad_bichos] = {0};
    estados[0]=-1;
    float opacidad_menu=0; ///transparencia del objeto 255=100% porciento
    for (int i=0; i<=cantidad_bichos-1; i++)
    {
        ///Seria un corte de control donde por cada vuelta de J se cargara un frame de un tipo de bicho, faltaria la forma
        ///dinamica de indicar a cual tipo de monstruo cargar en cada fila de la matriz
        /*
        for (int j=0;j++<=2;j++) {*/
        /*
        v[i][j]...
        v[i][j]...
        v[i][j]...
        */
        /*
        v[i]=CircleShape(25.f);
        */

        /*
        v[i].setTexture(textura_bicho);
        v[i].setColor(Color(255,255,255,opacidad_objetos[i]));
        v[i].setPosition(285,0);
        */
        /*
        }*/
    }

    int objetos=1;
    int tiempo=1;

    ///Convertir una variable en un string, variable tiempo
    char tiempo_char[10];
    itoa(tiempo, tiempo_char, 10);
    string tiempo_string = string(tiempo_char);
    texto_variable.setString(tiempo_string);
    texto_variable.setCharacterSize(25);
    texto_variable.setPosition(600,300);
    texto_variable.setFillColor(Color::Black);

    ///variables de char y string para las axis del mouse
    char mousex_char[10],mousey_char[10];
    string mousex_string,mousey_string;
    ///--------------------------------------------------

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
    for (int i=0; i<cantidad_bichos; i++)
    {
        texto_vida[i].setString(vida_string);
        texto_vida[i].setCharacterSize(13);
        texto_vida[i].setFillColor(Color::Black);
    }

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

        mousexy[0]=Mouse::getPosition(window).x;
        mousexy[1]=Mouse::getPosition(window).y;

        ///Configuracion de los botones dentro del juego
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (habilitacionmouse)
            {
                ///sonido
                if (mousexy[0]>=sonido.getEsix()&&mousexy[0]<=sonido.getEsdx()&&mousexy[1]>=sonido.getEsdy()&&mousexy[1]<=sonido.getEidy())
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

                ///Torre-1 --------------------------------------------------------------------------------------------------------------
                if (mousexy[0]>=torre1.getEsix()&&mousexy[0]<=torre1.getEsdx()&&mousexy[1]>=torre1.getEsiy()&&mousexy[1]<=torre1.getEidy())
                {
                    /// SE ABRE EL MENU DE TORRES
                    menu_torre[0]=true;
                }
                else
                {
                    menu_torre[0]=false;
                }
                ///Torre-2 --------------------------------------------------------------------------------------------------------------
                if (mousexy[0]>=torre2.getEsix()&&mousexy[0]<=torre2.getEsdx()&&mousexy[1]>=torre2.getEsiy()&&mousexy[1]<=torre2.getEidy())
                {
                    /// SE ABRE EL MENU DE TORRES
                    menu_torre[1]=true;
                }
                else
                {
                    menu_torre[1]=false;
                }
                ///Torre-3 --------------------------------------------------------------------------------------------------------------
                if (mousexy[0]>=torre3.getEsix()&&mousexy[0]<=torre3.getEsdx()&&mousexy[1]>=torre3.getEsiy()&&mousexy[1]<=torre3.getEidy())
                {
                    /// SE ABRE EL MENU DE TORRES
                    menu_torre[2]=true;
                }
                else
                {
                    menu_torre[2]=false;
                }
                ///Torre-4 --------------------------------------------------------------------------------------------------------------
                if (mousexy[0]>=torre4.getEsix()&&mousexy[0]<=torre4.getEsdx()&&mousexy[1]>=torre4.getEsiy()&&mousexy[1]<=torre4.getEidy())
                {
                    /// SE ABRE EL MENU DE TORRES
                    menu_torre[3]=true;
                }
                else
                {
                    menu_torre[3]=false;
                }
                ///Torre-5 --------------------------------------------------------------------------------------------------------------
                if (mousexy[0]>=torre5.getEsix()&&mousexy[0]<=torre5.getEsdx()&&mousexy[1]>=torre5.getEsiy()&&mousexy[1]<=torre5.getEidy())
                {
                    /// SE ABRE EL MENU DE TORRES
                    menu_torre[4]=true;
                }
                else
                {
                    menu_torre[4]=false;
                }
                ///Torre-6 --------------------------------------------------------------------------------------------------------------
                if (mousexy[0]>=torre6.getEsix()&&mousexy[0]<=torre6.getEsdx()&&mousexy[1]>=torre6.getEsiy()&&mousexy[1]<=torre6.getEidy())
                {
                    /// SE ABRE EL MENU DE TORRES
                    menu_torre[5]=true;
                }
                else
                {
                    menu_torre[5]=false;
                }
                ///Torre-7 --------------------------------------------------------------------------------------------------------------
                if (mousexy[0]>=torre7.getEsix()&&mousexy[0]<=torre7.getEsdx()&&mousexy[1]>=torre7.getEsiy()&&mousexy[1]<=torre7.getEidy())
                {
                    /// SE ABRE EL MENU DE TORRES
                    menu_torre[6]=true;
                }
                else
                {
                    menu_torre[6]=false;
                }
                ///Torre-8 --------------------------------------------------------------------------------------------------------------
                if (mousexy[0]>=torre8.getEsix()&&mousexy[0]<=torre8.getEsdx()&&mousexy[1]>=torre8.getEsiy()&&mousexy[1]<=torre8.getEidy())
                {
                    /// SE ABRE EL MENU DE TORRES
                    menu_torre[7]=true;
                }
                else
                {
                    menu_torre[7]=false;
                }
                ///Torre-9 --------------------------------------------------------------------------------------------------------------
                if (mousexy[0]>=torre9.getEsix()&&mousexy[0]<=torre9.getEsdx()&&mousexy[1]>=torre9.getEsiy()&&mousexy[1]<=torre9.getEidy())
                {
                    /// SE ABRE EL MENU DE TORRES
                    menu_torre[8]=true;
                }
                else
                {
                    menu_torre[8]=false;
                }

                ///mientras el mouse este presionado no repetira ninguna accion en bucle hasta q se suelte el click izquierdo
                habilitacionmouse=false;
            }
        }


        else
            ///una vez que se solto el mouse, recien se habilita para una nueva accion
            habilitacionmouse=true;

        window.clear();

        for (int i=1; i<=objetos; i++)
        {
            if (estados[i-1]!=-1)
            {
                window.draw(mapa);
                ///zona de variables mouse ------
                itoa(mousexy[0], mousex_char, 10);
                mousex_string=string(mousex_char);
                texto_mousex.setString(mousex_string);
                itoa(mousexy[1], mousey_char, 10);
                mousey_string=string(mousey_char);
                texto_mousey.setString(mousey_string);
                window.draw(texto_mousex);
                window.draw(texto_mousey);
                ///-------------------------------
                window.draw(texto_variable);
                window.draw(rango_prueba);

                for (int x=0; x<tam_torres; x++)
                {
                    if (menu_torre[x]==true)
                    {
                        window.draw(Sprite_menu_torre[x]);

                    }
                }

                if (!boolmusica)
                {
                    musica_juego.play();
                    boolmusica=true;
                }

                for (int d=1; d<=objetos; d++)
                {
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
                }
            }
            ///Pequeña maquina de estados
            switch (estados[i-1])
            {
            case -1:
                menu.setColor(Color(255,255,255,opacidad_menu));
                window.draw(menu);
                window.draw(nueva_partida.getBoton());
                window.draw(texto_prueba);
                ///zona de variables mouse ------
                itoa(mousexy[0], mousex_char, 10);
                mousex_string=string(mousex_char);
                texto_mousex.setString(mousex_string);
                itoa(mousexy[1], mousey_char, 10);
                mousey_string=string(mousey_char);
                texto_mousey.setString(mousey_string);
                window.draw(texto_mousex);
                window.draw(texto_mousey);
                ///-------------------------------

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
                        if (mousexy[0]>=nueva_partida.getEsix()&&mousexy[0]<=nueva_partida.getEsdx()&&mousexy[1]>=nueva_partida.getEsdy()&&mousexy[1]<=nueva_partida.getEidy())
                        {
                            /*
                            volumen_menu-=0.1;
                            musica_menu.setVolume(volumen_menu);
                                */
                            musica_menu.stop();
                            texto_mousex.setFillColor(Color(Color::Black));
                            texto_mousey.setFillColor(Color(Color::Black));
                            estados[0]=0;
                        }
                        ///Cargar Partida
                        if (mousexy[0]>=cargar_partida.getEsix()&&mousexy[0]<=cargar_partida.getEsdx()&&mousexy[1]>=cargar_partida.getEsdy()&&mousexy[1]<=cargar_partida.getEidy())
                        {
                            musica_menu.stop();
                            musica_juego.play();

                        }
                        ///Salir
                        if (mousexy[0]>=salir.getEsix()&&mousexy[0]<=salir.getEsdx()&&mousexy[1]>=salir.getEsdy()&&mousexy[1]<=salir.getEidy())
                        {
                            musica_menu.stop();
                            window.close();
                        }

                    }
                }
                break;
            case 0:

                ///el pixelperfectTest del mapa colisionable reemplazara a la tecnica del paint y el limite de pixeles
                ///mientras cambio los limites colisionables sobre el mapa del lvl1, seguimos con los pixeles.
                if (/*PixelPerfectTest(v[i-1],camino1.getSprite())*/v[i-1].getPosition().y<199&&v[i-1].getPosition().x==285)
                {
                    if(opacidad_bichos[i-1]<255)
                    {
                        opacidad_bichos[i-1]+=5;
                        v[i-1].setColor(Color(255,255,255,opacidad_bichos[i-1]));
                    }
                    mov_obj_abajo(v,i-1,0.5);
                }
                else
                    estados[i-1]=1;
                break;

            case 1:
                if (v[i-1].getPosition().x>47)
                {
                    mov_obj_izq(v,i-1,0.5);
                }
                else
                    estados[i-1]=2;
                break;
            case 2:
                if (v[i-1].getPosition().y<500)
                {
                    mov_obj_abajo(v,i-1,0.5);
                }
                else
                    estados[i-1]=3;
                break;
            case 3:
                if (v[i-1].getPosition().x<485)
                {
                    mov_derecha(v,i-1,0.5);
                }
                else
                    estados[i-1]=4;
                break;
            case 4:
                if (v[i-1].getPosition().y>177)
                {
                    mov_obj_arriba(v,i-1,0.5);
                }
                else
                    estados[i-1]=5;
                break;
            case 5:
                if (v[i-1].getPosition().x<700)
                {
                    mov_derecha(v,i-1,0.5);
                }
                else
                    estados[i-1]=6;
                break;
            case 6:
                if (opacidad_bichos[i-1]!=0)
                {
                    opacidad_bichos[i-1]-=5;
                    v[i-1].setColor(Color(255,255,255,opacidad_bichos[i-1]));
                    mov_derecha(v,i-1,0.5);
                }
                else
                    estados[i-1]=0;
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
                glorious morning           mov_obj_abajo(v,objetos,0.1);

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
        if (tiempo%200==0)
        {
            if (objetos<cantidad_bichos)
            {
                objetos++;
                tiempo=1;
            }
        }
        if (estados[0]!=-1)
        {
            tiempo++;

            ///cada vez que se actualiza la variable se tiene que actualizar el string
            itoa(tiempo,tiempo_char,10);
            tiempo_string = string(tiempo_char);
            texto_variable.setString(tiempo_string);
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
        window.display();
    }
    return 0;
}


#endif // JUEGO_H_INCLUDED
