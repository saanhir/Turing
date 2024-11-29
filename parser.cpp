#include "parser.hpp"


vector<string> split(string &s, char delim) 
{
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline (ss, item, delim)) 
    {
        result.push_back (item);
    }

    return result;
}



map<tuple<char,char>, tuple<char,char, char>> getRuleDict(string table)
{
    map<tuple<char,char>, tuple<char,char,char>> m;

    vector<string> rules = split(table, '_');
    for (int i =0; i<6; i++)
    {
        string r0 = rules[i].substr(0,3);
        string r1 = rules[i].substr(3);

        //cout << "r0 " << r0 << "\n";
        //cout << "r1 " << r1 << "\n";

        char wt0 = r0[0] == '1' ?  1 : 0;
        char wt1 = r1[0] == '1' ?  1 : 0;

        char dr0 = r0[1] == 'R' ? 1 : 0;
        char dr1 = r1[1] == 'R' ? 1 : 0;

        char qn0 = r0[2] != '-' ? r0[2]-64 : 0;
        char qn1 = r1[2] != '-' ? r1[2]-64 : 0;        

        m[make_tuple(0, i+1)] = make_tuple(wt0, dr0, qn0);
        m[make_tuple(1, i+1)] = make_tuple(wt1, dr1, qn1);

    }

    return m;

}