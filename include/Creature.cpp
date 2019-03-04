#include <cmath>
#include <algorithm>
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
    if(armor != NULL){
        int result =0;
        result += armor->getAc();
        result += ( armor->getType()== 'h'? 0 : (armor->getType()== 'm'? (this->getDEX()>2 ? 2 : this->getDEX() ) : this->getDEX() ) );
        result += this->getTempAcGain();
        return result;
    }
    else return ac+getDEX()+this->getTempAcGain();
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

//Creature constructor
Creature::Creature(string name) {
    ifstream f;

    string pathHero;
    if(PLATFORM_NAME == "windows") pathHero = "heroClasses\\"+name+".json";
    else pathHero = "./heroClasses/"+name+".json";

    string pathMonster;
    if(PLATFORM_NAME == "windows") pathMonster = "monsters\\"+name+".json";
    else pathMonster = "./monsters/"+name+".json";

    f.open(pathHero);

    if(!f.is_open()) f.open(pathMonster);
    if(f.is_open()){
        const Document& document = parseFromFile(&f);

        //setting base advantages
        advantages = make_shared<Advantages>();
        advantages->STR = 0;
        advantages->DEX = 0;
        advantages->CON = 0;
        advantages->INT = 0;
        advantages->WIS = 0;
        advantages->CHA = 0;
        advantages->attack = 0;
        advantages->global = 0;

        //setting properties
        maxHP = document["hp"].GetInt();
        curHP = document["hp"].GetInt();
        maxMana = document["mana"].GetInt();
        curMana = document["mana"].GetInt();
        ac = document["ac"].GetInt() - document["dex"].GetInt();
        prof = document["prof"].GetInt();
        STR = document["str"].GetInt();
        DEX = document["dex"].GetInt();
        CON = document["con"].GetInt();
        INT = document["int"].GetInt();
        WIS = document["wis"].GetInt();
        CHA = document["cha"].GetInt();
        actionsPerRound = document["actionsPerRound"].GetInt();
        level=1;
        hitDiceNumber=1;


        //AC modifier for status effects
        tempAcGain = 0;

        //setting armor
        armor = NULL;

        //setting inventory;
        const Value& c = document["inventory"];
        for (SizeType i = 0; i < c.Size(); i++){
            Item* item = new Item(c[i].GetString());
            //if duplicate stack items
            int check = isInVector(inventory,item);
            if(check == -1)
                inventory.push_back(item);
            else
                inventory[check]->setCount(inventory[check]->getCount()+1);
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
    else cout<<"hero or monster file not open"<<endl;
    f.close();
}
//Monster constructor
Monster::Monster(string name, int level) : Creature(name) {
    ifstream f;
    string path;
    if(PLATFORM_NAME == "windows") path = "monsters\\"+name+".json";
    else path = "./monsters/"+name+".json";
    f.open(path);
    if(f.is_open()){
        const Document& document = parseFromFile(&f);

        //setting monster name
        this->setName(document["name"].GetString()+to_string(rand()%100));

        //Setting hit dice
        this->setHitDice(6);

        //setting experience
        this->setExperience(document["experience"].GetInt());

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

        //setting level
        this->lvlUp(level);
    }
    else cout<<"monster file not open"<<endl;
    f.close();
}
//Hero constructor
Hero::Hero(string name, int level) : Creature(name) {
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
        this->setName(name);

        //Setting hit dice
        this->setHitDice(document["hitDice"].GetInt());

        //setting experience
        this->setExperience(0);

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
        if(document["armor"].GetStringLength()>0) armor = new Armor(document["armor"].GetString());

        //setting level
        this->lvlUp(level);
    }
    else cout<<"hero file not open"<<endl;
    f.close();
}

char Creature::checkDamage(const string& type) {
    for (int i=0; i<this->immunity.size(); i++)
        if (this->immunity[i] == type) return 'i';

    for (int i=0; i<this->resist.size(); i++)
        if (this->resist[i] == type) return 'r';

    for (int i=0; i<this->weakness.size(); i++)
        if (this->weakness[i] == type) return 'w';

    return 'n';
}

//Monster overrides
int Monster::isHero() {
    return 0;
}
Action* Monster::actionChoose(Creature* c) {
    int choice = randomWeight(actionWeight);

    //check for manacost
    if(actionList[choice]->getType() == 's' || actionList[choice]->getType() == 'a'){
        Spell* spell = (Spell*)actionList[choice];
        if(spell->getManaCost() > this->getCurMana()) return NULL;
        else return actionList[choice];
    }
    else return actionList[choice];
}
Creature* Monster::chooseTarget(struct cList* actors){
    return getRandomListMember(actors,1);
}

//Hero overrides and methods
int Hero::isHero() {
    return 1;
}
Action* Hero::actionChoose(Creature* c) {
    cout<<"Choose an action:"<<endl;
    if(weapons.size()>0 && spellBook.size()>0){

        while(1){
            cout<<"1. Weapon"<<endl;
            cout<<"2. Spell"<<endl;
            cout<<"3. Use consumable"<<endl;
            cout<<"4. Check Status Effects"<<endl;
            cout<<"5. Check Stats"<<endl;
            cout<<"6. Back"<<endl;
            int choice;
            string choice_string;
            cin>>choice_string;
            try{
                choice=stoi(choice_string);
            }
            catch(...) {
                cout<<"INVALID INPUT enter a NUMBER"<<endl;
                choice=0;
            }
            if(choice==1) return this->selectWeapon();
            else if (choice==2) return this->selectSpell();
            else if (choice==3) return this->selectConsumable();
            else if (choice==4) StatusEffectMenu(c);
            else if (choice==5) StatsMenu(c);
            else if (choice==6) return NULL;
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
        string choice_string;
        cin>>choice_string;
        try{
            choice=stoi(choice_string);
        }
        catch(...) {
            cout<<"INVALID INPUT enter a NUMBER"<<endl;
            choice=0;
        }
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
        string choice_string;
        cin>>choice_string;
        try{
            choice=stoi(choice_string);
        }
        catch(...) {
            cout<<"INVALID INPUT enter a NUMBER"<<endl;
            choice=0;
        }
        if(choice<1 || choice>spellBook.size()+1) cout<<"Invalid input, try again."<<endl;
        else if(spellBook.size()+1==choice) return NULL;
        else {
            Spell* spell = (Spell*) spellBook[choice-1];
            if(spell->getManaCost() > this->getCurMana()){
                cout<<"You don't have enough mana to cast this."<<endl;
                return NULL;
            }
            else return spellBook[choice-1];
        }
    }
}
Action* Hero::selectConsumable() {
    cout<<"Consumables:"<<endl;
    vector<Item*> consumables;
    int i=1;
    for(int j=0; j<inventory.size(); j++){
        if(inventory[j]->getItemType() == 'c'){
            cout<<i<<". "<<inventory[j]->getUIname();
            if(inventory[j]->getCount() > 1) cout<<" ("<<inventory[j]->getCount()<<")";
            cout<<endl;
            consumables.push_back(inventory[j]);
            i++;
        }
    }
    cout<<i<<". Back"<<endl;
    while(1){
        int choice;
        string choice_string;
        cin>>choice_string;
        try{
            choice=stoi(choice_string);
        }
        catch(...) {
            cout<<"INVALID INPUT enter a NUMBER"<<endl;
            choice=0;
        }
        if(choice<1 || choice>i) cout<<"Invalid input, try again."<<endl;
        else if (choice == i) return nullptr;
        else {
            Action* tmp = new Action(consumables[choice-1]->consumableEffectList);

            //using in inventory
            int positionInInventory = isInVector(inventory,consumables[choice-1]);
            inventory[positionInInventory]->setCount(inventory[positionInInventory]->getCount() - 1);
            if(inventory[positionInInventory]->getCount()==0){
                delete inventory[positionInInventory];
                this->inventory.erase(this->inventory.begin() + positionInInventory);
            }

            return tmp;
        }
    }
}
Creature* Hero::chooseTarget(struct cList* actors){
    struct cList* tmp = actors;
    int numberOfTargets = 0;
    cout<<"Choose your target (sorted by initiative) "<<endl;
    while(tmp!=NULL){
        numberOfTargets++;
        string output = tmp->CPL->getName()+" "+to_string(tmp->CPL->getCurHP())+"/"+to_string(tmp->CPL->getMaxHP())+" HP";
        if (tmp->CPL->isHero() == 1) output += " "+to_string(tmp->CPL->getCurMana())+"/"+to_string(tmp->CPL->getMaxMana())+" Mana";
        cout<<numberOfTargets<<". ";
        if (this == tmp->CPL) colorPrint(output,"ltBlue");
        else cout<<output;
        cout<<endl;
        tmp=tmp->next;
    }
    while(1){
        int choice_container_int;
        string choice_container;
        cin>>choice_container;
        try{
            choice_container_int=stoi(choice_container);
        }
        catch(...) {
            cout<<"INVALID INPUT enter a NUMBER"<<endl;
            choice_container_int=0;
        }
        if(choice_container_int<1 || choice_container_int>numberOfTargets) cout<<"Invalid input, try again.";
        else{
            tmp=actors;
            for(int i=1; i<choice_container_int; i++) tmp=tmp->next;
            return tmp->CPL;
        }
    }
}
void Hero::listEquipped() {
    if(weapons.size() == 0) cout<<"You don't have any weapons equipped.";
    else{
        cout<<"Equipped items (select to unequip):"<<endl;
        int choiceMax;
        for(choiceMax=1; choiceMax<=weapons.size(); choiceMax++){
            cout<<choiceMax<<". "<<weapons[choiceMax-1]->getName()<<endl;
        }
        if(armor!=NULL){
            cout<<choiceMax<<". "<<armor->getUIname()<<endl;
            choiceMax++;
        }
        cout<<choiceMax<<". Back"<<endl;
        while(1){
            int choice;
            string choice_string;
            cin>>choice;
            try{
                choice=stoi(choice_string);
            }
            catch(...) {
                cout<<"INVALID INPUT enter a NUMBER"<<endl;
                choice=0;
            }
            if(choice<1 || choice>choiceMax) cout<<"Invalid input, try again."<<endl;
            else if (choice == choiceMax) return;
            else {
                if(choice == choiceMax-1 && armor!=NULL){
                    this->inventory.push_back(new Item(armor->getName()));
                    delete armor;
                    armor=NULL;
                    return;
                }
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
            cout<<i<<". ";
            if(this->getCurMana() < ((Spell*)spellBook[i-1])->getManaCost()) colorPrint(spellBook[i-1]->getName(),"red");
            cout<<endl;
        }
        cout<<endl;
    }
}
Item* Hero::listInventory(){
    Item* ajtem=nullptr;
    if(inventory.size() == 0) cout<<"Inventory empty."<<endl;
    else{
        cout<<"Inventory:"<<endl;
        int i=1;
        for(i=1; i<=inventory.size(); i++){
            cout<<i<<". "<<inventory[i-1]->getUIname();
            if(inventory[i-1]->getCount() > 1) cout<<" ("<<inventory[i-1]->getCount()<<")";
            cout<<endl;
        }
        cout<<i<<". Back"<<endl;
        while(1){
            int choice_int;
            string choice;
            cin>>choice;
            try{
                choice_int=stoi(choice);
            }
            catch(...) {
                cout<<"INVALID INPUT enter a NUMBER"<<endl;
                choice_int=0;
            }
            if(choice_int<1 || choice_int>inventory.size()+1) cout<<"Invalid input, try again."<<endl;
            else if (choice_int == inventory.size()+1) return NULL;
            else {
                bool equipFlag = false;
                char itemType = inventory[choice_int-1]->getItemType();
                if(itemType == 'w' || itemType == 'a'){
                    cout<<"0. Equip"<<endl;
                    equipFlag=true;
                }
                else if (itemType == 'c'){
                    cout<<"0. Use"<<endl;
                    equipFlag=true;
                }
                cout<<"1. Show item description"<<endl;
                cout<<"2. Drop one"<<endl;
                cout<<"3. Drop all"<<endl;
                cout<<"4. Back"<<endl;
                while(1){
                    string itemManagementChoice;
                    int itemManagementChoice_int;
                    cin>>itemManagementChoice;
                    try{
                        itemManagementChoice_int=stoi(itemManagementChoice);
                    }
                    catch(...) {
                        cout<<"INVALID INPUT enter a NUMBER"<<endl;
                        itemManagementChoice_int=-1;
                    }
                    int tmp = (equipFlag? 0:1);
                    if(itemManagementChoice_int<tmp || itemManagementChoice_int>4) cout<<"Invalid input, try again."<<endl;
                    else {
                        switch (itemManagementChoice_int) {
                            case 0:
                                if (itemType == 'w')
                                    this->weapons.push_back(callConstuctor(inventory[choice_int-1]->getName()));
                                else if(itemType == 'a')
                                    armor=new Armor(inventory[choice_int-1]->getName());
                                else
                                    this->SE_Inflict(inventory[choice_int-1]->consumableEffectList,this);

                                inventory[choice_int-1]->setCount(inventory[choice_int-1]->getCount() - 1);

                                if(inventory[choice_int-1]->getCount()==0){
                                    delete inventory[choice_int-1];
                                    this->inventory.erase(this->inventory.begin() + choice_int-1);
                                }
                                return NULL;
                            case 1:
                                cout<<inventory[choice_int-1]->getDesc()<<endl;
                                return NULL;
                            case 2:
                                ajtem = new Item(inventory[choice_int-1]->getName());

                                inventory[choice_int-1]->setCount(inventory[choice_int-1]->getCount() - 1);
                                if(inventory[choice_int-1]->getCount()==0){
                                    delete inventory[choice_int-1];
                                    this->inventory.erase(this->inventory.begin() + choice_int-1);
                                }

                                return ajtem;
                            case 3:
                                ajtem=inventory[choice_int-1];
                                this->inventory.erase(this->inventory.begin() + choice_int-1);
                                return ajtem;
                            case 4:
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
            else return this->execHeal(actors,spell,tar);
        }
        case 'a':{
            SpellAoE* spellAoE = (SpellAoE*) action;
            return this->execAoE(actors,spellAoE,tar);
        }
        case 'c':{
            this->SE_Inflict(action->actionStatusEffect,tar);
            delete action;
            return 0;
        }
        default:{
            cout<<"invalid action type in "<<action->getName()<<endl;
            return 0;

        }
    }
}
int Creature::execWeaponAttack(Weapon *action, Creature* tar){
    int atcRoll, bonus,deathCount=0;

    //determining bonus
    if(action->isFinesse()) bonus=this->getDEX();
    else bonus=this->getSTR();

    //attack roll
    bool critFlag = false;
    atcRoll = dRoll(20,this->getAdvantage("attackAdv")+this->getAdvantage("globalAdv"),1);
    if(atcRoll == 20) critFlag = true;
    else atcRoll += bonus+this->getProf();

    //attack success
    if(critFlag || atcRoll >= tar->getAc()){
        vector<string> dmgBreakdown;

        int dmgTotal = tar->calcDamage(bonus,action,dmgBreakdown);
        if(critFlag) dmgTotal += tar->calcDamage(0,action,dmgBreakdown);
        tar->setCurHP(tar->getCurHP()-dmgTotal);

        //print
        printDamage(this->getName(),tar->getName(),action->getName(),dmgTotal,dmgBreakdown,critFlag,this->isHero(),tar->isHero());

        if(action->actionStatusEffect.size()>0)  SE_Inflict(action->actionStatusEffect,tar); //(de)buff handling here
        if(tar->getCurHP() <= 0){

            deathCount++; //target died
        }
        if(tar!=this && this->getCurHP()<1)deathCount++; //attacker died

        return deathCount;
    }

    //attack failed
    else {
        cout<<this->getName()<<" missed."<<endl;
        return 0;
    }
}
int Creature::execSpellAttackST(Spell *action, Creature* tar){
    if(action->isStatusEffectOnly() == false){
        int atcRoll, bonus,deathCount=0;

        //reducing mana from creature -- checks if you can cast the spell at all are done in actionChoose
        if(action->getType() == 's') this->setCurMana(this->getCurMana()-action->getManaCost());

        //setting bonus
        if (action->getSpellCastMod() == "int") bonus=this->getINT();
        else if (action->getSpellCastMod() == "wis") bonus=this->getWIS();
        else bonus=this->getCHA();

        //attack roll
        bool critFlag = false;
        atcRoll = dRoll(20,this->getAdvantage("attackAdv")+this->getAdvantage("globalAdv"),1);
        if(atcRoll == 20) critFlag = true;
        else atcRoll += bonus+this->getProf();

        //attack success
        if(action->isSavingThrowFlag()? true : (critFlag || atcRoll >= tar->getAc())){
            vector<string> dmgBreakdown;

            int dmgTotal = tar->calcDamage(( action->isSpellCastModAddedToRoll()? bonus:0 ),action,dmgBreakdown);
            if( action->isSavingThrowFlag() && critFlag ) dmgTotal += tar->calcDamage(0,action,dmgBreakdown);
            if( action->isSavingThrowFlag() && tar->rollSave(action->getSavingThrowType()) >= action->getSavingThrowDC() ){
                dmgTotal/=2;
                dmgBreakdown.emplace_back("Succeded save (all damage halved)");
            }
            tar->setCurHP(tar->getCurHP()-dmgTotal);

            //print
            printDamage(this->getName(),tar->getName(),action->getName(),dmgTotal,dmgBreakdown,critFlag,this->isHero(),tar->isHero());

            if(action->actionStatusEffect.size()>0)  SE_Inflict(action->actionStatusEffect,tar);//(de)buff handling here
            if(tar->getCurHP() <= 0){

                deathCount++; //target died
            }
            if(this!=tar && this->getCurHP() <= 0) deathCount++; //attacker died

            return deathCount;
        }

            //attack failed
        else {
            cout<<this->getName()<<" missed."<<endl;
            return 0;
        }
    }
    else {
        if(action->actionStatusEffect.size()>0)  SE_Inflict(action->actionStatusEffect,tar);//(de)buff handling here
        if(tar->getCurHP() <= 0){
            cout<<tar->getName()<<" died."<<endl;
            return 1; //something died
        }
        else
        {

            return 0; //something didn't die
        }
    }
}
int Creature::execHeal(struct cList* actors, Spell *action, Creature* tar) {
    int bonus;

    //reducing mana from creature -- checks if you can cast the spell at all are done in actionChoose
    if(action->getType() == 's') this->setCurMana(this->getCurMana()-action->getManaCost());

    //setting bonus
    if (action->getSpellCastMod() == "int") bonus=this->getINT();
    else if (action->getSpellCastMod() == "wis") bonus=this->getWIS();
    else bonus=this->getCHA();

    //if its a monster .. to change the target to the lowest HP monster in combat
    if(this->isHero() == 0){
        struct cList* tmp = actors;
        while(tmp->CPL->isHero() == 1)
            tmp = tmp->next;
        Creature* mostInjuredDude = tmp->CPL;

        tmp = actors;
        while(tmp!=NULL){
            if(tmp->CPL->isHero() == 0){
                int missingHealthTmp = tmp->CPL->getMaxHP() - tmp->CPL->getCurHP();
                int missingHealthLargest = mostInjuredDude->getMaxHP() - mostInjuredDude->getCurHP();
                if(missingHealthTmp > missingHealthLargest)
                    mostInjuredDude = tmp->CPL;
            }
            tmp=tmp->next;
        }

        tar=mostInjuredDude;
    }

    //healing
    int healRoll= dRoll(action->getRoll(),0,action->getDiceNumber()) + (action->isSpellCastModAddedToRoll()? bonus:0);
    tar->setCurHP( tar->getCurHP()+healRoll > tar->getMaxHP()? tar->getMaxHP() : tar->getCurHP()+healRoll );

    //print
    colorPrint(this->getName(),this->isHero());
    cout<<" healed ";
    colorPrint(tar->getName(),tar->isHero());
    cout<<" for "<<healRoll<<" with "<<action->getName()<<"."<<endl;
    if(action->actionStatusEffect.size()>0) SE_Inflict(action->actionStatusEffect,tar);
    return 0;
}
int Creature::execAoE(struct cList* actors, SpellAoE *action, Creature* tar){
    struct cList* targets=NULL;
    targets=append_node(tar,targets);

    //number of valid targets
    int validTargets;
    if (tar->isHero() == 1) validTargets = heroNum(actors);
    else validTargets = monsterNum(actors);

    //choosing targets
     if(validTargets>1){
         for (int i=0; i<action->getNumberOfTargets()-1;i++){
             while(validTargets>1){
                 Creature* tmp = getRandomListMember(actors,(this->isHero() == 1? 0:1));
                 if(!isInList(tmp,targets)){
                     targets=append_node(tmp,targets);
                     validTargets--;
                     break;
                 }
             }
         }
     }

    //removing mana
    this->setCurMana(this->getCurMana()-action->getManaCost());

    //execution
    struct cList* tmp=targets;
    int deaths=0;
    while(tmp!=NULL){
        if(action->isHeal()) deaths+=this->execHeal(actors,(Spell*)action,tmp->CPL);
        else deaths+=this->execSpellAttackST((Spell*)action,tmp->CPL);
        tmp=tmp->next;
    }

    return deaths;
}
string Creature::toString(){
    string s;
    if(curHP<=0) s = name+" is dead.\n";
    else s = "Name: "+name;
    s += "\nLevel: "+to_string(level);
    s += "\nMax HP: "+to_string(maxHP);
    s += "\nCurrent HP: "+to_string(curHP);
    s += "\nMax Mana: "+to_string(maxMana);
    s += "\nCurrent Mana: "+to_string(curMana);
    s += "\nAC: "+to_string(this->getAc());
    s += "\nProficiency: "+to_string(prof);
    s += "\nStrength: "+to_string(STR);
    s += "\nDexterity: "+to_string(DEX);
    s += "\nConstitution: "+to_string(CON);
    s += "\nIntelligence: "+to_string(INT);
    s += "\nWisdom: "+to_string(WIS);
    s += "\nCharisma: "+to_string(CHA)+"\n";
    return s;
}
void Creature::listSpellBook(){};
void Creature::listEquipped(){};
Item* Creature::listInventory(){return NULL;}

int Creature::rollSave(string atr)
{
    return dRoll(20,this->getAdvantage(atr)+this->getAdvantage("globalAdv"),1);
}

int Creature::SE_Inflict(vector <shared_ptr<statusEffect>> SEV,Creature* trg)    //Inflicting status effects(buffing/debuffing)
{
    Creature* target = trg;
    for(int i =0; i<SEV.size(); i++)   //Iterates through action effects to inflict all of them
    {
        SEV[i]->target=="Self"? target=this : target=trg;   //If target is "Self" the Creature doing the action inflicts the effect on itself regardless of his targeting
        if(target->getCurHP()>0){ //Checks if target is alive

            if(SEV[i]->saveDC<1 ||  SEV[i]->saveDC>target->rollSave(SEV[i]->saving_throw_skill)) //Saving throw for the effect, assumes the effect auto-passes if SaveDC is 0 or less
            {
                if(SEV[i]->target=="Self"){ //Slightly different output text if target is self
                    colorPrint(this->getName(),this->isHero());
                    cout <<" gets inflicted by " << SEV[i]->name << endl;
                }
                else{
                    colorPrint(this->getName(),this->isHero());
                    cout << " inflicted "<<SEV[i]->name << " on ";
                    colorPrint(target->getName(),target->isHero());
                    cout << endl;
                }



                target->activeSE.push_back(SEV[i]); //Inserts the effect into the targets vector for holding status effects
                target->SEcounter.push_back(SEV[i]->duration); //Sets a counter parallel(same i) to the effect in another vector that counts down the duration later on to determine when the (de)buff should end

                for (int j = 0; j < SEV[i]->affects.size(); j++) { //Iterates through "affects" of the effect which determine what is changed by the (de)buff

                    string s = SEV[i]->affects[j];  //set s equal to the string of the j-th attribute in the i-th status effect that needs to be changed     (this is for readability purposes only)

                    target->setFieldsByString(s, target->getFieldsByString(s) + SEV[i]->val); //(de)buff the attribute of the target






                }
            }
            if(target->getMaxHP()<target->getCurHP())       target->setCurHP(target->getMaxHP());                           //Set HP to Max HP if it overflows due to status effects
            if(target->getMaxMana()<target->getCurMana())   target->setCurMana(target->getMaxMana());

        }
    }


    return 0;

}

int Creature::SE_Inflict(shared_ptr<statusEffect> ptr,Creature* trg)    //overloaded for single statuseffect
{
    Creature* target = trg;

        ptr->target=="Self"? target=this : target=trg;   //If target is "Self" the Creature doing the action inflicts the effect on itself regardless of his targeting
        if(target->getCurHP()>0){ //Checks if target is alive

            if(ptr->saveDC<1 ||  ptr->saveDC>target->rollSave(ptr->saving_throw_skill)) //Saving throw for the effect, assumes the effect auto-passes if SaveDC is 0 or less
            {
                if(ptr->target=="Self"){ //Slightly different output text if target is self
                    colorPrint(this->getName(),this->isHero());
                    cout << " gets inflicted by " << ptr->name << endl;
                }
                else{
                    colorPrint(this->getName(),this->isHero());
                    cout << " inflicted " << ptr->name << " on ";
                    colorPrint(target->getName(),target->isHero());
                    cout << endl;
                }

                target->activeSE.push_back(ptr); //Inserts the effect into the targets vector for holding status effects
                target->SEcounter.push_back(ptr->duration); //Sets a counter parallel(same i) to the effect in another vector that counts down the duration later on to determine when the (de)buff should end

                for (int j = 0; j < ptr->affects.size(); j++) { //Iterates through "affects" of the effect which determine what is changed by the (de)buff

                    string s = ptr->affects[j];  //set s equal to the string of the j-th attribute in the status effect that needs to be changed     (this is for readability purposes only)

                    target->setFieldsByString(s, target->getFieldsByString(s) + ptr->val); //(de)buff the attribute of the target
                }
            }
            if(target->getMaxHP()<target->getCurHP())       target->setCurHP(target->getMaxHP());                           //Set HP to Max HP if it overflows due to status effects
            if(target->getMaxMana()<target->getCurMana())   target->setCurMana(target->getMaxMana());

        }



    return 0;

}

void Creature::CTurnTick(int ticks,bool overrideTimer) {       //turn ticks of a creature to handle debuffs etc.

    while (ticks >= 1 && activeSE.size() != 0 && SEcounter.size() != 0) {                               //while the creature is debuffed
        if (activeSE.size() != SEcounter.size())
            cout << "FATAL ERROR RELATED TO (DE)BUFFS IN " << this->getName() << " activeSE != SEcounter" << endl;

            if (activeSE.size() != SEcounter.size())
                cout << "FATAL ERROR RELATED TO (DE)BUFFS IN " << this->getName() << " activeSE != SEcounter" << endl;

            for (int i = 0; i < SEcounter.size(); i++){
                SEcounter[i]--;                         //Decrementing duration counters for all (de)buffs at beginning of the creatures turn

            if (activeSE[i]->DOTflag == true && overrideTimer==false) { //if status effect is a dot

                setCurHP(getCurHP() + activeSE[i]->val);    //dot effect
                if (activeSE[i]->val > 0)
                    cout << this->getName() << " heals for " << activeSE[i]->val << " from " << activeSE[i]->name<< endl;                       //output if heal dot                                                                         //auto assumes dots only applies to current hp
                else
                    cout << this->getName() << " takes " << (-1) * (activeSE[i]->val) << " damage" << " from "<< activeSE[i]->name << endl;     //output if damage dot

                if (getCurHP() > getMaxHP()) setCurHP(getMaxHP()); //stops current hp from overflowing
            }

            if (SEcounter[i]<1 ||overrideTimer==true) {                                       //if counter to the corresponding status effect is less than 1 reverse the affected attributes and end the (de)buff
                for (int j = 0;j < activeSE[i]->affects.size(); j++) {  //iterates over all the attributes a single effect changed

                    string s = activeSE[i]->affects[j];                                                      // set s equal to the string of the j-th attribute in the i-th status effect that needs to be reversed (readability purposes)
                    if(s!="CurHP"||s!="CurMana")this->setFieldsByString(s, this->getFieldsByString(s) - activeSE[i]->val); //restore attribute

                }
                activeSE.erase(activeSE.begin() + i);
                SEcounter.erase(SEcounter.begin() + i);
            }
        }

        if (this->getMaxMana() < this->getCurMana()) this->setCurMana(this->getMaxMana());   //Stop mana and HP from overflowing
        if (this->getMaxHP() < this->getCurHP()) this->setCurHP(this->getMaxHP());



        ticks--; //decrement ticks
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

int Creature::StatusEffectMenu(Creature* c)
{
    int choice_max=0;
    int choice_container;
    while(true)
    {
    for(int i=0;i<c->activeSE.size(); i++)
    {
        cout<<i+1<<". "<<c->activeSE[i]->name<<" ( "<<c->SEcounter[i]<<" turns remaining )"<<endl;
        choice_max=i+1;
    }
        choice_max++;
        cout << choice_max << ". Back" << endl;
        cin >> choice_container;
        if (choice_container == choice_max) return 0;
        else if(choice_container>choice_max || choice_container<1) cout<<"Invalid input, try again"<<endl;
        else
        {
            cout<<"                   "<<c->activeSE[choice_container-1]->name<<endl;
            cout<<c->activeSE[choice_container-1]->description<<endl;
            cout<<c->SEcounter[choice_container-1]<<" turns remaining"<<endl;
        }

    }
}

void Creature::StatsMenu(Creature *c)
{
    int choice_int;
    string choice;
    cout<<c->toString()<<endl;
    cout<<"1. Back"<<endl;
    do{

        cin>>choice;
        try{
            choice_int=stoi(choice);
        }
        catch(...) {
            cout<<"INVALID INPUT enter a NUMBER "<<endl;
            choice_int=0;
        }

    }while(choice_int!=1);

}

int Creature::getActionsPerRound() const {
    return actionsPerRound;
}

void Creature::setActionsPerRound(int actionsPerRound) {
    Creature::actionsPerRound = actionsPerRound;
}

int Creature::getTempAcGain() const {
    return tempAcGain;
}

void Creature::setTempAcGain(int tempAcGain) {
    Creature::tempAcGain = tempAcGain;
}

int Creature::getAdvantage(string type){
    if(type == "strAdv" || type == "STR") return this->advantages->STR;
    if(type == "dexAdv" || type == "DEX") return this->advantages->DEX;
    if(type == "conAdv" || type == "CON") return this->advantages->CON;
    if(type == "intAdv" || type == "INT" || type == "Investigation" || type == "Arcana" ) return this->advantages->INT;
    if(type == "wisAdv" || type == "WIS" || type== "Perception" || type=="Survival" ) return this->advantages->WIS;
    if(type == "chaAdv" || type == "CHA") return this->advantages->CHA;
    if(type == "attackAdv") return this->advantages->attack;
    if(type == "globalAdv") return this->advantages->global;
    else
    {
        cout<<"Possible error passing string: '"<<type<<" to Creature::getAdvantage(string) in: "<<this->name<<endl;
        return 0;
    }
}

int Creature::getFieldsByString(string s)
{
    if(s == "STR")      return this->STR;
    if(s == "DEX")      return this->DEX;
    if(s == "CON")      return this->CON;
    if(s == "INT")      return this->INT;
    if(s == "WIS")      return this->WIS;
    if(s == "CHA")      return this->CHA;
    if(s == "AC")       return this->tempAcGain;
    if(s == "Prof")     return this->prof;
    if(s == "MaxHP")    return this->maxHP;
    if(s == "CurHP")    return this->curHP;
    if(s == "MaxMana")  return this->maxMana;
    if(s == "CurMana")  return this->curMana;
    else                return this->getAdvantage(s);
}

void Creature::setFieldsByString(string s,int n)
{
    if(s == "STR")      this->STR=n;
    if(s == "DEX")      this->DEX=n;
    if(s == "CON")      this->CON=n;
    if(s == "INT" || s == "Investigation" || s == "Arcana")          this->INT=n;
    if(s == "WIS" || s == "Perception" || s=="Survival")             this->WIS=n;
    if(s == "CHA")      this->CHA=n;
    if(s == "AC")       this->tempAcGain=n;
    if(s == "Prof")     this->prof=n;
    if(s == "MaxHP")    this->maxHP=n;
    if(s == "CurHP")    this->curHP=n;
    if(s == "MaxMana")  this->maxMana=n;
    if(s == "CurMana")  this->curMana=n;
    if(s == "strAdv")   this->advantages->STR=n;
    if(s == "dexAdv")   this->advantages->DEX=n;
    if(s == "conAdv")   this->advantages->CON=n;
    if(s == "intAdv")   this->advantages->INT=n;
    if(s == "wisAdv")   this->advantages->WIS=n;
    if(s == "chaAdv")   this->advantages->CHA=n;
    if(s == "attackAdv")this->advantages->attack=n;
    if(s == "globalAdv")this->advantages->global=n;
}

int Creature::getLevel() const {
    return level;
}

void Creature::setLevel(int level) {
    Creature::level = level;
}


int Creature::getHitDice() const {
    return hitDice;
}

void Creature::setHitDice(int hitDice) {
    Creature::hitDice = hitDice;
}

int Creature::getHitDiceNumber() const {
    return hitDiceNumber;
}

void Creature::setHitDiceNumber(int hitDiceNumber) {
    Creature::hitDiceNumber = hitDiceNumber;
}

float Creature::getExperience() const {
    return experience;
}

void Creature::setExperience(float experience) {
    Creature::experience = experience;
}

void Creature::lvlUp(int newLevel){
    for(int i=this->getLevel(); i<newLevel; i++){
        //setting new health
        int newHealth = this->getMaxHP();
        int ignoreStatusEffects = 0;
        for(int i=0; i<this->activeSE.size(); i++){
            for(int j=0; j<this->activeSE[i]->affects.size(); j++)
                if(this->activeSE[i]->affects[j] == "CON")
                    ignoreStatusEffects += activeSE[i]->val;
        }
        int x= dRoll(this->getHitDice())+this->getCON()-ignoreStatusEffects;
        newHealth += x<1? 1:x;
        this->setMaxHP(newHealth);
        this->setCurHP(newHealth);

        //setting new mana
        int newMana = this->getMaxMana();
        ignoreStatusEffects = 0;
        for(int i=0; i<this->activeSE.size(); i++){
            for(int j=0; j<this->activeSE[i]->affects.size(); j++)
                if(this->activeSE[i]->affects[j] == "MaxMana")
                    ignoreStatusEffects += activeSE[i]->val;
        }
        newMana -= ignoreStatusEffects;
        newMana *= 1.25;
        this->setMaxMana(newMana);
        this->setMaxMana(this->getMaxMana()+ignoreStatusEffects);
        this->setCurMana(newMana);

        //every even level add +1 to prof
        if(i%2 == 0){
            int newProf = this->getProf();
            newProf++;
            this->setProf(newProf);
        }

        //every level add +1 to random stat
        int randomStat=rand()%6;
        switch (randomStat){
            case 0: this->setSTR(this->getSTR()+1); break;
            case 1: this->setDEX(this->getDEX()+1); break;
            case 2: this->setCON(this->getCON()+1); break;
            case 3: this->setINT(this->getINT()+1); break;
            case 4: this->setWIS(this->getWIS()+1); break;
            case 5: this->setCHA(this->getCHA()+1); break;
        }

        //updating level
        this->setLevel(this->getLevel()+1);

        //updating hit dice numer
        this->setHitDiceNumber(this->getLevel());

        if(this->isHero() == 0)
            this->setExperience(this->getLevel()*this->getExperience()*1.25);
    }
}

void Hero::checkExperience() {
    float expOverflow = this->getExperience() - 50*1.25*(this->getLevel()+1);
    if(expOverflow >=0){
        cout<<this->getName()<<" has leveled up"<<endl;
        this->lvlUp(this->getLevel()+1);
        this->setExperience(expOverflow);
        this->checkExperience();
    }
}