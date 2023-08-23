#include <iostream>
#include<string>
#include <vector>

using namespace std;

class HashTable{
    private:
        static const unsigned int H_max = 125;
        string table[H_max];
        int total_elements;

        // Hash function to calculate hash for a value:
        int getHash(int key){
            return key % 1900;
        }

    public:
        // Constructor to create a hash table with 'n' indices:
        HashTable(int n){
            total_elements = n;
        }

        HashTable(){
            total_elements = 125;
        }

        // Insert data in the hash table:
        void insertElement(string value, int keyIndex){
            table[getHash(keyIndex)] = value;
        }

        void show(std::string playerName)const{
            // Traverse each index:
            for(int i = 0; i < total_elements; i++){
                if(!(table[i].empty())){
                    cout << playerName << " played for the " << (i+1900) << " "  << table[i] << endl;
                }
            }
        }

        void showTeam(std::string playerName, std::string teamName)const{

            bool playedinteam = false;

            for(int i = 0; i < total_elements; i++){
                if(!(table[i].empty())){
                    if (table[i] == teamName){
                        cout << playerName << " played for the " << (i+1900) << " " << table[i] << endl;
                        playedinteam = true;
                    }
                }
            }
            if(playedinteam == false)
                cout << playerName << " has never played for the " << teamName << endl;
        }

        //count how many years a player played in a team
        int countYears(std::string teamName)const{
            
            int count = 0; 

            for(int i = 0; i < total_elements; i++){
                if(!(table[i].empty())){
                    if (table[i] == teamName){
                        count++;
                    }
                }
            }

            return count;
        }

    std::string getValue(int val){
        return table[val];
    }
    
};