/**
 *  Player.hpp
 *  Player parent class. Has child classes: Roadrunner and Coyotee.
 *  Homework 03
 *
 *  Created by Salil D. Maharjan on 4/7/19.
 *  Copyright © 2019 Salil D. Maharjan. All rights reserved.
 */

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>

///Player types
enum PlayerType
{
    ROADRUNNER,
    COYOTE
};

class Player
{
public:
    //Constructor: creates a player in environment env at position (x,y)
    Player(class Environment* a_env, int a_x, int a_y);
    
    //Destructor: Deallocates memory for Player
    virtual ~Player();
    
    //Moves the player in the environment. Overloaded in Roadrunner and Coyote.
    virtual void move()=0;
    
    //Breeds the player in the environment. Overloaded in Roadrunner and Coyote.
    virtual void breed()=0;
    
    //Getter: Gets player type and returns it.
    virtual PlayerType getPtype()=0;
    int getXpos(){return x;};
    int getYpos(){return y;};
    
    //Gets the character representation of the player, which is the player code.
    virtual char player_code()=0;
    
    //Settter: Sets move flag for the player.
    void set_move_flag(bool moved){move_flag=moved;};
    
    //Getter: Gets move flag for the player.
    bool get_move_flag(){return move_flag;};
    
    //Checks if the player is dead.
    virtual bool is_dead()const{return false;};
    
    //Checks if (x,y) is in the range of the environment. Used in breedPlayer() and in class Roadrunner and Coyote.
    bool in_range(int x_coord, int y_coord);
    
protected:
    ///Player's position in the environment.
    int x,y;
    
    ///Move flag for Player.
    bool move_flag=false;
    
    ///Number of steps since breeding.
    int breed_count=0;
    
    ///Pointer to the environment of the Players.
    Environment* m_environment;
    
    ///Generates an offspring that was bred in position (x,y)
    virtual void new_bred_player(int x_pos, int y_pos)=0;
    
    ///Moves player to new position (x_new, y_new)
    void moveTo(int x_new, int y_new);
    
    ///Breeds the player and places the offspring in one possible position in order of Moves enum.
    void breedPlayer();
    
private:
    
};

#endif /* Player_hpp */
