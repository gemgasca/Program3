#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include "priorityqueue.h"

int main(int argc, char** argv) {
    nlohmann::json jsonInput;           // creates input object

    std::string json_name = argv[2];    // opens argument file
    std::ifstream json_file;
    json_file.open(json_name);

    if (json_file.is_open()) {
        json_file >> jsonInput;             // makes sure file is open, then reads json data into object
    }
    else{
        std::cout << "Error: File Not Open. Exiting..." << std::endl;
        return 0;
    }

    int numPlayers = jsonInput["metadata"]["numPlayers"];

    // create a priority queue object
    PriorityQueue pq = PriorityQueue(1000);

    for (auto elem : jsonInput["teamStats"]){                    // builds priority queue
//        std::cout << elem << std::endl;
        try{
            int player1 = elem["playerOne"];                    // value 1
            int player2 = elem["playerTwo"];                    // value 2
            double winPercent = elem["winPercentage"];          // key
            double diff = abs(50-winPercent);                      // calculates difference from 50, so closest will be at root of min heap
            std::pair<Key, Value> kv = std::make_pair(diff, std::make_pair(player1, player2));      // makes pair
            pq.insert(kv);
        }
        catch(...){
            continue;
        }
    }

    nlohmann::json result;          // output

    std::vector<std::vector<int>> allTeams;

    while(pq.size() > 0){
        KeyValuePair min = pq.removeMin();  // gets team
        Value minVals = min.second;
        pq.removeDupPlayers(minVals);       // gets rid of player duplicates

        std::vector<int> team;              // makes vector of both player ID's
        team.push_back(minVals.first);
        team.push_back(minVals.second);

        allTeams.push_back(team);       // adds each team to vector of teams
    }

    result["teams"] = allTeams;         // formats json
    std::cout << result.dump(2);        // prints results to screen

    json_file.close();
    return 0;
}
