#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <X11/Xlib.h>

class Records{

    public:
    sf::Text *TituloCronometro;
    sf::Text *TituloPuntaje;
    sf::Font *FondoLetras;
    sf::Text *CronometroT[10];
    sf::Text *PuntajeT[10];
    Records();        
    sf::RenderWindow *ventana_Historial;
    void Eventos();
    void VerDatos();
    void CargarSprites();
    void Visualizar();
    void Dibujar();

};