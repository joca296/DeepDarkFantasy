#include <iostream>
#include <sstream>
#include <fstream>
#include "include/Creature.h"
#include "include/functions.h"

using namespace std;
using namespace rapidjson;

int main(){
    srand(time(NULL));
    Hero x("barbarian");
    Monster y("goblin");
    for(int i=0; i<3; i++)
        if(x.actionExec(&y,x.actionChoose()) == 1 || y.actionExec(&x,y.actionChoose()) == 1) break;
    cout<<x.toString();
    cout<<y.toString();
    system("PAUSE");
}