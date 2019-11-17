#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include "priorityqueue.h"

int main(int argc, char** argv) {
    nlohmann::json jsonInput;   // creates input object

    std::ifstream json_file;    // opens argument file
    json_file.open(argv[2]);

    if (json_file.is_open()) {
        json_file >> jsonInput;         // makes sure file is open, then reads json data into object
    }
    else{
        std::cout << "Error: File Not Open. Exiting..." << std::endl;
        return 0;
    }

    int maxHeapSize = jsonInput["metadata"]["maxHeapSize"];            // metadata
    int numOperations = jsonInput["metadata"]["numOperations"];

    PriorityQueue pq = PriorityQueue(maxHeapSize);    // create a priority queue object

    for(auto elem: jsonInput){
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

    nlohmann::json result = pq.JSON();
    result["metadata"]["maxHeapSize"] = maxHeapSize;
    result["metadata"]["numOperations"] = numOperations;
    std::cout << result.dump(2);

    json_file.close();

    return 0;
}
