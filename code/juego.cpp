#include "juego.h"
#include <thread>
#include <X11/Xlib.h>
#include <math.h>

juego::juego()
{

    ventana = new sf::RenderWindow(sf::VideoMode(800, 600), "Game Screen");
    ventana->setFramerateLimit(60);
    juego::cargarTexturas();
    ventana->clear(sf::Color::Black);
    ventana->display();
    juego::gameloops();
}

void juego::gameloops()
{

    XInitThreads();
    std::thread draw(&juego::draw, this);
    std::thread Eventos_Teclado(&juego::Eventos_Teclado, this);
    std::thread mov_fantasmas(&juego::movfantasmas, this);
    std::thread colision_fantasma(&juego::ColisionFantasma, this);

    mov_fantasmas.join();
    draw.join();
  
    Eventos_Teclado.join();
    colision_fantasma.join();
}

void juego::draw()
{
    while (ventana->isOpen())
    {
        ventana->clear(sf::Color::Black);

        ventana->draw(*s_pacman);
        ventana->draw(*l_wall);
        ventana->draw(*r_wall);
        ventana->draw(*t_wall);
        ventana->draw(*d_wall);

        ventana->draw(*bloque_si);
        ventana->draw(*bloque_sm);
        ventana->draw(*bloque_sd);

        ventana->draw(*bloque_mi);
        ventana->draw(*bloque_mm);
        ventana->draw(*bloque_md);

        ventana->draw(*bloque_ii);
        ventana->draw(*bloque_im);
        ventana->draw(*bloque_id);

        //comida
        for (int i = 0; i < 96; i++) {
          ventana->draw(*comidaSprites[i]);
        }

        //fantasma
        for (int i = 0; i < 5; i++) {
          ventana->draw(*fantasmaSprites[i]);
        }

        //texto
        ventana->draw(*s_lives);
        ventana->draw(*Score);
        //vidas
        for (int i = 0; i < 3; i++) {
            ventana->draw(*s_vida[i]);
        }

        //
        ventana->display();

        sf::sleep(sf::Time(sf::milliseconds(20)));
    }
}

