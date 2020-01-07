//
// Created by cristina on 10/12/2019.
//

#include "TileMap.h"
TileMap::TileMap( int x, int y, int tiles, sf::Vector2u tileSize, std::shared_ptr<std::vector<int>> mat, sf::Vector2i goal):
        width(x),height(y),tiles(tiles),m_tileSize(tileSize), goal(goal){
    matX = std::move(mat);
    isThereAGoal = true;
   // print(matX,x,y);
    srand((unsigned)time(nullptr));
}
TileMap::TileMap( int x, int y, int tiles, sf::Vector2u tileSize, std::shared_ptr<std::vector<int>>& mat, sf::Vector2i goal):
        width(x),height(y),tiles(tiles),m_tileSize(tileSize), goal(goal){
    matX = std::move(mat);
    isThereAGoal = true;
    // print(matX,x,y);
    srand((unsigned)time(nullptr));
}
void TileMap::matXCasuale(std::shared_ptr<std::vector<int>>& matX, int x, int y, int n){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            setValueAt(i + j * x, genRandomNumber(n));
        }
    }
}
void TileMap::matXCasualeWithPercentage(std::shared_ptr<std::vector<int>>& matX, int x, int y, int n, int percentage){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            setValueAt(i + j * x, genRandomNumberWithPercentage(n,percentage));
        }
    }
}
void TileMap::print( std::shared_ptr<std::vector<int>>& matX,int x, int y){
    std::string a;
    for(int j = 0; j < y; j++){
        for(int i = 0; i < x; i++){
            a += std::to_string(getValueAt(i + j * x)) + " ";
        }
        std::cout<< a <<std::endl;
        a = "";
    }
    std::cout<<std::endl;
}
void TileMap::generateGoal(sf::Vector2i pos) {
    int goalx, goaly;
    do {
        goalx = genRandomNumber(width);
        goaly = genRandomNumber(height);
    } while (goalx == pos.x && goaly == pos.y);
   // std::cout << "trovato un goal possibile in: "<<goalx<<" "<<goaly << std::endl;
    setValueAt(goalx + width * goaly, 5); //5 è il goal)
    goal = sf::Vector2i(goalx,goaly);
    isThereAGoal = true;
}
void TileMap::setGoal(sf::Vector2i newGoal, const std::string& tileset,sf::Vector2i pos){
    if(isThereAGoal){
        setValueAt(goal, 0);
    }
    goal = newGoal;

    load(tileset, pos);
}
bool TileMap::load(const std::string& tileset, sf::Vector2i pos)
{
    if (!m_tileset.loadFromFile(tileset)){
        std::cout<<"problemi nello scaricare la texture della mappa"<< std::endl;
        return false;
    }

    if(!isThereAGoal || (goal.x == pos.x && goal.y == pos.y) || goal.x < 0 || goal.y < 0 || goal.x > width - 1|| goal.y > height - 1){
        generateGoal(pos);
    }else{
        setValueAt(goal.x + width * goal.y, 5);
    }
    //print(matX,width,height);

    m_vertices.clear();
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4 ); //ogni elemento della matX ha 4 punti


    for (int i = 0; i < width; ++i){
        for ( int j = 0; j < height; ++j)
        {

            int tileNumber = getValueAt(i + j * width);

            int tu = tileNumber % (m_tileset.getSize().x / m_tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / m_tileSize.x); //nel nostro caso è sempre zero

            sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

            quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
            quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);
            if(tileNumber == 5){ //goal
                quad[0].color = sf::Color::Red;
                quad[1].color = sf::Color::Red;
                quad[2].color = sf::Color::Red;
                quad[3].color = sf::Color::Red;
            }
            else {
                quad[0].texCoords = sf::Vector2f(tu * m_tileSize.x, tv * m_tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
            }
        }
    }
    return true;
}
sf::Vector2i  TileMap::makePlayerStartGreen( sf::Vector2i posInitPlayer){
    unsigned int i = posInitPlayer.x;
    unsigned int j = posInitPlayer.y;
    if(getValueAt(i + j * width) != 0) {
        std::cout << "l'allocazione fornita non è uno spazio verde." << std::endl;
        std::cout << "Verrà assegnato il primo spazio verde disponibile" << std::endl;
        i = 0;
        j = 0;
        while (getValueAt(i + j * width) != 0) {
            if (i == (width - 1) && j != (height - 1)) {
                i = 0;
                j++;
            } else if (i != (width - 1)) {
                i++;
            } else {
                std::cout << "non ci sono spazi verdi dove allocare il player" << std::endl;
                return sf::Vector2i(-1, -1);
            }
            std::cout << "sono ancora nel while" << std::endl;
        }
    }
    return sf::Vector2i(i, j);
}
int TileMap::genRandomNumber(int n){
    int i;
    i = (rand()%n);
    return i;
}
int TileMap::genRandomNumberWithPercentage(int n, int percentage){
    int i;
    i = (rand()%100) + 1; // da 0 a 99
    if(i <= percentage){
        return 0; //perchè a 0 corrisponde il prato verde (gli altri sono ostacoli)
    }
    i = (i % (n - 1)) + 1;
    return i;
}
bool TileMap::checkGridPossibileMove(char direction, sf::Vector2i posPlayer){ // si basa sul fatto che l'elemento 0 della matric è l'unico attraversabile
    // std::cout<<" player from: "<< .x <<" " <<.y<< std::endl;
    int num = posPlayer.x + posPlayer.y * width;
    std::set<int> allowedTiles = {0,1,5};
    switch(direction){
        case 'u':
            if(allowedTiles.find(getValueAt(num - width)) == allowedTiles.end() || posPlayer.y == 0){
              //  std::cout<<"can't go up"<<std::endl;
                return false;
            }
            break;
        case 'd':
            if(allowedTiles.find(getValueAt(num + width)) == allowedTiles.end()|| posPlayer.y == height - 1 ){
               // std::cout<<"can't go down"<<std::endl;
                return false;
            }
            break;
        case 'l':
            if(allowedTiles.find(getValueAt(num - 1)) == allowedTiles.end() || posPlayer.x == 0 ){
              //  std::cout<<"can't go left"<<std::endl;
                return false;
            }
            break;
        case 'r':
            if(allowedTiles.find(getValueAt(num + 1)) == allowedTiles.end() || posPlayer.x == width - 1 ) {
              //  std::cout << "can't go right" << std::endl;
                return false;
            }
            break;
        default:
            std::cout<<"problemi nella scelta della direzione"<<std::endl;
    }
    return true;
}
sf::Vector2i TileMap::getGoal(){
    return goal;
}
int TileMap::getValueAt(int num){
    if(num < matX.get()->size() && num >= 0){
        return matX.get()->at(num);
    }else{
        return 3; //3 è un ostacolo
    }
}
void TileMap::setValueAt(int pos, int num){
    if(pos < matX.get()->size() && pos >= 0){
        matX.get()->at(pos) = num;
    }
}
void TileMap::setValueAt(sf::Vector2i pos, int num){
    setValueAt(pos.x + width * pos.y, num);
}
int TileMap::getWidth(){
    return width;
}
int TileMap::getHeigth(){
    return height;
}