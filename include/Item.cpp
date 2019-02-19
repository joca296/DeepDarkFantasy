#include "Item.h"

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
        Document document = parseFromFile(&f);

        name=document["name"].GetString();
        desc=document["desc"].GetString();
    }
    f.close();
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
        Document document = parseFromFile(&f);

        ac=document["ac"].GetInt();
        type=document["type"].GetString()[0];
    }
    f.close();
}