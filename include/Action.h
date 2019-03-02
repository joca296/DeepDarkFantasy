#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include "functions.h"
#include "statusEffect.h"

//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

using namespace std;

struct addtlEffect {
    int roll, diceNumber;
    string rollType;
};

class Action {
private:
    int roll, diceNumber;
    char type;
    string name, rollType;
    //Additional effect TBD
public:
    vector <shared_ptr<statusEffect>> actionStatusEffect;
    vector <shared_ptr<addtlEffect>> addtlEffects;
    char getType() const;
    void setType(char type);
    int getRoll() const;
    void setRoll(int roll);
    int getDiceNumber() const;
    void setDiceNumber(int diceNumber);
    const string &getName() const;
    void setName(const string &name);
    const string &getRollType() const;
    void setRollType(const string &rollType);

    Action(const Document& action);
    Action(vector <shared_ptr<statusEffect>> consumableEffectList);
    Action();
};

class Spell: public Action {
private:
    string spellCastMod, savingThrowType;
    bool spellCastModAddedToRoll, savingThrowFlag, heal;
    int savingThrowDC, manaCost;
public:
    const string &getSpellCastMod() const;
    void setSpellCastMod(const string &spellCastMod);
    bool isSpellCastModAddedToRoll() const;
    void setSpellCastModAddedToRoll(bool spellCastModAddedToRoll);
    bool isHeal() const;
    void setHeal(bool heal);
    bool isSavingThrowFlag() const;
    void setSavingThrowFlag(bool savingThrowFlag);
    const string &getSavingThrowType() const;
    void setSavingThrowType(const string &savingThrowType);
    int getSavingThrowDC() const;
    void setSavingThrowDC(int savingThrowDC);
    int getManaCost();
    void setManaCost(int);


    Spell(const Document& action);
    Spell();
};

class SpellAoE: public Spell {
private:
    int numberOfTargets;
public:
    int getNumberOfTargets() const;
    void setNumberOfTargets(int numberOfTargets);

    SpellAoE(const Document& action);
    SpellAoE();
};

class Weapon: public Action {
private:
    bool finesse;
public:
    bool isFinesse() const;
    void setFinesse(bool finesse);

    Weapon(const Document& action);
    Weapon();
};

Action* callConstuctor(string name);