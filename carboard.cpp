#include "game.h"
#include "helper.h"

#include <iostream>
#include <vector>
#include <limits>

using std::string;
using std::cout;
using std::endl;
using std::vector;

void showStudentInformation(string name, string id, string email);
void showMainMenu();
bool menuInput();

int main()
{

    showMainMenu();

    while(menuInput())
    {
        showMainMenu();
    }


    std::cout << "Good bye!\n\n";

    return EXIT_SUCCESS;
}



bool menuInput()
{
    string userInput = Helper::readInput();
    int returnVal = 1;
    

    if (Helper::isNumber(userInput) && userInput.size() <= std::numeric_limits<int>::digits10)
    {

    
        if (std::stoi(userInput) == 1)   // Game Starts
        {
            Game* newGame = new Game();
            newGame->start();

            delete newGame;

        }
        else if (std::stoi(userInput) == 2)
        {
            showStudentInformation("Adam De Fazio","s3661985","s3661985@student.rmit.edu.au");
        }
        else if(std::stoi(userInput) == 3)
        {
            returnVal = 0;
        }
    }
    else
    {
        Helper::printInvalidInput();
    }

    return returnVal;

}



void showStudentInformation(string name, string id, string email){
    cout << endl << endl;

    cout << " -----------------------------------" << endl;
    cout << "Name: " << name << endl;
    cout << "No: " << id << endl;
    cout << "Email: " << email << endl;

    cout << " -----------------------------------" << endl;

    cout << endl;

}

void showMainMenu()
{
    cout << "Welcome to Car Board" << endl;
    cout << "--------------------" << endl;
    cout << "1. Play Game" << endl;
    cout << "2. Show student's information" << endl;
    cout << "3. Quit" << endl;

    cout << endl;

    cout << "Please enter your choice: ";


}

