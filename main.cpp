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

/*vector<Item*> Ivec2;
Item* makeitemObject();*/

int main(){
    /*Item* iptr;
    iptr=makeitemObject();
    cout<<iptr->getName()<<endl;
    Ivec2.push_back(iptr);*/
    srand(time(NULL));
    Hero x("barbarian");
    room* r;
    r=new room("caveEntrance");
    //rHead=append_node(r,rHead);
    while(r!=NULL){
    r=r->enterRoom(&x);
    }
    delete_rList(rHead);
   /* string s[]={"kobold","goblin","twigBlight"};
    combat(&x,s,3);
    Monster y("kobold");
    for(int i=0; i<3; i++)
        if(x.actionExec(&y,x.actionChoose()) == 1 || y.actionExec(&x,y.actionChoose()) == 1) break;
    cout<<x.toString();
    cout<<y.toString();*/
}

/*Item* makeitemObject()
{    Item* myItem;
     myItem= new Item("dagger");
     return myItem;
}*/
