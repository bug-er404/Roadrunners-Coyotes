/**
 *  Roadrunner.cpp
 *  Implementation of Roadrunner.hpp
 *  Homework 03
 *
 *  Created by Salil D. Maharjan on 4/7/19.
 *  Copyright © 2019 Salil D. Maharjan. All rights reserved.
 */

#include "Roadrunner.hpp"
#include "Player.hpp"
#include "Environment.hpp"



/**
 * Constructor for Roadrunner class.
 * Constructor: Creates a Roadrunner in a_env at position (x,y). Calls Player Constructor.
 * @param a_env Environment* Environment where the players are.
 * @param x int x position to place player.
 * @param y int y position to place player.
 */
Roadrunner::Roadrunner(class Environment* a_env, int x, int y):Player(a_env,x,y)
{
}

/**
 * Move method for Roadrunners.
 * Overloaded move method to move Roadrunner according to its behaviour.
 * @see can_move
 * @see check_surrounding
 * @see get_agent
 * @see moveTo
 * @see random_pos
 * @see in_range
 */
void Roadrunner::move()
{
    //Update breed counter
    breed_count++;
    
    //When all adjacent cells are occupied
    if(!m_environment->can_move(x,y))
        return;
        
    //When there are coyotes in adjacent cells
    if(check_surrounding(x, y) != 0)
    {
        
        // Possible moves
        int u1, u2, d1, d2, l1, l2, r1, r2;
        
        // Least number of roadrunners
        // Initialized to the max value + 1.
        int min = 9;
        // Cell with least number of roadrunners;
        std::string min_cell = "NULL";
        
        //Check surrounding above
        //One cell above
        u1=check_surrounding(x, y+1);
        //First initialization
        //Checking if cell is empty and in range
        if (m_environment->get_agent(x, y+1)==NULL && in_range(x,y+1))
        {
            if(u1<min)
            {
            min = u1;
            min_cell = "u1";
            }
        }
        //Two cell above
        u2=check_surrounding(x, y+2);
        if (m_environment->get_agent(x, y+2)==NULL && in_range(x,y+2))
        {
            if(u2<min)
            {
                min=u2;
                min_cell="u2";
            }
        }
        
        //Check surrounding below
        d1=check_surrounding(x, y-1);
        if (m_environment->get_agent(x, y-1)==NULL && in_range(x,y-1))
        {
            if(d1<min)
            {
                min=d1;
                min_cell="d1";
                
            }
        }
        d2=check_surrounding(x, y-2);
        if (m_environment->get_agent(x, y-2)==NULL && in_range(x,y-2))
        {
            if(d2<min)
            {
                min=d2;
                min_cell="d2";
            }
        }
        
        //Check surrounding to the right
        r1=check_surrounding(x+1, y);
        if (m_environment->get_agent(x+1, y)==NULL && in_range(x+1,y))
        {
            if(r1<min)
            {
                min=r1;
                min_cell="r1";
                
            }
        }
        r2=check_surrounding(x+2, y);
        if (m_environment->get_agent(x+2,y)==NULL && in_range(x+2,y))
        {
            if(r2<min)
            {
                min=r2;
                min_cell="r2";
            }
        }
        
        //Check surrounding to the left
        l1=check_surrounding(x-1, y);
        if (m_environment->get_agent(x-1, y)==NULL && in_range(x-1,y))
        {
            if(l1<min)
            {
                min=l1;
                min_cell="l1";
                
            }
        }
        l2=check_surrounding(x-2, y);
        if (m_environment->get_agent(x-2, y)==NULL && in_range(x-2,y))
        {
            if(l2<min)
            {
                min=l2;
                min_cell="l2";
                
            }
        }
        
        //Moving Roadrunner to the safest location
        if(min_cell != "NULL")
        {
            if(min_cell == "u1")
                moveTo(x, y+1);
            else if(min_cell == "u2")
                moveTo(x, y+2);
            else if(min_cell == "d1")
                moveTo(x, y-1);
            else if(min_cell == "d2")
                moveTo(x, y-2);
            else if(min_cell == "r1")
                moveTo(x, y-2);
            else if(min_cell == "r2")
                moveTo(x, y-2);
            else if(min_cell == "l1")
                moveTo(x, y-2);
            else if(min_cell == "l2")
                moveTo(x, y-2);
            else
            {
                //No possible moves
                set_move_flag(true);
            }
        }//No safe location found
        else{set_move_flag(true);}
    }
    //If no coyotes are sensed, we generate a random move.
    else
    {
        int loop_count = 0;
        while(get_move_flag()==false)
        {
            loop_count++;
            //Generate random move.
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
}

/**
 * Breed method for Roadrunners.
 * Overloaded breed method to breed Roadrunners.
 * @see breedPlayer
 */
void Roadrunner::breed()
{
    if(breed_count >= RUNNER_BREED_TIME)
        breedPlayer();
}

/**
 * Method to generate new bred offspring for Roadrunners.
 * Generates a new offspring after breeding at (x_pos,y_pos)
 * @param x_pos int x position to put new offspring
 * @param y_pos int y position to put new offspring
 */
void Roadrunner::new_bred_player(int x_pos, int y_pos)
{
    new Roadrunner(this->m_environment, x_pos, y_pos);
    breed_count=0;
}

/**
 * Method to check Runner's surroundings.
 * Checks the roadrunner's surroundings for coyotes.
 * @param x_pos int x position of the runner.
 * @param y_pos int y position of the runner.
 * @return int number of roadrunners in the surrounding of (x_pos,y_pos)
 */
int Roadrunner::check_surrounding(int x_pos, int y_pos)
{
    int total_coyotes=0;
    
    //Checking position above for a coyote
    if(m_environment->get_agent(x, y+1) != NULL && m_environment->get_agent(x, y+1)->getPtype() == COYOTE)
        total_coyotes++;
    //Checking position below for a coyote
    if(m_environment->get_agent(x, y-1) != NULL && m_environment->get_agent(x, y-1)->getPtype() == COYOTE)
        total_coyotes++;
    //Checking position left for a coyote
    if(m_environment->get_agent(x-1, y) != NULL && m_environment->get_agent(x-1, y)->getPtype() == COYOTE)
        total_coyotes++;
    //Checking position right for a coyote
    if(m_environment->get_agent(x+1, y) != NULL && m_environment->get_agent(x+1, y)->getPtype() == COYOTE)
        total_coyotes++;
    
    return total_coyotes;
}

