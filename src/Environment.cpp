/**
 *  Environment.cpp
 *  Implementation of Environment.hpp
 *  Homework 03
 *
 *  Created by Salil D. Maharjan on 4/7/19.
 *  Copyright © 2019 Salil D. Maharjan. All rights reserved.
 */

#include "Environment.hpp"
#include "Roadrunner.hpp"
#include "Coyote.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <iomanip>

///Singleton class instance pointer
Environment* Environment::game_instance = 0;

/**
 * Instantiation method for singleton Environment class.
 * Takes number of roadrunner, coyotes and grid size to construct a single Environment.
 * @param roadrunners int Number of Roadrunners to put in the game initially.
 * @param coyotes int Number of Coyotes to put in the game initially.
 * @param environment int Grid size of the environment.
 */
Environment* Environment::getInstance(int roadrunners, int coyotes, int environment)
{
    if(!game_instance)
        game_instance = new Environment(roadrunners, coyotes, environment);
    return game_instance;
}


/**
 * Singleton Constructor for the class.
 * Takes number of roadrunner, coyotes and grid size to construct Environment.
 * @param roadrunners int Number of Roadrunners to put in the game initially.
 * @param coyotes int Number of Coyotes to put in the game initially.
 * @param environment int Grid size of the environment.
 */
Environment::Environment(int roadrunners, int coyotes, int environment):
ROADRUNNER_COUNT(roadrunners),
COYOTE_COUNT(coyotes),
ENV_SIZE(environment)
{
    //seeding a random number
    srand((int)time(0));

    int i, j;
    for(i=0 ; i<ENV_SIZE ; i++)
    {
        for(j=0 ; j<ENV_SIZE ; j++)
        {
            env_grid[i][j]=NULL;
        }
    }
    
    //Initializing the players
    createPlayers(ROADRUNNER, ROADRUNNER_COUNT);
    createPlayers(COYOTE, COYOTE_COUNT);
}

/**
 * Environment Class Destructor
 * Frees dynamically allocated memory for the players in the game.
 */
Environment::~Environment()
{
    int i, j;
    
    for (i=0; i<ENV_SIZE; i++)
    {
        for (j=0; j<ENV_SIZE; j++)
        {
            delete env_grid[i][j];
        }
    }
}

/**
 * Accessor method to get agents.
 * Gets agent at position (x,y). Returns 0 if invalid.
 * @param x int x-position of the agent.
 * @param y int y-position of the agent.
 * @return Player* Player pointer to the agent in position (x,y)
 */
Player* Environment::get_agent(int x, int y)
{
    if ((x>=0) && (x<ENV_SIZE) && (y>=0) && (y<ENV_SIZE))
    {
        return env_grid[x][y];
    }
    else
    {
        return 0;
    }
}

/**
 * Mutator method to seet agents.
 * Sets Player agent at position (x,y).
 * @param x int x-position of the agent.
 * @param y int y-position of the agent.
 * @param agent Player* Agent to place in position (x,y)
 */
void Environment::set_agent(int x, int y, Player* agent)
{
    if ((x>=0) && (x<ENV_SIZE) && (y>=0) && (y<ENV_SIZE))
        env_grid[x][y]=agent;
}

/**
 * Random position generator
 * Returns random position in the environment grid.
 * @see Position
 * @return Position struct that holds (x,y) co-ordinatees
 */
Position Environment::random_pos()
{
    Position pos;
    pos.x = rand()%ENV_SIZE;
    pos.y = rand()%ENV_SIZE;
    
    return pos;
}

/**
 * Random move generator
 * Returns a random move in the environment.
 * @see Moves
 * @return Position enum that holds all possible moves in the environment.
 */
Moves Environment::random_move()
{
    return static_cast<Moves>(rand()%4);
}

/**
 * Step Simulator.
 * Simulates one step in the environment.
 * @see resetPlayers
 * @see movePlayer
 * @see cleanDead
 * @see breedPlayer
 */
void Environment::step_simulator()
{
    //Reset move flag for all players
    resetPlayers();
    
    // Move Coyotes and Roadrunners randomly.
    int rand_case = (int)rand()%2;
    if(rand_case == 0)
    {
        movePlayer(ROADRUNNER);
        movePlayer(COYOTE);
    }else
    {
        movePlayer(COYOTE);
        movePlayer(ROADRUNNER);
    }
    
    //Check and clean dead players
    cleanDead();
    
    //Breed players
    breedPlayer();
}

/**
 * Method to display the game environment.
 * Displays the environment as a character grid.
 */
