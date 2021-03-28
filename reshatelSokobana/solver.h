#ifndef SOLVER_H
#define SOLVER_H

#include"pole.h"
#include<string>
#include<vector>
using namespace std;

class solver
{
private:
    pole start;

    pair<int,pair<pole,string>> do_dvig(tuple<std::pair<int, int>,std::pair<int, int>, char, string>&,int,vector<string>);
    bool win(const vector<string>&);
public:
    solver(vector<string>);
    string reshi_plez_po_bratski();
};

#endif // SOLVER_H
