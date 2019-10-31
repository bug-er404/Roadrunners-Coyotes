/**
 *  Coyote.cpp
 *  Implements Coyote.hpp class.
 *  Homework 03
 *
 *  Created by Salil D. Maharjan on 4/7/19.
 *  Copyright © 2019 Salil D. Maharjan. All rights reserved.
 */

#include "Coyote.hpp"
#include "Player.hpp"

/**
 * Constructor for Coyotee class.
 * Constructor: Creates a Coyote in a_env at position (x,y). Calls Player constructor.
 * @param a_env Environment* Environment where the players are.
 * @param x int x position to place player.
 * @param y int y position to place player.
 */
Coyote::Coyote(class Environment* a_env, int x, int y):Player(a_env,x,y)
{
    starve_count = 0;
}

/**
 * Move method for Coyotes.
 * Overloaded move method to move Coyotes according to its behaviour.
 * @see can_move
 * @see get_agent
 * @see moveTo
 * @see random_pos
 * @see in_range
 */
void Coyote::move()
{
    //When all adjacent cells are occupied
    if(!m_environment->can_move(x,y))
        return;
    
    //updating breed and starve counters
    breed_count++;
    starve_count++;
    
    //Checking position above for a roadrunner
    if(m_environment->get_agent(x, y+1) != NULL)
    {
        if(m_environment->get_agent(x, y+1)->getPtype() == ROADRUNNER)
        {
            //Reset starvation
            starve_count = 0;
            //Delete Roadrunner in the position
            delete m_environment->get_agent(x, y+1);
            //Move to the position.
            moveTo(x, y+1);
            return;
        }
    }
    
    //Checking position below for a roadrunner
    if(m_environment->get_agent(x, y-1) != NULL)
    {
        if(m_environment->get_agent(x, y-1)->getPtype() == ROADRUNNER)
        {
            //Reset starvation
            starve_count = 0;
            //Delete Roadrunner in the position
            delete m_environment->get_agent(x, y-1);
            //Move to the position.
            moveTo(x, y-1);
            return;
        }
    }
    
    //Checking position left for a roadrunner
    if(m_environment->get_agent(x-1, y) != NULL)
    {
        if(m_environment->get_agent(x-1, y)->getPtype() == ROADRUNNER)
        {
            //Reset starvation
            starve_count = 0;
            //Delete Roadrunner in the position
            delete m_environment->get_agent(x-1, y);
            //Move to the position.
            moveTo(x-1, y);
            return;
        }
    }
    
    //Checking position right for a roadrunner
    if(m_environment->get_agent(x+1, y) != NULL)
    {
        if(m_environment->get_agent(x+1, y)->getPtype() == ROADRUNNER)
        {
            //Reset starvation
            starve_count = 0;
            //Delete Roadrunner in the position
            delete m_environment->get_agent(x+1, y);
            //Move to the position.
            moveTo(x+1, y);
            return;
        }
    }
    
    //IF no roadrunner is found, a random move is generated.
    //Generate random move.
    int loop_count = 0;
    while(get_move_flag() == false)
    {
        loop_count++;
        Moves move_in = m_environment->random_move();
        switch(move_in)
        {
            case Moves::UP:
                if(m_environment->get_agent(x, y+1)==NULL && in_range(x, y+1))
                    moveTo(x, y+1);
                break;
            case Moves::DOWN:
                if(m_environment->get_agent(x, y-1)==NULL && in_range(x, y-1))
                    moveTo(x, y-1);
                break;
            case Moves::LEFT:
                if(m_environment->get_agent(x-1, y)==NULL && in_range(x-1, y))
                    moveTo(x-1, y);
                break;
            case Moves::RIGHT:
                if(m_environment->get_agent(x+1, y)==NULL && in_range(x+1, y))
                    moveTo(x+1, y);
                break;
            default:
                break;
        }
        //If no move is possible
        if(loop_count == 4)
            set_move_flag(true);
    }
    
}

/**
 * Breed method for Coyotes.
 * Overloaded breed method to breed Coyotes.
 * @see breedPlayer
 */
void Coyote::breed()
{
    if(breed_count >= COYOTE_BREED_TIME)
        breedPlayer();
}

/**
 * Method to check if a Coyote is dead.
 * Checks if the coyote starved to death.
 * @return bool dead or not.
 */
bool Coyote::is_dead()
{
    if(starve_count >= COYOTE_STARVE_TIME)
        return true;
    else
        return false;
}

/**
 * Method to generate new bred offspring for Coyotes.
 * Generates a new offspring after breeding at (x_pos,y_pos)
 * @param x_pos int x position to put new offspring
 * @param y_pos int y position to put new offspring
 */
void Coyote::new_bred_player(int x_pos, int y_pos)
{
    new Coyote(this->m_environment,x_pos,y_pos);
    breed_count=0;
}

