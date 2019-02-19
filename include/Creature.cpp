#include "Creature.h"
#include "cList.h"

string Creature::getName() const {
    return name;
}
void Creature::setName(string name) {
    Creature::name = name;
}
int Creature::getProf() const {
    return prof;
}
void Creature::setProf(int prof) {
    Creature::prof = prof;
}
int Creature::getMaxHP() const {
    return maxHP;
}
void Creature::setMaxHP(int maxHP) {
    Creature::maxHP = maxHP;
}
int Creature::getCurHP() const {
    return curHP;
}
void Creature::setCurHP(int curHP) {
    Creature::curHP = curHP;
}
int Creature::getAc() const {
    return ac;
}
void Creature::setAc(int ac) {
    Creature::ac = ac;
}
int Creature::getSTR() const {
    return STR;
}
void Creature::setSTR(int STR) {
    Creature::STR = STR;
}
int Creature::getDEX() const {
    return DEX;
}
void Creature::setDEX(int DEX) {
    Creature::DEX = DEX;
}
int Creature::getCON() const {
    return CON;
}
void Creature::setCON(int CON) {
    Creature::CON = CON;
}
int Creature::getINT() const {
    return INT;
}
void Creature::setINT(int INT) {
    Creature::INT = INT;
}
int Creature::getWIS() const {
    return WIS;
}
void Creature::setWIS(int WIS) {
    Creature::WIS = WIS;
}
int Creature::getCHA() const {
    return CHA;
}
void Creature::setCHA(int CHA) {
    Creature::CHA = CHA;
}
int Creature::getInit() const {
    return init;
}
void Creature::setInit(int init) {
    Creature::init = init;
}


//Monster::~Monster(){cout<<"This nigga dead "<<endl;}
//Monster constructor
Monster::Monster(string name){
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
        for (SizeType i = 0; i < a.Size(); i++){
            Action* action = callConstuctor(a[i].GetString());
            actionList.push_back(action);
        }

        //adding weights
        const Value& b = document["actionWeight"];
        for (SizeType i = 0; i < b.Size(); i++){
            actionWeight.push_back(b[i].GetInt());
        }
    }
    else cout<<"monster file not open"<<endl;
    f.close();
}

//Monster overrides
int Monster::isHero() {
    return 0;
}
Action* Monster::actionChoose() {
    int choice = randomWeight(actionWeight);
    return actionList[choice];
}
Creature* Monster::chooseTarget(struct cList* actors){
    struct cList* tmp = actors;
    while(tmp!=NULL){
        if(tmp->CPL->isHero()) return tmp->CPL;
        tmp=tmp->next;
    }
    return NULL;
}

