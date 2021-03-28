#ifndef POLE_H
#define POLE_H

#include<string>
#include<vector>
#include<map>
#include <string>


using namespace std;
class pole
{
private:
    vector<string> game;
    pair<int,int> start;
    map<pair<int,int>,int> all;
    vector<pair<pair<int,int>,char>> goods;
    int weight;

    bool step(int,pair<int,int>);
    void get_way(string&,pair<int,int>);
public:
    pole(vector<string> &&);
    bool shag();
    vector<string> get_memory();
    vector<tuple<std::pair<int,int>,std::pair<int,int>,char,string>> get_hods();
    vector<string> get_game();
    pole() = default;
};

#endif // POLE_H
