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

int Spell::getManaCost()
{
    return manaCost;
}
void Spell::setManaCost(int n)
{
    manaCost=n;
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
Action::Action(Document& action) {
    name = action["name"].GetString();
    roll = action["roll"].GetInt();
    diceNumber = action["diceNumber"].GetInt();
    type = action["type"].GetString()[0];
}

Spell::Spell() {}
Spell::Spell(Document& action) : Action(action){
    spellCastMod = action["spellCastMod"].GetString();
    spellCastModAddedToRoll = action["spellCastModAddedToRoll"].GetBool();
    heal = action["heal"].GetBool();
    savingThrowFlag = action["savingThrowFlag"].GetBool();
    if(savingThrowFlag){
        savingThrowType = action["savingThrowType"].GetString();
        savingThrowDC = action["savingThrowDC"].GetInt();
    }
}

SpellAoE::SpellAoE() {}
SpellAoE::SpellAoE(Document& action) : Spell(action) {
    numberOfTargets = action["numberOfTargets"].GetInt();
}

Weapon::Weapon() {}
Weapon::Weapon(Document& action) : Action(action){
    finesse = action["finesse"].GetBool();
}

Action* callConstuctor(string name){
    ifstream f;
    string path;
    if(PLATFORM_NAME == "windows") path = "items_and_spells\\"+name+".json";
    else path = "./items_and_spells/"+name+".json";
    f.open(path);
    if(f.is_open()){
        Document document = parseFromFile(&f);

        Action* result;

        //determining type of attack
        string type = document["type"].GetString();
        switch (type[0]){
            case 'w' :  result = new Weapon(document); break;
            case 's' :  result = new Spell(document); break;
            case 'a' :  result = new SpellAoE(document); break;
        }
        return result;
    }
    else cout<<"action file not open"<<endl;
    f.close();
    return NULL;
}
