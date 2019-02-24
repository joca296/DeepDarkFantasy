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

#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

using namespace std;
using namespace rapidjson;
class statusEffect
{
private:

    public:
        statusEffect(string);

        int val,saveDC,duration;
        string jname,name;
        string target;
        string saving_throw_skill;
        vector <string> affects;


};

#endif // STATUSEFFECT_H
