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
        numberOfActions=0;
        this->actionList = NULL;
        for (SizeType i = 0; i < a.Size(); i++){
            Action* action = callConstuctor(a[i].GetString());
            this->actionList = insert_action(action,this->actionList);
            numberOfActions++;
        }

        //adding weights
        const Value& b = document["actionWeight"];
        int j=0;
        for (SizeType i = 0; i < b.Size(); i++){
            actionWeight[j]=b[i].GetInt();
            j++;
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
    int choice = randomWeight(numberOfActions,actionWeight);
    ActionList* tmp=this->actionList;
    int i=0;
    while(tmp!=NULL){
        if(i==choice) return tmp->action;
        i++;
        tmp=tmp->next;
    }
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
        const Value& a = document["actionList"];
        numberOfActions=0;
        this->actionList = NULL;
        for (SizeType i = 0; i < a.Size(); i++){
            Action* action = callConstuctor(a[i].GetString());
            this->actionList = insert_action(action,this->actionList);
            numberOfActions++;
        }
    }
    else cout<<"hero file not open"<<endl;
    f.close();
}
//Hero overrides
int Hero::isHero() {
    return 1;
}
Action* Hero::actionChoose() {
    int i=0;
    cout<<"Choose an action:"<<endl;
    ActionList* tmp=this->actionList;
    while(tmp!=NULL){
        cout<<i<<". "<<tmp->action->getName()<<endl;
        i++;
        tmp=tmp->next;
    }
    while(1){
        int choice;
        cin>>choice;
        if(choice<0 || choice>=numberOfActions)
            cout<<"Invalid input. Try again"<<endl;
        else{
            i=0;
            tmp=this->actionList;
            while(tmp!=NULL){
                if(i==choice) return tmp->action;
                i++;
                tmp=tmp->next;
            }
        }
    }
}

//Creature class method definitions
int Creature::actionExec(struct cList* actors, Creature* tar, Action *action){
    //rework
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
    }
}
int Creature::execWeaponAttack(Weapon *action, Creature* tar){
    int atcRoll, bonus;

    //determining attack roll
    if(action->isFinesse()) bonus=this->getDEX();
    else bonus=this->getSTR();
    atcRoll = dRoll()+bonus+this->getProf();

    //attack success
    if(atcRoll >= tar->getAc() || atcRoll-bonus == 20){
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
    if(atcRoll >= tar->getAc() || atcRoll-bonus == 20){
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
/*int Creature::execAoE(struct cList* actors, Action *action, Creature* tar){
    //For now if target is hero .. spell will randomly take tarNumber-1 monsters for aoe
    //Monsters only target hero for now because party not implemented
    struct cList* targets=NULL;
    insert_node(tar,targets);

    if(this->isHero()){
        struct cList* tmp=actors;
        int x = tarNumber-1;
        while(tmp!=NULL && x>0){
            if(tmp->CPL->isHero()==0){
                insert_node(tmp->CPL,targets);
                x--;
            }
            tmp=tmp->next;
        }
    }

    //To be continued
}*/
string Creature::toString(){
    string s;
    if(curHP<=0) s = name+" is dead.\n";
    else s = "Name: "+name+"\nMax HP: "+to_string(maxHP)+"\nCurrent HP: "+to_string(curHP)+"\nAC: "+to_string(ac)+"\nProf: "+to_string(prof)+"\n";
    return s;
}
