#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "Item.h"
#include "Action.h"
#include "statusEffect.h"

using namespace std;

//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

struct Advantages{
    int STR, DEX, CON, INT, WIS, CHA, attack, global;
};

class Creature {
private:
    int maxHP, curHP, maxMana, curMana, ac, prof, STR, DEX, CON, INT, WIS, CHA, init, actionsPerRound, tempAcGain, level, hitDice, hitDiceNumber;
    float experience;
public:
    float getExperience() const;

    void setExperience(float experience);

private:
    string name, tag;
public:
    //Inventory
    vector<Item*> inventory;
    Armor* armor;

    //Immunities, resists and weaknesses
    vector<string> immunity, resist, weakness;

    //Status effects
    vector<shared_ptr<statusEffect>> activeSE;
    vector<int> SEcounter;

    //Advantages
    shared_ptr<Advantages> advantages;

    //getters and setters
    int getActionsPerRound() const;
    void setActionsPerRound(int actionsPerRound);
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
    const string &getTag() const;
    void setTag(const string &tag);
    int getTempAcGain() const;
    void setTempAcGain(int tempAcGain);
    int getInit() const;
    void setInit(int init);
    int getLevel() const;
    void setLevel(int level);
    int getHitDice() const;
    void setHitDice(int hitDice);
    int getHitDiceNumber() const;
    void setHitDiceNumber(int hitDiceNumber);

    //constructors
    Creature(){};
    Creature(string name);

    //methods
    char checkDamage(const string& type);
    virtual Action* actionChoose(Creature* c)=0;
    virtual Creature* chooseTarget(struct cList* actors)=0;
    virtual int isHero()=0;
    int actionExec(struct cList* actors, Creature* tar, Action *action);
    int execWeaponAttack(Weapon *action, Creature* tar);
    int execSpellAttackST(Spell *action, Creature* tar);
    int execHeal(struct cList* actors, Spell *action, Creature* tar);
    int execAoE(struct cList* actors, SpellAoE *action, Creature* tar);
    string toString();
    virtual void listSpellBook();
    virtual void listEquipped();
    virtual Item* listInventory();
    virtual ~Creature() {};    //virtual destructor
    int SE_Inflict(vector <shared_ptr<statusEffect>> SEV,Creature* trg);
    int SE_Inflict(shared_ptr<statusEffect> ptr,Creature* trg); //overloaded for single SE
    int rollSave(string atr);
    void CTurnTick(int ticks=1);
    int calcDamage(int bonus, Action* action, vector<string> &dmgBreakdown);
    int StatusEffectMenu(Creature* c);
    void StatsMenu(Creature *c);
    int getAdvantage(string type = "globalAdv");
    int getFieldsByString(string s);
    void setFieldsByString(string s,int n);
    void lvlUp(int level);
    virtual void checkExperience(){};
};

class Monster: public Creature{
public:
    vector<Action*> actionList;
    vector<int> actionWeight;

    //constructors
    Monster(){};
    Monster(string name, int level=1);

    //overrides
    int isHero() override;
    Action* actionChoose(Creature* c) override;
    Creature* chooseTarget(struct cList* actors) override;
};

class Hero : public Creature{
public:
    vector<Action*> weapons, spellBook;

    //constructors
    Hero(){};
    Hero(string name, int level=1);

    //overrides and methods
    int isHero() override;
    Action* actionChoose(Creature* c) override;
    Action* selectSpell();
    Action* selectWeapon();
    Creature* chooseTarget(struct cList* actors) override;
    void listEquipped() override;
    void listSpellBook() override;
    Item* listInventory() override;
    void checkExperience() override;
};
