#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/functions.h"
#include "../include/rapidjson/document.h"
#define maxMonsterActions 10

//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

using namespace std;
using namespace rapidjson;

#ifndef DEEPDARKFANTASY_CREATURE_H
#define DEEPDARKFANTASY_CREATURE_H


class Creature {
private:
    int maxHP, curHP, ac, prof, STR, DEX, CON, INT, WIS, CHA;
    string name;
public:
    string actionList[maxMonsterActions];
    int actionWeight[maxMonsterActions], numberOfActions;

    //getters and setters
    string getName() const {
        return name;
    }
    void setName(string name) {
        Creature::name = name;
    }
    int getProf() const {
        return prof;
    }
    void setProf(int prof) {
        Creature::prof = prof;
    }
    int getMaxHP() const {
        return maxHP;
    }
    void setMaxHP(int maxHP) {
        Creature::maxHP = maxHP;
    }
    int getCurHP() const {
        return curHP;
    }
    void setCurHP(int curHP) {
        Creature::curHP = curHP;
    }
    int getAc() const {
        return ac;
    }
    void setAc(int ac) {
        Creature::ac = ac;
    }
    int getSTR() const {
        return STR;
    }
    void setSTR(int STR) {
        Creature::STR = STR;
    }
    int getDEX() const {
        return DEX;
    }
    void setDEX(int DEX) {
        Creature::DEX = DEX;
    }
    int getCON() const {
        return CON;
    }
    void setCON(int CON) {
        Creature::CON = CON;
    }
    int getINT() const {
        return INT;
    }
    void setINT(int INT) {
        Creature::INT = INT;
    }
    int getWIS() const {
        return WIS;
    }
    void setWIS(int WIS) {
        Creature::WIS = WIS;
    }
    int getCHA() const {
        return CHA;
    }
    void setCHA(int CHA) {
        Creature::CHA = CHA;
    }

    //methods
    virtual string actionChoose()=0;
    virtual int isHero()=0;
    int execWeaponAttack(int damage, int diceCount, bool finesse, Creature* tar, string actionName);
    int execSpellAttackST(int damage, int diceCount, string spellCastMod, bool spellCastModAddedToDamage, Creature* tar, string actionName);
    int execHeal(int healing, int diceCount, string spellCastMod, bool spellCastModAddedToDamage, Creature* tar, string actionName);
    int actionExec(Creature* tar, string actionName);
    string toString();
};

class Monster: public Creature{
public:
    //constructors
    Monster(){};
    Monster(string name){
        ifstream f;
        string path;
        if(PLATFORM_NAME == "windows") path = "monsters\\"+name+".json";
        else path = "./monsters/"+name+".json";
        f.open(path);
        if(f.is_open()){
            Document document = parseFromFile(&f);

            //setting base monster values
            this->setName(document["name"].GetString()+to_string(rand()%100));
            this->setMaxHP(document["hp"].GetInt());
            this->setCurHP(document["hp"].GetInt());
            this->setAc(document["ac"].GetInt());
            this->setProf(document["prof"].GetInt());
            this->setSTR(document["str"].GetInt());
            this->setDEX(document["dex"].GetInt());
            this->setCON(document["con"].GetInt());
            this->setINT(document["int"].GetInt());
            this->setWIS(document["wis"].GetInt());
            this->setCHA(document["cha"].GetInt());

            //setting actions
            const Value& a = document["actionList"];
            numberOfActions=0;
            int j=0;
            for (SizeType i = 0; i < a.Size(); i++){
                actionList[j]=a[i].GetString();
                j++;
                numberOfActions++;
            }

            const Value& b = document["actionWeight"];
            j=0;
            for (SizeType i = 0; i < b.Size(); i++){
                actionWeight[j]=b[i].GetInt();
                j++;
            }
        }
        else cout<<"monster file not open"<<endl;
        f.close();
    }

    //overrides
    int isHero() override{
        return 0;
    }
    string actionChoose() override{
        int choice = randomWeight(numberOfActions,actionWeight);
        string actionName = actionList[choice];
        return actionName;
    }

};

class Hero : public Creature{
public:
    //constructors
    Hero(){};
    Hero(string name){
        ifstream f;
        string path;
        if(PLATFORM_NAME == "windows") path = "heroClasses\\"+name+".json";
        else path = "./heroClasses/"+name+".json";
        f.open(path);
        if(f.is_open()){
            Document document = parseFromFile(&f);

            //setting hero name
            string name;
            cout<<"Name your character."<<endl;
            cin>>name;

            //setting base hero values
            this->setName(name);
            this->setMaxHP(document["hp"].GetInt());
            this->setCurHP(document["hp"].GetInt());
            this->setAc(document["ac"].GetInt());
            this->setProf(document["prof"].GetInt());
            this->setSTR(document["str"].GetInt());
            this->setDEX(document["dex"].GetInt());
            this->setCON(document["con"].GetInt());
            this->setINT(document["int"].GetInt());
            this->setWIS(document["wis"].GetInt());
            this->setCHA(document["cha"].GetInt());

            //setting actions
            const Value& a = document["actionList"];
            numberOfActions=0;
            int j=0;
            for (SizeType i = 0; i < a.Size(); i++){
                actionList[j]=a[i].GetString();
                j++;
                numberOfActions++;
            }
        }
        else cout<<"hero file not open"<<endl;
        f.close();
    }

