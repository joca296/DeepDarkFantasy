#include <iostream>
#include "include/Creature.h"
#include "include/room.h"
#include <windows.h>

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
    /*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,1);*/
    Hero x("barbarian");
    //cout<<x.toString();
    room* r;
    r=new room("caveEntrance");

    while(r!=NULL){
    r=r->enterRoom(&x);
    }
    delete_rList(rHead);

}
