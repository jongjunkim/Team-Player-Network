# cs240-spring2022-cp5-group-21
cs240-spring2022-cp5-group-21 created by GitHub Classroom

**CASE 0a and 0b**

Analysis:  
O(1)  

Description:  
Report the output error message with is constant time  
  
  
**CASE 1**  

Analysis:  
O(L)  
L = lines of input file  

Description:  
The while loop reads each line of the input file   

**CASE 2a**  
   
Analysis:  
P = number of players  
H_max = size of hash table  
O(P(H_max))  

Description:    
The number of time in the for loop is determined by the number of players(P). Inside the loop, the show() function loops through each element in the hashtable determined by its size (H_max).  

Thus, the runtime complexity is O(P(H_max))  
  
  
**CASE 2b**  

Analysis:  
O(P(H_max))  
P = number of players  
H_max = size of hash table   
 
Description:  
The for loop consist of size of P. Inside the loop, the showTeam() function loops through each element in the hashtable determined by its size (H_max).  

Thus, the runtime complexity is O(P(H_max))  
  
  
**CASE 3**  

Analysis:  
If P >= H_max: O(P^2)  
Else: O(P(H_max))  
P = number of players  
H_max = size of hash table  

Description:  
The worst case is all the players played in the team.  

The for loop consist size of P; In the loop, the getPlayers() function will call the countYears function which has a for loop with the max hash table size (H_Max). In addition, because the if statement is true, which getPlayers() function is called again. So the runtime complexity is O(P(2H_max))  

Then to sorted the players by the year played in team, there is a while loop with size of P. There is a for loop within the while loop of size P, After each while loop, the size of the for loop will decrease by 1. The runtime complexity is O((P(P-1))/2).  

Finally, there is a for loop to print out the sorted player. The runtime complexity is O(P).  
Overall runtime complexity is O(P(2H_max)) + O((P^2-P)/2) + O(P) = O(P^2) if number of players is greater than H_max and O(P(H_max)) if less than H_max.  
  
  
**CASE 4a and 4b**  

Analysis:  
O(P^3)  
P = number of players  

Description:  
To create the graph (createGraph() and createGraphWT() function), the first loop with size of P is use to set the player's verticies number and push them into a vector to represent the vertices. Next, there is a three nested for loops it to check if each player is connected to every other player by using the hashtable. The checking part to check wheather or not the players are connected is constant time since we are using a hashtable. If they are connected (the index and teamname are the same) then we add and edge between the two players (addEdge() function with adjacency list).
The runtime complexity is O(H_max(P)(P-1)/2).  

To find and print the short distance we use a breath first search to detemine whether the path exist, if it does then print the shortest path. For the breath first search, the number of vertices and the size of each adjacency array is same as the number of players P. The first two nested for loop is to find the start and end vertice which runtime complexity is P^2. For the while loop, the size of while loop with worst case is the number of players P and there consist a for loop inside the while loop with size of P. The runtime complexity for the while loop is P^2. So The runtime complexity for the breath first search is O(2(P^2)).  

To print the shortest path, a nested nested loop is used. The size of while loop is P and for each while loop the size of for loop increases by 1. Thus, the runtime complexity is O((P(P^2-P))/2) = O((P^3-P^2)/2)  

Overall runtime complexity is O(H_max(P)(P-1)/2) + O(2(P^2)) + O((P^3-P^2)/2) = O(P^3)  