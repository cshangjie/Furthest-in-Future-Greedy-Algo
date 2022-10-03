#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <unordered_set>
using namespace std;

int main()
{
    int numInstances;
    cin >> numInstances;
    while (numInstances--)
    {
        // number of pages in each cache
        int cacheNumPages; 
        cin >> cacheNumPages;

        // number of requests in a sequence (space delimited)
        int requestSequenceLength; 
        cin >> requestSequenceLength;

        // request sequence string
        string reqSeqStr; 
        getline(cin >> ws, reqSeqStr);

        // populating vec representation of requests
        string tmpStr;
        stringstream ss(reqSeqStr);
        unordered_set<int> requests;

        vector<int> reqSeqVec;

        while(getline(ss, tmpStr, ' ')){
            reqSeqVec.push_back(stoi(tmpStr));
        }

        int pageFaultCount = 0;
        // iterate over requests
        for (int elem: reqSeqVec){
            // if elem isn't in page table
            if(requests.find(elem) == requests.end()){
                // if table size is less than cacheNumPages, insert elem into the page table
                if(requests.size() < cacheNumPages){
                    requests.insert(elem);
                }
                // eviction time + increment page fault counter
                else{
                    // TODO eviction stuff
                    pageFaultCount++;
                }
            }
        }
    }
}