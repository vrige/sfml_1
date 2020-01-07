#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tests/TileMap.h"
#include "Tests/Player.h"
#include "Tests/AStar.h"


using namespace std;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
/*
    sf::RenderWindow window(sf::VideoMode(736, 736), "Tileset");
    window.setPosition(sf::Vector2i(620,0));
    int x = 4;
    int y = 4;
    int tiles = 4;
    int speedView = 30;
    string tileSetForPlayer = "./Tests/img/game34x34.png";
    string tileSet = "./Tests/img/tileset.png";
    sf::Vector2u tileSize(32, 32);
    sf::Vector2i posInitPlayer(1, 3);

    int matrice[] = {
            0, 0, 2, 0,
            0, 0, 2, 0,
            1, 1, 2, 0,
            0, 0, 2, 0
    };
    sf::Vector2i goal(0, 0);
    std::vector<int> vettore(matrice, matrice + sizeof(matrice) / sizeof(int));
    auto ptr = make_shared<vector<int>>(vettore);

    auto player = make_shared<Player>(tileSetForPlayer, tileSize);
    auto map = make_shared<TileMap>(x, y, tiles, tileSize, move(ptr), goal);

    if (!map.get()->load(tileSet, posInitPlayer)) {
        cout << "problemi nel rendering della mappa" << endl;
    }

    posInitPlayer = map.get()->makePlayerStartGreen(posInitPlayer);
    player.get()->setPosInMatrix(posInitPlayer);
    player.get()->setPosInSprite(sf::Vector2f(posInitPlayer.x * tileSize.x, posInitPlayer.y * tileSize.y));


    AStar* aStar = new AStar(map, player, map.get()->getGoal());

    int matrice2[] = {
            //0,1,2, 3,     4, 5, 6, 7,     8, 9,10, 11
            0, 1, 0, 0,     0, 1, 0, 0,     0, 0, 0, 0,
            0, 1, 0, 1,     0, 1, 0, 2,     1, 1, 1, 0,
            0, 0, 0, 1,     0, 1, 0, 2,     0, 0, 0, 0,
            1, 1, 1, 1,     0, 1, 0, 2,     0, 1, 1, 1,

            1, 1, 2, 0,     0, 1, 0, 2,     0, 0, 0, 0,
            0, 0, 2, 0,     2, 2, 0, 2,     1, 1, 1, 0,
            0, 0, 2, 0,     0, 0, 0, 2,     0, 0, 0, 0,
            0, 0, 2, 2,     2, 2, 2, 2,     0, 1, 1, 1,

            2, 0, 0, 0,     0, 0, 0, 0,     0, 2, 2, 0,
    };
    std::vector<int> vettore2(matrice2, matrice2 + sizeof(matrice2) / sizeof(int));
    auto ptr2 = make_shared<vector<int>>(vettore2);

    player.get()->setPosInMatrix(0,0);
    player.get()->setPosInSprite(sf::Vector2f(0,0));
    sf::Vector2i nextGoal(0,6);
    int x2 = 12;
    int y2 = 9;

    aStar->setAstar(ptr2,x2,y2,nextGoal,tileSet, player.get()->getPosInMatrix());

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
                        if(map.get()->checkGridPossibileMove('u', player.get()->getPosInMatrix()) && !player.get()->getIsMoved()){
                            player.get()->movePlayer('u');
                            view.move(0, -speedView);
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Down)
                    {
                        cout << "down" << endl;
                        if(map.get()->checkGridPossibileMove('d', player.get()->getPosInMatrix()) && !player.get()->getIsMoved()){
                            player.get()->movePlayer('d');
                            view.move(0, speedView);
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Left)
                    {
                        cout << "left" << endl;
                        if(map.get()->checkGridPossibileMove('l', player.get()->getPosInMatrix()) && !player.get()->getIsMoved()){
                            player.get()->movePlayer('l');
                            view.move(-speedView, 0);
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Right)
                    {
                        cout << "right" << endl;
                        if(map.get()->checkGridPossibileMove('r', player.get()->getPosInMatrix()) && !player.get()->getIsMoved()){
                            player.get()->movePlayer('r');
                            view.move(speedView, 0);
                        }
                    }
                    else if (event.key.code == sf::Keyboard::A) {
                        cout << "tasto A" << endl;
                        if (!player.get()->getIsMoved()) {
                            
                            if (aStar->findPath()) {
                                vector<char> path = aStar->getEasierToReadPath();

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
                                            player.get()->movePlayer(iter);
                                            view.setCenter(player.get()->getPosInMatrix().x * player.get()->getPlayerSize().x, player.get()->getPosInMatrix().y * player.get()->getPlayerSize().y);
                                            player.get()->setIsMoved(false);

                                            window.setView(view);
                                            window.clear(sf::Color::White);
                                            window.draw(*map.get());
                                            window.draw(*player.get());
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
                        view.setCenter(player.get()->getPosInMatrix().x * player.get()->getPlayerSize().x, player.get()->getPosInMatrix().y * player.get()->getPlayerSize().y);
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
                         player.get()->setIsMoved(false);
                     }
                     if(event.key.code == sf::Keyboard::Down)
                     {
                         cout << "release down" << endl;
                         player.get()->setIsMoved(false);
                     }
                     if(event.key.code == sf::Keyboard::Left)
                     {
                         cout << "release left" << endl;
                         player.get()->setIsMoved(false);
                     }
                     if(event.key.code == sf::Keyboard::Right)
                     {
                         cout << "release right" << endl;
                         player.get()->setIsMoved(false);
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
         window.draw(*map.get());
         window.draw(*player.get());
         window.display();
     }

     return 0;*/
 }