#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main(){
    ifstream inputFile;
    inputFile.open("C:/Users/corpd/Desktop/COL333/test.graph");

    if (!inputFile.is_open()) {
        cerr << "Error opening file" << std::endl;
        return 1;
    }

    string line;
    vector<string>inp;
    while (std::getline(inputFile, line)) {
    // Process the read line
        inp.push_back(line);
    // std::cout << "Read line: " << line << std::endl;
    }
    
    std::string input = inp[0];
    std::istringstream iss(input);
    std::vector<int> tokens;

    std::string token;
    while (iss >> token) {
        tokens.push_back(stoi(token));
    }
    

    inputFile.close();
    int n, k1, k2;
    n=tokens[0],k1=tokens[2],k2=tokens[3];
    bool edges[n][n];

    for(int i=0;i<tokens[1];i++){
        std::string input = inp[i+1];
        std::istringstream iss(input);
        std::vector<int> tokens;
        int u,v;
        iss>>u>>v;
        // cout<<u<<" "<<v<<endl;
        edges[u-1][v-1]=1;
        edges[v-1][u-1]=1;
    }


    vector<vector<int>> clauses;
    //variables k1*n, k2*n
    // select any1 from 
    for(int i=0;i<k1;i++){
        vector<int> c;
        for(int j=0;j<n;j++){
            c.push_back(j+1+n*i);
        }
        c.push_back(0);
        clauses.push_back(c);
    }
    for(int i=0;i<k2;i++){
        vector<int> c;
        for(int j=0;j<n;j++){
            c.push_back(j+1+n*i+k1*n);
        }
        c.push_back(0);
        clauses.push_back(c);
    }
    // same position cannot be occupied by multiple values
    for(int i=0;i<k1;i++){
        for(int j=0;j<n;j++){
            for(int l=j+1;l<n;l++){
                clauses.push_back({-(j+1+n*i),-(l+1+n*i),0});
            }
        }
    }
    for(int i=0;i<k2;i++){
        for(int j=0;j<n;j++){
            for(int l=j+1;l<n;l++){
                clauses.push_back({-(j+1+n*i+k1*n),-(l+1+n*i+k1*n),0});
            }
        }
    }
    //same value cant be given to multiple positions
    for(int u=0;u<n;u++){
        for(int j=0;j<k1;j++){
            for(int l=j+1;l<k1;l++){
                clauses.push_back({-(u+1+n*j),-(u+1+n*l),0});
            }
        }
    }
    for(int u=0;u<n;u++){
        for(int j=0;j<k2;j++){
            for(int l=j+1;l<k2;l++){
                clauses.push_back({-(u+1+n*j+k1*n),-(u+1+n*l+k1*n),0});
            }
        }
    }
    // same value cannot be taken by two cliques
    for(int u=0;u<n;u++){
        for(int i=0;i<k1;i++){
            for(int j=0;j<k2;j++){
                clauses.push_back({-(i*n+u+1),-(j*n+u+1+k1*n),0});
            }
        }
    }
    // edge constraints
    for(int u=0;u<n;u++){
        for(int v=u+1;v<n;v++){
            if(!edges[u][v]){
                for(int i=0;i<k1;i++){
                    for(int j=0;j<k1;j++){
                        clauses.push_back({-(u+1+n*i),-(v+1+n*j),0});
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
                        clauses.push_back({-(u+1+n*i+k1*n),-(v+1+n*j+k1*n),0});
                    }
                }
            }
        }
    }

    cout<<"c  simple_v3_c2.cnf"<<endl;
    cout<<"c"<<endl;
    cout<<"p cnf "<<n*(k1+k2)<<" "<<clauses.size()<<endl;

    for(auto ef : clauses){
        for(auto fe : ef)cout<<fe<<" ";
        cout<<endl;
    }

}