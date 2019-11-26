#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Tileset");


    int x = 20;
    int y = 20;
    int tiles = 4;
   // int percentageOfZero = 60;
    string tileset = "C:/Users/cristina/CLionProjects/sfml_1/img/tileset.png";
    sf::Vector2u tileSize(32, 32);
//    sf::Vector2i posInitPlayer(16,16);


   TileMap map(x,y,tiles,tileSize);


   if (!map.load(tileset)){
       cout<<"problemi nel rendering della mappa"<<endl;
       return -1;
   }

   while (window.isOpen())
   {
       sf::Event event;
       while (window.pollEvent(event))
       {
           if (event.type == sf::Event::Closed)
               window.close();
       }

       window.clear();
       window.draw(map);
       window.display();
   }

    return 0;
}