void juego::Eventos_Teclado()
{
    while (ventana->isOpen())
    {

        sf::Event event;

        if (ventana->pollEvent(event) || movimiento != 0)
        {
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            {
                ventana->close();
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right) || movimiento == 1)
            {
              movimiento = 1;
                if ((!s_pacman->getGlobalBounds().intersects(r_wall->getGlobalBounds())))
                {
                    s_pacman->setPosition(s_pacman->getPosition().x + 5, s_pacman->getPosition().y);
                      //ANIMACION PACMAN
                      if (cuadros_mov <=10)
                      {
                        s_pacman->setTexture(*t_pacmanClose);
                        cuadros_mov++;
                      }else if(cuadros_mov<= 20)
                      {
                        s_pacman->setTexture(*t_pacman);
                        cuadros_mov++;

                      }else{
                        cuadros_mov = 0;
                      }

                      
                    if ((s_pacman->getGlobalBounds().intersects(bloque_si->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_sd->getGlobalBounds())) ||
                        (s_pacman->getGlobalBounds().intersects(bloque_sm->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_mi->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_mm->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_md->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_ii->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_im->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_id->getGlobalBounds())))
                    {
                        s_pacman->setPosition(s_pacman->getPosition().x - 5, s_pacman->getPosition().y);
                        movimiento = 0;
                    }
                      for (int i = 0; i < 96; i++) {
                          if((s_pacman->getGlobalBounds().intersects(comidaSprites[i]->getGlobalBounds()) && comidaSprites[i]->getColor() != sf::Color::Transparent)){
                           
                               comidaSprites[i]->setColor(sf::Color::Transparent);
                               ContadorScore++;
                            if ( ContadorScore == 96)
                            {
                              ventana->close();
                            }
                            
                          
                          }
                      }

                }else{
                        movimiento = 0;


                }
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left) || movimiento == 2)
            {
              movimiento = 2;

                if (!s_pacman->getGlobalBounds().intersects(l_wall->getGlobalBounds()))
                {
                    s_pacman->setPosition(s_pacman->getPosition().x - 5, s_pacman->getPosition().y);
                      //ANIMACION PACMAN
                      if (cuadros_mov <=10)
                      {
                        s_pacman->setTexture(*t_pacmanClose);
                        cuadros_mov++;
                      }else if(cuadros_mov<= 20)
                      {
                        s_pacman->setTexture(*t_pacman180);
                        cuadros_mov++;

                      }else{
                        cuadros_mov = 0;
                      }


                    if ((s_pacman->getGlobalBounds().intersects(bloque_si->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_sd->getGlobalBounds())) ||
                        (s_pacman->getGlobalBounds().intersects(bloque_sm->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_mi->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_mm->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_md->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_ii->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_im->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_id->getGlobalBounds())))
                    {
                        s_pacman->setPosition(s_pacman->getPosition().x + 5, s_pacman->getPosition().y);
                        movimiento = 0;
                    }
                      for (int i = 0; i < 96; i++) {
                          if((s_pacman->getGlobalBounds().intersects(comidaSprites[i]->getGlobalBounds()) && comidaSprites[i]->getColor() != sf::Color::Transparent)){
                           
                               comidaSprites[i]->setColor(sf::Color::Transparent);
                               ContadorScore++;
                              if ( ContadorScore == 96)
                            {
                              ventana->close();
                            }
                          
                          }
                      }

                }else{

                  movimiento = 0;
                }
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up) || movimiento ==3)
            {
              movimiento = 3;
                if (!s_pacman->getGlobalBounds().intersects(t_wall->getGlobalBounds()))
                {
                    s_pacman->setPosition(s_pacman->getPosition().x, s_pacman->getPosition().y - 5);
                    //ANIMACION PACMAN
                      if (cuadros_mov <=10)
                      {
                        s_pacman->setTexture(*t_pacmanClose);
                        cuadros_mov++;
                      }else if(cuadros_mov<= 20)
                      {
                        s_pacman->setTexture(*t_pacman270);
                        cuadros_mov++;

                      }else{
                        cuadros_mov = 0;
                      }


                    if ((s_pacman->getGlobalBounds().intersects(bloque_si->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_sd->getGlobalBounds())) ||
                        (s_pacman->getGlobalBounds().intersects(bloque_sm->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_mi->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_mm->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_md->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_ii->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_im->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_id->getGlobalBounds())))
                    {
                        s_pacman->setPosition(s_pacman->getPosition().x, s_pacman->getPosition().y + 5);
                        movimiento = 0;
                    }
                      for (int i = 0; i < 96; i++) {
                          if((s_pacman->getGlobalBounds().intersects(comidaSprites[i]->getGlobalBounds()) && comidaSprites[i]->getColor() != sf::Color::Transparent)){
                           
                               comidaSprites[i]->setColor(sf::Color::Transparent);
                               ContadorScore++;
                              if ( ContadorScore == 96)
                            {
                              ventana->close();
                            }
                          
                          }
                      }

                }else{

                  movimiento = 0;
                }
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down) || movimiento == 4)
            {
              movimiento = 4;
                if (!s_pacman->getGlobalBounds().intersects(d_wall->getGlobalBounds()))
                {
                    s_pacman->setPosition(s_pacman->getPosition().x, s_pacman->getPosition().y + 5);
                    //ANIMACION PACMAN
                      if (cuadros_mov <=10)
                      {
                        s_pacman->setTexture(*t_pacmanClose);
                        cuadros_mov++;
                      }else if(cuadros_mov<= 20)
                      {
                        s_pacman->setTexture(*t_pacman90);
                        cuadros_mov++;

                      }else{
                        cuadros_mov = 0;
                      }


                    if ((s_pacman->getGlobalBounds().intersects(bloque_si->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_sd->getGlobalBounds())) ||
                        (s_pacman->getGlobalBounds().intersects(bloque_sm->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_mi->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_mm->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_md->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_ii->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_im->getGlobalBounds())) || (s_pacman->getGlobalBounds().intersects(bloque_id->getGlobalBounds())))
                    {
                        s_pacman->setPosition(s_pacman->getPosition().x, s_pacman->getPosition().y - 5);
                        movimiento = 0;
                    }
                      for (int i = 0; i < 96; i++) {
                           if((s_pacman->getGlobalBounds().intersects(comidaSprites[i]->getGlobalBounds()) && comidaSprites[i]->getColor() != sf::Color::Transparent)){
                           
                               comidaSprites[i]->setColor(sf::Color::Transparent);
                               ContadorScore++;
                              if ( ContadorScore == 96)
                            {
                              ventana->close();
                            }
                          
                          }
                      }
                    
                }else
                {
                  movimiento = 0;

                }
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            {
            }
        }
    sf::sleep(sf::Time(sf::milliseconds(20)));

    }

}

