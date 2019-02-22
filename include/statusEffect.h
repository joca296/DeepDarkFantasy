#ifndef STATUSEFFECT_H
#define STATUSEFFECT_H
#include <vector>
#include <iterator>
#include <sstream>
#include <string>
#include <cstdio>
#include <fstream>
#include "functions.h"
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;
class statusEffect
{
private:

    public:
        statusEffect(string);

        int val,saveDC;
        string jname;
        string saving_throw_skill;
        vector <string> affects;


};

#endif // STATUSEFFECT_H