    //overrides
    int isHero() override{
        return 1;
    }
    string actionChoose() override{
        while(1){
            cout<<"Choose an action:"<<endl;
            for(int i=0;i<numberOfActions;i++)
                cout<<i<<". "<<actionList[i]<<endl;
            int x;
            cin>>x;
            if(x<0 || x>=numberOfActions)
                cout<<"Invalid input. Try again";
            else return actionList[x];
        }
    }
};

//Creature class method definitions
int Creature::execWeaponAttack(int damage, int diceCount, bool finesse, Creature* tar, string actionName){
    int atcRoll, bonus;

    //determining attack roll
    if(finesse) bonus=this->getDEX();
    else bonus=this->getSTR();
    atcRoll = dRoll()+bonus+this->getProf();

    //attack success
    if(atcRoll >= tar->getAc() || atcRoll-bonus == 20){
        int dmgRoll = dRoll(damage,0,diceCount) + bonus;
        if(atcRoll-bonus == 20) dmgRoll+=dRoll(damage,0,diceCount);
        tar->setCurHP(tar->getCurHP()-dmgRoll);

        //print
        cout<<this->getName()<<" hit "<<tar->getName()<<" for "<<dmgRoll<<" damage with ";
        if(actionName[0]=='a') cout<<"an ";
        else cout<<"a ";
        cout<<actionName<<".";
        if(atcRoll-bonus == 20) cout<<" (crit)";
        cout<<endl;

        if(tar->getCurHP() <= 0){
            cout<<tar->getName()<<" died."<<endl;
            return 1; //something died
        }
        else return 2; //something didn't die
    }

    //attack failed
    else {
        cout<<this->getName()<<" missed."<<endl;
        return 0;
    }
}
int Creature::execSpellAttackST(int damage, int diceCount, string spellCastMod, bool spellCastModAddedToDamage, Creature* tar, string actionName){
    int atcRoll, bonus;

    //setting bonus
    if (spellCastMod == "int") bonus=this->getINT();
    else if (spellCastMod == "wis") bonus=this->getWIS();
    else bonus=this->getCHA();

    //attack roll
    atcRoll=dRoll()+bonus+this->getProf();

    //attack success
    if(atcRoll >= tar->getAc() || atcRoll-bonus == 20){
        int dmgRoll = dRoll(damage,0,diceCount) + ( spellCastModAddedToDamage? bonus:0 );
        if(atcRoll-bonus == 20) dmgRoll+=dRoll(damage,0,diceCount);
        tar->setCurHP(tar->getCurHP()-dmgRoll);

        //print
        cout<<this->getName()<<" hit "<<tar->getName()<<" for "<<dmgRoll<<" damage with ";
        if(actionName[0]=='a') cout<<"an ";
        else cout<<"a ";
        cout<<actionName<<".";
        if(atcRoll-bonus == 20) cout<<" (crit)";
        cout<<endl;

        if(tar->getCurHP() <= 0){
            cout<<tar->getName()<<" died."<<endl;
            return 1; //something died
        }
        else return 2; //something didn't die
    }

    //attack failed
    else {
        cout<<this->getName()<<" missed."<<endl;
        return 0;
    }
}
int Creature::execHeal(int healing, int diceCount, string spellCastMod, bool spellCastModAddedToHealing, Creature *tar, string actionName) {
    int bonus;

    //setting bonus
    if (spellCastMod == "int") bonus=this->getINT();
    else if (spellCastMod == "wis") bonus=this->getWIS();
    else bonus=this->getCHA();

    //healing
    int healRoll= dRoll(healing,0,diceCount) + (spellCastModAddedToHealing? bonus:0);
    tar->setCurHP( tar->getCurHP()+healRoll > tar->getMaxHP()? tar->getMaxHP() : tar->getCurHP()+healRoll );

    //print
    cout<<this->getName()<<" healed "<<tar->getName()<<" for "<<healRoll<<" with "<<actionName<<"."<<endl;
    return 2;
}
int Creature::actionExec(Creature* tar, string actionName){
    ifstream f;
    string path;
    if(PLATFORM_NAME == "windows") path = "items_and_spells\\"+actionName+".json";
    else path = "./items_and_spells/"+actionName+".json";
    f.open(path);
    if(f.is_open()){
        Document document = parseFromFile(&f);

        //determining type of attack
        string type = document["type"].GetString();
        switch (type[0]){
            case 'w': return this->execWeaponAttack(document["damage"].GetInt(),document["diceCount"].GetInt(),document["finesse"].GetBool(),tar,actionName);
            case 's': return this->execSpellAttackST(document["damage"].GetInt(),document["diceCount"].GetInt(),document["spellCastMod"].GetString(),document["spellCastModAddedToDamage"].GetBool(),tar,actionName);
            case 'h': return this->execHeal(document["healing"].GetInt(),document["diceCount"].GetInt(),document["spellCastMod"].GetString(),document["spellCastModAddedToDamage"].GetBool(),tar,actionName);
        }
    }
    else cout<<"action file not open"<<endl;
    f.close();
    return -1; //File error
};
string Creature::toString(){
    string s;
    if(curHP<=0) s = name+" is dead.\n";
    else s = "Name: "+name+"\nMax HP: "+to_string(maxHP)+"\nCurrent HP: "+to_string(curHP)+"\nAC: "+to_string(ac)+"\nProf: "+to_string(prof)+"\n";
    return s;
}

#endif //DEEPDARKFANTASY_CREATURE_H
