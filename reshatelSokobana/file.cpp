#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<string> read_file(string& filename)
{
    ifstream file(filename);
    string str;
    vector<string> all;

    if(!file)
    {
        return all;
    }
    while(!file.eof())
    {
        getline(file,str);
        all.push_back(str);
    }
    file.close();
    return all;
}
