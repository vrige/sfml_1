//
// Created by cristina on 04/12/2019.
//
#include "gtest/gtest.h"
#include "Player.h"
#include "RenderingMap.h"
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
            map = make_shared<RenderingMap>(x, y, tiles, tileSize, move(ptr), goal);

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
        void follow( std::vector<char> path,float frametime ){
            sf::RenderWindow window(sf::VideoMode(736, 736), "Tileset");
            window.setPosition(sf::Vector2i(620,0));
            sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f));
            view.setSize(736.f, 736.f);
            sf::Clock clock;
            sf::Time timeSinceLastUpdate = sf::Time::Zero;
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
        shared_ptr<RenderingMap> map;
        AStar *aStar;
    };

}

TEST_F(AstarFixture, firstTestAstar){
    float frametime = 1.0f / 1.0f; //è un immagine al secondo


    std::vector<int> path = { 13, 12 , 8 , 4 ,0};                         //   5, 0, 2, 0,
    std::vector<char> easierToReadPath = {'l', 'u' ,'u' ,'u'};            //   0, 0, 2, 0,
    ASSERT_EQ(aStar->findPath(),true);                         //   1, 1, 2, 0,
    ASSERT_EQ(aStar->getPath(),path); // 13 12 8 4 0                //   0, St, 2, 0,
    ASSERT_EQ(aStar->getEasierToReadPath(),easierToReadPath); //l u u u
    follow(easierToReadPath,frametime);



    sf::Vector2i nextGoal2(3,3);                  //   St, 0, 2, 0,
    aStar->setGoal(nextGoal2, tileSet);           //   0,  0, 2, 0,
    vector<int> path2 ={};                               //   1,  1, 2, 0,
    vector<char> easierToReadPath2 ={};                  //   0,  0, 2, 5,
    ASSERT_EQ(aStar->findPath(),false);
    ASSERT_EQ(aStar->getPath(),path2); // empty
    ASSERT_EQ(aStar->getEasierToReadPath(),easierToReadPath2); // empty
    follow(easierToReadPath2,frametime);



    sf::Vector2i nextGoal3(1,2);
    aStar->setGoal(nextGoal3, tileSet);                    //   St, 0, 2, 0,
    vector<int> path3 ={0,1,5,9};                                 //   0,  0, 2, 0,
    vector<char> easierToReadPath3 ={'r','d','d'};                //   1,  5, 2, 0,
    ASSERT_EQ(aStar->findPath(),true);                 //   0,  0, 2, 0,
    ASSERT_EQ(aStar->getPath(),path3); // 0 1 5 9
    ASSERT_EQ(aStar->getEasierToReadPath(),easierToReadPath3); // r d d
    follow(easierToReadPath3,frametime);
}



TEST_F(AstarFixture, secondTestAstar){
    float frametime = 1.0f / 6.0f;
    int matrice2[] = {
            //0,1,2, 3,     4, 5, 6, 7,     8, 9,10, 11
            0, 1, 0, 0,     0, 1, 0, 0,     0, 0, 0, 0,
            0, 1, 0, 1,     0, 1, 0, 2,     1, 1, 1, 0,
            0, 0, 0, 1,     0, 1, 0, 2,     0, 0, 0, 0,
            1, 1, 1, 1,     0, 1, 0, 2,     0, 1, 1, 1,

            1, 1, 2, 0,     0, 1, 0, 2,     0, 0, 0, 0,
            0, 0, 2, 0,     2, 2, 0, 2,     1, 1, 1, 0,
            0, 0, 2, 0,     0, 0, 0, 2,     0, 0, 0, 0,
            1, 0, 2, 2,     2, 2, 2, 2,     0, 1, 1, 1,

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

    std::vector<int> path = {0, 12, 24, 25, 26, 14, 2, 3, 4, 16, 28, 40, 52, 51, 63, 75, 76, 77,
                             78, 66, 54, 42, 30, 18, 6, 7, 8, 9, 10, 11, 23, 35,34,33,32,44,56,57,
                             58,59,71,83,82,81,80,92,104,103,102,101,100,99,98,97,85,73,72};
    std::vector<char> easierToReadPath = {
            'd','d','r','r','u','u','r','r','d','d','d','d','l','d','d','r','r','r','u','u','u','u','u','u','r','r',
            'r','r','r','d','d','l','l','l','d','d','r','r','r','d','d','l','l','l','d','d','l','l','l','l','l','l',
            'l','u','u','l'
    };
    ASSERT_EQ(aStar->findPath(),true);
    EXPECT_EQ(aStar->getPath(),path);
    EXPECT_EQ(aStar->getEasierToReadPath(),easierToReadPath);
    follow(easierToReadPath,frametime);
}


TEST_F(AstarFixture, thirdTestAstar){
    float frametime = 1.0f / 2.0f;
    int matrice2[] = {
            //0,1,2, 3,     4, 5, 6, 7,     8, 9,10, 11
            0, 1, 0, 0,     0, 1, 0, 0,     0, 0, 0, 0,
            0, 1, 0, 1,     0, 1, 0, 2,     1, 1, 1, 0,
            0, 0, 0, 1,     0, 1, 0, 2,     0, 0, 0, 0,
            1, 1, 1, 1,     0, 1, 0, 2,     0, 1, 1, 1,

            0, 0, 2, 0,     0, 1, 0, 2,     0, 0, 0, 0,
            0, 0, 2, 0,     2, 2, 0, 2,     1, 1, 1, 0,
            0, 0, 2, 0,     0, 0, 0, 2,     0, 0, 0, 0,
            1, 0, 2, 2,     2, 2, 2, 2,     0, 1, 1, 1,

            2, 0, 1, 0,     0, 0, 0, 0,     0, 2, 2, 0,
            2, 0, 1, 0,     0, 0, 0, 0,     0, 2, 2, 0,
            2, 0, 1, 0,     0, 0, 0, 0,     0, 2, 2, 0,
            2, 0, 0, 0,     0, 0, 0, 0,     0, 2, 2, 0,


    };
    std::vector<int> vettore2(matrice2, matrice2 + sizeof(matrice2) / sizeof(int));
    auto ptr2 = make_shared<vector<int>>(vettore2);

    player.get()->setPosInMatrix(0,0);
    player.get()->setPosInSprite(sf::Vector2f(0,0));
    sf::Vector2i nextGoal(0,6);
    int x2 = 12;
    int y2 = 12;

    aStar->setAstar(ptr2,x2,y2,nextGoal,tileSet, player.get()->getPosInMatrix());

    std::vector<int> path = {0, 12, 24, 36, 48 , 60, 72};
    std::vector<char> easierToReadPath = {'d','d','d','d','d','d'};
    ASSERT_EQ(aStar->findPath(),true);
    EXPECT_EQ(aStar->getPath(),path);
    EXPECT_EQ(aStar->getEasierToReadPath(),easierToReadPath);
    follow(easierToReadPath,frametime);
}