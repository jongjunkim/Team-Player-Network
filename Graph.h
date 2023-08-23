#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Queue.h"
#include "Player.h"
// #include "Edge.h"

using namespace std;
class Graph {
   public:
      const unsigned int H_max = 125;
      bool BFS(Player startVertex,Player endVertex);
      void createGraph(vector<Player> pv, string p1, string p2);
      void createGraphWT(vector<Player> pv, string p1, string p2, string teamname);
      void addEdge(int i, int k, Player one, Player two, int j);
      void displayAdjList();

      bool checkVisited(Player p1);
      void printShortDistance(Player start, Player end);
      void printTeamYear(string p1, string p2);
      ~Graph();

   private:
      vector<Player> *adj; 
      vector<int> *loc; 

      vector<Player> vertices;
      vector<int> distance;
      vector<int> pred;
      int numVertices;
      int start, end;
};

#endif