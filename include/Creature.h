#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <fstream>
#include <string>
#include "functions.h"

using namespace std;

//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

#define maxMonsterActions 10

class Creature {
private:
    int maxHP, curHP, ac, prof, STR, DEX, CON, INT, WIS, CHA;
    string name;
public:
    string actionList[maxMonsterActions];
    int actionWeight[maxMonsterActions], numberOfActions;

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

    //methods
    virtual string actionChoose()=0;
    virtual int isHero()=0;
    int actionExec(Creature* tar, string actionName);
    int execWeaponAttack(int damage, int diceCount, bool finesse, Creature* tar, string actionName);
    int execSpellAttackST(int damage, int diceCount, string spellCastMod, bool spellCastModAddedToDamage, Creature* tar, string actionName);
    int execHeal(int healing, int diceCount, string spellCastMod, bool spellCastModAddedToHealing, Creature* tar, string actionName);
    string toString();
    virtual ~Creature() {};    //virtual destructor

};

class Monster: public Creature{
public:
    //constructors
    //~Monster();
    Monster(){};
    Monster(string name);

    //overrides
    int isHero() override;
    string actionChoose() override;

};

class Hero : public Creature{
public:
    //constructors
    Hero(){};
    Hero(string name);

    //overrides
    int isHero() override;
    string actionChoose() override;
};

#endif //DEEPDARKFANTASY_CREATURE_H
