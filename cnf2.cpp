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
    bool edges[n+1][n+1];

    for(int i=0;i<tokens[1];i++){
        std::string input = inp[i+1];
        std::istringstream iss(input);
        std::vector<int> tokens;
        int u,v;
        iss>>u>>v;
        edges[u][v]=1;
        edges[v][u]=1;
    }
    int d=1;
    int x=1;
    while(x<n){
        x*=2; d++;
    }
    vector<vector<int>> clauses;
    
    // initialize extra leaves false
    for(int i=n+1;i<=x;i++){
        clauses.push_back({-i,0});
        clauses.push_back({-i-d*x,0});
    }

    // non-connected vertices cannot be in same clique
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(!edges[i][j]){
                clauses.push_back({-i,-j,0});
                clauses.push_back({-i-d*x,-j-d*x,0});
            }
        }
    }

    // vertex cannot be present in both cliques
    for(int i=1;i<=n;i++){
        clauses.push_back({-i,-i-d*x,0});
    }

    // there are k vertices in a clique
    int var=2; int nodes= x/2; int h=1;
    while(nodes){
        for(int i=1;i<=nodes;i++){
            int c1=2*i-1; int c2=2*i;
            int cvar=var/2;
            for(int j=1;j<=var;j++){
                if(j<=cvar){
                    clauses.push_back({-((c1-1)*cvar+j+(h-1)*x),(i-1)*var+j+h*x,0});
                    clauses.push_back({-((c2-1)*cvar+j+(h-1)*x),(i-1)*var+j+h*x,0});
                    clauses.push_back({-((c1-1)*cvar+j+(h-1)*x+d*x),(i-1)*var+j+h*x+d*x,0});
                    clauses.push_back({-((c2-1)*cvar+j+(h-1)*x+d*x),(i-1)*var+j+h*x+d*x,0});
                }
                int j2=j+1;
                if(j2<=cvar){
                    clauses.push_back({(c1-1)*cvar+j2+(h-1)*x,(c2-1)*cvar+1+(h-1)*x,-((i-1)*var+j2+h*x),0});
                    clauses.push_back({(c1-1)*cvar+1+(h-1)*x,(c2-1)*cvar+j2+(h-1)*x,-((i-1)*var+j2+h*x),0});
                    clauses.push_back({(c1-1)*cvar+j2+(h-1)*x+d*x,(c2-1)*cvar+1+(h-1)*x+d*x,-((i-1)*var+j2+h*x+d*x),0});
                    clauses.push_back({(c1-1)*cvar+1+(h-1)*x+d*x,(c2-1)*cvar+j2+(h-1)*x+d*x,-((i-1)*var+j2+h*x+d*x),0});
                }
                else if(j2<=var){
                    clauses.push_back({(c2-1)*cvar+1+(h-1)*x,-((i-1)*var+j2+h*x),0});
                    clauses.push_back({(c1-1)*cvar+1+(h-1)*x,-((i-1)*var+j2+h*x),0});
                    clauses.push_back({(c2-1)*cvar+1+(h-1)*x+d*x,-((i-1)*var+j2+h*x+d*x),0});
                    clauses.push_back({(c1-1)*cvar+1+(h-1)*x+d*x,-((i-1)*var+j2+h*x+d*x),0});
                }
                for(int a=1;a<j;a++){
                    int b=j-a;
                    if(a<=cvar && b<=cvar){
                        clauses.push_back({-((c1-1)*cvar+a+(h-1)*x),-((c2-1)*cvar+b+(h-1)*x),(i-1)*var+j+h*x,0});
                        clauses.push_back({-((c1-1)*cvar+a+(h-1)*x+d*x),-((c2-1)*cvar+b+(h-1)*x+d*x),(i-1)*var+j+h*x+d*x,0});
                    }
                    int a2=a+1; int b2=b+1; int j2=j+1;
                    if(a2<=cvar && b2<=cvar && j2<=var){
                        clauses.push_back({(c1-1)*cvar+a2+(h-1)*x,(c2-1)*cvar+b2+(h-1)*x,-((i-1)*var+j2+h*x),0});
                        clauses.push_back({(c1-1)*cvar+a2+(h-1)*x+d*x,(c2-1)*cvar+b2+(h-1)*x+d*x,-((i-1)*var+j2+h*x+d*x),0});
                    }
                    else if(a2<=cvar && j2<=var){
                        clauses.push_back({(c1-1)*cvar+a2+(h-1)*x,-((i-1)*var+j2+h*x),0});
                        clauses.push_back({(c1-1)*cvar+a2+(h-1)*x+d*x,-((i-1)*var+j2+h*x+d*x),0});
                    }
                    else if(b2<=cvar && j2<=var){
                        clauses.push_back({(c2-1)*cvar+b2+(h-1)*x,-((i-1)*var+j2+h*x),0});
                        clauses.push_back({(c2-1)*cvar+b2+(h-1)*x+d*x,-((i-1)*var+j2+h*x+d*x),0});
                    }
                    
                }
            }
            clauses.push_back({(c1-1)*cvar+1+(h-1)*x,(c2-1)*cvar+1+(h-1)*x,-((i-1)*var+1+h*x),0});
            clauses.push_back({(c1-1)*cvar+1+(h-1)*x+d*x,(c2-1)*cvar+1+(h-1)*x+d*x,-((i-1)*var+1+h*x+d*x),0});
        }
        var*=2; nodes/=2; h++;
    }

    clauses.push_back({(d-1)*x+k1,0});
    clauses.push_back({(2*d-1)*x+k2,0});

    cout<<"c  simple_v3_c2.cnf"<<endl;
    cout<<"c"<<endl;
    cout<<"p cnf "<<2*d*x<<" "<<clauses.size()<<endl;

    for(auto ef : clauses){
        for(auto fe : ef) cout<<fe<<" ";
        cout<<endl;
    }

}