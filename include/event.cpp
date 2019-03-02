#include "event.h"
#include "functions.h"

void event::setCheckDC(int n)
{
    CheckDC=n;
}
int event::getCheckDC()
{
    return CheckDC;
}
void event::setSaveDC(int n)
{
    SaveDC=n;
}
int event::getSaveDC()
{
    return SaveDC;
}
void event::setDMG(int n)
{
    DMG=n;
}
int event::getDMG()
{
    return DMG;
}
void event::setDNum(int n)
{
    dNum=n;
}
int event::getDNum()
{
    return dNum;
}
void event::setDisarmDC(int n)
{
    DisarmDC=n;
}
int event::getDisarmDC()
{
    return DisarmDC;
}


void event::setInteract_text(string s)
{
    interact_text=s;
}
string event::getInteract_text()
{
    return interact_text;
}
void event::setCheck_succ_text(string s)
{
    check_succ_text=s;
}
string event::getCheck_succ_text()
{
    return check_succ_text;
}
void event::setSave_succ_text(string s)
{
    save_succ_text=s;
}
string event::getSave_succ_text()
{
    return save_succ_text;
}
void event::setSave_fail_text(string s)
{
    save_fail_text=s;
}

string event::getSave_fail_text()
{
    return save_fail_text;
}

void event::setSkill(string s)
{
    skill=s;
}
string event::getSkill()
{
    return skill;
}
void event::setSave(string s)
{
    save = s;
}
string event::getSave()
{
    return save;
}

void event::setDisarm_succ_text(string s)
{
    disarm_succ_text=s;
}
string event::getDisarm_succ_text()
{
    return disarm_succ_text;
}

void event::setDisarm_fail_text(string s)
{
    disarm_fail_text=s;
}
string event::getDisarm_fail_text()
{
    return disarm_fail_text;
}

void event::setSaveMulti(float f)
{
    SaveMulti=f;
}
float event::getSaveMulti()
{
    return SaveMulti;
}


trap::trap(string name)
{
    ifstream f;
    string path;
    if(PLATFORM_NAME == "windows") path = "events\\"+name+".json";
    else path = "./events/"+name+".json";
    f.open(path);
    if(f.is_open()){
        const Document& document = parseFromFile(&f);

        this->setInteract_text(document["Interact"].GetString());
        this->setDMG(document["DMG"].GetInt());
        this->setDNum(document["dNum"].GetInt());
        this->setCheckDC(document["CheckDC"].GetInt());
        this->setSkill(document["Skill"].GetString());
        this->setCheck_succ_text(document["CheckSUCC"].GetString());
        this->setSaveDC(document["SaveDC"].GetInt());
        this->setSave(document["Save"].GetString());
        this->setSave_succ_text(document["SaveSUCC"].GetString());
        this->setSave_fail_text(document["SaveFAIL"].GetString());
        this->setSaveMulti(document["SaveMulti"].GetFloat());
        this->setDisarmDC(document["DisarmDC"].GetInt());
        this->setDisarm_succ_text(document["DisSucc"].GetString());
        this->setDisarm_fail_text(document["DisFail"].GetString());

        const Value& a = document["statusEffectList"];
        shared_ptr<statusEffect> ptr;
        for(SizeType i = 0; i<a.Size(); i++)
        {
            ptr=make_shared<statusEffect>(a[i].GetString());
            eventStatusEffect.push_back(ptr);
        }

    }
    else cout<<"trap file not open"<<endl;
    f.close();
}

hiddenItem::hiddenItem(string name)
{
    ifstream f;
    string path;
    if(PLATFORM_NAME == "windows") path = "events\\"+name+".json";
    else path = "./events/"+name+".json";
    f.open(path);
    if(f.is_open()){
        const Document& document = parseFromFile(&f);

        this->setCheckDC(document["CheckDC"].GetInt());
        this->setSkill(document["Skill"].GetString());
        this->setCheck_succ_text(document["CheckSUCC"].GetString());

        const Value& a = document["ItemList"];
        Item* ptr;
        for(SizeType i = 0; i<a.Size(); i++)
        {
            ptr=new Item(a[i].GetString());
            hItems.push_back(ptr);
        }
    }
    else cout<<"hiddenItem file not open"<<endl;
    f.close();
}
