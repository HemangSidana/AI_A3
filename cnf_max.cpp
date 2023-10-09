#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unistd.h>
using namespace std;

vector<int> search(int k, int n, int edg, bool **edges, string file){
    string out=file;
    out+=".satinput";
    std::ofstream outputFile(out);
    if(k>n || k*(k-1)/2 > edg){
        outputFile <<"p cnf "<<1<<" "<<2<<endl;
        outputFile <<-1<<" "<<0<<"\n";
        outputFile <<1<<" "<<0<<"\n";
        return 0;
    }
    bool run=true;
    while(run){
        bool change=false;
        for(int i=1;i<=n;i++){
            if(is[i]){
                if(deg[i]<k-1){
                    is[i]=0; change=true;
                    for(int j=1;j<=n;j++){
                        if(edges[i][j]){deg[j]--;}
                    }
                }
            }
        }
        if(!change){run=false;}
    }
    int d=1;
    int x=1;
    while(x<n){
        x*=2; d++;
    }
    vector<vector<int>> clauses;

    // initialize not possible leaves false
    for(int i=1;i<=n;i++){
        if(!is[i]) {
            clauses.push_back({-i,0});
        }
    }

    // initialize extra leaves false
    for(int i=n+1;i<=x;i++){
        clauses.push_back({-i,0});
    }

    // non-connected vertices cannot be in same clique
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(!edges[i][j]){
                clauses.push_back({-i,-j,0});
            }
        }
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
                }
                int j2=j+1;
                if(j2<=cvar){
                    clauses.push_back({(c1-1)*cvar+j2+(h-1)*x,(c2-1)*cvar+1+(h-1)*x,-((i-1)*var+j2+h*x),0});
                    clauses.push_back({(c1-1)*cvar+1+(h-1)*x,(c2-1)*cvar+j2+(h-1)*x,-((i-1)*var+j2+h*x),0});
                }
                else if(j2<=var){
                    clauses.push_back({(c2-1)*cvar+1+(h-1)*x,-((i-1)*var+j2+h*x),0});
                    clauses.push_back({(c1-1)*cvar+1+(h-1)*x,-((i-1)*var+j2+h*x),0});
                }
                for(int a=1;a<j;a++){
                    int b=j-a;
                    if(a<=cvar && b<=cvar){
                        clauses.push_back({-((c1-1)*cvar+a+(h-1)*x),-((c2-1)*cvar+b+(h-1)*x),(i-1)*var+j+h*x,0});
                    }
                    int a2=a+1; int b2=b+1; int j2=j+1;
                    if(a2<=cvar && b2<=cvar && j2<=var){
                        clauses.push_back({(c1-1)*cvar+a2+(h-1)*x,(c2-1)*cvar+b2+(h-1)*x,-((i-1)*var+j2+h*x),0});
                    }
                    else if(a2<=cvar && j2<=var){
                        clauses.push_back({(c1-1)*cvar+a2+(h-1)*x,-((i-1)*var+j2+h*x),0});
                    }
                    else if(b2<=cvar && j2<=var){
                        clauses.push_back({(c2-1)*cvar+b2+(h-1)*x,-((i-1)*var+j2+h*x),0});
                    }                
                }
            }
            clauses.push_back({(c1-1)*cvar+1+(h-1)*x,(c2-1)*cvar+1+(h-1)*x,-((i-1)*var+1+h*x),0});
        }
        var*=2; nodes/=2; h++;
    }
    clauses.push_back({(d-1)*x+k,0});
    outputFile<<"p cnf "<<d*x<<" "<<clauses.size()<<endl;
    for(auto ef : clauses){
        for(auto fe : ef) outputFile<<fe<<" ";
        outputFile<<endl;
    }
    outputFile.close();
}

int main(int argc, char* argv[]){
    string file="";
    string inputfilename (argv[1]);
    for(auto x: argv[1]){
        if(x=='.') break;
        file+=x;
    }
    fstream inputFile;
    inputFile.open(inputfilename, ios::in);
    if (!inputFile) {
        cout << "No such file\n";
        exit( 0 );
    }

    string line;
    vector<string>inp;
    while (std::getline(inputFile, line)) {
    // Process the read line
        inp.push_back(line);
    // std::cout << "Read line: " << line << std::endl;
    }
    if (inp.empty()) {
        cerr << "Input file is empty." << endl;
        return 1;
    }
    
    std::string input = inp[0];
    std::istringstream iss(input);
    std::vector<int> tokens;

    std::string token;
    while (iss >> token) {
        tokens.push_back(stoi(token));
    }
    inputFile.close();
    int n,edg;
    n=tokens[0]; edg=token[1];
    vector<int> deg(n+1,0);
    vector<int> is(n+1,1);
    bool edges[n+1][n+1];
    for(int i=0;i<=n;i++){for(int j=0;j<=n;j++) edges[i][j]=false;}

    for(int i=0;i<edg;i++){
        std::string input = inp[i+1];
        std::istringstream iss(input);
        std::vector<int> tokens;
        int u,v;
        iss>>u>>v;
        deg[u]++; deg[v]++;
        edges[u][v]=1;
        edges[v][u]=1;
    }
    search(k);
}