#include "player.h"

Position::Position()
{
    this-> x = 0;
    this-> y = 0;
}


Position::Position(int x, int y)
{
    this-> x = x;
    this-> y = y;
}

Player::Player()
{
    // do nothing
}

void Player::initialisePlayer(Position* position, Direction direction)
{
    this->position = *position;
    this->direction = direction;
    this->moves = 0;
    
}

void Player::turnDirection(TurnDirection turnDirection)
{
    if(turnDirection == TURN_LEFT)
    {
        if(this->direction == NORTH)
        {
            this->direction = WEST;
        }
        else if(this->direction == EAST)
        {
            this->direction = NORTH;
        }
        else if(this->direction == WEST)
        {
            this->direction = SOUTH;
        }
        else if(this->direction == SOUTH)
        {
            this->direction = EAST;
        }
    }
    else if(turnDirection == TURN_RIGHT)
    {
         if(this->direction == NORTH)
        {
            this->direction = EAST;
        }
        else if(this->direction == EAST)
        {
            this->direction = SOUTH;
        }
        else if(this->direction == WEST)
        {
            this->direction = NORTH;
        }
        else if(this->direction == SOUTH)
        {
            this->direction = WEST;
        }
    }
}

Position Player::getNextForwardPosition()
{
    Position forwardpos;

    if(this->direction == NORTH)
    {
        forwardpos.x = this->position.x;
        forwardpos.y = this->position.y - 1;
    }
    else if(this->direction == EAST)
    {
        forwardpos.x = this->position.x + 1;
        forwardpos.y = this->position.y;
    }
    else if(this->direction == SOUTH)
    {
        forwardpos.x = this->position.x;
        forwardpos.y = this->position.y + 1;
    }
    else if(this->direction == WEST)
    {
        forwardpos.x = this->position.x - 1;
        forwardpos.y = this->position.y;
    }

    return forwardpos;
}

void Player::updatePosition(Position position)
{
    this->position.x = position.x;
    this->position.y = position.y;
    ++moves;
}

void Player::displayDirection()
{
    if(this->direction == NORTH)
    {
        std::cout << DIRECTION_ARROW_OUTPUT_NORTH;
    }
    else if(this->direction == SOUTH)
    {
        std::cout << DIRECTION_ARROW_OUTPUT_SOUTH;
    }
    else if(this->direction == EAST)
    {
        std::cout << DIRECTION_ARROW_OUTPUT_EAST;
    }
    else if(this->direction == WEST)
    {
        std::cout << DIRECTION_ARROW_OUTPUT_WEST;
    }
}
