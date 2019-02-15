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
    else cout<<"monster file not open"<<endl;
    f.close();
}

//Monster overrides
int Monster::isHero() {
    return 0;
}
string Monster::actionChoose() {
    int choice = randomWeight(numberOfActions,actionWeight);
    string actionName = actionList[choice];
    return actionName;
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
        int j=0;
        for (SizeType i = 0; i < a.Size(); i++){
            actionList[j]=a[i].GetString();
            j++;
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
string Hero::actionChoose() {
    while(1){
        cout<<"Choose an action:"<<endl;
        for(int i=0;i<numberOfActions;i++)
            cout<<i<<". "<<actionList[i]<<endl;
        int x;
        cin>>x;
        if(x<0 || x>=numberOfActions)
            cout<<"Invalid input. Try again";
        else return actionList[x];
    }
}

//Creature class method definitions
int Creature::actionExec(struct cList* actors, Creature* tar, string actionName){
    ifstream f;
    string path;
    if(PLATFORM_NAME == "windows") path = "items_and_spells\\"+actionName+".json";
    else path = "./items_and_spells/"+actionName+".json";
    f.open(path);
    if(f.is_open()){
        Document document = parseFromFile(&f);

        //determining type of attack
        string type = document["type"].GetString();
        switch (type[0]){
            case 'w': return this->execWeaponAttack(document["damage"].GetInt(),document["diceCount"].GetInt(),document["finesse"].GetBool(),tar,actionName);
            case 's': return this->execSpellAttackST(document["damage"].GetInt(),document["diceCount"].GetInt(),document["spellCastMod"].GetString(),document["spellCastModAddedToDamage"].GetBool(),tar,actionName);
            case 'h': return this->execHeal(document["healing"].GetInt(),document["diceCount"].GetInt(),document["spellCastMod"].GetString(),document["spellCastModAddedToHealing"].GetBool(),tar,actionName);
        }
    }
    else cout<<"action file not open"<<endl;
    f.close();
    return -1; //File error
}
int Creature::execWeaponAttack(int damage, int diceCount, bool finesse, Creature* tar, string actionName){
    int atcRoll, bonus;

    //determining attack roll
    if(finesse) bonus=this->getDEX();
    else bonus=this->getSTR();
    atcRoll = dRoll()+bonus+this->getProf();

    //attack success
    if(atcRoll >= tar->getAc() || atcRoll-bonus == 20){
        int dmgRoll = dRoll(damage,0) + bonus;
        if(atcRoll-bonus == 20) dmgRoll+=dRoll(damage,0,diceCount);
        tar->setCurHP(tar->getCurHP()-dmgRoll);

        //print
        cout<<this->getName()<<" hit "<<tar->getName()<<" for "<<dmgRoll<<" damage with ";
        if(actionName[0]=='a') cout<<"an ";
        else cout<<"a ";
        cout<<actionName<<".";
        if(atcRoll-bonus == 20) cout<<" (crit)";
        cout<<endl;

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
int Creature::execSpellAttackST(int damage, int diceCount, string spellCastMod, bool spellCastModAddedToDamage, Creature* tar, string actionName){
    //Add saving throws

    int atcRoll, bonus;

    //setting bonus
    if (spellCastMod == "int") bonus=this->getINT();
    else if (spellCastMod == "wis") bonus=this->getWIS();
    else bonus=this->getCHA();

    //attack roll
    atcRoll=dRoll()+bonus+this->getProf();

    //attack success
    if(atcRoll >= tar->getAc() || atcRoll-bonus == 20){
        int dmgRoll = dRoll(damage,0) + ( spellCastModAddedToDamage? bonus:0 );
        if(atcRoll-bonus == 20) dmgRoll+=dRoll(damage,0,diceCount);
        tar->setCurHP(tar->getCurHP()-dmgRoll);

        //print
        cout<<this->getName()<<" hit "<<tar->getName()<<" for "<<dmgRoll<<" damage with ";
        if(actionName[0]=='a') cout<<"an ";
        else cout<<"a ";
        cout<<actionName<<".";
        if(atcRoll-bonus == 20) cout<<" (crit)";
        cout<<endl;

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
int Creature::execHeal(int healing, int diceCount, string spellCastMod, bool spellCastModAddedToHealing, Creature *tar, string actionName) {
    int bonus;

    //setting bonus
    if (spellCastMod == "int") bonus=this->getINT();
    else if (spellCastMod == "wis") bonus=this->getWIS();
    else bonus=this->getCHA();

    //healing
    int healRoll= dRoll(healing,0,diceCount) + (spellCastModAddedToHealing? bonus:0);
    tar->setCurHP( tar->getCurHP()+healRoll > tar->getMaxHP()? tar->getMaxHP() : tar->getCurHP()+healRoll );

    //print
    cout<<this->getName()<<" healed "<<tar->getName()<<" for "<<healRoll<<" with "<<actionName<<"."<<endl;
    return 2;
}
int Creature::execAoE(struct cList* actors, int roll, int diceCount, int tarNumber, string spellCastMod, bool spellCastModAddedToRoll, Creature* tar, string actionName){
    //For now if target is hero .. spell will randomly take tarNumber-1 monsters for aoe
    //Monsters only target hero for now because party not implemented
    struct cList* targets=NULL;
    insert_node(0,tar,targets);

    if(this->isHero()){
        struct cList* tmp=actors;
        int x = tarNumber-1;
        while(tmp!=NULL && x>0){
            if(tmp->CPL->isHero()==0){
                insert_node(0,tmp->CPL,targets);
                x--;
            }
            tmp=tmp->next;
        }
    }

    //To be continued
}
string Creature::toString(){
    string s;
    if(curHP<=0) s = name+" is dead.\n";
    else s = "Name: "+name+"\nMax HP: "+to_string(maxHP)+"\nCurrent HP: "+to_string(curHP)+"\nAC: "+to_string(ac)+"\nProf: "+to_string(prof)+"\n";
    return s;
}