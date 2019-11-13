#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include "priorityqueue.h"

int main(int argc, char** argv) {
    nlohmann::json jsonInput;           // creates input object
    nlohmann::json jsonOutput;          // creates output object

    std::string json_name = argv[2];    // opens argument file
    std::ifstream json_file;
    json_file.open(json_name);

    json_file >> jsonInput;             // reads json data into object

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


//    std::cout << jsonOutput.dump(2) << std::endl;                           // outputs content to screen
//
//    std::ofstream outFile;                                                  // creates file of output for testing purposes
//    outFile.open("SV_results.json", std::ios::out);
//    outFile << jsonOutput.dump(2);
//
//    jsonInput.close();
//    outFile.close();

    return 0;
}
