#ifndef DEEPDARKFANTASY_ITEM_H
#define DEEPDARKFANTASY_ITEM_H

#include <string>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"
#include "functions.h"

//cross-platform support
#ifdef __linux__
#define PLATFORM_NAME "linux"
#elif _WIN32
#define PLATFORM_NAME "windows"
#else
#endif

using namespace std;
using namespace rapidjson;

class Item {
private:
    string name, desc;
    char itemType;
public:
    char getItemType() const;
    void setItemType(char itemType);
    const string &getName() const;
    void setName(const string &name);
    const string &getDesc() const;
    void setDesc(const string &desc);

    Item(){};
    Item(string name);
};

class Armor: public Item {
private:
    int ac;
    char type;
public:
    int getAc() const;
    void setAc(int ac);
    char getType() const;
    void setType(char type);

    Armor(){};
    Armor(string name);
};


#endif //DEEPDARKFANTASY_ITEM_H