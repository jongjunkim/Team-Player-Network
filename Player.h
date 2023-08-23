#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Hashtable.cpp"

using namespace std;
class Player {
   public:
      static const unsigned int H_max = 125;
      Player(string name, string team, unsigned int year, int n);
      Player();
      void printPlayer1(string inputfile, string player);
      std::string getName() const {return player_name;};
      void addHash(std::string team, int year);
      void show(std::string playerName) const;
      void showTeam(std::string playerName, std::string teamName) const;
      std::string getValue(int val);

      //for case 3
      Player(int years, string name, string team);
      Player getPlayers(std::string teamName);
      Player getName(std::string player_name);
      int getNum_of_years(){ return number_of_years; }

      //for BFS
      bool getVisited(){ return visited;}
      void setVisited(bool visit){visited =visit; }
      int getVnum(){return verticeNum;}
      void setVnum(int number){verticeNum = number;}
      string getTeamname(){return team_name; }
      int getYears(){return year;}


   private:
      string player_name;
      string team_name;
      unsigned int year;
      HashTable ht;
      unsigned int number_of_years;
            

      //graph
      bool visited;
      int verticeNum;
      
};

#endif
