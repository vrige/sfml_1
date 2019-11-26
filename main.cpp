#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"
#include "Player.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(736, 736), "Tileset");
    //window.setPosition(sf::Vector2i(620,0));

    int x = 20;
    int y = 20;
    int tiles = 4;
    int percentageOfZeros = 65;
    string tileSet = "C:/Users/cristina/CLionProjects/sfml_1/img/tileset.png";
    string tileSetForPlayer = "C:/Users/cristina/CLionProjects/sfml_1/img/game34x34.png";
    sf::Vector2u tileSize(32, 32);
//    sf::Vector2i posInitPlayer(16,16);


    Player player(tileSetForPlayer,tileSize);


    TileMap map(x,y,tiles,tileSize,percentageOfZeros);

    if (!map.load(tileSet)){
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
        window.draw(player);
        window.display();
    }

    return 0;
}