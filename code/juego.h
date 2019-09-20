#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

class juego
{

public:
    sf::RenderWindow *ventana;
    juego();
    void cargarTexturas();
    void gameloops();
    void draw();
    void Eventos_Teclado();
    void movfantasmas();
    void ColisionFantasma();

    //Comida no power up
    sf::Texture *comidat;
    sf::Sprite *comidas;
    sf::Sprite *comidaSprites[96];

    //fantasmas
    sf::Texture *fantasmaT;
    sf::Sprite *fantasmaS;
    sf::Sprite *fantasmaSprites[5];

    bool direcionx[5] = {true, false, true, true, false};
    bool direcciony[5] = {false, true, true, true, false};
    int movimiento = 0;
    int vidas = 3;
    int cuadros_mov = 0;
    //vidas
    sf::Texture *t_vida;
    sf::Sprite *s_vida[3];
    //cronometro
    sf::Text *t_cronometro;
    sf::Font *f_cronometro;
    int Cronometro;
    std::string CronometroS;
    //Cronometro 2 xD
    sf::Time tiempoT;
    float tiempoF;

    // movimiento  = 1 -- derecha
    // movimiento  = 2 int Cronometro;int Cronometro;-- izquierda
    // movimiento  = 3 -- arriba
    // movimiento  = 4 -- abajo

    //Pacman
    sf::Texture *t_pacman;
    sf::Texture *t_pacmanClose;
    sf::Texture *t_pacman90;
    sf::Texture *t_pacman180;
    sf::Texture *t_pacman270;

    sf::Sprite *s_pacman;
    //Fin De Pacman
    //Paredes
    sf::Texture *t_cuadro;
    sf::Sprite *l_wall;
    sf::Sprite *t_wall;
    sf::Sprite *d_wall;
    sf::Sprite *r_wall;

    //-----------------------
    sf::Sprite *bloque_si;
    sf::Sprite *bloque_sm;
    sf::Sprite *bloque_sd;
    //-----------------------

    sf::Sprite *bloque_mi;
    sf::Sprite *bloque_mm;
    sf::Sprite *bloque_md;

    //--------------------

    sf::Sprite *bloque_ii;
    sf::Sprite *bloque_im;
    sf::Sprite *bloque_id;

    //texto
    sf::Texture *t_lives;
    sf::Sprite *s_lives;

    //Score
    int ContadorScore = 0;
    sf::Text *ScoreT;
    sf::Font *ScoreF;
    sf::Text *Score;
    sf::Font *FontS;

    //Final
    sf::Text *Ending;
    bool final = false;

    //Perdiste
    sf::Text *Par;
    bool perdi = false;
};