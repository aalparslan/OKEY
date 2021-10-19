//
//  main.cpp
//  OKEY
//
//  Created by Guest on 10/18/21.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include "okey.h"



void set_all_tas(vector<Tas> &all_tas){
    bool doubled = false;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; ){
            Tas t;
            t.setDistribution(false);
            if(i == 0){
                // yellow
                t.setColor("yellow");
                t.setNumber(j+1);
            }else if (i == 1){
                // blue
                t.setColor("blue");
                t.setNumber(j+1);
            }else if (i == 2){
                // black
                t.setColor("black");
                t.setNumber(j+1);
            }else if (i == 3){
                // red
                t.setColor("red");
                t.setNumber(j+1);
            }
            // push the tas to vector
            all_tas.push_back(t);
            
            if(doubled == true){
                j++;
                doubled = false;
            }else{
                doubled = true;
            }
        }
    }
    // push sahte okeys to vector.
    Tas sahte1,sahte2;
    sahte1.setColor("none");sahte1.setNumber(0);sahte2.setColor("none"); sahte2.setNumber(0);
    // sahte okeys will be represented none as their color and 0 as their number.
    all_tas.push_back(sahte1);
    all_tas.push_back(sahte2);
}

int random_number_generator(int beginning, int end){
    random_device dev;
    mt19937 rgn(dev());
    uniform_int_distribution<mt19937::result_type> dist6(beginning,end);
    return dist6(rgn);

}

void mix_tas(vector<Tas> &all_tas){

    int index1, index2;
    Tas temp;
    for(int i = 0; i < 10000; i++){
        index1 = random_number_generator(0, 105);
        index2 = random_number_generator(0, 105);
        temp.setColor(all_tas[index1].getColor());
        temp.setNumber(all_tas[index1].getNumber());
        all_tas[index1].setColor(all_tas[index2].getColor());
        all_tas[index1].setNumber(all_tas[index2].getNumber());
        all_tas[index2].setColor(temp.getColor());
        all_tas[index2].setNumber(temp.getNumber());
    }
}

void distribute_tases(int number_of_players, vector<Tas> &all_tas, vector<Player> &players ){
    // select first player randomly
    unsigned int selected_player = random_number_generator(0, number_of_players-1);
    unsigned int tas_number_to_be_distributed;
    unsigned int all_tas_intex = 0;
    for(int i = 0; i < 4; i++){
        Player p;
        p.setPlayerID(i);
        if(i == selected_player){
            tas_number_to_be_distributed = 15;
            while (tas_number_to_be_distributed != 0) {
                p.addTasToHand(all_tas[all_tas_intex]);
                tas_number_to_be_distributed--;
                all_tas_intex++;
            }
        }else{
            tas_number_to_be_distributed = 14;
            while (tas_number_to_be_distributed != 0) {
                p.addTasToHand(all_tas[all_tas_intex]);
                tas_number_to_be_distributed--;
                all_tas_intex++;
            }
        }
        players.push_back(p);
    }
}

bool find_If_Tas_Exists(string color, unsigned int number, vector<Tas> &hand, int handSize, bool isDifferentColor){
    for(int i = 0; i < handSize; i++){
        if(!isDifferentColor && hand[i].getColor() == color && hand[i].getNumber() == number){
            return true;
        }
        if(isDifferentColor && hand[i].getColor() != color && hand[i].getNumber() == number){
            return true;
        }
    }
    return false;
}


unsigned int find_number_tases_which_are_not_useful(Player &p){
    int number_of_tas = p.getPlayerHand().size();
    vector<Tas> playerHand = p.getPlayerHand();
    unsigned int not_useful_tas_number = 0;
    for(int i = 0; i < number_of_tas; i++){
       
        // find if there is a sequence
        if(find_If_Tas_Exists(playerHand[i].getColor(), playerHand[i].getNumber()-1, playerHand, number_of_tas, false)){
            continue;
        }
        if(find_If_Tas_Exists(playerHand[i].getColor(), playerHand[i].getNumber()+1, playerHand, number_of_tas, false)){
            continue;
        }
        
        // find if there are same number but different colors
        if(find_If_Tas_Exists(playerHand[i].getColor(), playerHand[i].getNumber(), playerHand, number_of_tas, true)){
            continue;
        }
        not_useful_tas_number++;
    }
    return not_useful_tas_number;
}
void find_winner(vector<Player> &players ){
    unsigned int winner_index;
    int not_useful_tas_amount = INT_MAX;
    for(int i = 0; i < 4; i++){
        if(not_useful_tas_amount > find_number_tases_which_are_not_useful(players[i])){
            winner_index = i;
            not_useful_tas_amount = find_number_tases_which_are_not_useful(players[i]);
        }
    }
    cout <<"Winner is the player at index: " << winner_index <<endl;
}
int main(int argc, const char * argv[]) {
    vector<Tas> all_tas;
    vector<Player> players;
    const int number_of_players = 4;
    Tas gosterge;
    Tas *okey = new Tas();
    
    // Total tas amount = 106. There are only 2 of the same tas.
    // Load all the tas to a an array.
    set_all_tas(all_tas);
    // Mix their order in the array.
    mix_tas(all_tas);
    // Select an gosterge tas
    gosterge = all_tas[random_number_generator(0, 105)];
    // Specify the okey tas.
    okey->setColor(gosterge.getColor());
    okey->setNumber(gosterge.getNumber() + 1);
    // Distribute tases. One player gets 15 others get only 14.
    distribute_tases(number_of_players, all_tas, players);
    // Check hands and print winner's name
    find_winner(players);
    
    
    return 0;
}
