#include <string>
#include <iostream>
#include <fstream>
#include "parser.hpp"
#include <tuple>
#include <vector>

int TAPE_SIZE = 128;
int MAX_STEPS = 10000;

using namespace std;

void print_tuple(tuple<int,int,int> t)
{
    cout << get<0>(t) << get<1>(t) << get<2>(t) << "\n";
}

void run_tm(string &line, int line_counter)
{
    map<tuple<char,char>, tuple<char,char,char>> rulemap = getRuleDict(line);
        bool halt = false;
        // init tape
        char tape[TAPE_SIZE];
        fill_n(tape, TAPE_SIZE, 0);

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

            tuple<int,int,int> x = rulemap[make_tuple(rd, q)];
            wt = get<0>(x);
            dr = get<1>(x);
            q_n = get<2>(x);

            tape[index] = wt;
            q = q_n;

            if (q == 0)
            {
                steps++;
                if (steps > 20)
                    cout << ">>HALT // steps: " << steps << " . . . . . " << line_counter << " . . . . .  "  << line << "\n";
                halt = true;
                break;
            }
            index = dr == 0 ? index-1 : index+1;
            if (index >= TAPE_SIZE || index < 0 )
            {
                //cout << "ERR: Out of bounds // ";
                break;
            }
            steps++;

        }

        //if (!halt) 
            //cout << "steps: " << steps << "\n";
}

int main(int argc, const char *argv[])
{
    if (argc == 2)
    {
        string tm = argv[1];
        run_tm(tm, 0);
        return 0;
    }

    
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
        run_tm(line, line_counter);

        line_counter++;
    }
    

    return 0;
}