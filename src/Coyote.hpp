/**
 *  Coyote.hpp
 *  Coyote class. Inherits from Player class.
 *  Homework 03
 *
 *  Created by Salil D. Maharjan on 4/7/19.
 *  Copyright © 2019 Salil D. Maharjan. All rights reserved.
 */

#ifndef Coyote_hpp
#define Coyote_hpp
#include "Player.hpp"
#include "Environment.hpp"

#include <stdio.h>


class Coyote: public Player
{
public:
    //Constructor: Creates a Coyote in a_env at position (x,y)
    Coyote(class Environment* a_env, int x, int y);
    
    //Overloaded move method to move Coyotes.
    void move();
    
    //Overloaded breed method to breed Coyotes.
    void breed();
    
    //Returns the player type of a Coyotes.
    PlayerType getPtype(){return COYOTE;};
    
    //Returns the player code representation of a Coyote.
    char player_code(){return 'C';};
    
    //Checks if the coyote is dead or not.
    bool is_dead();
    
private:
    
    //Generates a new offspring after breeding at (x_pos,y_pos)
    void new_bred_player(int x_pos, int y_pos);
    
    //Counter to count when the coyote starves to death.
    int starve_count;
};


#endif /* Coyote_hpp */
