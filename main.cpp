#include <iostream>
#include <sstream>
#include <fstream>
#include "include/Creature.h"
#include "include/functions.h"

using namespace std;
using namespace rapidjson;

int main(){
    Monster x("goblin");
    cout<<x.toString();
    cout<<dRoll()<<endl;
    system("PAUSE");
}