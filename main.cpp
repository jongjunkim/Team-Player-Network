#include <iostream>
#include <fstream>
#include<string>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <cstdlib>
#include "Player.h"
#include "Queue.h"
#include <vector>
#include <sstream>
#include "Graph.h"

using namespace std;

void loadPlayers(std::string &name, std::string &team, int &year, vector<Player> &vec_p, ifstream &inFS, std::string input_string, std::string p){
    int line = 0;
    int n = 0;
    int numIn = 1;
    bool badInput = false;

    while(std::getline(inFS, input_string)){ //reading while not end of the file
        line++;
        std::stringstream ss(input_string);
        bool name_in_use = false;
        while(getline(ss, input_string, ',')){
            if (numIn == 1){
                name = input_string;
                numIn++;
            }
            else if (numIn == 2){
                team = input_string;
                numIn++;
            }
            else{

                for(unsigned int i = 0; i<input_string.length(); i++){
                     if(isdigit(input_string[i]) == false && name == p){
                         cout << "Year is not an integer" << endl;
                         exit(1);
                     }
                     else if(isdigit(input_string[i]) == false){
                         badInput = true;
                         numIn = 1;
                         break;
                     }
                 }

                 if(badInput == true){
                     badInput = false;
                     continue;
                 }

                year = stoi(input_string);
                //check if player exist or not
                //if exist then only add the team and year
                    //need a function to add team and year to hashtable
                for (unsigned int i = 0; i < vec_p.size(); i++){
                        if (vec_p.at(i).getName() == name){
                            name_in_use = true;
                            vec_p.at(i).addHash(team, year);
                        }
                    }
                if (!(name_in_use)){
                    Player newPlayer = Player(name, team, year, n);
                    newPlayer.addHash(team, year);
                    vec_p.push_back(newPlayer);
                    n++;
                }
                numIn = 1;
            }

        }
    }
}

