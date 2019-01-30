#include <iostream>
#include <sstream>
#include <fstream>
#include "include/rapidjson/document.h"
#include "creature/Creature.h"

using namespace std;
using namespace rapidjson;

int main(){
    Monster x("goblin");
    cout<<x.toString();
}