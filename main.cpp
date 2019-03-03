#include <iostream>
#include "include/Creature.h"
#include "include/cList.h"
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
    srand(time(nullptr));
    const int PARTY_SIZE = 1;
    struct cList* partyHead = createParty(PARTY_SIZE);
    room* r;
    r=new room("caveEntrance");

    while(r!=nullptr){
    r=r->enterRoom(partyHead);
    }
    delete_rList(rHead);

}
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//SetConsoleTextAttribute(hConsole,1);