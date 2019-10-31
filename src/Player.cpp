/**
 *  Player.cpp
 *  Implementation of Player.hpp
 *  Homework 03
 *
 *  Created by Salil D. Maharjan on 4/7/19.
 *  Copyright © 2019 Salil D. Maharjan. All rights reserved.
 */

#include "Player.hpp"
#include "Environment.hpp"

#include <iostream>


/**
 * Constructor for Player Class.
 * Constructor: Creates a player in environment env at position (x,y)
 * @param a_env Environment* Environment where the players are.
 * @param a_x int x position to place player.
 * @param a_y int y position to place player.
 */
Player::Player(class Environment* a_env, int a_x, int a_y)
{
    m_environment = a_env;
    x = a_x;
    y = a_y;
    breed_count = 0;
    move_flag = false;
    m_environment->set_agent(x, y, this);
}

/**
 * Empty Destructor for Player class.
 */
Player::~Player()
{
}

/**
 * Method to check if cell is in range.
 * Checks if a position is in the board or out of range.
 * @param x_coord int x position in the board.
 * @param y_coord int y position in the board.
 * @return bool if (x,y) is in the board.
 */
bool Player::in_range(int x_coord, int y_coord)
{
    return (x_coord>=0) && (x_coord<m_environment->getEnvSize()) && (y_coord>=0) && (y_coord<m_environment->getEnvSize());
}

/**
 * Player move method in the environment.
 * Moves player from (x,y) to new position (x_new, y_new).
 * @see set_agent
 * @see get_agent
 * @param x_new int X-position to move agent to.
 * @param y_new int Y-position to move agent to.
 */
void Player::moveTo(int x_new, int y_new)
{
    //Moving player from (x,y) to (x_new, y_new)
    m_environment->set_agent(x_new, y_new, m_environment->get_agent(x, y));
    
    //Clearing (x,y)
    m_environment->set_agent(x, y, NULL);
    x = x_new;
    y = y_new;
    

    if(m_environment->get_agent(x_new,y_new)!=NULL)
        m_environment->get_agent(x_new,y_new)->set_move_flag(true);

}

/**
 * Method to check breeding cell.
 * Breeds the player and places the offspring in one possible position in order of Moves enum.
 * @see new_bred_player
 */
void Player::breedPlayer()
{
    //UP
    if((m_environment->get_agent(x, y+1))==NULL && in_range(x, y+1))
        new_bred_player(x, y+1);
    //DOWN
    else if((m_environment->get_agent(x, y-1))==NULL && in_range(x, y-1))
        new_bred_player(x, y-1);
    //LEFT
    else if((m_environment->get_agent(x-1, y))==NULL && in_range(x-1, y))
        new_bred_player(x-1, y);
    //RIGHT
    else if((m_environment->get_agent(x+1, y))==NULL && in_range(x+1, y))
        new_bred_player(x+1, y);
}

