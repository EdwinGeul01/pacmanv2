#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <X11/Xlib.h>

class menu{
 

public:
    menu();
    sf::RenderWindow *ventana_Menu;
    void Eventos();
    

private:
    void cargar_sprite();

    sf::Texture *background_texture;
    sf::Sprite  *background_sprite ;

    sf::Texture *play_button_texture;
    sf::Sprite  *play_button_sprite ;

     sf::Texture *Inst_button_texture;
    sf::Sprite  *Inst_button_sprite ;
};