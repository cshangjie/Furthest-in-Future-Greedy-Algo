#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>

// Returns the element to be removed from the pages.
int findFurthest(int currentRequestIndex, std::vector<int> requestSequenceVector, std::unordered_set<int> pages){
    int ret = INT_MIN;
    int furthestOccurenceIndex = currentRequestIndex + 1;
    for(int element: pages){
        int j = 0;
        // Iterate over remaining requests
        for (j = currentRequestIndex + 1; j < requestSequenceVector.size(); j++){
            if (element == requestSequenceVector[j]){
                if(j > furthestOccurenceIndex){
                    furthestOccurenceIndex = j;
                    ret = element;
                }
                break;
            }
        }
        // if the elem is not found in a future request, return it
        if(j == requestSequenceVector.size()){
            return element;
        }
    }
    return (ret == INT_MIN) ?  INT_MIN : ret;
}

int main()
{
    int numInstances;
    std::cin >> numInstances;
    std::string ans = "";
    while (numInstances--)
    {
        // number of pages in each cache
        int cacheNumPages; 
        std::cin >> cacheNumPages;

        // number of requests in a sequence (space delimited)
        int requestSequenceLength; 
        std::cin >> requestSequenceLength;
        std::cout << requestSequenceLength << '\n';

        // request sequence string
        std::string reqSeqStr; 
        std::getline(std::cin >> std::ws, reqSeqStr);

        // populating vec representation of requests
        std::string tmpStr;
        std::stringstream requestInputStream(reqSeqStr);
        std::unordered_set<int> pages;

        std::vector<int> requestSequenceVector;

        int index = 0;
        while(getline(requestInputStream, tmpStr, ' ')){
            requestSequenceVector.push_back(stoi(tmpStr));
            index++;
        }
        for(int request: requestSequenceVector){
            std::cout << request << ' ';
        }
        std::cout << '\n';


        int pageFaultCount = 0;
        for(int i = 0; i < requestSequenceLength; i++){
            //hit
            if(pages.find(requestSequenceVector[i]) != pages.end()){
                continue;
            }
            // miss
            else{          
                // if there is space in the pages
                if(pages.size() < cacheNumPages){
                    pages.insert(requestSequenceVector[i]);
                    pageFaultCount++;
                    // std::cout << "Empty Page Fault on request#: " << i << '\n';
                }
                // no space, find furthest in future and evict
                else {
                    int toBeRemoved = findFurthest(i, requestSequenceVector, pages);
                    if (toBeRemoved == INT_MIN){
                        pages.erase(pages.begin());
                    }
                    else{
                        pages.erase(toBeRemoved);
                    }
                    pages.insert(requestSequenceVector[i]);
                    pageFaultCount++;
                    // std::cout << "Eviction Page Fault on request#: " << i << '\n';
                }
            }
        }
        std::cout << pageFaultCount;
    }
}