#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "include/Creature.h"
#include "include/functions.h"
#include "include/cList.h"
#include "include/combat.h"
#include "room.h"

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

