//  main.cpp
//  Homework 3 OOP
//
//  Created by Salil D. Maharjan on 3/9/19.
//  Copyright © 2019 Salil D. Maharjan. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "Environment.hpp"

using namespace std;


int main()
{
    int num_roadrunners;
    int num_coyotes;
    int environment_size;
    
    cout<<"WELCOME TO ROADRUNNERS AND COYOTES!!!"<<endl
    <<"Before we begin, let's initialize the game according to your preference"<<endl
    <<"NOTE: The environment size should be bigger than the total number of players."<<endl
    <<"NOTE: Maximum size for the environment is 256."<<endl
    <<"-----------------------------"<<endl
    <<"-----------------------------"<<endl;
    
    //Getting user input for configuration variables.
    do
    {
        cout<<"Please enter the number of Roadrunners you want in the environment: ";
        cin>>num_roadrunners;
    } while(num_roadrunners<=0);
    
    do
    {
        cout<<"Please enter the number of Coyotes you want in the environment: ";
        cin>>num_coyotes;
    } while(num_coyotes<=0);
    
    do
    {
        cout<<"Please enter the environment size:  ";
        cin>>environment_size;
    } while(environment_size<(num_coyotes+num_roadrunners));
    
    Environment* myGame = Environment::getInstance(num_roadrunners, num_coyotes, environment_size);
    myGame->display_world();
    
    char c;
    
    while( (cin.get(c)) && c != 'Q')
    {
        myGame->step_simulator();
        myGame->display_world();
    }
    
    return 0;
}

