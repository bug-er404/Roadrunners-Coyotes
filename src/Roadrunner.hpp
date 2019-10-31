/**
 *  Roadrunner.hpp
 *  Roadrunner class. Inherits from Player class.
 *  Homework 03
 *
 *  Created by Salil D. Maharjan on 4/7/19.
 *  Copyright © 2019 Salil D. Maharjan. All rights reserved.
 */

#ifndef Roadrunner_hpp
#define Roadrunner_hpp
#include "Player.hpp"
#include "Environment.hpp"

#include<iostream>

class Roadrunner: public Player
{
public:
    
    //Constructor: Creates a Roadrunner in a_env at position (x,y)
    Roadrunner(class Environment* a_env, int x, int y);
    
    //Overloaded move method to move Roadrunner.
    void move();
    
    //Overloaded breed method to breed Roadrunners.
    void breed();
    
    //Returns the player type of a Roadrunner.
    PlayerType getPtype(){return ROADRUNNER;};
    
    //Returns the player code representation of a Roadrunner.
    char player_code(){return 'R';};
    
private:
    //Generates a new offspring after breeding at (x_pos,y_pos)
    void new_bred_player(int x_pos, int y_pos);
    
    //Checks runner's surroundings
    int check_surrounding(int x_pos, int y_pos);
};


#endif /* Roadrunner_hpp */
