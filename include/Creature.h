#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <fstream>
#include <string>
#include "Action.h"
#include "ActionList.h"
#include "functions.h"
#include "event.h"

using namespace std;

//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

#define maxMonsterActions 100

class Creature {
private:
    int maxHP, curHP, ac, prof, STR, DEX, CON, INT, WIS, CHA, init;
    string name;
public:
    //getters and setters
    string getName() const;
    void setName(string name);
    int getProf() const;
    void setProf(int prof);
    int getMaxHP() const;
    void setMaxHP(int maxHP);
    int getCurHP() const;
    void setCurHP(int curHP);
    int getAc() const;
    void setAc(int ac);
    int getSTR() const;
    void setSTR(int STR);
    int getDEX() const;

    void setDEX(int DEX);
    int getCON() const;
    void setCON(int CON);
    int getINT() const;
    void setINT(int INT);
    int getWIS() const;
    void setWIS(int WIS);
    int getCHA() const;
    void setCHA(int CHA);

    int getInit() const;
    void setInit(int init);

    //methods
    virtual Action* actionChoose()=0;
    virtual Creature* chooseTarget(struct cList* actors)=0;
    virtual int isHero()=0;
    int actionExec(struct cList* actors, Creature* tar, Action *action);
    int execWeaponAttack(Weapon *action, Creature* tar);
    int execSpellAttackST(Spell *action, Creature* tar);
    int execHeal(Spell *action, Creature* tar);
    int execAoE(struct cList* actors, SpellAoE *action, Creature* tar);
    string toString();
    virtual ~Creature() {};    //virtual destructor

};

class Monster: public Creature{
public:
    ActionList* actionList;
    int numberOfActions, actionWeight[maxMonsterActions];
    //constructors
    //~Monster();
    Monster(){};
    Monster(string name);

    //overrides
    int isHero() override;
    Action* actionChoose() override;
    Creature* chooseTarget(struct cList* actors) override;
};

class Hero : public Creature{
public:
    ActionList *weapons, *spellBook;

    //constructors
    Hero(){};
    Hero(string name);

    //overrides and methods
    int isHero() override;
    Action* actionChoose() override;
    Action* selectSpell();
    Action* selectWeapon();
    Creature* chooseTarget(struct cList* actors) override;
    void listWeapons();
    void listSpellBook();
};

#endif //DEEPDARKFANTASY_CREATURE_H
