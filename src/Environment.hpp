
/**
 *  Environment.hpp
 *  The board/Environment header file.
 *  Homework 03
 *
 *  Created by Salil D. Maharjan on 4/7/19.
 *  Copyright © 2019 Salil D. Maharjan. All rights reserved.
 */

#ifndef Environment_hpp
#define Environment_hpp

#include<vector>
#include "Player.hpp"


///ENVIRONMENT ATTRIBUTES:
///Roadrunner Breeding Time
const unsigned int RUNNER_BREED_TIME = 3;
///Coyotes Breeding Time
const unsigned int COYOTE_BREED_TIME = 8;
///Coyotes Starvation death Time
const unsigned int COYOTE_STARVE_TIME = 4;

///Position in the environment
struct Position
{
    int x;
    int y;
};

///The possible moves in environment
enum Moves
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

///SINGLETON ENVIRONMENT CLASS
class Environment
{
public:
    ///Singleton object constructor
    static Environment* getInstance(int roadrunners, int coyotes, int environment);
    
    ///Destructor
    ~Environment();
    
    ///Accessors
    Player* get_agent(int x, int y);
    unsigned int getEnvSize(){return ENV_SIZE;};
    unsigned int getRunnersCount(){return ROADRUNNER_COUNT;};
    unsigned int getCoyotesCount(){return COYOTE_COUNT;};
    
    ///Mutators
    void set_agent(int x, int y, Player* agent);
    
    //Random position generator
    //Random position in the environment
    Position random_pos();
    
    //Random move generator
    //Generates a random move
    Moves random_move();
    
    //Step simulator
    //Simulates a step in the environment
    void step_simulator();
    
    //Display world
    void display_world();
    
    //Checks if there is possible space to move
    bool can_move(int x, int y);
    
private:
    static Environment* game_instance;
    
    /// Private Singleton Constructor. Creates and initializes the environment.
    Environment(int roadrunners, int coyotes, int environment);

    /// Private copy constructor
    Environment(Environment const&){};
    
    /// Operator overload for singleton class
    void operator = (Environment const&){};
    
    /// Environment Grid where the players play.
    Player* env_grid[256][256];
    
    /// Reset move flags for all players
    void resetPlayers();
    
    /// Move all players of PlayerType p_type
    void movePlayer(PlayerType ptype);
    
    /// Check and clean all dead players in the environment
    void cleanDead();
    
    /// Breed players in the environment
    void breedPlayer();
    
    /// Creates Players in the environment.
    void createPlayers(PlayerType player_type, int count);
    
    /// WORLD CONFIGURATION VARIABLES
    /// Size of the world
    unsigned int ENV_SIZE = 5;
    /// Number of Roadrunners
    unsigned int ROADRUNNER_COUNT = 2;
    /// Number of Coyotes
    unsigned int COYOTE_COUNT = 2;
    
};

#endif /* Environment_hpp */