void Environment::display_world()
{
    int runner_counter=0;
    int coyote_counter=0;
    int i,j;
    std::cout<<"-------------------------------------------------------------------"<<std::endl;
    std::cout<<"-------------------------------------------------------------------"<<std::endl;
    
    for (i = 0; i<ENV_SIZE; i++)
    {
        for (j = 0; j<ENV_SIZE; j++)
        {
            if(env_grid[i][j]==NULL)
                std::cout<< std::setw(5) <<".";
            else
            {
                std::cout<< std::setw(5) <<env_grid[i][j]->player_code();
                if(env_grid[i][j]->player_code()=='R')
                    runner_counter++;
                else
                    coyote_counter++;
            }
    
        }
        std::cout<<std::endl;
        std::cout<<std::endl;
    }
    
    std::cout<<std::setw(5) <<"Number of Roadrunners: "<<runner_counter<<std::endl;
    std::cout<<std::setw(5) <<"Number of Coyotes:     "<<coyote_counter<<std::endl;
    
    //Checking if any agent won.
    if(coyote_counter==0)
    {
        std::cout<<"********************"<<std::endl;
        std::cout<<"ROADRUNNERS WIN!!!!!"<<std::endl;
        std::cout<<"********************"<<std::endl;
        exit(0);
    }
    if(runner_counter==0)
    {
        std::cout<<"********************"<<std::endl;
        std::cout<<"COYOTES WIN!!!!!!!!!"<<std::endl;
        std::cout<<"********************"<<std::endl;
        exit(0);
    }
    
}

/**
 * Method to create agents.
 * Creates count number of players of type player_type. Calls overloaded constructors in Roadrunner and Coyote.
 * @see random_pos
 * @see Roadrunner
 * @see Coyote
 * @param player_type PlayerType Type of player to create(Roadrunner/Coyote)
 * @param count int Number of agents to create.
 */
void Environment::createPlayers(PlayerType player_type, int count)
{
    int player_count = 0;
    
    while (player_count<count)
    {
        Position pos = random_pos();
        
        //Check and place in empty spots
        if(env_grid[pos.x][pos.y] == NULL)
        {
            player_count++;
            //Create a new roadrunner.
            if(player_type == ROADRUNNER)
            {
                new Roadrunner(this, pos.x, pos.y);
            }
            //Create a new coyote.
            else if (player_type == COYOTE)
            {
                new Coyote(this, pos.x, pos.y);
            }
        }
    }
}

/**
 * Method to reset move flags for all players
 * Sets move flag for all players to False. Used to reinstatiate the move state.
 */
void Environment::resetPlayers()
{
    int i,j;
    
    for(i=0 ; i<ENV_SIZE ; i++)
    {
        for(j=0 ; j<ENV_SIZE ; j++)
        {
            if(env_grid[i][j]!=NULL)
                env_grid[i][j]->set_move_flag(false);
        }
    }
}

/**
 * Method to move players of PlayerType
 * Moves all players in the environment of type PlayerType.
 * @param ptype PlayerType Type of players to move.
 * @see getPtype
 * @see get_move_flag
 */
void Environment::movePlayer(PlayerType ptype)
{
    int i, j;
    
    for(i=0 ; i<ENV_SIZE ; i++)
    {
        for(j=0 ; j<ENV_SIZE ; j++)
        {
            if(env_grid[i][j]!=NULL)
            {
                if(env_grid[i][j]->getPtype()==ptype && !(env_grid[i][j]->get_move_flag()))
                {
                    if(can_move(i, j))
                        env_grid[i][j]->move();
                }
            }
        }
    }
}

/**
 * Clean dead players from the environment.
 * Checks status of all the players in the environment and removes dead agents.
 */
void Environment::cleanDead()
{
    int i, j;
    
    for(i=0 ; i<ENV_SIZE ; i++)
    {
        for(j=0 ; j<ENV_SIZE ; j++)
        {
            if(env_grid[i][j]!=NULL)
            {
                if (env_grid[i][j]->is_dead())
                {
                    delete env_grid[i][j];
                    env_grid[i][j] = NULL;
                }
            }
        }
    }
}

/**
 * Checks the breeding status of players in the environment.
 * Calls the breed function for all players to check if they have enough steps to breed.
 * @see breed
 */
void Environment::breedPlayer()
{
    int i, j;
    for(i=0 ; i<ENV_SIZE ; i++)
    {
        for(j=0 ; j<ENV_SIZE ; j++)
        {
            if(env_grid[i][j]!=NULL)
            {
                env_grid[i][j]->breed();
            }
        }
    }
}

/**
 * Checks if there is possible space to move.
 * Checks all four adjacent places for a place to move. Returns a boolean.
 * @return bool If there is a cell to move to or not.
 */
bool Environment::can_move(int x, int y)
{
    int possible_moves = 0;
    
    if(env_grid[x-1][y]==NULL)
        possible_moves++;
    if(env_grid[x+1][y]==NULL)
        possible_moves++;
    if(env_grid[x][y-1]==NULL)
        possible_moves++;
    if(env_grid[x][y+1]==NULL)
        possible_moves++;
    
    if(possible_moves==0)
        return false;
    else
        return true;
    
}

