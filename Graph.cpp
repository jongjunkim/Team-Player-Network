#include <iostream>
#include <stdlib.h>
#include <string>
#include "Graph.h"
#include <climits>
#include "Queue.h"

void Graph::createGraph(vector<Player> pv, string p1, string p2){
    adj = new vector<Player>[pv.size()];
    loc = new vector<int>[pv.size()];

    for(unsigned int i = 0; i<pv.size(); i++){
        vertices.push_back(pv.at(i));
        pv.at(i).setVnum(i);
    }

    Player from;
    Player to;
    for(unsigned int i = 0; i < pv.size(); i++){ 
        for(unsigned int k = i + 1; k < pv.size(); k++){ 
            for(unsigned int j = 0; j < H_max; j++){
                 if (pv[i].getName() == p1){
                     from = pv[i];
                 }
                 if (pv[k].getName() == p2){
                     to = pv[k];
                 }
                 if((pv[i].getValue(j) != "")  && (pv[i].getValue(j) == pv[k].getValue(j))){
                    addEdge(i,k,pv[i], pv[k], j);
                }
            }
        }
    }
    numVertices=pv.size();
}

void Graph::createGraphWT(vector<Player> pv, string p1, string p2, string teamname){

    adj = new vector<Player>[pv.size()];
    loc = new vector<int>[pv.size()];


    for(unsigned int i = 0; i<pv.size(); i++){
        vertices.push_back(pv.at(i));
        pv.at(i).setVnum(i);
    }

    Player from;
    Player to;
    for(unsigned int i = 0; i < pv.size(); i++){
        for(unsigned int k = i + 1; k < pv.size(); k++){
            for(unsigned int j = 0; j < H_max; j++){
                 if (pv[i].getName() == p1){
                     from = pv[i];
                 }
                 if (pv[k].getName() == p2){
                     to = pv[k];
                 }
                 if((pv[i].getValue(j) != "")  && (pv[i].getValue(j) == pv[k].getValue(j)) && (pv[i].getValue(j) == teamname)){
                    addEdge(i,k,pv[i], pv[k], j);
                }
            }
        }
    }
    numVertices=pv.size();
}

void Graph::addEdge(int i,int k, Player one, Player two, int j){
     adj[i].push_back(two);
     adj[k].push_back(one);
     loc[i].push_back(j);
     loc[k].push_back(j);
}



void Graph::displayAdjList(){
    for (int d = 0; d < numVertices; ++d) {
        cout << "\n Vertex "<< d << ":";
        cout << vertices.at(d).getName();
        for (unsigned int x = 0; x < adj[d].size(); ++x){
            cout << "-> " << adj[d][x].getName() << " " << adj[d][x].getValue(loc[d][x]) << " " << (loc[d][x] + 1900)<< endl;
        }
        printf("\n");
    }
}


bool Graph::BFS(Player startVertice, Player endVertice){
    
    Queue q;
    start= -1;
    end= -1;
    distance.resize(numVertices, 0);
    pred.resize(numVertices, -1);

    for(int d = 0; d<numVertices; d++){
        for(unsigned int x = 0; x < adj[d].size(); x++){
            if(adj[d][x].getName() == startVertice.getName()){
                start = adj[d][x].getVnum();
                vertices.at(start).setVisited(true);
                q.enQueue(adj[d][x]);
                distance[startVertice.getVnum()]  = 0; 
            }
            if(adj[d][x].getName() == endVertice.getName()){
                end = adj[d][x].getVnum();
            }
        }
    }

    while(!q.empty()){

        Player current = q.getFrontPlayer();

        start = q.getFrontPlayer().getVnum();
        q.deQueue();

        for(unsigned int k = 0 ; k < adj[start].size(); ++k){
            if(!checkVisited(adj[start][k])){
                vertices.at((adj[start][k]).getVnum()).setVisited(true);
                distance.at((adj[start][k]).getVnum()) = distance[start] + 1;
                pred.at((adj[start][k]).getVnum()) = start;
                q.enQueue((adj[start][k]));
            }
        }
    }

    if(end == -1 || distance.at(end) == 0){
        cout << "No teammate path exists between " << startVertice.getName() << " and " <<  endVertice.getName() << endl;
        return false;
    }else{
        cout << endVertice.getName()  << "'s " << startVertice.getName() << " number is " << distance.at(end) << endl;
        return true;
    }

}

bool Graph::checkVisited(Player p1){

    for(unsigned int i = 0; i<vertices.size(); i++){
        if(vertices.at(i).getName() == p1.getName())
            if(vertices.at(i).getVisited() == true){
                return true;
            }
    }
    return false;
}


void Graph::printShortDistance(Player startPlayer, Player endPlayer){
    
    if(BFS(startPlayer,endPlayer)==false){
        return;
    }

    vector<Player> path;
    vector<int> yearPath;
    path.push_back(endPlayer);
    
    while(pred.at(end) != -1){ 
        path.push_back(vertices.at(pred[end]));
        for(int i = path.size() - 1 ;i>=1; i--){
            for (unsigned int x = 0; x < adj[vertices.at(pred[end]).getVnum()].size(); ++x){
                if (adj[vertices.at(pred[end]).getVnum()][x].getName()== path[i-1].getName()){
                    yearPath.push_back(loc[vertices.at(pred[end]).getVnum()][x]);
                }
            }
        }
        end = pred[end];
    }

    int ynum = yearPath.size() - 1;
    for(int i = path.size() - 1;i>=1; i--){
        cout << path[i].getName() << " played with " << path[i-1].getName() << " on the " << yearPath[ynum]+1900 << " " << path[i].getValue(yearPath[ynum]) << endl;
        ynum--;
    }

    
}

Graph::~Graph(){
    delete [] adj;
    delete [] loc;
}
