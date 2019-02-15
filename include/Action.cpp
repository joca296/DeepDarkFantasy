#include <utility>
#include "Action.h"
#include "functions.h"

char Action::getType() const {
    return type;
}

void Action::setType(char type) {
    Action::type = type;
}

int Action::getRoll() const {
    return roll;
}

void Action::setRoll(int roll) {
    Action::roll = roll;
}

int Action::getDiceNumber() const {
    return diceNumber;
}

void Action::setDiceNumber(int diceNumber) {
    Action::diceNumber = diceNumber;
}

const string &Action::getName() const {
    return name;
}

void Action::setName(const string &name) {
    Action::name = name;
}

const string &Spell::getSpellCastMod() const {
    return spellCastMod;
}

void Spell::setSpellCastMod(const string &spellCastMod) {
    Spell::spellCastMod = spellCastMod;
}

bool Spell::isSpellCastModAddedToRoll() const {
    return spellCastModAddedToRoll;
}

void Spell::setSpellCastModAddedToRoll(bool spellCastModAddedToRoll) {
    Spell::spellCastModAddedToRoll = spellCastModAddedToRoll;
}

bool Spell::isSavingThrowFlag() const {
    return savingThrowFlag;
}

void Spell::setSavingThrowFlag(bool savingThrowFlag) {
    Spell::savingThrowFlag = savingThrowFlag;
}

bool Spell::isHeal() const {
    return heal;
}

void Spell::setHeal(bool heal) {
    Spell::heal = heal;
}


const string &Spell::getSavingThrowType() const {
    return savingThrowType;
}

void Spell::setSavingThrowType(const string &savingThrowType) {
    Spell::savingThrowType = savingThrowType;
}

int Spell::getSavingThrowDC() const {
    return savingThrowDC;
}

void Spell::setSavingThrowDC(int savingThrowDC) {
    Spell::savingThrowDC = savingThrowDC;
}

int SpellAoE::getNumberOfTargets() const {
    return numberOfTargets;
}

void SpellAoE::setNumberOfTargets(int numberOfTargets) {
    SpellAoE::numberOfTargets = numberOfTargets;
}

bool Weapon::isFinesse() const {
    return finesse;
}

void Weapon::setFinesse(bool finesse) {
    Weapon::finesse = finesse;
}

Action::Action() {}
Action::Action(const char* action) {
    Document document;
    document.Parse(action);

    name = document["name"].GetString();
    roll = document["roll"].GetInt();
    diceNumber = document["diceNumber"].GetInt();
    type = document["type"].GetString()[0];
}

Spell::Spell() {}
Spell::Spell(const char* action) : Action(action){
    Document document;
    document.Parse(action);

    spellCastMod = document["spellCastMod"].GetString();
    spellCastModAddedToRoll = document["spellCastModAddedToRoll"].GetBool();
    heal = document["heal"].GetBool();
    savingThrowFlag = document["savingThrowFlag"].GetBool();
    if(savingThrowFlag){
        savingThrowType = document["savingThrowType"].GetString();
        savingThrowDC = document["savingThrowDC"].GetInt();
    }
}

SpellAoE::SpellAoE() {}
SpellAoE::SpellAoE(const char* action) : Spell(action) {
    Document document;
    document.Parse(action);

    numberOfTargets = document["numberOfTargets"].GetInt();
}

Weapon::Weapon() {}
Weapon::Weapon(const char* action) : Action(action){
    Document document;
    document.Parse(action);

    finesse = document["finesse"].GetBool();
}

Action* callConstuctor(string name){
    ifstream f;
    string path;
    if(PLATFORM_NAME == "windows") path = "items_and_spells\\"+name+".json";
    else path = "./items_and_spells/"+name+".json";
    f.open(path);
    if(f.is_open()){
        //converting file to a char* to parse file
        stringstream stream;
        stream<<f.rdbuf();
        string str = stream.str();
        const char* json = str.c_str();
        Document document;
        document.Parse(json);

        Action* result;

        //determining type of attack
        string type = document["type"].GetString();
        switch (type[0]){
            case 'w' :  result = new Weapon(json); break;
            case 's' :  result = new Spell(json); break;
            case 'a' :  result = new SpellAoE(json); break;
        }
        return result;
    }
    else cout<<"action file not open"<<endl;
    f.close();
    return NULL;
}