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
    for(int i=0; i<10; i++){
        int a = x.action(&x);
    }
    system("PAUSE");
}