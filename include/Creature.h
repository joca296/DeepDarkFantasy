#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "Item.h"
#include "Action.h"
#include "functions.h"
#include "event.h"
#include "statusEffect.h"

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
    int maxHP, curHP,maxMana,curMana, ac, prof, STR, DEX, CON, INT, WIS, CHA, init;
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
    void setMaxMana(int);
    int getMaxMana();
    void setCurMana(int);
    int getCurMana();
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

    //Inventory
    vector<Item*> inventory;
    vector<shared_ptr<statusEffect>> activeSE;

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
    virtual void listSpellBook();
    virtual void listWeapons();
    virtual Item* listInventory();
    virtual ~Creature() {};    //virtual destructor
    int SE_Inflict(Action* aptr,Creature* target);

};

class Monster: public Creature{
public:
    vector<Action*> actionList;
    vector<int> actionWeight;

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
    vector<Action*> weapons, spellBook;
    Armor* armor;

    //constructors
    Hero(){};
    Hero(string name);

    //overrides and methods
    int isHero() override;
    Action* actionChoose() override;
    Action* selectSpell();
    Action* selectWeapon();
    Creature* chooseTarget(struct cList* actors) override;
    void listWeapons() override;
    void listSpellBook() override;
    Item* listInventory() override;
    int getAc() const;
};

#endif //DEEPDARKFANTASY_CREATURE_H
