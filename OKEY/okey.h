//
//  okey.h
//  OKEY
//
//  Created by Guest on 10/18/21.
//

#ifndef okey_h
#define okey_h

#include <vector>

using namespace::std;


class Tas {
    string color;
    unsigned int number;
    bool isDistributed;
    
public:
    
    string getColor(){
        return color;
    }
    unsigned int getNumber(){
        return number;
    }
    bool getDistribution(){
        return isDistributed;
    }
    void setColor(string color){
        this->color = color;
    }
    void setNumber(unsigned int number){
        this->number = number;
    }
    void setDistribution(bool isDistributed){
        this->isDistributed = isDistributed;
    }
    
};


class Player{
    unsigned int player_id;
    vector<Tas> player_hand;
public:
    unsigned int getPlayerID(){
        return this->player_id;
    }
    vector<Tas> getPlayerHand(){
        return player_hand;
    }
    void setPlayerID(unsigned int pid){
        player_id = pid;
    }
    void addTasToHand(Tas t){
        player_hand.push_back(t);
    }
    
};


#endif /* okey_h */
