#include <iostream>
#include <vector>
using namespace std;

void bankersAlgorithm(int n, int m, vector<vector<int>>& allocation, vector<vector<int>> max, vector<int> available){
    vector<vector<int>> need(n,vector<int>(m));
    cout<<"Need Matrix: "<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j]=max[i][j]-allocation[i][j];
            cout<<need[i][j]<<" ";
        }
        cout<<endl;
    }

    vector<int> finish(n,0);
    vector<int> safeSequence;
    
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            if(finish[i] == 0){
                bool possible=true;
                for(int j=0;j<m;j++){
                    if(need[i][j] > available[j]){
                        possible=false;
                        break;
                    }
                }
                if(possible){
                    for(int j=0;j<m;j++){
                        available[j]+=allocation[i][j];
                    }
                    safeSequence.push_back(i);
                    finish[i]=1;
                }
            }
        }
    }
    bool safe=true;
    for(int i=0;i<n;i++){
        if(finish[i] == 0){
            safe=false;
        }
    }
    if(safe){
        cout<<"System is in Safe State"<<endl;
        cout<<"safe Sequence: ";
        for(int p:safeSequence){
            cout<<"P"<<p<<" ";
        }
    }
    else{
        cout<<"System is Not in Safe State"<<endl;
    }
}

int main() {
    int n,m;
    cout<<"Enter number of processes: ";
    cin>>n;
    cout<<"Enter number of resource types: ";
    cin>>m;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<int> available(m);

    cout<<"Enter Allocation Matrix: "<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>allocation[i][j];
        }
    }
    cout<<"Enter Max Matrix: "<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>max[i][j];
        }
    }
    cout<<"Enter Available Matrix: "<<endl;
    for(int i=0;i<m;i++){
        cin>>available[i];
    }

    bankersAlgorithm(n,m,allocation,max,available);
    
    return 0;
}