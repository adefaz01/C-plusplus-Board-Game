#include "board.h"

#define DIRECTION_NORTH "north"
#define DIRECTION_EAST "east"
#define DIRECTION_SOUTH "south"
#define DIRECTION_WEST "west"


#include<cstdlib>

using std::vector;
using std::cout;

const vector<vector<Cell>> Board::BOARD_1 =
{
    { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

const vector<vector<Cell>> Board::BOARD_2 =
{
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};




const vector<vector<Cell>> Board::EMPTY_BOARD =
{
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

Board::Board()
{
    this->board = new vector<vector<Cell>>;


}

Board::~Board()
{
    delete board;

}

void Board::generate(int x, double y)
{
    this->board->clear();

    int number = y * 100;
    int randomNumber = 0;

    for(int i = 0; i < x; ++i)
    {   
        vector<Cell> column (x);
        this->board->push_back(column);

        for(int j = 0; j < x; ++j)
        {   
            randomNumber = rand() % 100;

            if(randomNumber <= number)
            {   
                (*this->board)[i][j] = BLOCKED;
            }
            else
            {   
                 (*this->board)[i][j] = EMPTY;
            }
             
        }
    }
}



void Board::load(int boardId)
{
    if(boardId == 1)
    {   
        for(int i = 0; i < (int) BOARD_1.size(); ++i)
        {
            for(int j = 0; j < (int) BOARD_1.size(); ++j)
            {
                (*this->board)[i][j] = BOARD_1[i][j];
            }
        }

    }
    else if (boardId == 2)
    {
        for(int i = 0; i < (int) BOARD_2.size(); ++i)
        {
            for(int j = 0; j < (int) BOARD_2.size(); ++j)
            {
                (*this->board)[i][j] = BOARD_2[i][j];
            }
        }
    }
}

bool Board::placePlayer(Position position)
{
    int returnVal = 0;

    if((*this->board)[position.y][position.x] != BLOCKED)
    {
        (*this->board)[position.y][position.x] = PLAYER;
        returnVal = 1;
    }
    return returnVal;
}

PlayerMove Board::movePlayerForward(Player* player)
{
    Position forwardpos = player->getNextForwardPosition();
    PlayerMove returnVal = PLAYER_MOVED;

    //check if position is out bounds
    if(!(forwardpos.x >=0 &&  forwardpos.x <= ((int) this->board->size() - 1)) || !(forwardpos.y >= 0 && forwardpos.y <= ((int) this->board->size() - 1)) )
    {   
        cout << "The car is at the edge of the board and cannot move furhter in that direction\n\n";
        returnVal = OUTSIDE_BOUNDS;
    }
    //check if position is blocked 
    else if((*this->board)[forwardpos.y][forwardpos.x] == BLOCKED)
    {   
        cout << "Unable to move as the cell is blocked\n\n";
        returnVal = CELL_BLOCKED;
    }
    //place player position at empty block
    else if(((*this->board)[forwardpos.y][forwardpos.x] == EMPTY))
    {

        (*this->board)[player->position.y][player->position.x] = EMPTY;
        player->updatePosition(forwardpos);
        placePlayer(forwardpos);

    }

    return returnVal;
}

void Board::display(Player* player)
{
    // code used to display the board 
    
    cout << LINE_OUTPUT EMPTY_OUTPUT LINE_OUTPUT;
        
        for(int i = 0,inner = 0; i< (int) this->board->size(); ++i)
        {   
            if(i > 9)
            {
                cout << inner << LINE_OUTPUT;
                ++inner;
            }
            else
            {
                cout << i <<LINE_OUTPUT;
            }
        }

        cout << std::endl;


        for(int i = 0,inner = 0; i < (int) this->board->size(); ++i)
        {   
            if( i > 9)
            {
                cout << LINE_OUTPUT << inner << LINE_OUTPUT;
                ++inner;
            }
            else
            {
                cout << LINE_OUTPUT << i << LINE_OUTPUT;
            }
            
            for(int j = 0; j < (int) this->board->size(); ++j)
            {
                if((*this->board)[i][j] == EMPTY)
                {   
                    cout << EMPTY_OUTPUT << LINE_OUTPUT;
                }
                else if ((*this->board)[i][j] == BLOCKED)
                {      
                    cout << BLOCKED_OUTPUT << LINE_OUTPUT;
                }
                else if((*this->board)[i][j] == PLAYER)
                {
                    player->displayDirection();
                    cout << LINE_OUTPUT;
                }
            }   

            cout << std::endl;
        }

    cout << std::endl;
}


bool Board::checkPoardPos(std::vector<std::string>* cords)
{
    int x = std::stoi((*cords)[0]);
    int y = std::stoi((*cords)[1]);
    int returnVal = 1;

    if((*this->board)[y][x] == BLOCKED)
    {
        returnVal = 0;
    }
    
    
    return returnVal;
    
}



bool Board::validCords(std::string str)
{
    
    std::vector<std::string> cords;
    int returnVal = 0;

    Helper::splitString(str,cords,",");

    // check first number 
    if(Helper::isNumber(cords[0]) && std::stoi(cords[0]) >= 0 && std::stoi(cords[0]) <= (int) this->board->size())
    {   
        // check scecond number
        if(Helper::isNumber(cords[1]) && std::stoi(cords[1]) >= 0 && std::stoi(cords[1]) <= (int) this->board->size())
        {
            // check direction
            if(cords[2] == DIRECTION_NORTH || cords[2] == DIRECTION_SOUTH || cords[2] == DIRECTION_EAST || cords[2] == DIRECTION_WEST)
            {
                returnVal = 1;
            }
        }
    
    }


    return returnVal;
}





