#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "Creature.h"
#include "combat.h"
#include "event.h"


#define MAX_ROOM_MONSTERS 10
#define MAX_CONNECTED_ROOMS 5
#define MAX_ROOM_TRAPS

//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

using namespace std;

const string global_default_Perception_FAIL_text = "You don't see anything of value";
const string global_default_Investigation_FAIL_text = "You don't find anything helpful";
const string global_default_Survival_FAIL_text = "Survival placeholder omegaLUL";
const string global_default_Arcana_FAIL_text = "You don't sense any specific magic";

class room
{
private:
    int DC_Perception, DC_Investigation, DC_Survival, DC_Arcana;

    int maxRollsAllowed;
    int numberOfConnections,numberOfMonsters,numberOfEvents;
    string Perception_SUCC_text, Investigation_SUCC_text, Survival_SUCC_text, Arcana_SUCC_text, Perception_FAIL_text, Investigation_FAIL_text, Survival_FAIL_text, Arcana_FAIL_text;
    string room_name,room_desc,combat_desc;
    string room_next[MAX_CONNECTED_ROOMS];
    string room_monsters[MAX_ROOM_MONSTERS];
    bool roomEnteredFlag=false;
public:


    event* room_traps[MAX_ROOM_TRAPS];


    void set_room_desc(string s);
    string get_room_desc();
    void set_room_name(string s);
    string get_room_name();
    void set_combat_desc(string s);
    string get_combat_desc();
    void set_room_next(int next[],int n);
    string* getRoomNext();
    void setMaxRollsAllowed(int n);
    int getMaxRollsAllowed();
    void setDC_Perception(int DC);
    int getDC_Perception();
    void setDC_Survival(int DC);
    int getDC_Survival();
    void setDC_Investigation(int DC);
    int getDC_Investigation();
    void setDC_Arcana(int DC);
    int getDC_Arcana();
    void setPerception_SUCC_text(string s);
    string getPerception_SUCC_text();
    void setInvestigation_SUCC_text(string s);
    string getInvestigation_SUCC_text();
    void setSurvival_SUCC_text(string s);
    string getSurvival_SUCC_text();
    void setArcana_SUCC_text(string s);
    string getArcana_SUCC_text();
    void setPerception_FAIL_text(string s);
    string getPerception_FAIL_text();
    void setInvestigation_FAIL_text(string s);
    string getInvestigation_FAIL_text();
    void setSurvival_FAIL_text(string s);
    string getSurvival_FAIL_text();
    void setArcana_FAIL_text(string s);
    string getArcana_FAIL_text();
    void setRoomEnteredFlag(bool f);
    bool getRoomEnteredFlag();

    room* enterRoom(Creature *p);
    void basic_choise_text(Creature *p);
    int basic_checks(Creature *p);
    void basic_checks_text();
    void activateTrap(event* e,Creature *p);
    string exit_room(Creature *p);

    room(string name);


};

struct rList
{
    struct rList *next;
    room *RPL;

};

struct rList *append_node(room* r,struct rList *rHead);
void delete_rList(struct rList *rHead);
struct rList *findRoom(struct rList *rHead,string s);
extern struct rList* rHead;


#endif // ROOM_H_INCLUDED
