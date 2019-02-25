#pragma once

#include <vector>
#include <iterator>
#include <sstream>
#include <string>
#include <cstdio>
#include <fstream>

#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

using namespace std;

class statusEffect
{
private:

    public:
        statusEffect(string);
        bool DOTflag;
        int val,saveDC,duration;
        string jname,name;
        string target;
        string description;
        string saving_throw_skill;
        vector <string> affects;


};