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

    int maxHeapSize = jsonInput["metadata"]["maxHeapSize"];            // metadata
    int numOperations = jsonInput["metadata"]["numOperations"];

    // create a priority queue object
    PriorityQueue pq = PriorityQueue(maxHeapSize);              // creates new priority queue

    for(auto elem: jsonInput){
        std::cout << elem << std::endl;
        try{
            double key = elem["key"];                           // insert code here
            pq.insert(key);
        }
        catch(...){
            try{
                if (elem["operation"] == "removeMin"){          // remove min code here
                    pq.removeMin();
                }
            }
            catch(...){
                continue;
            }
        }
    }

    pq.JSON();

    json_file.close();

    return 0;
}
