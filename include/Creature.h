#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/functions.h"
#include "../include/rapidjson/document.h"
#define maxMonsterActions 10

using namespace std;
using namespace rapidjson;

#ifndef DEEPDARKFANTASY_CREATURE_H
#define DEEPDARKFANTASY_CREATURE_H


class Creature {
private:
    int maxHP, curHP, ac, prof, STR, DEX, CON, INT, WIS, CHA;
    string name;
public:
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

    virtual int action(Creature* tar)=0;
    string toString(){
        string s = "Name: "+name+"\nMax HP: "+to_string(maxHP)+"\nCurrent HP: "+to_string(curHP)+"\nAC: "+to_string(ac)+"\nProf: "+to_string(prof)+"\n";
        return s;
    }
};

class Monster: public Creature{
private:
    string actionList[maxMonsterActions];
    int actionWeight[maxMonsterActions], numberOfActions;

public:
    Monster(string name){
        ifstream f;
        string path = "monsters\\"+name+".json";
        f.open(path);
        if(f.is_open()){
            //converting file to a char* to parse file
            stringstream stream;
            stream<<f.rdbuf();
            string str = stream.str();
            const char* json = str.c_str();
            Document document;
            document.Parse(json);

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
        else cout<<"File not open"<<endl;
        f.close();
    }

    int action (Creature* tar) override{
        int choice = randomWeight(numberOfActions,actionWeight);
        string actionName = actionList[choice];
        string path = "items_and_spells\\"+actionName+".json";
        ifstream f;
        f.open(path);
        if(f.is_open()){
            //converting file to a char* to parse file
            stringstream stream;
            stream<<f.rdbuf();
            string str = stream.str();
            const char* json = str.c_str();
            Document document;
            document.Parse(json);

            //determining type of attack
            string type = document["type"].GetString();
            switch (type[0]){
                case 'w': {
                    int damage = document["damage"].GetInt(), atcRoll, bonus;
                    bool finesse = document["finesse"].GetBool();

                    //determining attack roll
                    if(finesse) bonus=this->getProf()+this->getDEX();
                    else bonus=this->getProf()+this->getSTR();
                    atcRoll = dRoll()+bonus;

                    //attack success
                    if(atcRoll >= tar->getAc() || atcRoll-bonus == 20){
                        int dmgRoll = dRoll(damage,0) + ( finesse? this->getDEX():this->getSTR() );
                        if(atcRoll-bonus == 20) dmgRoll+=dRoll(damage,0);
                        tar->setCurHP(tar->getCurHP()-dmgRoll);

                        cout<<this->getName()<<" hit "<<tar->getName()<<" for "<<dmgRoll<<" damage with ";
                        if(actionName[0]=='a') cout<<"an ";
                        else cout<<"a ";
                        cout<<actionName<<"."<<endl;

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
                break;
                case 's': /*wip*/ break;
            }
        }
        else cout<<"File not open"<<endl;
        f.close();
        return -1; //File error
    }
};

class Hero : public Creature{

};


#endif //DEEPDARKFANTASY_CREATURE_H