//Hero constructor
Hero::Hero(string name){
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
        const Value& a = document["weapons"];
        for (SizeType i = 0; i < a.Size(); i++){
            Action* action = callConstuctor(a[i].GetString());
            weapons.push_back(action);
        }

        const Value& b = document["spellBook"];
        for (SizeType i = 0; i < b.Size(); i++){
            Action* action = callConstuctor(b[i].GetString());
            spellBook.push_back(action);
        }
    }
    else cout<<"hero file not open"<<endl;
    f.close();
}
//Hero overrides and methods
int Hero::isHero() {
    return 1;
}
Action* Hero::actionChoose() {
    cout<<"Choose an action:"<<endl;
    if(weapons.size()>0 && spellBook.size()>0){
        cout<<"1. Weapon"<<endl<<"2. Spell"<<endl;
        while(1){
            int choice;
            cin>>choice;
            if(choice==1) return this->selectWeapon();
            else if (choice==2) return this->selectSpell();
            else cout<<"Invalid input, try again."<<endl;
        }
    }
    else if (spellBook.size() == 0) return this->selectWeapon();
    else return this->selectSpell();
}
Action* Hero::selectWeapon() {
    for(int i=1; i<=weapons.size(); i++){
        cout<<i<<". "<<weapons[i-1]->getName()<<endl;
    }
    while(1){
        int choice;
        cin>>choice;
        if(choice<1 || choice>weapons.size()) cout<<"Invalid input, try again."<<endl;
        else return weapons[choice-1];
    }
}
Action* Hero::selectSpell() {
    for(int i=1; i<=spellBook.size(); i++){
        cout<<i<<". "<<spellBook[i-1]->getName()<<endl;
    }
    while(1){
        int choice;
        cin>>choice;
        if(choice<1 || choice>spellBook.size()) cout<<"Invalid input, try again."<<endl;
        else return spellBook[choice-1];
    }
}
Creature* Hero::chooseTarget(struct cList* actors){
    struct cList* tmp = actors;
    int numberOfTargets = 0;
    cout<<"Choose your target (sorted by initiative) "<<endl;
    while(tmp!=NULL){
        numberOfTargets++;
        cout<<numberOfTargets<<". "<<tmp->CPL->getName()<<" "<<tmp->CPL->getCurHP()<<"/"<<tmp->CPL->getMaxHP()<<" HP"<<endl;
        tmp=tmp->next;
    }
    while(1){
        int choice;
        cin>>choice;
        if(choice<1 || choice>numberOfTargets) cout<<"Invalid input, try again.";
        else{
            tmp=actors;
            for(int i=1; i<choice; i++) tmp=tmp->next;
            return tmp->CPL;
        }
    }
}
void Hero::listWeapons() {
    if(weapons.size() == 0) cout<<"You don't have any weapons equipped.";
    else{
        cout<<"Weapons:"<<endl;
        for(int i=1; i<=weapons.size(); i++){
            cout<<i<<". "<<weapons[i-1]->getName()<<endl;
        }
        cout<<endl;
    }
}
void Hero::listSpellBook() {
    if(spellBook.size() == 0) cout<<"You don't know any spells.";
    else{
        cout<<"Spells:"<<endl;
        for(int i=1; i<=spellBook.size(); i++){
            cout<<i<<". "<<spellBook[i-1]->getName()<<endl;
        }
        cout<<endl;
    }
}