void juego::cargarTexturas()
{

  //cargando texturas y sprites
    t_vida =new sf::Texture();
    t_lives = new sf::Texture();
    t_pacman = new sf::Texture();
    t_pacmanClose = new sf::Texture();
    t_pacman180 = new sf::Texture();
    t_pacman90 = new sf::Texture();
    t_pacman270 = new sf::Texture();
    s_pacman = new sf::Sprite();
    t_cuadro = new sf::Texture();
    s_lives = new sf::Sprite();
    l_wall = new sf::Sprite();
    t_wall = new sf::Sprite();
    r_wall = new sf::Sprite();
    d_wall = new sf::Sprite();
    bloque_sd = new sf::Sprite();
    bloque_si = new sf::Sprite();
    bloque_sm = new sf::Sprite();
    bloque_md = new sf::Sprite();
    bloque_mi = new sf::Sprite();
    bloque_mm = new sf::Sprite();
    bloque_id = new sf::Sprite();
    bloque_ii = new sf::Sprite();
    bloque_im = new sf::Sprite();
    comidat= new sf::Texture();
    comidas = new sf::Sprite();
    fantasmaT = new sf::Texture();
    fantasmaS = new sf::Sprite();
    Score=new sf::Text();
    FontS=new sf::Font();

    for (int i = 0; i < 3; i++)
    {
      s_vida[i]= new sf::Sprite();
    }
    

    //Pacman
    t_pacman->loadFromFile("../recursos/PacmanOpen.png");
    t_pacmanClose->loadFromFile("../recursos/PacmanClose.png");
    t_pacman180->loadFromFile("../recursos/PacmanOpen180.png");
    t_pacman270->loadFromFile("../recursos/PacmanOpen270.png");
    t_pacman90->loadFromFile("../recursos/PacmanOpen90.png");


    s_pacman->setTexture(*t_pacman);
    //Textures De Fantasmas

    //Texture de comida
    comidat->loadFromFile("../recursos/food.png");
    //Sprite de Comida
    comidas->setTexture(*comidat);


    for (int i = 0; i < 96; i++) {
        comidaSprites[i]=new sf::Sprite(*comidat);
    }


    //textura de fantasma
    fantasmaT->loadFromFile("../recursos/Phantasm1.png");
    //sprite de fantasma
    fantasmaS->setTexture(*fantasmaT);
    for (int i = 0; i < 5; i++) {
        fantasmaSprites[i]=new sf::Sprite(*fantasmaT);
    }

    //texto
    t_lives->loadFromFile("../recursos/lives.png");
    s_lives->setTexture(*t_lives);
    FontS->loadFromFile("../recursos/Square.ttf");

    //vidas
    t_vida->loadFromFile("../recursos/heart.png");
    for (int i = 0; i < 3; i++) {
        s_vida[i]=new sf::Sprite(*t_vida);
    }

    //texturas del mapa
    t_cuadro->loadFromFile("../recursos/cuadro.png");
    l_wall->setTexture(*t_cuadro);
    r_wall->setTexture(*t_cuadro);
    t_wall->setTexture(*t_cuadro);
    d_wall->setTexture(*t_cuadro);
    bloque_si->setTexture(*t_cuadro);
    bloque_sd->setTexture(*t_cuadro);
    bloque_sm->setTexture(*t_cuadro);
    bloque_mi->setTexture(*t_cuadro);
    bloque_md->setTexture(*t_cuadro);
    bloque_mm->setTexture(*t_cuadro);
    bloque_ii->setTexture(*t_cuadro);
    bloque_id->setTexture(*t_cuadro);
    bloque_im->setTexture(*t_cuadro);
    s_lives->setTexture(*t_lives);

    //Texto
    Score->setFont(*FontS);
    Score->setPosition(600,150);//primero izquierda derecha, segundo arriba y abajo
    std::string punt = "Puntaje: " + ContadorScore;
    std::cout << punt;
    Score->setString(punt);
    Score->setCharacterSize(0);
    Score->setFillColor(sf::Color::White);


    //Color Fantasmas

    //Pacman
    s_pacman->setScale(0.05, 0.05);
    //Muros
    l_wall->setScale(0.2, 400);
    t_wall->setScale(400, 0.2);
    r_wall->setScale(0.2, 400);
    d_wall->setScale(400, 0.2);

    //bloques
    bloque_si->setScale(4.5, 4.5);
    bloque_sd->setScale(4.5, 4.5);
    bloque_sm->setScale(4.6, 5);

    bloque_mi->setScale(4.5, 4.5);
    bloque_md->setScale(4.5, 4.5);
    bloque_mm->setScale(4.6, 4.6);

    bloque_ii->setScale(5, 4.4);
    bloque_id->setScale(5, 4.4);
    bloque_im->setScale(4.6, 5.8);

    //Comida
    comidas->setScale(0.01,0.01);

    for (int i = 0; i < 96; i++) {
      comidaSprites[i]->setScale(0.01, 0.01);
    }

    //Fantasmas
    for (int i = 0; i < 5; i++) {
      fantasmaSprites[i]->setScale(0.25, 0.25);
    }

    //texto
    s_lives->setScale(0.5,0.5);

    //vidas
    for (int i = 0; i < 3; i++) {
        s_vida[i]->setScale(0.15,0.15);
    }


    //POSICIONES
    bloque_si->setPosition(35, 35);
    bloque_sm->setPosition(226, 0);
    bloque_sd->setPosition(405, 35);

    bloque_mi->setPosition(35, 230);
    bloque_mm->setPosition(226, 230);
    bloque_md->setPosition(405, 230);

    bloque_ii->setPosition(35, 420);
    bloque_im->setPosition(226, 420);
    bloque_id->setPosition(405, 420);

    r_wall->setPosition(592, 0);
    d_wall->setPosition(0, 592);
    s_pacman->setPosition(280, 390);

    s_lives->setPosition(600,0);
    //Fantasmas
    for (int i = 0; i < 5; i++) {
      fantasmaSprites[i]->setPosition(250 + (i*20), 250);
    }
    //comida

    int y=20;
    for (int i = 0; i < 15; i++) {
      comidaSprites[i]->setPosition(20, y);
      y+=40;
    }
    y=20;
    for (int i = 15; i < 30; i++) {
      comidaSprites[i]->setPosition(580, y);
      y+=40;
    }
    y=20;
    for (int i = 30; i < 45; i++) {
      comidaSprites[i]->setPosition(390, y);
      y+=40;
    }
    y=20;
    for (int i = 45; i < 60; i++) {
      comidaSprites[i]->setPosition(210, y);
      y+=40;
    }
    int x=60;
    for (int i = 60; i < 64; i++) {
      comidaSprites[i]->setPosition(x, 20);
      x+=40;
    }
    x=60;
    for (int i = 64; i < 68; i++) {
      comidaSprites[i]->setPosition(x, 210);
      x+=40;
    }
    x=60;
    for (int i = 68; i < 72; i++) {
      comidaSprites[i]->setPosition(x, 400);
      x+=40;
    }
    x=60;
    for (int i = 72; i < 76; i++) {
      comidaSprites[i]->setPosition(x, 580);
      x+=40;
    }

    x=430;
    for (int i = 76; i < 80; i++) {
      comidaSprites[i]->setPosition(x, 20);
      x+=40;
    }
    x=430;
    for (int i = 80; i < 84; i++) {
      comidaSprites[i]->setPosition(x, 210);
      x+=40;
    }
    x=430;
    for (int i = 84; i < 88; i++) {
      comidaSprites[i]->setPosition(x, 400);
      x+=40;
    }
    x=430;
    for (int i = 88; i < 92; i++) {
      comidaSprites[i]->setPosition(x, 580);
      x+=40;
    }
    x=237;
    for (int i = 92; i < 96; i++) {
      comidaSprites[i]->setPosition(x, 172);
      x+=40;
    }

    //vidas
    s_vida[0]->setPosition(610,60);
    s_vida[1]->setPosition(650,60);
    s_vida[2]->setPosition(700,60);

      




}

