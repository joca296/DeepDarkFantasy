#include <iostream>
#include <fstream>
#include "../include/functions.h"
#include "../include/rapidjson/document.h"

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

    void action(Creature tar){}
    string toString(){
        string s = "Name: "+name+"\nMax HP: "+to_string(maxHP)+"\nCurrent HP: "+to_string(curHP)+"\nAC: "+to_string(ac)+"\nProf: "+to_string(prof)+"\n";
        return s;
    }

};

class Monster: public Creature{
public:
    Monster(string name){
        ifstream f;
        string path = "monsters\\"+name+".json";
        f.open(path);
        if(f.is_open()){
            stringstream stream;
            stream<<f.rdbuf();
            string str = stream.str();
            const char* json = str.c_str();
            Document document;
            document.Parse(json);
            this->setName(document["name"].GetString());
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
        }
        else cout<<"File not open"<<endl;
        f.close();
    }
};

class Hero : public Creature{

};


#endif //DEEPDARKFANTASY_CREATURE_H
