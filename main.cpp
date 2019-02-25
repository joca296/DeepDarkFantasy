#include <iostream>
#include "include/Creature.h"
#include "include/room.h"

//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

using namespace std;



int main(){

    srand(time(NULL));
    Hero x("barbarian");
    //cout<<x.toString();
    room* r;
    r=new room("caveEntrance");
    //rHead=append_node(r,rHead);
    while(r!=NULL){
    r=r->enterRoom(&x);
    }
    delete_rList(rHead);
   /*
    cout<<x.toString();
    cout<<y.toString();*/
}
