#include <iostream>
#include "include/Creature.h"
#include "include/cList.h"
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
    srand(time(nullptr));
    const int PARTY_SIZE = 3;
    struct cList* partyHead = createParty(PARTY_SIZE);
    room* r;
    r=new room("caveEntrance");

    while(r!=nullptr){
    r=r->enterRoom(partyHead);
    }
    delete_rList(rHead);
    cout<<"You lost omegaLUL"<<endl;
    return 0;

}
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//SetConsoleTextAttribute(hConsole,1);