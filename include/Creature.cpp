#include "Creature.h"
#include "cList.h"
#include "functions.h"

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
void Creature::setMaxMana(int n)
{
    maxMana=n;
}
int Creature::getMaxMana()
{
    return maxMana;
}
void Creature::setCurMana(int n)
{
    curMana=n;
}
int Creature::getCurMana()
{
    return curMana;
}
const string &Creature::getTag() const {
    return tag;
}
void Creature::setTag(const string &tag) {
    Creature::tag = tag;
};

char Creature::checkDamage(const string& type) {
    for (int i=0; i<this->immunity.size(); i++)
        if (this->immunity[i] == type) return 'i';

    for (int i=0; i<this->resist.size(); i++)
        if (this->resist[i] == type) return 'r';

    for (int i=0; i<this->weakness.size(); i++)
        if (this->weakness[i] == type) return 'w';

    return 'n';
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
        const Document& document = parseFromFile(&f);

        //setting base monster values
        this->setName(document["name"].GetString()+to_string(rand()%100));
        this->setMaxHP(document["hp"].GetInt());
        this->setCurHP(document["hp"].GetInt());
        this->setMaxMana(document["mana"].GetInt());
        this->setCurMana(document["mana"].GetInt());
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

        //setting inventory;
        const Value& c = document["inventory"];
        for (SizeType i = 0; i < c.Size(); i++){
            Item* item = new Item(c[i].GetString());
            inventory.push_back(item);
        }

        //setting immunities
        const Value& d = document["immunity"];
        for (SizeType i = 0; i < d.Size(); i++){
            immunity.push_back(d[i].GetString());
        }

        //setting resists
        const Value& e = document["resist"];
        for (SizeType i = 0; i < e.Size(); i++){
            resist.push_back(e[i].GetString());
        }

        //setting weaknesses
        const Value& f = document["weakness"];
        for (SizeType i = 0; i < f.Size(); i++){
            weakness.push_back(f[i].GetString());
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
        const Document& document = parseFromFile(&f);

        //setting hero name
        string name;
        cout<<"Name your character."<<endl;
        cin>>name;

        //setting base hero values
        this->setName(name);
        this->setMaxHP(document["hp"].GetInt());
        this->setCurHP(document["hp"].GetInt());
        this->setMaxMana(document["mana"].GetInt());
        this->setCurMana(document["mana"].GetInt());
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

        //setting armor
        armor = NULL;
        if(document["armor"].GetString() != "") armor = new Armor(document["armor"].GetString());

        //setting inventory;
        const Value& c = document["inventory"];
        for (SizeType i = 0; i < c.Size(); i++){
            Item* item = new Item(c[i].GetString());
            inventory.push_back(item);
        }

        //setting immunities
        const Value& d = document["immunity"];
        for (SizeType i = 0; i < d.Size(); i++){
            immunity.push_back(d[i].GetString());
        }

        //setting resists
        const Value& e = document["resist"];
        for (SizeType i = 0; i < e.Size(); i++){
            resist.push_back(e[i].GetString());
        }

        //setting weaknesses
        const Value& f = document["weakness"];
        for (SizeType i = 0; i < f.Size(); i++){
            weakness.push_back(f[i].GetString());
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
        cout<<"1. Weapon"<<endl<<"2. Spell"<<endl<<"3. Back"<<endl;
        while(1){
            int choice;
            cin>>choice;
            if(choice==1) return this->selectWeapon();
            else if (choice==2) return this->selectSpell();
            else if (choice==3) return NULL;
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
    cout<<weapons.size()+1<<". Back"<<endl;
    while(1){
        int choice;
        cin>>choice;
        if(choice<1 || choice>weapons.size()+1) cout<<"Invalid input, try again."<<endl;
        else if(weapons.size()+1==choice) return NULL;
        else return weapons[choice-1];
    }
}
Action* Hero::selectSpell() {
    for(int i=1; i<=spellBook.size(); i++){
        cout<<i<<". "<<spellBook[i-1]->getName()<<endl;
    }
    cout<<spellBook.size()+1<<". Back"<<endl;
    while(1){
        int choice;
        cin>>choice;
        if(choice<1 || choice>spellBook.size()+1) cout<<"Invalid input, try again."<<endl;
        else if(spellBook.size()+1==choice) return NULL;
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
        cout<<"Weapons (select to unequip):"<<endl;
        int i=1;
        for(i=1; i<=weapons.size(); i++){
            cout<<i<<". "<<weapons[i-1]->getName()<<endl;
        }
        cout<<i<<". Back"<<endl;
        while(1){
            int choice;
            cin>>choice;
            if(choice<1 || choice>weapons.size()+1) cout<<"Invalid input, try again."<<endl;
            else if (choice == weapons.size()+1) return;
            else {
                this->inventory.push_back(new Item(weapons[choice-1]->getName()));
                delete weapons[choice-1];
                this->weapons.erase(this->weapons.begin() + choice-1);
                return;
            }
        }
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
Item* Hero::listInventory(){
    Item* ajtem=NULL;
    if(inventory.size() == 0) cout<<"Inventory empty."<<endl;
    else{
        cout<<"Inventory:"<<endl;
        int i=1;
        for(i=1; i<=inventory.size(); i++){
            cout<<i<<". "<<inventory[i-1]->getName()<<endl;
        }
        cout<<i<<". Back"<<endl;
        while(1){
            int choice;
            cin>>choice;
            if(choice<1 || choice>inventory.size()+1) cout<<"Invalid input, try again."<<endl;
            else if (choice == inventory.size()+1) return NULL;
            else {
                bool weaponFlag = false;
                if(inventory[choice-1]->getItemType() == 'w') { cout<<"0. Equip weapon"<<endl; weaponFlag=true; }
                cout<<"1. Show item description"<<endl;
                cout<<"2. Drop item"<<endl;
                cout<<"3. Back"<<endl;
                while(1){
                    int itemManagementChoice;
                    cin>>itemManagementChoice;
                    if(choice<(weaponFlag? 0:1) || choice>3) cout<<"Invalid input, try again."<<endl;
                    else {
                        switch (itemManagementChoice) {
                            case 0:
                                this->weapons.push_back(callConstuctor(inventory[choice-1]->getName()));
                                delete inventory[choice-1];
                                this->inventory.erase(this->inventory.begin() + choice-1);
                                return NULL;
                            case 1:
                                cout<<inventory[choice-1]->getDesc()<<endl;
                                return NULL;
                            case 2:

                                ajtem=inventory[choice-1];
                                this->inventory.erase(this->inventory.begin() + choice-1);
                                return ajtem;
                            case 3:
                                return NULL;
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }
    return NULL;
}
int Hero::getAc() const{
    if(armor != NULL){
        int result =0;
        result += armor->getAc();
        result += ( armor->getType()== 'h'? 0 : (armor->getType()== 'm'? (this->getDEX()>2 ? 2 : this->getDEX() ) : this->getDEX() ) );
        return result;
    }
    else return this->getAc()+this->getDEX();
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
        default:{
            cout<<"invalid action type in "<<action->getName()<<endl;
            return 0;

        }
    }
}
int Creature::execWeaponAttack(Weapon *action, Creature* tar){
    int atcRoll, bonus;

    //determining bonus
    if(action->isFinesse()) bonus=this->getDEX();
    else bonus=this->getSTR();

    //attack roll
    bool critFlag = false;
    atcRoll = dRoll();
    if(atcRoll == 20) critFlag = true;
    else atcRoll += bonus+this->getProf();

    //attack success
    if(critFlag || atcRoll >= tar->getAc()){
        vector<string> dmgBreakdown;

        int dmgTotal = tar->calcDamage(bonus,action,dmgBreakdown);
        if(critFlag) dmgTotal += tar->calcDamage(0,action,dmgBreakdown);
        tar->setCurHP(tar->getCurHP()-dmgTotal);

        //print
        printDamage(this->getName(),tar->getName(),action->getName(),dmgTotal,dmgBreakdown,critFlag);

        if(tar->getCurHP() <= 0){
            cout<<tar->getName()<<" died."<<endl;
            return 1; //something died
        }
        else
        {
            if(action->actionStatusEffect.size()>0) SE_Inflict(action,tar);                           //(de)buff handling here
            return 0; //something didn't die
        }
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
    bool critFlag = false;
    atcRoll = dRoll();
    if(atcRoll == 20) critFlag = true;
    else atcRoll += bonus+this->getProf();

    //attack success
    if(critFlag || atcRoll >= tar->getAc()){
        vector<string> dmgBreakdown;

        int dmgTotal = tar->calcDamage(( action->isSpellCastModAddedToRoll()? bonus:0 ),action,dmgBreakdown);
        if(critFlag) dmgTotal += tar->calcDamage(0,action,dmgBreakdown);
        tar->setCurHP(tar->getCurHP()-dmgTotal);

        //print
        printDamage(this->getName(),tar->getName(),action->getName(),dmgTotal,dmgBreakdown,critFlag);


        if(tar->getCurHP() <= 0){
            cout<<tar->getName()<<" died."<<endl;
            return 1; //something died
        }
        else
        {
            if(action->actionStatusEffect.size()>0) SE_Inflict(action,tar);                           //(de)buff handling here
            return 0; //something didn't die
        }
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
    if(action->actionStatusEffect.size()>0) SE_Inflict(action,tar);
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
Item* Creature::listInventory(){return NULL;}

int Creature::rollSave(string atr,int sideNum, int adv, int dNum)
{
    if(atr=="STR") return dRoll(sideNum,adv,dNum)+getSTR();
    else if(atr=="DEX") return dRoll(sideNum,adv,dNum)+getDEX();
    else if(atr=="CON") return dRoll(sideNum,adv,dNum)+getCON();
    else if(atr=="INT") return dRoll(sideNum,adv,dNum)+getINT();
    else if(atr=="WIS") return dRoll(sideNum,adv,dNum)+getWIS();
    else if(atr=="CHA") return dRoll(sideNum,adv,dNum)+getCHA();
    else
    {
        cout<<"ERROR in rollSave"<<endl;
        return 0;
    }
}

int Creature::SE_Inflict(Action* aptr,Creature* target) //Inflicting status effects(buffing/debuffing)
{
    for(int i =0; i<aptr->actionStatusEffect.size(); i++)
    {
        if(aptr->actionStatusEffect[i]->saveDC<1 || aptr->actionStatusEffect[i]->saveDC>target->rollSave(aptr->actionStatusEffect[i]->saving_throw_skill))
        {
            cout << this->getName() << " inflicted " << aptr->actionStatusEffect[i]->name << " on " << target->getName()<< endl;
            target->activeSE.push_back(aptr->actionStatusEffect[i]);
            target->SEcounter.push_back(aptr->actionStatusEffect[i]->duration);
            for (int j = 0; j < aptr->actionStatusEffect[i]->affects.size(); j++) {


                if (aptr->actionStatusEffect[i]->affects[j] == "MaxHP") {
                    target->setMaxHP(target->getMaxHP() + aptr->actionStatusEffect[i]->val);
                    if(target->getMaxHP()<target->getCurHP()) target->setCurHP(target->getMaxHP());

                }
                else if (aptr->actionStatusEffect[i]->affects[j] == "CurHP") {
                    target->setCurHP(target->getCurHP() + aptr->actionStatusEffect[i]->val);
                }
                else if (aptr->actionStatusEffect[i]->affects[j] == "MaxMana") {
                    target->setMaxMana(target->getMaxMana() + aptr->actionStatusEffect[i]->val);
                    if(target->getMaxMana()<target->getCurMana()) target->setCurMana(target->getMaxMana());
                }
                else if (aptr->actionStatusEffect[i]->affects[j] == "CurMana") {
                    target->setCurMana(target->getCurMana() + aptr->actionStatusEffect[i]->val);
                }
                else if (aptr->actionStatusEffect[i]->affects[j] == "AC") {
                    target->setAc(target->getAc() + aptr->actionStatusEffect[i]->val);
                }
                else if (aptr->actionStatusEffect[i]->affects[j] == "Prof") {
                    target->setProf(target->getProf() + aptr->actionStatusEffect[i]->val);
                }
                else if (aptr->actionStatusEffect[i]->affects[j] == "STR") {
                    target->setSTR(target->getSTR() + aptr->actionStatusEffect[i]->val);
                }
                else if (aptr->actionStatusEffect[i]->affects[j] == "DEX") {
                    target->setDEX(target->getDEX() + aptr->actionStatusEffect[i]->val);
                }
                else if (aptr->actionStatusEffect[i]->affects[j] == "CON") {
                    target->setCON(target->getCON() + aptr->actionStatusEffect[i]->val);
                }
                else if (aptr->actionStatusEffect[i]->affects[j] == "INT") {
                    target->setINT(target->getINT() + aptr->actionStatusEffect[i]->val);
                }
                else if (aptr->actionStatusEffect[i]->affects[j] == "WIS") {
                    target->setWIS(target->getWIS() + aptr->actionStatusEffect[i]->val);
                }
                else if (aptr->actionStatusEffect[i]->affects[j] == "CHA") {
                    target->setCHA(target->getCHA() + aptr->actionStatusEffect[i]->val);
                }
                else cout<<"ERROR in a status effect 'affect' json probably"<<endl;


            }
        }
    }

    return 0;

}

void Creature::CTurnTick(int ticks) {
    while(ticks>1 && activeSE.size()!=0 && SEcounter.size()!=0)
    {
        if (activeSE.size() != SEcounter.size())
            cout << "FATAL ERROR RELATED TO (DE)BUFFS IN " << this->getName() << " activeSE != SEcounter" << endl;

        for (int i = 0; i < SEcounter.size(); i++) {
            SEcounter[i]--;                                         //Decrementing duration counters for (de)buffs at the begining of the creatures turn
        }

        for (int i = 0; i < SEcounter.size(); i++) {
            if (activeSE.size() != SEcounter.size())
                cout << "FATAL ERROR RELATED TO (DE)BUFFS IN " << this->getName() << " activeSE != SEcounter" << endl;

            if (activeSE[i]->DOTflag == true)
                setCurHP(
                        getCurHP() + activeSE[i]->val);                   //auto assumes dots only applies to current hp
            if (SEcounter[i] < 1) {                                       //if counter to the corrseponding status effect is less than 1 end the (de)buff
                for (int j = 0; j < activeSE[i]->affects.size(); j++) {


                    if (activeSE[i]->affects[j] == "MaxHP") {
                        this->setMaxHP(this->getMaxHP() - activeSE[i]->val);
                        if (this->getMaxHP() < this->getCurHP()) this->setCurHP(this->getMaxHP());

                    }
                        //else if (activeSE[i]->affects[j] == "CurHP")

                    else if (activeSE[i]->affects[j] == "MaxMana") {
                        this->setMaxMana(this->getMaxMana() + activeSE[i]->val);
                        if (this->getMaxMana() < this->getCurMana()) this->setCurMana(this->getMaxMana());
                    }
                        /*else if (activeSE[i]->affects[j] == "CurMana") {
                            this->setCurMana(this->getCurMana() + activeSE[i]->val);
                        }*/
                    else if (activeSE[i]->affects[j] == "AC") {
                        this->setAc(this->getAc() - activeSE[i]->val);
                    } else if (activeSE[i]->affects[j] == "Prof") {
                        this->setProf(this->getProf() - activeSE[i]->val);
                    } else if (activeSE[i]->affects[j] == "STR") {
                        this->setSTR(this->getSTR() - activeSE[i]->val);
                    } else if (activeSE[i]->affects[j] == "DEX") {
                        this->setDEX(this->getDEX() - activeSE[i]->val);
                    } else if (activeSE[i]->affects[j] == "CON") {
                        this->setCON(this->getCON() - activeSE[i]->val);
                    } else if (activeSE[i]->affects[j] == "INT") {
                        this->setINT(this->getINT() - activeSE[i]->val);
                    } else if (activeSE[i]->affects[j] == "WIS") {
                        this->setWIS(this->getWIS() - activeSE[i]->val);
                    } else if (activeSE[i]->affects[j] == "CHA") {
                        this->setCHA(this->getCHA() - activeSE[i]->val);
                    } else cout << "ERROR in a status effect 'affect' field json probably" << endl;


                }

                activeSE.erase(activeSE.begin() + i);
                SEcounter.erase(SEcounter.begin() + i);
            }
        }
        ticks--;

    }
}

int Creature::calcDamage(int bonus, Action *action, vector<string> &dmgBreakdown) {
    //regular damage calculation
    int dmgTotal = dRoll(action->getRoll(),0,action->getDiceNumber()) + bonus;
    char check = this->checkDamage(action->getRollType());
    switch(check){
        case 'i' :
            dmgTotal=0;
            dmgBreakdown.push_back(to_string(dmgTotal)+" "+action->getRollType()+" (immune)");
            break;
        case 'r' :
            dmgTotal/=2;
            dmgBreakdown.push_back(to_string(dmgTotal)+" "+action->getRollType()+" (resistant)");
            break;
        case 'w' :
            dmgTotal*=2;
            dmgBreakdown.push_back(to_string(dmgTotal)+" "+action->getRollType()+" (weak)");
            break;
        default:
            dmgBreakdown.push_back(to_string(dmgTotal)+" "+action->getRollType());
    }

    //additional damage calculation
    for (int i=0; i<action->addtlEffects.size(); i++){
        int tmp = 0;
        tmp+= dRoll(action->addtlEffects[i]->roll,0,action->addtlEffects[i]->diceNumber);
        char tmpCheck = this->checkDamage(action->addtlEffects[i]->rollType);
        switch(tmpCheck){
            case 'i' :
                tmp=0;
                dmgBreakdown.push_back(to_string(tmp)+" "+action->addtlEffects[i]->rollType+" (immune)");
                break;
            case 'r' :
                tmp/=2;
                dmgBreakdown.push_back(to_string(tmp)+" "+action->addtlEffects[i]->rollType+" (resistant)");
                break;
            case 'w' :
                tmp*=2;
                dmgBreakdown.push_back(to_string(tmp)+" "+action->addtlEffects[i]->rollType+" (weak)");
                break;
            default:
                dmgBreakdown.push_back(to_string(tmp)+" "+action->addtlEffects[i]->rollType);
        }
        dmgTotal+=tmp;
    }

    return dmgTotal;
}