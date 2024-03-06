#include "game.h"
#include <string>
#include <algorithm>

using std::cout;


void showCommands();
bool validCords(std::string str);



Game::Game()
{
    this->board = new Board();
    this->player = new Player();

}

Game::~Game()
{
    delete board;
    delete player;
}


void Game::start()
{
   
 showCommands();


        if(loadBoard())
        {
            if(initializePlayer())
            {
                play();
                cout << "Total Player Moves: " << player->moves << std::endl << std::endl;
            }
        }
    

}




bool Game::loadBoard()
{   
    int condition = 1;
    int returnVal = 1;

    while(condition)
    {
        cout << "At this stage of the program only two commands are acceptable\n"
                "generate <d>,<p>\n"
                "quit\n" << std::endl;

        
        std::string userInput = Helper::readInput();

        std::string command = userInput.substr(0, userInput.find(" "));
        std::string number = "-1";

        std::vector<std::string> values;

        if(command != userInput)
        {      

            number = userInput.substr(userInput.find(" "), userInput.find('\0'));

            // remove all whitespaces in string
            number.erase(remove(number.begin(), number.end(), ' '), number.end());

            Helper::splitString(number,values,",");
            
        }
        
        if(userInput == COMMAND_QUIT) 
        {
            returnVal = 0;
            condition = 0;
        }
        else if(number.length() != 6)
        {
            Helper::printInvalidInput();
        }
        else if(command == COMMAND_GENERATE_RANDOM)
        {
            if(Helper::isNumber(values[0]) && (std::stoi(values[0]) >= 10 && std::stoi(values[0]) <= 20)) 
            {
                if(Helper::isNumber(values[1]) && (std::stoi(values[0]) >= 0.1) && std::stoi(values[1]) <= 0.9)
                {
                    this->board->generate(std::stoi(values[0]),std::stod(values[1]));
                    this->board->display(this->player);
                    condition = 0;
                }
            }
            else
            {
                Helper::printInvalidInput();

            }
            
        }
        else
        {
            Helper::printInvalidInput();
        }
    } 
   


    return returnVal;
}


bool Game::initializePlayer()
{
    int condition = 1;
    int returnVal = 1;

    while(condition)
    {   

         cout << "You can use the following commands to play the game:\n"
            "generate <d>,<p>\n"
            "init <x>,<y>,<direction>\n"
            "quit" << std::endl;
        
        std::string userInput = Helper::readInput();

        std::string command = userInput.substr(0, userInput.find(" "));
        std::string number = "-1";

        std::vector<std::string> values;

        if(command != userInput)
        {      

            number = userInput.substr(userInput.find(" "), userInput.find('\0'));

            // remove all whitespaces in string
            number.erase(remove(number.begin(), number.end(), ' '), number.end());

            Helper::splitString(number,values,",");
            
        }

        if(userInput == COMMAND_QUIT)
        {
            returnVal = 0;
            condition = 0;
        }
        else if(command == COMMAND_GENERATE_RANDOM && number.length() == 6)
        {
            if(Helper::isNumber(values[0]) && (std::stoi(values[0]) >= 10 && std::stoi(values[0]) <= 20)) 
            {
                if(Helper::isNumber(values[1]) && (std::stoi(values[0]) >= 0.1) && std::stoi(values[1]) <= 0.9)
                {
                    this->board->generate(std::stoi(values[0]),std::stod(values[1]));
                    this->board->display(this->player);
                }
            }
            else
            {
                this->board->display(this->player);
                Helper::printInvalidInput();
            }
        }
        else if(command == COMMAND_INIT && this->board->validCords(number))
        {   
            std::vector<std::string> cords;
            Helper::splitString(number,cords,",");

            // check to see if init position is blocked 
            if(!(this->board->checkPoardPos(&cords)))
            {
                cout << "Unable to place player at that position -- cell is blocked\n\n";
                this->board->display(this->player);
            }
            else
            {   
                //initizialise the player at position
                Position Position(std::stoi(cords[0]),std::stoi(cords[1]));


                //init direction

                Direction direction = NORTH;


                if(cords[2] == DIRECTION_EAST)
                {
                     direction = EAST;
                }
                else if(cords[2] == DIRECTION_WEST)
                {
                    direction = WEST;
                }
                else if(cords[2] == DIRECTION_NORTH)
                {
                    direction = NORTH;
                }
                else if(cords[2] == DIRECTION_SOUTH)
                {
                    direction = SOUTH;
                }
                
                // place player and display board
                this->player->initialisePlayer(&Position,direction);

                this->board->placePlayer(this->player->position);
                this->board->display(this->player);
                condition = 0;
            }

        }
        else
        {   
            this->board->display(this->player);
            Helper::printInvalidInput();
        }


    }

    
    return returnVal;
}

void Game::play()
{   
    // variable used in condition to break out of the loop
    int condition = 1;

    while(condition)
    {
        cout <<"\nAt this stage of the program, only four commands are acceptable:\n"
               "forward (or f)\n"
               "turn_left (or l)\n"
               "turn_right (or r)\n"
               "quit\n" << std::endl;

    
        std::string userInput = Helper::readInput();

        if(userInput == COMMAND_FORWARD ||  userInput == COMMAND_FORWARD_SHORTCUT)
        {
            this->board->movePlayerForward(this->player);
            this->board->display(this->player);
        }
        else if(userInput == COMMAND_TURN_LEFT || userInput == COMMAND_TURN_LEFT_SHORTCUT)
        {
            TurnDirection left = TURN_LEFT;
            this->player->turnDirection(left);
            this->board->display(this->player);

        }
        else if(userInput == COMMAND_TURN_RIGHT || userInput == COMMAND_TURN_RIGHT_SHORTCUT)
        {
            TurnDirection right = TURN_RIGHT;
            this->player->turnDirection(right);
            this->board->display(this->player);
        }
        else if(userInput == COMMAND_QUIT)
        {   
            // set loop condition to 0 to break out of loop
            condition = 0;
        }
        else
        {
            this->board->display(this->player);
            Helper::printInvalidInput();
        }
    }
}


void showCommands()
{

    cout << " You can use the following commands to play the game:\n\n"
                " generate <d>,<p>\n"
                "    d: the dimension of the game board to be generated\n"
                "    p: the probability of the blocks on board to be generated randomly\n"
                " init <x>,<y>,<direction>\n"
                "    x: horizontal position of the car on the board\n"
                "    y: vertival position of the var on the board\n"
                "    direction: direction of the car's movement (north, south, east, west)\n"
                " forward (or f)\n"
                " turn_left (or l)\n"
                " turn_right (or r)\n"
                " quit\n" << std::endl;
        

    
    cout << "Press enter to continue..." << std::endl;

    std::cin.ignore();

}


