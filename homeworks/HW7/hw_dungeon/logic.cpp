#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {  
    ifstream inFS;
    inFS.open(fileName);
    if(!inFS.is_open()) {
        return nullptr;
    }

    inFS >> maxRow;
    inFS >> maxCol;
    

    char** level = createMap(maxRow, maxCol);
    if (level == nullptr) {
        return nullptr;
    }

    inFS >> player.row;
    inFS >> player.col;
    

    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            char nextChar; 
            inFS >> nextChar;
            if (inFS.fail()) {
                return nullptr;      
            }
            level[i][j] = nextChar;
        }
    }
    level[player.row][player.col] = TILE_PLAYER;

    inFS.close();
    return level;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    if(input == MOVE_DOWN) {
        nextRow += 1;
    }
    if(input == MOVE_LEFT) {
        nextCol -= 1;
    }
    if(input == MOVE_RIGHT) {
        nextCol += 1;
    }
    if(input == MOVE_UP) {
        nextRow -= 1;
    }

    
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    if(maxRow < 1 || maxCol < 1) {
        return nullptr;
    }  
    char** map = new char*[maxRow];
    for(int i = 0; i < maxRow; i++) {
        map[i] = new char[maxCol];
    }

    for(int row = 0; row < maxRow; row++) {
        for(int col = 0; col < maxCol; col++) {
            map[row][col] = TILE_OPEN;
        }
    }
    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    for(int i = 0; i < maxRow; i++) {
        delete[] map[i];
        map[i] = nullptr;
    }
    delete[] map;
    maxRow = 0;
    map = nullptr;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {

    

    char** newMap = createMap(maxRow*2,maxCol*2);

    if(newMap == nullptr) {
        return nullptr;
    }
    for(int row = 0; row < maxRow; row++) {
        for(int col = 0; col < maxCol; col++) {
            newMap[row][col] = map[row][col];
        }
    }
    for(int row = 0; row < maxRow; row++) {
        for(int col = 0; col < maxCol; col++) {
            if(map[row][col] != TILE_PLAYER) {
                newMap[row + maxRow][col] = map[row][col];
                newMap[row][col + maxCol] = map[row][col];
                newMap[row + maxRow][col + maxCol] = map[row][col];
            } else {
                newMap[row + maxRow][col] = TILE_OPEN;
                newMap[row][col + maxCol] = TILE_OPEN;
                newMap[row + maxRow][col + maxCol] = TILE_OPEN;
            }
        }
    }
    for(int i = 0; i < maxRow; i++) {
        delete[] map[i];
        map[i] = nullptr;
    }
    delete[] map;
    map = nullptr;
    maxRow *= 2;
    maxCol *= 2;
    return newMap;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    if(nextRow >= maxRow || nextRow < 0 || nextCol >= maxCol || nextCol < 0) {
        nextRow = player.row;
        nextCol = player.col;
        return STATUS_STAY;
    }

    if(player.row == nextRow && player.col == nextCol) {
        return STATUS_STAY;
    }

    if(map[nextRow][nextCol] == TILE_MONSTER || map[nextRow][nextCol] == TILE_PILLAR) {
        nextRow = player.row;
        nextCol = player.col;
        return STATUS_STAY;
    }

    if(map[nextRow][nextCol] == TILE_OPEN) {
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;
        return STATUS_MOVE;
    }

    if(map[nextRow][nextCol] == TILE_TREASURE) {
        player.treasure += 1;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;
        return STATUS_TREASURE;
    }

    if(map[nextRow][nextCol] == TILE_AMULET) {
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;
        return STATUS_AMULET;
    }

    if(map[nextRow][nextCol] == TILE_DOOR) {
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = TILE_PLAYER;
        return STATUS_LEAVE;
    }

    if(map[nextRow][nextCol] == TILE_EXIT) {
        if(player.treasure >= 1) {
            map[player.row][player.col] = TILE_OPEN;
            player.row = nextRow;
            player.col = nextCol;
            map[player.row][player.col] = TILE_PLAYER;
            return STATUS_ESCAPE;
        } else {
            nextRow = player.row;
            nextCol = player.col;
            return STATUS_STAY;
        }
    }

    return 0;
}

/**
 09--* TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    bool monsterGotYa = false;

    for(int i = player.row + 1; i < maxRow; i++) {
        if(map[i][player.col] == TILE_PILLAR) {
            break;
        }
        if(map[i][player.col] == TILE_MONSTER) {
            map[i-1][player.col] = TILE_MONSTER;
            map[i][player.col] = TILE_OPEN;
        }
    }

    for(int i = player.row - 1; i >= 0; i--) {
        if(map[i][player.col] == TILE_PILLAR) {
            break;
        }
        if(map[i][player.col] == TILE_MONSTER) {
            map[i+1][player.col] = TILE_MONSTER;
            map[i][player.col] = TILE_OPEN;
        }
    }

    for(int i = player.col + 1; i < maxCol; i++) {
        if(map[player.row][i] == TILE_PILLAR) {
            break;
        }
        if(map[player.row][i] == TILE_MONSTER) {
            map[player.row][i-1] = TILE_MONSTER;
            map[player.row][i] = TILE_OPEN;
        }
    }

    for(int i = player.col - 1; i >= 0; i--) {
        if(map[player.row][i] == TILE_PILLAR) {
            break;
        }
        if(map[player.row][i] == TILE_MONSTER) {
            map[player.row][i+1] = TILE_MONSTER;
            map[player.row][i] = TILE_OPEN;
        }
    }

    if(map[player.row][player.col] == TILE_MONSTER) {
        monsterGotYa = true;
    }

    return monsterGotYa;
}
