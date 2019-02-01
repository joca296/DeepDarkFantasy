#include <iostream>
#include <sstream>
#include <fstream>
#include "include/Creature.h"
#include "include/functions.h"

using namespace std;
using namespace rapidjson;

int main(){
    srand(time(NULL));
    Monster x("goblin");
    cout<<x.toString()<<endl;
    system("PAUSE");
}