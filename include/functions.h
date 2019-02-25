#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

int dRoll(int sideNum = 20, int adv = 0,int dNum = 1);
int randomWeight(const vector<int>& choiceWeight);
Document parseFromFile(std::ifstream *f);