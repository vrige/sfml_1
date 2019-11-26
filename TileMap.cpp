#include "TileMap.h"
TileMap::TileMap( int x, int y, int tiles, sf::Vector2u tileSize):width(x),height(y),tiles(tiles),m_tileSize(tileSize){
    this->matX = new int[x*y];
    matXCasuale(matX,x,y,tiles);
    print(matX,x,y);
}
TileMap::TileMap( int x, int y, int tiles, sf::Vector2u tileSize, int percentualeZeri):width(x),height(y),tiles(tiles),m_tileSize(tileSize){
    this->matX = new int[x*y];
    matXCasualeWithPercentage(matX,x,y,tiles,percentualeZeri);
    print(matX,x,y);
}
TileMap::~TileMap() {
    std::cout<<"delete matX"<<std::endl;
    delete matX;
}
void TileMap::matXCasuale(int* matX, int x, int y, int n){
    srand((unsigned)time(nullptr));
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            matX[i + j * x] = genRandomNumber(n);
        }
    }
    //print(matX,x,y);
}
void TileMap::matXCasualeWithPercentage(int* matX, int x, int y, int n, int percentage){
    srand((unsigned)time(nullptr));
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            matX[i + j * x] = genRandomNumberWithPercentage(n,percentage);
        }
    }
    //print(matX,x,y);
}
bool TileMap::load(const std::string& tileset)
{
    if (!m_tileset.loadFromFile(tileset)){
        std::cout<<"problemi nello scaricare la texture"<< std::endl;
        return false;
    }

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4 ); //ogni elemento della matX ha 4 punti

    for (unsigned int i = 0; i < width; ++i){
        for (unsigned int j = 0; j < height; ++j)
        {
            int tileNumber = matX[i + j * width];

            int tu = tileNumber % (m_tileset.getSize().x / m_tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / m_tileSize.x);

            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
            quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);

            quad[0].texCoords = sf::Vector2f(tu * m_tileSize.x, tv * m_tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
        }
    }
    return true;
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

