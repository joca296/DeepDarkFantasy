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

Item::Item(string name, int count) {
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
        UIname=document["UIname"].GetString();
        this->count=count;

        if(itemType=='c'){
            const Value& a = document["consumableEffectList"];
            shared_ptr<statusEffect> ptr;
            for(SizeType i = 0; i<a.Size(); i++)
            {
                ptr=make_shared<statusEffect>(a[i].GetString());
                consumableEffectList.push_back(ptr);
            }
        }
    }
    f.close();
}

char Item::getItemType() const {
    return itemType;
}

void Item::setItemType(char itemType) {
    Item::itemType = itemType;
}

int Item::getCount() const {
    return count;
}

void Item::setCount(int count) {
    Item::count = count;
}

const string &Item::getUIname() const {
    return UIname;
}

void Item::setUIname(const string &UIname) {
    Item::UIname = UIname;
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

Armor::Armor(string name, int count) : Item(name,count) {
    ifstream f;
    string path;
    if(PLATFORM_NAME == "windows") path = "items_and_spells\\"+name+".json";
    else path = "./items_and_spells/"+name+".json";
    f.open(path);
    if(f.is_open()){
        const Document& document = parseFromFile(&f);
        ac=document["ac"].GetInt();
        type=document["type"].GetString()[0];
        if(document["type"].GetString()[0] == 'h') STRreq=document["STRreq"].GetInt();
    }
    f.close();
}

int Armor::getSTRreq() const {
    return STRreq;
}

void Armor::setSTRreq(int STRreq) {
    Armor::STRreq = STRreq;
}

int isInVector(vector<Item*> haystack, Item* needle){
    for (int i=0 ; i<haystack.size(); i++)
        if(haystack[i]->getName() == needle->getName())
            return i;
    return -1;
}