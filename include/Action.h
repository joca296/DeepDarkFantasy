#ifndef DEEPDARKFANTASY_ACTION_H
#define DEEPDARKFANTASY_ACTION_H

#include <iostream>
#include <fstream>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"

//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

using namespace std;
using namespace rapidjson;

class Action {
private:
    int roll, diceNumber;
    char type;
    string name;
    //Additional effect TBD
public:
    char getType() const;
    void setType(char type);
    int getRoll() const;
    void setRoll(int roll);
    int getDiceNumber() const;
    void setDiceNumber(int diceNumber);
    const string &getName() const;
    void setName(const string &name);

    Action(Document& action);
    Action();
};

class Spell: public Action {
private:
    string spellCastMod, savingThrowType;
    bool spellCastModAddedToRoll, savingThrowFlag, heal;
    int savingThrowDC;
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

    Spell(Document& action);
    Spell();
};

class SpellAoE: public Spell {
private:
    int numberOfTargets;
public:
    int getNumberOfTargets() const;
    void setNumberOfTargets(int numberOfTargets);

    SpellAoE(Document& action);
    SpellAoE();
};

class Weapon: public Action {
private:
    bool finesse;
public:
    bool isFinesse() const;
    void setFinesse(bool finesse);

    Weapon(Document& action);
    Weapon();
};

Action* callConstuctor(string name);
#endif //DEEPDARKFANTASY_ACTION_H
