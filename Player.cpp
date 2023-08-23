#include <iostream>
#include <stdlib.h>
#include <string>
#include "Player.h"
// #include "Hashtable.cpp"

using namespace std;

Player::Player(string name, string team, unsigned int yearIn, int n) {
    player_name = name;
    team_name = team;
    year = yearIn;
    ht = HashTable(H_max);
    visited = false;
    verticeNum= n; 
}
Player::Player() {
	player_name = "";
    team_name = "";
    year = -1;
    ht = HashTable(H_max);
}

void Player::addHash(std::string team, int year){
    ht.insertElement(team, year);
}

void Player::show(std::string playerName)const{
    ht.show(playerName);
}

void Player::showTeam(std::string playerName, std::string teamName)const{
    ht.showTeam(playerName, teamName);
}

//for case 3 
Player::Player(int years, string name, string team){
    number_of_years = years;
    player_name = name;
    team_name = team;

}

Player Player::getPlayers(std::string teamName){
    int years = ht.countYears(teamName);

    return Player(years, player_name, teamName);
    
}

std::string Player::getValue(int val){
    return ht.getValue(val);
}