void juego::movfantasmas()
{
  long mover =  (rand() % 5)+1;
  while (ventana->isOpen())
  {

    for (int i = 0; i < 5; i++)
    {
      mover =  (rand() % 2)+1;
      if (direcionx[i])
      {
        fantasmaSprites[i]->setPosition(fantasmaSprites[i]->getPosition().x+mover,fantasmaSprites[i]->getPosition().y);
        if (fantasmaSprites[i]->getGlobalBounds().intersects(r_wall->getGlobalBounds()))
        {
        fantasmaSprites[i]->setPosition(fantasmaSprites[i]->getPosition().x-mover,fantasmaSprites[i]->getPosition().y);
        direcionx[i] = !direcionx[i];

        }
        
      }else{
        
        fantasmaSprites[i]->setPosition(fantasmaSprites[i]->getPosition().x-mover,fantasmaSprites[i]->getPosition().y);
        if (fantasmaSprites[i]->getGlobalBounds().intersects(l_wall->getGlobalBounds()))
        {
        fantasmaSprites[i]->setPosition(fantasmaSprites[i]->getPosition().x+mover,fantasmaSprites[i]->getPosition().y);
        direcionx[i] = !direcionx[i];

        }
      }

       if (direcciony[i])
      {
        fantasmaSprites[i]->setPosition(fantasmaSprites[i]->getPosition().x,fantasmaSprites[i]->getPosition().y+mover);
        if (fantasmaSprites[i]->getGlobalBounds().intersects(d_wall->getGlobalBounds()))
        {
        fantasmaSprites[i]->setPosition(fantasmaSprites[i]->getPosition().x,fantasmaSprites[i]->getPosition().y-mover);
        //inteligencia para seguir al jugador
        if (fantasmaSprites[i]->getPosition().x < s_pacman->getPosition().x)
        {
          direcionx[i] = true;
        }else{
            direcionx[i]=false;
        }
        
        direcciony[i] = !direcciony[i];

        }

      }else{

        fantasmaSprites[i]->setPosition(fantasmaSprites[i]->getPosition().x,fantasmaSprites[i]->getPosition().y-mover);
         
         if (fantasmaSprites[i]->getGlobalBounds().intersects(t_wall->getGlobalBounds()))
        {
        fantasmaSprites[i]->setPosition(fantasmaSprites[i]->getPosition().x,fantasmaSprites[i]->getPosition().y+mover);
        //inteligencia para seguir al jugador
        if (fantasmaSprites[i]->getPosition().x < s_pacman->getPosition().x)
        {
          direcionx[i] = true;
        }else{
            direcionx[i]=false;
        }
        direcciony[i] = !direcciony[i];

        }
      }
      
      

    }
    
    sf::sleep(sf::Time(sf::milliseconds(20)));


  }
  

}

void juego::ColisionFantasma()
{
  while (ventana->isOpen())
  {
    for (int i = 0; i < 5; i++)
    {
      if (fantasmaSprites[i]->getGlobalBounds().intersects(s_pacman->getGlobalBounds()))
      {
        s_pacman->setPosition(280,390);
        for (int i = 0; i < 5; i++) {
             fantasmaSprites[i]->setPosition(250 + (i*20), 250);
             
      }
        vidas --;
        s_vida[vidas]->setColor(sf::Color::Transparent);
      if (vidas == 0 )
      {
          ventana->close();
      }
      
      }
      
    }
    

  }
  

}