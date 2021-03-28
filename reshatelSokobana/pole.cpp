#include "pole.h"

using namespace std;

pole::pole(vector<string> && kart)
{
    weight = 0;
    game = move(kart);
    for(size_t i = 0;i < game.size();++i)
    {
        for(size_t j = 0;j < game.at(i).size();++j)
        {
            if(game.at(i).at(j) == '@' || game.at(i).at(j) == 'a')
            {
                start = make_pair(i,j);
                step(0,start);
                return;
            }
        }
    }
}

bool pole::shag()
{
    ++weight;
    return step(0,start);;
}

vector<string> pole::get_memory()
{
    auto v = game;
    for(auto f:all)
    {
        v.at(f.first.first).at(f.first.second) = '1';
    }
    return v;
}

vector<tuple<std::pair<int, int>,std::pair<int, int>, char, string>> pole::get_hods()
{
    vector<tuple<std::pair<int, int>,std::pair<int, int>, char, string>> ans;
    for(auto r:goods)
    {
        string str;
        get_way(str,r.first);
        tuple a = {start,r.first,r.second,str};
        ans.push_back(a);
    }
    return ans;
}

vector<string> pole::get_game()
{
    return game;
}

bool pole::step(int _weight,pair<int,int> st)
{
    bool fl[] = {false,false,false,false};
    pair koord = {st.first,st.second};
    if(_weight == weight)
    {
        if(all.find(koord) == all.cend())
        {
            pair to_all = {koord,weight};
            all.emplace(to_all);

            if(game.at(koord.first).at(koord.second-1) == '*' ||
               game.at(koord.first).at(koord.second-1) == 'o')
            {
                goods.push_back(make_pair(koord,'l'));
            }
            else if(game.at(koord.first).at(koord.second-1) != '#'
                    && all.find(make_pair(koord.first,koord.second-1)) == all.cend())
            {
                fl[0] = true;
            }

            if(game.at(koord.first).at(koord.second+1) == '*' ||
               game.at(koord.first).at(koord.second+1) == 'o')
            {
                goods.push_back(make_pair(koord,'r'));
            }
            else if(game.at(koord.first).at(koord.second+1) != '#'
                    && all.find(make_pair(koord.first,koord.second+1)) == all.cend())
            {
                fl[1] = true;
            }

            if(game.at(koord.first-1).at(koord.second) == '*' ||
               game.at(koord.first-1).at(koord.second) == 'o')
            {
                goods.push_back(make_pair(koord,'u'));
            }
            else if(game.at(koord.first-1).at(koord.second) != '#'
                    && all.find(make_pair(koord.first-1,koord.second)) == all.cend())
            {
                fl[2] = true;
            }

            if(game.at(koord.first+1).at(koord.second) == '*' ||
               game.at(koord.first+1).at(koord.second) == 'o')
            {
                goods.push_back(make_pair(koord,'d'));
            }
            else if(game.at(koord.first+1).at(koord.second) != '#'
                    && all.find(make_pair(koord.first+1,koord.second)) == all.cend())
            {
                fl[3] = true;
            }
        }
    }
    else
    {
        if(!(game.at(koord.first).at(koord.second-1) == '*'||
             game.at(koord.first).at(koord.second-1) == 'o'||
             game.at(koord.first).at(koord.second-1) == '#'))
        {
            fl[0] = step(_weight+1,make_pair(koord.first,koord.second-1));
        }

        if(!(game.at(koord.first).at(koord.second+1) == '*'||
             game.at(koord.first).at(koord.second+1) == 'o'||
             game.at(koord.first).at(koord.second+1) == '#'))
        {
            fl[1] = step(_weight+1,make_pair(koord.first,koord.second+1));
        }

        if(!(game.at(koord.first-1).at(koord.second) == '*'||
             game.at(koord.first-1).at(koord.second) == 'o'||
             game.at(koord.first-1).at(koord.second) == '#'))
        {
            fl[2] = step(_weight+1,make_pair(koord.first-1,koord.second));
        }

        if(!(game.at(koord.first+1).at(koord.second) == '*'||
             game.at(koord.first+1).at(koord.second) == 'o'||
             game.at(koord.first+1).at(koord.second) == '#'))
        {
            fl[3] = step(_weight+1,make_pair(koord.first+1,koord.second));
        }
    }

    return (fl[0] || fl[1] || fl[2] || fl[3]);
}

void pole::get_way(string& way,pair<int,int> koord)
{
    int w = all.find(koord)->second;
    if(w == 0)
    {
        return;
    }
    else
    {
        if(auto it = all.find(make_pair(koord.first,koord.second-1));it != all.cend())
        {
            if(it->second + 1 == w)
            {
                way.insert(way.cbegin(),'r');
                get_way(way,it->first);
                return;
            }
        }

        if(auto it = all.find(make_pair(koord.first,koord.second+1));it != all.cend())
        {
            if(it->second + 1 == w)
            {
                way.insert(way.cbegin(),'l');
                get_way(way,it->first);
                return;
            }
        }

        if(auto it = all.find(make_pair(koord.first-1,koord.second));it != all.cend())
        {
            if(it->second + 1 == w)
            {
                way.insert(way.cbegin(),'d');
                get_way(way,it->first);
                return;
            }
        }

        if(auto it = all.find(make_pair(koord.first+1,koord.second));it != all.cend())
        {
            if(it->second + 1 == w)
            {
                way.insert(way.cbegin(),'u');
                get_way(way,it->first);
                return;
            }
        }
    }
}