int main(int argc, char** argv) {
    int opt;
    int argNum = 2;
    ifstream inFS;

    std::string name;
    std::string team;
    std::string input_string;
    int year;
    
	
	string inputfile = "";
    string playerOne = "";
    string playerTwo = "";
    string teamname = "";
    vector<Player> vec_p;

    bool have_inputfile = false;
    bool player_one_input = false;
    bool player_two_input = false;
    bool teamname_input = false;

    Graph graph;
	
	while ( (opt = getopt(argc, argv, "i:s:d:t:")) != -1 ) { 
		switch ( opt ) {
			case 'i':
					inputfile = argv[argNum];
                    inFS.open(inputfile); //opening input file
                    if(inFS.fail()){
                        cout << "File doesn't exist in this repository" << endl;
                    }
                    have_inputfile = true;
                    argNum+=2;
				break;
			case 's':
					playerOne = argv[argNum];
                    player_one_input = true;
                    argNum+=2;
				break;
            case 'd':
					playerTwo = argv[argNum];
                    player_two_input = true;
                    argNum+=2;
				break;
        	case 't':
					teamname = argv[argNum];
                    teamname_input = true;
                    argNum+=2;
				break;
			case '?':  // unknown option...
					cerr << "Unknown option: '" << char(optopt) << "'!" << endl;
				break;
		}
	}

    //case 0a
    if (have_inputfile == false){
        cout << "Usage: " << endl;
        cout << "\t" << argv[0] << " -i <input-filename> [-s <player1-name>]" << endl;
        inFS.close();
        return 0;
    }

    //case 0b
    else if((player_one_input == false) && (player_two_input == true)){
        cout << "If you specify <player2-name> with -d, then you must specify <player1-name> with -s." << endl;
        cout << "Usage: " << endl;
        cout << "\t" << argv[0] << " -i <input-filename> [-s <player1-name>]" << endl;
        inFS.close();
        return 0;  
    }

    //case 1
    else if((have_inputfile == true) && (player_one_input == false) && (player_two_input == false) && (teamname_input == false)){
        //echo data in the inputfile
        while(std::getline(inFS, input_string)){
            cout << input_string << endl;
        }
        inFS.close();
        return 0;
    }

    //make player objects out of the inputfile
    loadPlayers(name, team, year, vec_p, inFS, input_string, playerOne);
    
    //case 2a
    if((player_one_input == true) && (player_two_input == false) && (teamname_input == false)){

        int find = -1;

        for (unsigned int i = 0; i < vec_p.size(); i++){
            if (vec_p.at(i).getName() == playerOne){
                find = i;
            }
        }

        if(find == -1){
            cout << playerOne << " does not appear in the input file" << endl;
            exit(1);
        }else{
            vec_p.at(find).show(playerOne);
        }
    }

    //case 2b
    else if((player_one_input == true) && (player_two_input == false) && (teamname_input == true)){
        //list the year player1 played on the teamname_input
        int find = -1;

        for (unsigned int i = 0; i < vec_p.size(); i++){
            if (vec_p.at(i).getName() == playerOne){
                find = i;
            }
        }

        if(find == -1){
            cout << playerOne << " does not appear in the input file" << endl;
            exit(1);
        }else{
            vec_p.at(find).showTeam(playerOne, teamname);
        }
    }

    //case 3
    else if((player_one_input == false) && (teamname_input == true)){
        //list all the players in the team 
        //player who have played for the most years are listed first
        //if players played the same number of year list them alphabecally

        vector<Player> num_years;
        vector<Player> sorted;

        for(unsigned int i = 0; i< vec_p.size(); i++){
            if(vec_p.at(i).getPlayers(teamname).getNum_of_years() != 0){
                num_years.push_back(vec_p.at(i).getPlayers(teamname));
            }
        }

        unsigned int size = num_years.size();

        if(size == 0){
            cout << teamname << " doesn't exit in the input file" << endl;
            exit(1);
        }
        

        while(sorted.size() != size){
            int priority = num_years.at(0).getNum_of_years();
            int index = 0;
            for(unsigned int i = 1; i<num_years.size(); i++){
                if(priority < num_years.at(i).getNum_of_years()){
                    priority = num_years.at(i).getNum_of_years();
                    index = i;
                }else if(priority == num_years.at(i).getNum_of_years()){
                    int compare = num_years.at(index).getName().compare(num_years.at(i).getName());
                    if (compare > 0)
                        index = i;
                }
            }
            sorted.push_back(num_years.at(index));
            num_years.erase(num_years.begin() + index);
        }

        for(unsigned int i = 0; i<sorted.size(); i++){
            cout << sorted.at(i).getName() << " played " << sorted.at(i).getNum_of_years() 
            << " years for the " << teamname << endl;
        }  
    }

    //case 4 -- needs implementation of BST and queue
    else if ((player_one_input == true) && (player_two_input == true)){
        //print shortest teammate path
        int firstPlayer;
        int secondPlayer;
        bool exist1 = false;
        bool exist2 = false;

        for(unsigned int i = 0; i<vec_p.size(); i++){
            if(vec_p.at(i).getName() == playerOne){
                firstPlayer = i;
                exist1 = true;
            }
            if(vec_p.at(i).getName() == playerTwo){
                secondPlayer =i;
                exist2 = true;
            }
        }   

        if(exist1 == false){
            cout << playerOne << " doesn't exist" << endl;
            exit(1);
        }else if(exist2 == false){
            cout << playerTwo << " doesn't exist" << endl;
            exit(1); 
        }else{
            //case 4a
            if(teamname_input == false){
                //shortest path may include any team
                graph.createGraph(vec_p, playerOne, playerTwo);    
                graph.printShortDistance(vec_p.at(firstPlayer), vec_p.at(secondPlayer));
            }

            //case 4b
            else{
                //path can only consider times when players are teammate in the specified team 
                graph.createGraphWT(vec_p, playerOne, playerTwo, teamname);    
                graph.printShortDistance(vec_p.at(firstPlayer), vec_p.at(secondPlayer));
            }
        }
    }
    inFS.close();
}