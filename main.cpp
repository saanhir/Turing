#include <string>
#include <iostream>
#include <fstream>
#include "parser.hpp"
#include <tuple>
#include <vector>
#include <bitset>
#include <unordered_map>

const int TAPE_SIZE = 256;
int MAX_STEPS = 10000;

using namespace std;

void print_stats(int arr[])
{
    cout << "N Halted: " << arr[0] << "\n";
    cout << "N Out of bounds: " << arr[1] << "\n";
    cout << "N Repeated config: " << arr[2] << "\n";
    cout << "N Exceeded max steps: " << arr[3] << "\n";
    cout << endl;
}

/*
RETURNS:
0 = machine halted
1 = machine ran out of tape bounds
2 = machine repeated config
3 = machine exceeded max time steps
*/
int run_tm(string &line, int line_counter)
{
    map<tuple<char,char>, tuple<char,char,char>> rulemap = getRuleDict(line);

    bool halt = false;
    // init tape
    bitset<TAPE_SIZE+10> tape;
    unordered_map<bitset<TAPE_SIZE+10>, bool> config_cache;

    int steps = 0;
    // tracing loop
    char rd;
    char wt;
    char dr;
    char q_n;
    char q=1;
    int index = TAPE_SIZE / 2;


    while(steps < MAX_STEPS && halt == false)
    {
        //cout << index << " " << q << steps << "\n";
        rd = tape[index];

        tuple<char,char,char> x = rulemap[make_tuple(rd, q)];
        wt = get<0>(x);
        dr = get<1>(x);
        q_n = get<2>(x);

        tape[index] = wt;
        q = q_n;

        if (q == 0)
        {
            steps++;
            if (steps > 25)
                cout << ">>HALT // steps: " << steps << " . . . . . " << line_counter << " . . . . .  "  << line << "\n";
            halt = true;
            return 0;
        }
        index = dr == 0 ? index-1 : index+1;
        // check tape bounds
        if (index >= TAPE_SIZE || index < 0 )
        {
            //cout << "ERR: Out of bounds // steps: " << steps << "\n";
            return 1;
        }
        // cache config
        bitset<4> state_bitset(q);
        bitset<7> index_bitset(index);
        tape[TAPE_SIZE+0] = state_bitset[2];
        tape[TAPE_SIZE+1] = state_bitset[1];
        tape[TAPE_SIZE+2] = state_bitset[0];
        for (int j = 0; j < 7; j++)
            tape[TAPE_SIZE+3+j] = index_bitset[j];
        
        if (config_cache.count(tape) != 0)
        {
            //cout << "Cache invoked: match found // steps: " << steps << "\n";
            return 2;
        }
        config_cache[tape] = 1;


        steps++;

    }

    ofstream outfile;
    outfile.open("LongTMs.txt", std::ios_base::app);
    outfile << line << "\n";

    return 3;

    // if (!halt) 
    //     cout << "steps: " << steps << "\n";
}

int main(int argc, const char *argv[])
{
    if (argc == 2)
    {
        string tm = argv[1];
        run_tm(tm, 0);
        return 0;
    }

    // stats 
    int statsArr[] = {0,0,0,0};
    //

    
    ifstream infile("strings.txt");
    // check
    if (!infile.is_open())
    {
        cerr << "ERR: File not open!" << endl;
        return 0;
    }

    string line;
    int line_counter = 0;
    //int max_lines = 3;
    while(getline(infile, line))
    {
        if(line.length() != 41)
        {
            cout << "ERR: fucked up string" << "\n";
            continue;
        }
        int result = run_tm(line, line_counter);
        statsArr[result] += 1;

        line_counter++;
    }

    print_stats(statsArr);
    

    return 0;
}