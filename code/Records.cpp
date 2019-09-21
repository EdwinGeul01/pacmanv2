#include "Records.h"
#include <thread>
#include "menu.h"
#include <fstream>
#include <string>


Records::Records(){
    Records::ventana_Historial= new sf::RenderWindow(sf::VideoMode(400,600),"Records");
    ventana_Historial->setFramerateLimit(60);
    Records::CargarSprites();
    ventana_Historial->clear(sf::Color::Black);
    ventana_Historial->display();
    Records::Visualizar();
}


void Records::Visualizar(){
    XInitThreads();
    std::thread eventos(&Records::Eventos,this);
    std::thread Dibujar(&Records::Dibujar,this);
    std::thread Datos(&Records::VerDatos,this);
    Dibujar.join();
    Datos.join();
    eventos.join();
}

void Records::Dibujar(){
    
    while(ventana_Historial->isOpen()){
        ventana_Historial->clear(sf::Color::Black);
        ventana_Historial->draw(*TituloCronometro);
        ventana_Historial->draw(*TituloPuntaje);
        for (int i = 0; i < 10; i++)
        {
           ventana_Historial->draw(*CronometroT[i]);
           ventana_Historial->draw(*PuntajeT[i]);
        }
        ventana_Historial->display();
        sf::sleep(sf::Time(sf::milliseconds(20)));
    }
}

void Records::CargarSprites(){
    TituloCronometro=new sf::Text();
    TituloPuntaje=new sf::Text();
    FondoLetras=new sf::Font();
    for (int i = 0; i < 10; i++)
    {
       CronometroT[i] = new sf::Text();
       PuntajeT[i] = new sf::Text();
    }
    //Titulos
    FondoLetras->loadFromFile("../recursos/Numero.ttf");
    TituloCronometro->setFont(*FondoLetras);
    TituloCronometro->setPosition(10,10);
    TituloCronometro->setCharacterSize(20);
    TituloCronometro->setFillColor(sf::Color::White);
    TituloCronometro->setString("Tiempo");
    TituloPuntaje->setFont(*FondoLetras);
    TituloPuntaje->setPosition(140,10);
    TituloPuntaje->setCharacterSize(20);
    TituloPuntaje->setFillColor(sf::Color::White);
    TituloPuntaje->setString("Puntaje");

    for (int i = 0; i < 10; i++)
    {
    CronometroT[i]->setFont(*FondoLetras);
    CronometroT[i]->setCharacterSize(20);
    CronometroT[i]->setPosition(10,(i+2)*20);
    CronometroT[i]->setFillColor(sf::Color::White);
    PuntajeT[i]->setFont(*FondoLetras);
    PuntajeT[i]->setCharacterSize(20);
    PuntajeT[i]->setPosition(140,(i+2)*20);
    PuntajeT[i]->setFillColor(sf::Color::White);
    }
}


void Records::Eventos(){

    while (ventana_Historial->isOpen()){
        sf::Event event;
        
        if (ventana_Historial->pollEvent(event))
        {
              if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            {
                ventana_Historial->close();
                menu main;
             }
        }
          sf::sleep(sf::Time(sf::milliseconds(20)));
    }
}


void Records::VerDatos(){
int cronometro, puntaje;
int contador=0;
std::string cronometroS;
std::string puntajeS;
std::ifstream ArchivoL("historial.dat", std::ios::in);
    if(ArchivoL){
        while(ArchivoL>>puntaje>>cronometro){
            cronometroS=std::to_string(cronometro);
            puntajeS=std::to_string(puntaje);
            CronometroT[contador]->setString(puntajeS);
            PuntajeT[contador]->setString(cronometroS);
            contador++;
        }
 }
}