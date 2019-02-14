



#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

int dRoll(int sideNum = 20, int adv = 0,int dNum = 1);
int randomWeight(int numberOfChoices, int choiceWeight[]);
Document parseFromFile(std::ifstream *f);




#endif // DEEPDARKFANTASY_FUNCTIONS_H
