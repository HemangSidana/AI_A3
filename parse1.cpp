#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unistd.h>
#define endl "\n";
using namespace std;

int main(int argc, char* argv[]){
    int n;
    string input_graph( argv[2]);
    fstream input_g;
    input_g.open(input_graph, ios::in);
    string line2;
    std::getline(input_g,line2);
    std::istringstream iss(line2);
    std::vector<int> tokens2;

    std::string token2;
    while (iss >> token2) {
        tokens2.push_back(stoi(token2));
    }
    input_g.close();
    n=tokens2[0];

    string inputfilename ( argv[1] );
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
    if(inp[0]=="SAT"){
        std::string input = inp[1];
        std::istringstream iss(input);
        std::vector<int> tokens;

        std::string token;
        while (iss >> token) {
            tokens.push_back(stoi(token));
        }
        cout<<"#1"<<endl;
        for(int i=0;i<n;i++){
            if(tokens[i]>0) cout<<tokens[i]<<" ";
        }
        cout<<endl;
        cout<<"#2"<<endl;
        int z=tokens.size()/2;
        for(int i=0;i<n;i++){
            if(tokens[i+z]>0) cout<<tokens[i+z]-z<<" ";
        }
        cout<<endl;

    }
    else{
        cout<<0<<endl;
    }
    inputFile.close();
}