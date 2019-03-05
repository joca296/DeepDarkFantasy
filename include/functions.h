#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include <windows.h>
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;



int dRoll(int sideNum = 20, int adv = 0,int dNum = 1);
int randomWeight(const vector<int>& choiceWeight);
Document parseFromFile(std::ifstream *f);
void printDamage(const string& actorName,const string& targetName,const string& actionName, int& dmgTotal,const vector<string>& dmgBreakdown, bool critFlag, int actorHero, int targetHero);
void colorPrint(const string& output,const string& color);
void colorPrint(const string& output,int hero);
int convertToAttribute(int attr);