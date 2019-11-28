#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"
#include "Player.h"
#include "AStar.h"


using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(736, 736), "Tileset");
    window.setPosition(sf::Vector2i(620,0));

    int x = 20;
    int y = 20;
    int tiles = 4;
    int percentageOfZeros = 85;
    float speedView = 30;
    string tileSet = "C:/Users/cristina/CLionProjects/sfml_1/img/tileset.png";
    string tileSetForPlayer = "C:/Users/cristina/CLionProjects/sfml_1/img/game34x34.png";
    sf::Vector2u tileSize(32, 32);
    sf::Vector2i posInitPlayer(10,10);


    Player player(tileSetForPlayer,tileSize);
    TileMap map(x,y,tiles,tileSize,percentageOfZeros,&player);

    if (!map.load(tileSet,posInitPlayer)){
        cout<<"problemi nel rendering della mappa"<<endl;
        return -1;
    }

    AStar aStar(&map, map.getGoal());
    aStar.astar();

    sf::View view1(sf::FloatRect(200.f, 200.f, 300.f, 200.f));
    view1.setSize(736.f, 736.f);


    while (window.isOpen())
    {
        sf::Vector2i pMouse = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        cout << "the left button was pressed" << endl;
                        cout << "pMouse.x " << pMouse.x << endl;
                        cout << "pMouse.y " << pMouse.y << endl;
                    }
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Up)
                    {
                        cout << "up" << endl;
                        if(map.checkGridPossibileMove('u') && !player.getIsMoved()){
                            player.movePlayer('u');
                            view1.move(0, -speedView);
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Down)
                    {
                        cout << "down" << endl;
                        if(map.checkGridPossibileMove('d') && !player.getIsMoved()){
                            player.movePlayer('d');
                            view1.move(0, speedView);
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Left)
                    {
                        cout << "left" << endl;
                        if(map.checkGridPossibileMove('l') && !player.getIsMoved()){
                            player.movePlayer('l');
                            view1.move(-speedView, 0);
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Right)
                    {
                        cout << "right" << endl;
                        if(map.checkGridPossibileMove('r') && !player.getIsMoved()){
                            player.movePlayer('r');
                            view1.move(speedView, 0);
                        }
                    }
                    else if (event.key.code == sf::Keyboard::A)
                    {
                        cout<<"tasto A"<<endl;
                        if(!player.getIsMoved()){
  /*                          player.setPos(posInitPlayer);
                            sf::Vector2f posIniz(posInitPlayer.x * tileSize.x,posInitPlayer.y * tileSize.y);
                            player.setPosition(posIniz);
                            view1.setCenter(posIniz);*/
                            aStar.astar();
                        }
                    }
                    break;
                case sf::Event::KeyReleased:
                    if(event.key.code == sf::Keyboard::Up)
                    {
                        cout << "release up" << endl;
                        player.setIsMoved(false);
                    }
                    if(event.key.code == sf::Keyboard::Down)
                    {
                        cout << "release down" << endl;
                        player.setIsMoved(false);
                    }
                    if(event.key.code == sf::Keyboard::Left)
                    {
                        cout << "release left" << endl;
                        player.setIsMoved(false);
                    }
                    if(event.key.code == sf::Keyboard::Right)
                    {
                        cout << "release right" << endl;
                        player.setIsMoved(false);
                    }

            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            view1.zoom(0.99f);
            cout<<"zoom in"<< endl;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
            view1.zoom(1.01f);
            cout<<"zoom out"<< endl;
        }

        window.setView(view1);
        window.clear(sf::Color::White);
        window.draw(map);
        window.draw(player);
        window.display();
    }

    return 0;
}