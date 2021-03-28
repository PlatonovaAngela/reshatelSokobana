#include "solver.h"
#include <map>
#include <set>
using namespace std;

pair<int, pair<pole, string>> solver::do_dvig(tuple<std::pair<int, int>, std::pair<int, int>, char, string> & data, int weight, vector<string> cart)
{
    pair koord_gamer = get<1>(data);
    pair<int,int> koord_y;

    if(get<2>(data) == 'u')
    {
        koord_gamer.first--;
        koord_y = koord_gamer;
        koord_y.first--;
    }
    else if(get<2>(data) == 'd')
    {
        koord_gamer.first++;
        koord_y = koord_gamer;
        koord_y.first++;
    }
    else if(get<2>(data) == 'l')
    {
        koord_gamer.second--;
        koord_y = koord_gamer;
        koord_y.second--;
    }
    else
    {
        koord_gamer.second++;
        koord_y = koord_gamer;
        koord_y.second++;
    }

    if(cart.at(koord_y.first).at(koord_y.second) == 'o'||
       cart.at(koord_y.first).at(koord_y.second) == '*'||
       cart.at(koord_y.first).at(koord_y.second) == '#' )
        return {0,{pole(),""}};

    if(cart.at(koord_y.first).at(koord_y.second)=='x'||
       cart.at(koord_y.first).at(koord_y.second)=='a' )
        cart.at(koord_y.first).at(koord_y.second) = '*';
    else
    {
        cart.at(koord_y.first).at(koord_y.second) = 'o';
    }

    if((cart.at(koord_y.first).at(koord_y.second-1)=='#' && cart.at(koord_y.first-1).at(koord_y.second)=='#')||
       (cart.at(koord_y.first).at(koord_y.second-1)=='#' && cart.at(koord_y.first+1).at(koord_y.second)=='#')||
       (cart.at(koord_y.first).at(koord_y.second+1)=='#' && cart.at(koord_y.first-1).at(koord_y.second)=='#')||
       (cart.at(koord_y.first).at(koord_y.second+1)=='#' && cart.at(koord_y.first+1).at(koord_y.second)=='#') )
    {
        if(cart.at(koord_y.first).at(koord_y.second) =='*')
            cart.at(koord_y.first).at(koord_y.second) = '#';
        else
            return {0,{pole(),""}};

    }

    if(cart.at(koord_gamer.first).at(koord_gamer.second) == '*')
    {
       cart.at(koord_gamer.first).at(koord_gamer.second) = 'a';
    }
    else
    {
        cart.at(koord_gamer.first).at(koord_gamer.second) = '@';
    }

    if(cart.at(get<0>(data).first).at(get<0>(data).second) == 'a')
    {
       cart.at(get<0>(data).first).at(get<0>(data).second) = 'x';
    }
    else
    {
        cart.at(get<0>(data).first).at(get<0>(data).second) = '.';
    }

    get<3>(data).push_back(get<2>(data));
    weight += get<3>(data).length();
    return {weight,{pole(std::move(cart)),get<3>(data)}};
}

bool solver::win(const vector<string> &x)
{
    for(auto str:x)
    {
        for(auto ch:str)
        {
            if(ch == 'a' || ch == 'x' || ch == 'o')
                return false;
        }
    }
    return true;
}

solver::solver(vector<string> game):start(move(game))
{
}

string solver::reshi_plez_po_bratski()
{
    multimap<int,pair<pole,string>> var = {{0,{start,""}}};
    set<vector<string>> history;

    while(true)
    {
        auto it = var.begin();

        if(win(it->second.first.get_game()))
            return it->second.second;

        while(it->second.first.shag());

        auto e = it->second.first.get_memory();

        if(history.find(e) == history.cend())
        {
            history.emplace(e);
        }
        else
        {
            var.erase(it);
            continue;
        }

        auto new_data = it->second.first.get_hods();
        int weight = it->first;
        auto kart = it->second.first.get_game();
        string way = it->second.second;
        var.erase(it);

        for(auto e:new_data)
        {
            auto f = do_dvig(e,weight,kart);
            if(f.first != 0)
            {
                f.second.second.insert(f.second.second.cbegin(),way.cbegin(),way.cend());
                var.emplace(f);
            }
        }


    }

}
