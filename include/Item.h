#pragma once

#include <string>
#include <memory>
#include <vector>
#include "statusEffect.h"

//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

using namespace std;

class Item {
private:
    string name, desc, UIname;
    char itemType;
    int count;
public:
    vector <shared_ptr<statusEffect>> consumableEffectList;

    int getCount() const;
    void setCount(int count);
    char getItemType() const;
    void setItemType(char itemType);
    const string &getUIname() const;
    void setUIname(const string &UIname);
    const string &getName() const;
    void setName(const string &name);
    const string &getDesc() const;
    void setDesc(const string &desc);

    Item(){};
    Item(string name, int count =1);
};

class Armor: public Item {
private:
    int ac, STRreq;
    char type;
public:
    int getSTRreq() const;
    void setSTRreq(int STRreq);
    int getAc() const;
    void setAc(int ac);
    char getType() const;
    void setType(char type);

    Armor(){};
    Armor(string name, int count =1);
};

int isInVector(vector<Item*> haystack, Item* needle);