//Creature class method definitions
int Creature::actionExec(struct cList* actors, Creature* tar, Action *action){
    char type = action->getType();
    switch(type){
        case 'w':{
            Weapon* weapon = (Weapon*) action;
            return this->execWeaponAttack(weapon,tar);
        }
        case 's':{
            Spell* spell = (Spell*) action;
            if(!spell->isHeal()) return this->execSpellAttackST(spell,tar);
            else return this->execHeal(spell,tar);
        }
        case 'a':{
            SpellAoE* spellAoE = (SpellAoE*) action;
            return this->execAoE(actors,spellAoE,tar);
        }
    }
}
int Creature::execWeaponAttack(Weapon *action, Creature* tar){
    int atcRoll, bonus;

    //determining attack roll
    if(action->isFinesse()) bonus=this->getDEX();
    else bonus=this->getSTR();
    atcRoll = dRoll()+bonus+this->getProf();

    //attack success
    if(atcRoll >= tar->getAc() || atcRoll-bonus-this->getProf() == 20){
        int dmgRoll = dRoll(action->getRoll(),0) + bonus;
        if(atcRoll-bonus == 20) dmgRoll+=dRoll(action->getRoll(),0,action->getDiceNumber());
        tar->setCurHP(tar->getCurHP()-dmgRoll);

        //print
        cout<<this->getName()<<" hit "<<tar->getName()<<" for "<<dmgRoll<<" damage with ";
        if(action->getName()[0]=='a') cout<<"an ";
        else cout<<"a ";
        cout<<action->getName()<<".";
        if(atcRoll-bonus == 20) cout<<" (crit)";
        cout<<endl;

        if(tar->getCurHP() <= 0){
            cout<<tar->getName()<<" died."<<endl;
            return 1; //something died
        }
        else return 0; //something didn't die
    }

    //attack failed
    else {
        cout<<this->getName()<<" missed."<<endl;
        return 0;
    }
}
int Creature::execSpellAttackST(Spell *action, Creature* tar){
    //Add saving throws

    int atcRoll, bonus;

    //setting bonus
    if (action->getSpellCastMod() == "int") bonus=this->getINT();
    else if (action->getSpellCastMod() == "wis") bonus=this->getWIS();
    else bonus=this->getCHA();

    //attack roll
    atcRoll=dRoll()+bonus+this->getProf();

    //attack success
    if(atcRoll >= tar->getAc() || atcRoll-bonus-this->getProf() == 20){
        int dmgRoll = dRoll(action->getRoll(),0) + ( action->isSpellCastModAddedToRoll()? bonus:0 );
        if(atcRoll-bonus == 20) dmgRoll+=dRoll(action->getRoll(),0,action->getDiceNumber());
        tar->setCurHP(tar->getCurHP()-dmgRoll);

        //print
        cout<<this->getName()<<" hit "<<tar->getName()<<" for "<<dmgRoll<<" damage with ";
        if(action->getName()[0]=='a') cout<<"an ";
        else cout<<"a ";
        cout<<action->getName()<<".";
        if(atcRoll-bonus == 20) cout<<" (crit)";
        cout<<endl;

        if(tar->getCurHP() <= 0){
            cout<<tar->getName()<<" died."<<endl;
            return 1; //something died
        }
        else return 0; //something didn't die
    }

    //attack failed
    else {
        cout<<this->getName()<<" missed."<<endl;
        return 0;
    }
}
int Creature::execHeal(Spell *action, Creature* tar) {
    int bonus;

    //setting bonus
    if (action->getSpellCastMod() == "int") bonus=this->getINT();
    else if (action->getSpellCastMod() == "wis") bonus=this->getWIS();
    else bonus=this->getCHA();

    //healing
    int healRoll= dRoll(action->getRoll(),0,action->getDiceNumber()) + (action->isSpellCastModAddedToRoll()? bonus:0);
    tar->setCurHP( tar->getCurHP()+healRoll > tar->getMaxHP()? tar->getMaxHP() : tar->getCurHP()+healRoll );

    //print
    cout<<this->getName()<<" healed "<<tar->getName()<<" for "<<healRoll<<" with "<<action->getName()<<"."<<endl;
    return 0;
}
int Creature::execAoE(struct cList* actors, SpellAoE *action, Creature* tar){
    //For now if target is hero .. spell will randomly take tarNumber-1 monsters for aoe
    //Monsters only target hero for now because party not implemented
    struct cList* targets=NULL;
    targets=append_node(tar,targets);

    if(this->isHero()){
        struct cList* tmp=actors;
        int x = action->getNumberOfTargets()-1;
        while(tmp!=NULL && x>0){
            if(tmp->CPL->isHero()==0 && tmp->CPL->getName()!=tar->getName()){
                targets=append_node(tmp->CPL,targets);
                x--;
            }
            tmp=tmp->next;
        }
    }

    struct cList* tmp=targets;
    int deaths=0;
    while(tmp!=NULL){
        if(action->isHeal()) deaths+=this->execHeal((Spell*)action,tmp->CPL);
        else deaths+=this->execSpellAttackST((Spell*)action,tmp->CPL);
        tmp=tmp->next;
    }

    return deaths;
}
string Creature::toString(){
    string s;
    if(curHP<=0) s = name+" is dead.\n";
    else s = "Name: "+name+"\nMax HP: "+to_string(maxHP)+"\nCurrent HP: "+to_string(curHP)+"\nAC: "+to_string(ac)+"\nProf: "+to_string(prof)+"\n";
    return s;
}
void Creature::listSpellBook(){};
void Creature::listWeapons(){};
