//
// Created by cristina on 04/12/2019.
//
#include "gtest/gtest.h"

#include "Player.h"
#include "TileMap.h"
#include "Player.h"
#include "AStar.h"
using testing::Eq;
using namespace std;

namespace{
    class testMovimentPlayer : public testing::Test{
    public:
        Player* player;
        testMovimentPlayer() {
            std::string tileSetForPlayer = "./Tests/img/game34x34.png";
            sf::Vector2u tileSize(32, 32);
            player = new Player(tileSetForPlayer, tileSize);
        }
    };
    class AStarFindSolutionFixture : public ::testing::Test {
    public:
        AStarFindSolutionFixture(){
            int x = 20;
            int y = 20;
            int tiles = 4;
            int percentageOfZeros = 50;
            float speedView = 30;
            string tileSet ="./Tests/img/tileset.png";
            string tileSetForPlayer = "./Tests/img/game34x34.png";
            sf::Vector2u tileSize(32, 32);
            sf::Vector2i posInitPlayer(10,10);


            int matrice[] = {
                    //0,1,2,3,     4,5,6,7,    8,9,10,11,   12,13,14,15  16,17,18,19
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    1,0,1,1,     1,1,1,1,     1,1,1,1,     1,1,1,1,     1,1,1,1,

                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,

                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,

                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,

                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
                    0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,     0,0,0,0,
            };
            sf::Vector2i goal(10,2);

            auto ptr = unique_ptr<int[]>(matrice);

            Player player(tileSetForPlayer,tileSize);
            TileMap map(x,y,tiles,tileSize,move(ptr),goal);

            if (!map.load(tileSet,posInitPlayer)){
                cout<<"problemi nel rendering della mappa"<<endl;
            }

            posInitPlayer = map.makePlayerStartGreen(posInitPlayer);
            player.setPosInMatrix(posInitPlayer);
            player.setPosInSprite(sf::Vector2f(posInitPlayer.x*tileSize.x,posInitPlayer.y*tileSize.y));


            aStar = new AStar(&map, &player, map.getGoal());

        }
        AStar* aStar;

    };
}
TEST_F(testMovimentPlayer, ExampleIfIsMoving){

    EXPECT_EQ(player->getIsMoved(), false);
}
TEST_F(AStarFindSolutionFixture, findTheGoal){

    EXPECT_EQ(aStar->findPath(),true); //aStar->findPath()
}