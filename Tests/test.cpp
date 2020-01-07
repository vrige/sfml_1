//
// Created by cristina on 04/12/2019.
//
#include "gtest/gtest.h"
#include "Player.h"
#include "TileMap.h"
#include "AStar.h"

using namespace std;

namespace {
    class AstarFixture : public ::testing::Test {
    public:
        virtual void SetUp() {
            int x = 4;
            int y = 4;
            int tiles = 4;
            string tileSetForPlayer = "./Tests/img/game34x34.png";
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

            player = make_shared<Player>(tileSetForPlayer, tileSize);
            map = make_shared<TileMap>(x, y, tiles, tileSize, move(ptr), goal);

            if (!map.get()->load(tileSet, posInitPlayer)) {
                cout << "problemi nel rendering della mappa" << endl;
            }

            posInitPlayer = map.get()->makePlayerStartGreen(posInitPlayer);
            player.get()->setPosInMatrix(posInitPlayer);
            player.get()->setPosInSprite(sf::Vector2f(posInitPlayer.x * tileSize.x, posInitPlayer.y * tileSize.y));


            aStar = new AStar(map, player, map.get()->getGoal());

        }
        virtual void TearDown() {
            delete aStar;
        }
        void follow( std::vector<char> path){
            sf::RenderWindow window(sf::VideoMode(736, 736), "Tileset");
            window.setPosition(sf::Vector2i(620,0));
            sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f));
            view.setSize(736.f, 736.f);
            sf::Clock clock;
            sf::Time timeSinceLastUpdate = sf::Time::Zero;
            float frametime = 1.0f / 1.0f; //è un immagine al secondo
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
        string tileSet = "./Tests/img/tileset.png";
        shared_ptr<Player> player;
        shared_ptr<TileMap> map;
        AStar *aStar;
    };

}

TEST_F(AstarFixture, firstTestAstar){
    cout<<"test1"<<endl;
    std::vector<int> path = { 13, 12 , 8 , 4 ,0};                         //   5, 0, 2, 0,
    std::vector<char> easierToReadPath = {'l', 'u' ,'u' ,'u'};            //   0, 0, 2, 0,
    ASSERT_EQ(aStar->findPath(),true);                         //   1, 1, 2, 0,
    ASSERT_EQ(aStar->getPath(),path); // 13 12 8 4 0                //   0, St, 2, 0,
    ASSERT_EQ(aStar->getEasierToReadPath(),easierToReadPath); //l u u u
    follow(easierToReadPath);



    cout<<"test2"<<endl;
    sf::Vector2i nextGoal2(3,3);                  //   St, 0, 2, 0,
    aStar->setGoal(nextGoal2, tileSet);           //   0,  0, 2, 0,
    vector<int> path2 ={};                               //   1,  1, 2, 0,
    vector<char> easierToReadPath2 ={};                  //   0,  0, 2, 5,
    ASSERT_EQ(aStar->findPath(),false);
    ASSERT_EQ(aStar->getPath(),path2); // empty
    ASSERT_EQ(aStar->getEasierToReadPath(),easierToReadPath2); // empty
    follow(easierToReadPath2);



    cout<<"test3"<<endl;
    sf::Vector2i nextGoal3(1,2);
    aStar->setGoal(nextGoal3, tileSet);                    //   St, 0, 2, 0,
    vector<int> path3 ={0,1,5,9};                                 //   0,  0, 2, 0,
    vector<char> easierToReadPath3 ={'r','d','d'};                //   1,  5, 2, 0,
    ASSERT_EQ(aStar->findPath(),true);                 //   0,  0, 2, 0,
    ASSERT_EQ(aStar->getPath(),path3); // 0 1 5 9
    ASSERT_EQ(aStar->getEasierToReadPath(),easierToReadPath3); // r d d
    follow(easierToReadPath3);
}
