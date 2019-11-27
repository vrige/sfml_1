#include "TileMap.h"
TileMap::TileMap( int x, int y, int tiles, sf::Vector2u tileSize, Player* player):
width(x),height(y),tiles(tiles),m_tileSize(tileSize),player(player){
    this->matX = new int[x*y];
    matXCasuale(matX,x,y,tiles);
    print(matX,x,y);
}
TileMap::TileMap( int x, int y, int tiles, sf::Vector2u tileSize, int percentualeZeri, Player* player):
width(x),height(y),tiles(tiles),m_tileSize(tileSize),player(player){
    this->matX = new int[x*y];
    matXCasualeWithPercentage(matX,x,y,tiles,percentualeZeri);
    print(matX,x,y);
}
TileMap::~TileMap() {
    std::cout<<"delete matX and player"<<std::endl;
    delete matX;
    delete player;
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
void TileMap::generateGoal() {
    int goalx, goaly;
    do {
        goalx = genRandomNumber(width);
        goaly = genRandomNumber(height);
    } while (goalx != player->getPos().x && goaly != player->getPos().y);
    std::cout << "trovato un goal possibile in: "<<goalx<<" "<<goaly << std::endl;
    matX[goalx + width * goaly] = 5; //5 è il goal
}
bool TileMap::load(const std::string& tileset, sf::Vector2i pos)
{
    if (!m_tileset.loadFromFile(tileset)){
        std::cout<<"problemi nello scaricare la texture"<< std::endl;
        return false;
    }

    generateGoal();

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4 ); //ogni elemento della matX ha 4 punti

    for (int i = 0; i < width; ++i){
        for ( int j = 0; j < height; ++j)
        {
            int tileNumber = matX[i + j * width];

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
    if(playerStartGreen(player,pos)){
        std::cout<<"player correttamente allocato"<< std::endl;
        return true;
    }
    std::cout<<"la posizione del personaggio è fuori dal tileset"<<std::endl;
    return false;
}
bool TileMap::playerStartGreen(Player* player, sf::Vector2i pos){
    if(0 <= pos.x && pos.x < width && 0 <= pos.y && pos.y < height){
        unsigned int i = pos.x;
        unsigned int j = pos.y;
        if(matX[i + j * width] != 0){
            std::cout<<"l'allocazione fornita non è uno spazio verde."<<std::endl;
            std::cout<<"Verrà assegnato il primo spazio verde disponibile"<<std::endl;
            i = 0;
            j = 0;
            while(matX[i + j * width] != 0){
                if(i == (width - 1) && j != (height - 1)){
                    i = 0;
                    j++;
                }
                else if(i != (width - 1)){
                    i++;
                }
                else{
                    std::cout<<"non ci sono spazi verdi dove allocare il player" << std::endl;
                    return false;
                }
                std::cout<<"sono ancora nel while" << std::endl;
            }
        }
        this->player->setPos(sf::Vector2i(i,j));
        this->player->setPosizione(sf::Vector2f(i*m_tileSize.x,j*m_tileSize.y));
        return true;
    }
    else{
        std::cout<<"la posizione del personaggio è fuori dal tileset"<<std::endl;
        return false;
    }
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
bool TileMap::checkGridPossibileMove(char direction){ // si basa sul fatto che l'elemento 0 della matric è l'unico attraversabile
    sf::Vector2i pos = this->player->getPos();
    std::cout<<"pos player: "<< pos.x <<" " <<pos.y<< std::endl;
    switch(direction){
        case 'u':
            if(matX[pos.x + (pos.y - 1)* width] != 0 || pos.y == 0){
                if( matX[pos.x + (pos.y - 1)* width] == 5){
                    std::cout<<"ma quello è il goal!"<<std::endl;
                }else{
                    std::cout<<"can't go up"<<std::endl;
                    return false;
                }
            }
            break;
        case 'd':
            if(matX[pos.x + (pos.y + 1)* width] != 0 || pos.y == height - 1 ){
                if(  matX[pos.x + (pos.y + 1)* width] == 5){
                    std::cout<<"ma quello è il goal!"<<std::endl;
                }else{
                    std::cout<<"can't go down"<<std::endl;
                    return false;
                }
            }
            break;
        case 'l':
            if(matX[(pos.x - 1) + pos.y * width] != 0 || pos.x == 0 ){
                if( matX[pos.x + (pos.y - 1)* width] == 5){
                    std::cout<<"ma quello è il goal!"<<std::endl;
                }else{
                    std::cout<<"can't go left"<<std::endl;
                    return false;
                }
            }
            break;
        case 'r':
            if(matX[(pos.x + 1) + pos.y * width] != 0  || pos.y == width - 1 ) {
                if (matX[pos.x + (pos.y - 1)* width] == 5) {
                    std::cout << "ma quello è il goal!" << std::endl;
                } else {
                    std::cout << "can't go right" << std::endl;
                    return false;
                }
            }
            break;
        default:
            std::cout<<"problemi nella scelta della direzione"<<std::endl;
    }
    return true;
}

