#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "include/functions.h"
#include "include/Creature.h"
#include "include/cList.h"
#include "include/combat.h"
#include "include/room.h"
#include "include/rapidjson/document.h"

//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

using namespace std;
using namespace rapidjson;



int main(){
    srand(time(NULL));
    Hero x("barbarian");
    room* r;
    r=new room("caveEntrance");
    while(r!=NULL){
    r=r->enterRoom(&x);
    }
   /* string s[]={"kobold","goblin","twigBlight"};
    combat(&x,s,3);
    Monster y("kobold");
    for(int i=0; i<3; i++)
        if(x.actionExec(&y,x.actionChoose()) == 1 || y.actionExec(&x,y.actionChoose()) == 1) break;
    cout<<x.toString();
    cout<<y.toString();*/




}

