#include <iostream> 
#include <math>
using namespace std;

int main(){
    int n, k1, k2;
    bool edges[n][n];
    vector<vector<int>> clauses;
    //variables k1*n, k2*n
    for(int i=0;i<k1;i++){
        vector<int> c;
        for(int j=0;j<n;j++){
            c.push_back(j+1+k1*i);
        }
        c.push_back(0);
        clauses.push_back(c);
    }
    for(int i=0;i<k2;i++){
        vector<int> c;
        for(int j=0;j<n;j++){
            c.push_back(j+1+k2*i+k1*n);
        }
        c.push_back(0);
        clauses.push_back(c);
    }
    for(int i=0;i<k1;i++){
        for(int j=0;j<n;j++){
            for(int l=j+1;l<n;l++){
                clauses.push_back({-(j+1+k1*i),-(l+1+k1*i),0});
            }
        }
    }
    for(int i=0;i<k2;i++){
        for(int j=0;j<n;j++){
            for(int l=j+1;l<n;l++){
                clauses.push_back({-(j+1+k1*i+k2*n),-(l+1+k1*i+k2*n),0});
            }
        }
    }
    for(int u=0;u<n;u++){
        for(int i=0;i<k1;i++){
            for(int j=0;j<k2;j++){
                clauses.push_back({-(i*k1+u+1),-(j*k2+u+1+k1*n),0})
            }
        }
    }
    for(int u=0;u<n;u++){
        for(int v=u+1;v<n;v++){
            if(!edges[u][v]){
                for(int i=0;i<k1;i++){
                    for(int j=0;j<k1;j++){
                        clauses.push_back({-(u+1+k1*i),-(v+1+k1*j),0});
                    }
                }
            }
        }
    }
    for(int u=0;u<n;u++){
        for(int v=u+1;v<n;v++){
            if(!edges[u][v]){
                for(int i=0;i<k2;i++){
                    for(int j=0;j<k2;j++){
                        clauses.push_back({-(u+1+k2*i+k1*n),-(v+1+k2*j+k1*n),0});
                    }
                }
            }
        }
    }
}