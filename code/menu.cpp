#include "menu.h"
#include <iostream>
#include <thread>
#include "juego.h"

menu::menu(){
    
    menu::ventana_Menu = new sf::RenderWindow(sf::VideoMode(400,600),"Menu");
    ventana_Menu->setFramerateLimit(60);
    
    ventana_Menu->clear();
    cargar_sprite();
    ventana_Menu->draw(*background_sprite);
    ventana_Menu->draw(*play_button_sprite);
    ventana_Menu->draw(*Inst_button_sprite);
    ventana_Menu->display();

    std::thread h_eventos(&menu::Eventos,this);
    h_eventos.join();

 

}


void menu::Eventos(){

    while (ventana_Menu->isOpen())
    {

        sf::Event event;
        
        if (ventana_Menu->pollEvent(event))
        {
            if ((event.type == sf::Event::KeyPressed) &&(event.key.code == sf::Keyboard::Space) )
            {
                ventana_Menu->close();
            }


            if ((event.type == sf::Event::KeyPressed) &&(event.key.code == sf::Keyboard::R) )
            {
                ventana_Menu->clear();
            }

            if ((event.type==sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
            {
                sf::Vector2f mposition(sf::Mouse::getPosition(*ventana_Menu));
                if (play_button_sprite->getGlobalBounds().contains(mposition))
                {
                    ventana_Menu->close();
                     juego game;
                    
                   
                    
                }
                
            }
            
            
        }
        
        

    }

        
std::terminate();
}

void menu::cargar_sprite(){
    background_texture = new sf::Texture();
    background_sprite = new sf::Sprite();
    play_button_texture = new sf::Texture();
    play_button_sprite = new sf::Sprite();
    Inst_button_texture = new sf::Texture();
    Inst_button_sprite = new sf::Sprite();

    background_texture->loadFromFile("../recursos/background.jpg");
    background_sprite->setTexture(*background_texture);

    play_button_texture->loadFromFile("../recursos/button.png");
    play_button_sprite->setTexture(*play_button_texture);
    
    Inst_button_texture->loadFromFile("../recursos/int.jpeg");
    Inst_button_sprite->setTexture(*Inst_button_texture);

    play_button_sprite->setScale(1,1);
    background_sprite->setScale(1,1);
    Inst_button_sprite->setScale(0.15,0.15);
    

    

    
    Inst_button_sprite->setPosition(290,510);
    play_button_sprite->setPosition(sf::Vector2f(120,200));

}


