#include "Item.h"
#include "functions.h"

const string &Item::getName() const {
    return name;
}

void Item::setName(const string &name) {
    Item::name = name;
}

const string &Item::getDesc() const {
    return desc;
}

void Item::setDesc(const string &desc) {
    Item::desc = desc;
}

Item::Item(string name) {
    ifstream f;
    string path;
    if(PLATFORM_NAME == "windows") path = "items_and_spells\\"+name+".json";
    else path = "./items_and_spells/"+name+".json";
    f.open(path);
    if(f.is_open()){
        const Document& document = parseFromFile(&f);
        this->name=document["name"].GetString();
        desc=document["desc"].GetString();
        itemType=document["itemType"].GetString()[0];
    }
    f.close();
}

char Item::getItemType() const {
    return itemType;
}

void Item::setItemType(char itemType) {
    Item::itemType = itemType;
}

int Armor::getAc() const {
    return ac;
}

void Armor::setAc(int ac) {
    Armor::ac = ac;
}

char Armor::getType() const {
    return type;
}

void Armor::setType(char type) {
    Armor::type = type;
}

Armor::Armor(string name) : Item(name) {
    ifstream f;
    string path;
    if(PLATFORM_NAME == "windows") path = "items_and_spells\\"+name+".json";
    else path = "./items_and_spells/"+name+".json";
    f.open(path);
    if(f.is_open()){
        const Document& document = parseFromFile(&f);
        ac=document["ac"].GetInt();
        type=document["type"].GetString()[0];
    }
    f.close();
}