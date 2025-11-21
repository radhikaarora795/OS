#include <iostream>
#include <vector>
using namespace std;

void firstFit(vector<int> blockSize,vector<int> processSize){
    int n=processSize.size();
    int m=blockSize.size();
    vector<int> allocation(n,-1); // initialize allocation array to -1 (not allocated)

    // pick each process and find first block that is large enough
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(blockSize[j]>=processSize[i]){
                allocation[i]=j;    // allocate block j to process i
                blockSize[j]-=processSize[i];   // reduce remaining memory 
                break;
            }
        }
    }
    cout<<"First Fit: "<<endl;
    for(int i=0;i<n;i++){
        if(allocation[i] != -1){
            cout<<"Process "<<i+1<<" allocated to Block "<<allocation[i]+1<<endl;
        }
        else{
            cout<<"Process "<<i+1<<" not allocated"<<endl;
        }
    }
}

void bestFit(vector<int> blockSize,vector<int> processSize){
    int n=processSize.size();
    int m=blockSize.size();
    vector<int> allocation(n,-1); // initialize allocation array to -1 (not allocated)

    for(int i=0;i<n;i++){
        int bestIndex=-1;   // no block selected yet
        for(int j=0;j<m;j++){
            // check if current block can fit the process
            if(blockSize[j] >= processSize[i]){ 
                // find the smallest available block that can fit the process.
                if(bestIndex == -1 || blockSize[j]<blockSize[bestIndex]){
                    bestIndex=j;
                }
            }
        }
        // if found suitable block
        if(bestIndex != -1){
            allocation[i]=bestIndex;
            blockSize[bestIndex]-=processSize[i];
        }
    }
    cout<<"Best Fit: "<<endl;
    for(int i=0;i<n;i++){
        if(allocation[i] != -1){
            cout<<"Process "<<i+1<<" allocated to Block "<<allocation[i]+1<<endl;
        }
        else{
            cout<<"Process "<<i+1<<" not allocated"<<endl;
        }
    }
}

void worstFit(vector<int> blockSize,vector<int> processSize){
    int n=processSize.size();
    int m=blockSize.size();
    vector<int> allocation(n,-1); // initialize allocation array to -1 (not allocated)

    // pick each process and find the largest block that fits
    for(int i=0;i<n;i++){
        int worstIndex=-1;  // stores index of the largest suitable block
        for(int j=0;j<m;j++){
            // check if current block can fit this process
            if(blockSize[j] >= processSize[i]){
                if(worstIndex == -1 || blockSize[j]>blockSize[worstIndex]){
                    worstIndex=j;
                }
            }
        }
        // if found suitable block
        if(worstIndex != -1){
            allocation[i]=worstIndex;
            blockSize[worstIndex]-=processSize[i];
        }
    }
    cout<<"Worst Fit: "<<endl;
    for(int i=0;i<n;i++){
        if(allocation[i] != -1){
            cout<<"Process "<<i+1<<" allocated to Block "<<allocation[i]+1<<endl;
        }
        else{
            cout<<"Process "<<i+1<<" not allocated"<<endl;
        }
    }
}

int main() {
    int m,n;
    cout<<"Enter number of memory blocks: ";
    cin>>m;
    vector<int> blockSize(m);
    for(int i=0;i<m;i++){
        cout<<"Enter memory size of block "<<i+1<<": ";
        cin>>blockSize[i];
    }

    cout<<"Enter number of processes: ";
    cin>>n;
    vector<int> processSize(n);
    for(int i=0;i<n;i++){
        cout<<"Enter memory size required for process "<<i+1<<": ";
        cin>>processSize[i];
    }

    firstFit(blockSize,processSize);
    bestFit(blockSize,processSize);
    worstFit(blockSize,processSize);
    
    return 0;
}