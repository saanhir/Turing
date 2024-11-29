#include <map>
#include <vector>
#include <sstream>
#include <iostream>

#include <string>


using namespace std;

struct delta_out{
    int write;
    int q_prime;
    int dir;
};

map<tuple<char,char>, tuple<char,char, char>> getRuleDict(string); 
vector<string> split(string &s, char delim) ;
