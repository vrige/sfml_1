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
    int percentageOfZeros = 55;
    float speedView = 30;
    string tileSet ="./img/tileset.png";
    string tileSetForPlayer = "./img/game34x34.png";
    sf::Vector2u tileSize(32, 32);
    sf::Vector2i posInitPlayer(10,10);


    Player player(tileSetForPlayer,tileSize);
    TileMap map(x,y,tiles,tileSize,percentageOfZeros);


    if (!map.load(tileSet,posInitPlayer)){
        cout<<"problemi nel rendering della mappa"<<endl;
        return -1;
    }


    posInitPlayer = map.makePlayerStartGreen(posInitPlayer);
    player.setPosInMatrix(posInitPlayer);
    player.setPosInSprite(sf::Vector2f(posInitPlayer.x*tileSize.x,posInitPlayer.y*tileSize.y));


    AStar aStar(&map, &player, map.getGoal());


    sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f));
    view.setSize(736.f, 736.f);


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
                        if(map.checkGridPossibileMove('u', player.getPosInMatrix()) && !player.getIsMoved()){
                            player.movePlayer('u');
                            view.move(0, -speedView);
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Down)
                    {
                        cout << "down" << endl;
                        if(map.checkGridPossibileMove('d', player.getPosInMatrix()) && !player.getIsMoved()){
                            player.movePlayer('d');
                            view.move(0, speedView);
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Left)
                    {
                        cout << "left" << endl;
                        if(map.checkGridPossibileMove('l', player.getPosInMatrix()) && !player.getIsMoved()){
                            player.movePlayer('l');
                            view.move(-speedView, 0);
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Right)
                    {
                        cout << "right" << endl;
                        if(map.checkGridPossibileMove('r', player.getPosInMatrix()) && !player.getIsMoved()){
                            player.movePlayer('r');
                            view.move(speedView, 0);
                        }
                    }
                    else if (event.key.code == sf::Keyboard::A) {
                        cout << "tasto A" << endl;
                        if (!player.getIsMoved()) {
                            /* aStar.astar();*/

                            if (aStar.findPath()) {
                                vector<char> path = aStar.getEasierToReadPath();

                                sf::Clock clock;
                                sf::Time timeSinceLastUpdate = sf::Time::Zero;
                                float frametime = 1.0f / 6.0f; //è un immagine al secondo
                                sf::Time frameTime = sf::seconds(frametime);

                                for (char iter : path) {
                                    while(true){
                                        sf::Time elapsedTime = clock.restart();
                                        timeSinceLastUpdate += elapsedTime;

                                        if (timeSinceLastUpdate > frameTime){

                                            timeSinceLastUpdate -= frameTime;
                                            player.movePlayer(iter);
                                            view.setCenter(player.getPosInMatrix().x * player.getPlayerSize().x, player.getPosInMatrix().y * player.getPlayerSize().y);
                                            player.setIsMoved(false);

                                            window.setView(view);
                                            window.clear(sf::Color::White);
                                            window.draw(map);
                                            window.draw(player);
                                            window.display();

                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else if (event.key.code == sf::Keyboard::T) {
                        cout << "tasto T" << endl;
                        //TEST
                    }
                    else if (event.key.code == sf::Keyboard::S) {
                        cout << "tasto S" << endl;
                        view.setCenter(player.getPosInMatrix().x * player.getPlayerSize().x, player.getPosInMatrix().y * player.getPlayerSize().y);
                    }
                    else if(event.key.code == sf::Keyboard::K)
                    {
                        cout << "move view down" << endl;
                        view.move(0, speedView);
                    }
                    else if(event.key.code == sf::Keyboard::J)
                    {
                        cout << "move view left" << endl;
                        view.move(-speedView, 0);
                    }
                    else if(event.key.code == sf::Keyboard::I)
                    {
                        cout << "move view up" << endl;
                        view.move(0, -speedView);
                    }
                    else if(event.key.code == sf::Keyboard::L)
                    {
                        cout << "move view rigth" << endl;
                        view.move(speedView, 0);
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
             view.zoom(0.99f);
             cout<<"zoom in"<< endl;
         }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
             view.zoom(1.01f);
             cout<<"zoom out"<< endl;
         }

         window.setView(view);
         window.clear(sf::Color::White);
         window.draw(map);
         window.draw(player);
         window.display();
     }

     return 0;
 }