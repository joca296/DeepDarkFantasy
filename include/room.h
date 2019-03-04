#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "Creature.h"
#include "event.h"


#define MAX_ROOM_MONSTERS 20
#define MAX_CONNECTED_ROOMS 8
#define MAX_ROOM_TRAPS 5

//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

using namespace std;

struct secretRoom {
    int DC;
    string Skill,jName,UIname,check_succ_text;
};

class room
{
private:
    int DC_Perception, DC_Investigation, DC_Survival, DC_Arcana;
    int maxRollsAllowed;
    int numberOfConnections,numberOfMonsters,numberOfTraps;
    string Perception_SUCC_text, Investigation_SUCC_text, Survival_SUCC_text, Arcana_SUCC_text, Perception_FAIL_text, Investigation_FAIL_text, Survival_FAIL_text, Arcana_FAIL_text;
    string room_name,room_desc,combat_desc,room_name_ui;
    static int short_rests_allowed;
    string room_monsters[MAX_ROOM_MONSTERS];
    bool roomEnteredFlag=false;
public:

    vector<shared_ptr<secretRoom>> room_hidden_room;
    vector<Item*> groundItems;
    vector <shared_ptr<event>> room_shrine;
    vector <hiddenItem*> room_hidden_items;
    event* room_traps[MAX_ROOM_TRAPS];
    string room_next[MAX_CONNECTED_ROOMS];
    string room_next_ui[MAX_CONNECTED_ROOMS];

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
    int getNumberOfConnections() const;
    void setNumberOfConnections(int numberOfConnections);
    void setRoom_name_ui(const string &room_name_ui);
    const string &getRoom_name_ui() const;

    string getSUCCbyString(string s);
    string getFAILbyString(string s);
    int getDCbyString(string s);


    room* enterRoom(struct cList* partyHead);
    void basic_choise_text(Creature *p);
    int basic_checks(Creature *p);
    int special_interactions(Creature *p);
    void InspectHero(struct cList* partyHead);
    void swapHero(struct cList* partyHead);
    void basic_checks_text();
    void activateTrap(event* e,Creature *p);
    void short_rest(struct cList* partyHead);
    string exit_room(Creature *p);

   int getShortRestsAllowed();
   void decrementShortRestsAllowed();

    room(string name);
};

struct rList
{
    struct rList *next;
    room *RPL;
};

struct rList *append_node(room* r,struct rList *rHead);
void delete_rList(struct rList *rHead);
struct rList *findRoom(struct rList *rHead,string& s);
extern struct rList* rHead;

void printMap(struct rList *rHead, room* current, int level=1);

void partyTurnTick(struct cList* partyHead, int n=10);