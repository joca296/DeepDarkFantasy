#include "room.h"
#include "combat.h"
#include "cList.h"

void room::set_room_desc(string s)
    {
        room_desc=s;
    }
    string room::get_room_desc()
    {
        return room_desc;
    }
    void room::set_room_name(string s)
    {
        room_name=s;
    }
    string room::get_room_name()
    {
        return room_name;
    }
    void room::set_combat_desc(string s)
    {
        combat_desc=s;
    }
    string room::get_combat_desc()
    {
        return combat_desc;
    }
    void room::set_room_next(int next[],int n)
    {
        for (int i=0; i<n; i++)
        {
            room_next[i]=next[i];
        }
    }

    string* room::getRoomNext()
    {
        return room_next;
    }
    void room::setMaxRollsAllowed(int n)
    {
        maxRollsAllowed=n;
    }
    int room::getMaxRollsAllowed()
    {
        return maxRollsAllowed;
    }

    void room::setDC_Perception(int DC)
    {
        DC_Perception=DC;
    }
    int room::getDC_Perception()
    {
        return DC_Perception;
    }
     void room::setDC_Survival(int DC)
    {
        DC_Survival=DC;
    }
    int room::getDC_Survival()
    {
        return DC_Survival;
    }
    void room::setDC_Investigation(int DC)
    {
         DC_Investigation=DC;
    }
    int room::getDC_Investigation()
    {
        return DC_Investigation;
    }
     void room::setDC_Arcana(int DC)
    {
         DC_Arcana=DC;
    }
    int room::getDC_Arcana()
    {
        return DC_Arcana;
    }

    void room::setPerception_SUCC_text(string s)
    {
        Perception_SUCC_text=s;
    }
    string room::getPerception_SUCC_text()
    {
        return Perception_SUCC_text;
    }
    void room::setInvestigation_SUCC_text(string s)
    {
        Investigation_SUCC_text=s;
    }
    string room::getInvestigation_SUCC_text()
    {
        return Survival_SUCC_text;
    }
    void room::setSurvival_SUCC_text(string s)
    {
        Survival_SUCC_text=s;
    }
    string room::getSurvival_SUCC_text()
    {
        return Survival_SUCC_text;
    }
    void room::setArcana_SUCC_text(string s)
    {
        Arcana_SUCC_text=s;
    }
    string room::getArcana_SUCC_text()
    {
        return Arcana_SUCC_text;
    }
    //

    void room::setPerception_FAIL_text(string s)
    {
        Perception_FAIL_text=s;
    }
    string room::getPerception_FAIL_text()
    {
        return Perception_FAIL_text;
    }
    void room::setInvestigation_FAIL_text(string s)
    {
        Survival_FAIL_text=s;
    }
    string room::getInvestigation_FAIL_text()
    {
        return Investigation_FAIL_text;
    }
    void room::setSurvival_FAIL_text(string s)
    {
        Survival_FAIL_text=s;
    }
    string room::getSurvival_FAIL_text()
    {
        return Survival_FAIL_text;
    }
    void room::setArcana_FAIL_text(string s)
    {
        Arcana_FAIL_text=s;
    }
    string room::getArcana_FAIL_text()
    {
        return Arcana_FAIL_text;
    }
    void room::setRoomEnteredFlag(bool f)
    {
        roomEnteredFlag=f;
    }
    bool room::getRoomEnteredFlag()
    {
        return roomEnteredFlag;
    }
    int room::getNumberOfConnections() const {
        return numberOfConnections;
    }

    void room::setNumberOfConnections(int numberOfConnections) {
        room::numberOfConnections = numberOfConnections;
    }

    const string &room::getRoom_name_ui() const {
        return room_name_ui;
    }

    void room::setRoom_name_ui(const string &room_name_ui) {
        room::room_name_ui = room_name_ui;
    }


room::room(string name) //constructor
{
    ifstream f;
    string path;
    if(PLATFORM_NAME == "windows") path = "rooms\\"+name+".json";
    else path = "./rooms/"+name+".json";
    f.open(path);
    if(f.is_open()){
        const Document& document = parseFromFile(&f);

        this->set_room_name(document["name"].GetString());
        this->setDC_Perception(document["DC_Perception"].GetInt());
        this->setDC_Investigation(document["DC_Investigation"].GetInt());
        this->setDC_Survival(document["DC_Survival"].GetInt());
        this->setDC_Arcana(document["DC_Arcana"].GetInt());
        this->setPerception_SUCC_text(document["Perc_SUCC"].GetString());
        this->setInvestigation_SUCC_text(document["Invest_SUCC"].GetString());
        this->setSurvival_SUCC_text(document["Surv_SUCC"].GetString());
        this->setArcana_SUCC_text(document["Arc_SUCC"].GetString());
        this->setPerception_FAIL_text(document["Perc_FAIL"].GetString());
        this->setInvestigation_FAIL_text(document["Invest_FAIL"].GetString());
        this->setSurvival_FAIL_text(document["Surv_FAIL"].GetString());
        this->setArcana_FAIL_text(document["Arc_FAIL"].GetString());
        this->set_combat_desc(document["combatDesc"].GetString());
        this->setMaxRollsAllowed(document["maxRolls"].GetInt());

        const Value& a = document["connectedRooms"];              //setting connected rooms
        int j=0;
        this->numberOfConnections=0;
        for (SizeType i = 0; i < a.Size(); i++){
            this->room_next[j]=a[i].GetString();
            j++;
            this->numberOfConnections++;
        }

        const Value& b = document["monsters"];              //setting monsters
        j=0;
        this->numberOfMonsters=0;
        if(b.Size()>0){
            for (SizeType i = 0; i < b.Size(); i++){
                this->room_monsters[j]=b[i].GetString();
                //cout<<this->room_monsters[j]<<endl;
                j++;
                this->numberOfMonsters++;
            }
        }
        const Value& c = document["events"];              //setting events
        j=0;
        this->numberOfTraps=0;
        if(c.Size()>0) {
            for (SizeType i = 0; i < c.Size(); i++) {

                this->room_traps[j] = new trap(c[i].GetString());
                //cout<<"ASS"<<endl;
                //cout<<this->room_events[j]<<endl;
                j++;
                this->numberOfTraps++;
            }
        }
        const Value& d = document["GroundItems"];              //setting events

        if(d.Size()>0){
            for (SizeType i = 0; i <d.Size(); i++){

                Item* Iptr=new Item(d[i].GetString());
                groundItems.push_back(Iptr);

            }
        }
        const Value& e = document["Shrines"];
        shared_ptr<event> ptr;
        if(e.Size()>0) {
            for (SizeType i = 0; i < a.Size(); i++) {
                ptr = make_shared<trap>(e[i].GetString());
                room_shrine.push_back(ptr);
            }
        }
        const Value& f = document["connectedRoomsUI"];
        j=0;
        for (SizeType i = 0; i < f.Size(); i++){
            this->room_next_ui[j]=f[i].GetString();
            j++;

        }
        const Value& g = document["HiddenItems"];
        hiddenItem* ptr2;
        for (SizeType i = 0; i < g.Size(); i++) {
            ptr2=new hiddenItem(g[i].GetString());
            this->room_hidden_items.push_back(ptr2);
        }
    }

    else cout<<"room file not open"<<endl;
    f.close();
}


room* room::enterRoom(struct cList *partyHead)
{
    room *nRoom=nullptr;
    string eChoice;

    if(getRoomEnteredFlag()==false)
    {
        rHead=append_node(this,rHead);

        if(numberOfMonsters>0)
        {
            if(combat(partyHead,room_monsters,numberOfMonsters,combat_desc)==-1) return nRoom;
        }
    }
    int current_tries_remain = this->getMaxRollsAllowed();

    int choice_container_int;
    string choice_container;

    //bool choice_made_flag=false;;
    cout<<get_room_desc()<<endl;
    while(true)
    {
        //choice_made_flag=false;
        basic_choise_text(partyHead->CPL);
        cin>>choice_container;
        try{
            choice_container_int=stoi(choice_container);
        }
        catch(...) {
            cout<<"INVALID INPUT enter a NUMBER of the class you wish to choose"<<endl;
            choice_container_int=0;
        }
        switch(choice_container_int)
        {
            case 1:
                if(current_tries_remain>0 && this->getRoomEnteredFlag()==false)
                {
                    if(basic_checks(partyHead->CPL)!=5) current_tries_remain--;
                }
                else cout<<"You have no further interest in this place "<<endl;
                break;
            case 2:
                cout<<"Special Interactions WIP "<<endl;
                special_interactions(partyHead->CPL);
                break;
            case 3:
                this->InspectHero(partyHead);
                break;
            case 4:
                printMap(rHead);
                cout<<endl;
                break;
            case 5:
                cout<<"short rest WIP"<<endl;
                break;
            case 6:
                //cout<<"EXIT WIP"<<endl;
                eChoice=exit_room(partyHead->CPL);
                if(partyHead->CPL->getCurHP()<1)
                {
                    partyHead=prune_cList(partyHead);
                }
                if(!eChoice.empty())
                {
                    if(findRoom(rHead,eChoice)==nullptr)
                    {
                        setRoomEnteredFlag(true);
                        partyTurnTick(partyHead);
                        partyHead=pruneParty(partyHead);
                        if(partyHead==nullptr)return nRoom;
                        nRoom=new room(eChoice);
                        return nRoom;
                    }
                    else
                    {


                        setRoomEnteredFlag(true);
                        return findRoom(rHead,eChoice)->RPL;
                    }

                }
                break;
            default:
                cout<<"INVALID INPUT "<<endl;
        }
    }
}

void room::basic_choise_text(Creature *p)
{
    cout<<"1. Basic Checks "<<endl;
    cout<<"2. Special Interactions "<<endl;
    cout<<"3. Inspect Hero"<<endl;
    cout<<"4. Show Map "<<endl;
    cout<<"5. Short Rest"<<endl;
    cout<<"6. Exit Room "<<endl;
}

void room::InspectHero(struct cList* partyHead) {

    int choice_container_int;
    string choice_container;
    do {
        cout << "1. Open Inventory " << endl;
        cout << "2. Show Equipped items " << endl;
        cout << "3. Open Spellbook" << endl;
        cout << "4. Open Stats " << endl;
        cout << "5. Open Status Effects"<<endl;
        cout << "6. Swap Hero " << endl;
        cout << "7. Back" << endl;
        cin >> choice_container;
        try{
            choice_container_int=stoi(choice_container);
        }
        catch(...) {
            cout<<"INVALID INPUT enter a NUMBER of the class you wish to choose"<<endl;
            choice_container_int=0;
        }
        switch (choice_container_int) {
            case 1: {
                Item *Itmp = partyHead->CPL->listInventory();
                //cout<<Itmp->getName()<<endl;

                if (Itmp != nullptr) {
                    for(int i=0; i<Itmp->getCount(); i++){
                        Item* x = new Item(Itmp->getName());
                        this->groundItems.push_back(x);
                    }
                    delete Itmp;
                }
                break;
            }
            case 2:
                partyHead->CPL->listEquipped();
                break;
            case 3:
                partyHead->CPL->listSpellBook();
                break;
            case 4:
                cout << partyHead->CPL->toString() << endl;
                break;
            case 5:
                partyHead->CPL->StatusEffectMenu(partyHead->CPL);
                break;
            case 6:
                cout<<"Swap Hero WIP"<<endl;
                this->swapHero(partyHead);
                break;
            case 7: return ;
        }
    }while(choice_container_int!=7);
    return ;
}

void room::swapHero(struct cList* partyHead)
{
    int counter=1,choice_container;
    struct cList* ptr=partyHead;
    while(ptr!=nullptr)
    {
        cout<<counter<<". ";
        if(partyHead->CPL==ptr->CPL)
            colorPrint(ptr->CPL->getName()+" (active) ","ltBlue");
        else cout<<ptr->CPL->getName();
        cout<<endl;
        counter++;
        ptr=ptr->next;
    }
    ptr=partyHead;
    do {
        cin >> choice_container;
        if(choice_container<1 || choice_container>counter)cout<<"Invalid input, try again"<<endl;
    }while(choice_container<1 || choice_container>counter);

    for(int i=1;i!=choice_container; i++)
    {
        ptr=ptr->next;
    }
    swapNode(partyHead,ptr);
    return ;
}
//meta getters
string room::getSUCCbyString(string s)
{

    if(s=="Perception") return getPerception_SUCC_text();
    if(s=="Investigation") return getInvestigation_SUCC_text();
    if(s=="Survival") return getSurvival_SUCC_text();
    if(s=="Arcana") return getArcana_SUCC_text();
    return s;
}
string room::getFAILbyString(string s)
{
    if(s=="Perception") return getPerception_FAIL_text();
    if(s=="Investigation") return getInvestigation_FAIL_text();
    if(s=="Survival") return getSurvival_FAIL_text();
    if(s=="Arcana") return getArcana_FAIL_text();
    return s;

}
int room::getDCbyString(string s)
{
    if(s=="Perception") return this->DC_Perception;
    if(s=="Investigation") return this->DC_Investigation;
    if(s=="Survival") return this->DC_Survival;
    if(s=="Arcana") return this->DC_Arcana;
    return 0;
}

int room::basic_checks(Creature *p)
{
    int choice_container,roll_container;
    string s,choice_container_string;
    bool isSomethingFound = false;
    do
    {
        basic_checks_text();
        cin>>choice_container_string;
        try{
            choice_container=stoi(choice_container_string);
        }
        catch(...) {
            cout<<"INVALID INPUT enter a NUMBER of the class you wish to choose"<<endl;
            choice_container=0;
        }
        switch(choice_container)                    //Converting choice int to needed string
        {
        case 1:
            s="Perception";
            break;
        case 2:
            s="Investigation";
            break;
        case 3:
            s="Survival";
            break;
        case 4:
            s="Arcana";
            break;
        case 5:
            return 5;
        default:
            cout<<"Invalid input, try again "<<endl;
        }
    }while(choice_container<1 || choice_container>5); //while input invalid

    roll_container = p->rollSave(s);
    for(int i=0; i<numberOfTraps;i++) //trap discovery handling
    {
        if(room_traps[i]->getSkill()==s && roll_container>=room_traps[i]->getCheckDC())  //if trap skill needed to find it corresponds to chosen skill and if passed the DC
        {
            room_traps[i]->eDisc=true;                                                   //Trap discovered flag set to true
            cout<<room_traps[i]->getCheck_succ_text()<<endl;                             //Output that the trap is found to the user
            isSomethingFound = true;                                                    //Set that something has been discovered for this scopes purposes

        }
    }
    for(int i=0; i<room_shrine.size(); i++) //shrine discovery handling
    {
        if(room_shrine[i]->getSkill()==s && roll_container>=room_shrine[i]->getCheckDC())
        {
            room_shrine[i]->eDisc=true;
            cout<<room_shrine[i]->getCheck_succ_text()<<endl;
            isSomethingFound = true;
        }
    }
    for(int i=0; i<room_hidden_items.size(); i++)                                               //Hidden Items handling
    {
        if(room_hidden_items.at(i)->getSkill()==s && roll_container>=room_hidden_items.at(i)->getCheckDC()) {
            cout<<room_hidden_items.at(i)->getCheck_succ_text()<<endl;
            isSomethingFound=true;
            for (int j=0; j<room_hidden_items.at(i)->hItems.size(); j++)
            {
                groundItems.push_back(room_hidden_items.at(i)->hItems.at(j));
            }
        }
    }
    if(getSUCCbyString(s)!="" && roll_container>=this->getDCbyString(s))
    {
        cout<<getSUCCbyString(s)<<endl;
        return 1;                                                                       //Additional room information if successful DC check
    }
    else if(isSomethingFound == false)                                                  //if nothing found and DC failed or failed by default cause the success string is empty print the fail text
    {
        cout<<getFAILbyString(s)<<endl;
        return -1;
    }
    return 0;

}

void room::basic_checks_text()
{
    cout<<"1. Perception "<<endl;
    cout<<"2. Investigation"<<endl;
    cout<<"3. Survival"<<endl;
    cout<<"4. Arcana"<<endl;
    cout<<"5. Back "<<endl;
}



string room::exit_room(Creature *p)
{
    string s;
    for(int i=0; i<numberOfTraps; i++)
    {
        if(this->numberOfTraps>0 && room_traps[i]->isDisarmed==false) activateTrap(room_traps[i],p);
        if(p->getCurHP()<1)
        {

            return s;

        }
    }
    while(true){
    int cContainer=0;
    string cContainer_string;
    int j=0;
    for(int i=0; i<this->numberOfConnections; i++)
    {
        cout<<i+1<<". "<<this->room_next_ui[i];if(findRoom(rHead,room_next[i])!=NULL)cout<<" (visited)";
        cout<<endl;
        j=i+2;
    }
    cout<<j<<". Back "<<endl;
    cin>>cContainer_string;
        try{
            cContainer=stoi(cContainer_string);
        }
        catch(...) {
            cout<<"INVALID INPUT enter a NUMBER"<<endl;
            cContainer=0;
        }
    if(cContainer<j && cContainer>0)
    {
        return this->room_next[cContainer-1];
    }
    else if(cContainer==j) return s;
    else cout<<"Invalid! Try again "<<endl;
    }

}

int room::special_interactions(Creature *p)
{
    int choice_container,roll_container;
    int counter=1, counterTraps=0,counterShrines=0;
    int item_counter=groundItems.size();
    string choice_container_string;
    do{             //prints choices and takes input
        counter=1;
        for(int i=0; i<numberOfTraps; i++)
        {
            if(numberOfTraps>0 && room_traps[i]->eDisc==true && room_traps[i]->isDisarmed==false)
            {
                cout<<counter<<". "<<room_traps[i]->getInteract_text()<<endl;
                counter++;
                counterTraps++;
            }
        }
        for(int i=0; i<room_shrine.size();i++)
        {
            if(room_shrine[i]->eDisc==true && room_traps[i]->isDisarmed==false)
            {
                cout<<counter<<". "<<room_shrine[i]->getInteract_text()<<endl;
                counter++;
                counterShrines++;
            }
        }
        for(int i=0; i<groundItems.size(); i++)
        {
            cout<<counter<<". Pick up "<<groundItems[i]->getName()<<endl;
            counter++;
        }
        cout<<counter<<". "<<"Back"<<endl;
        cin>>choice_container_string;
        try{
            choice_container=stoi(choice_container_string);
        }
        catch(...) {
            cout<<"INVALID INPUT enter a NUMBER"<<endl;
            choice_container=0;
        }
        if(choice_container>counter || choice_container<1) cout<<"Invalid input, try again! "<<endl;
    }while(choice_container>counter || choice_container<1);
    if(choice_container==counter) return 0;
    else if(choice_container<counter-item_counter-counterShrines)
    {
        roll_container=p->rollSave(room_traps[choice_container-1]->getSave());                                                                                  //trap disarm
        if(roll_container>=room_traps[choice_container-1]->getDisarmDC() && roll_container!=1)
        {
            cout<<room_traps[choice_container-1]->getDisarm_succ_text()<<endl;
            room_traps[choice_container-1]->isDisarmed=true;
            return 1;
        }
        else
        {
            room_traps[choice_container-1]->getDisarm_fail_text();
            activateTrap(room_traps[choice_container-1],p);
            return -1;
        }

    }
    else if(choice_container<counter-item_counter) {
        if (room_shrine[choice_container - 1 - counterTraps]->eventStatusEffect.size() != 2)
        {
            cout<<"ERROR shrine needs to have 2 status effects"<<endl;
            return -2;
        }
        roll_container=p->rollSave(room_shrine[choice_container-1-counterTraps]->getSave());
        if(roll_container>=room_shrine[choice_container-1-counterTraps]->getDisarmDC() && roll_container!=1)
        {
            cout<<room_shrine[choice_container-1-counterTraps]->getDisarm_succ_text()<<endl;
            p->SE_Inflict(room_shrine[choice_container-1-counterTraps]->eventStatusEffect[0],p);
        }
        else
        {
            cout<<room_shrine[choice_container-1-counterTraps]->getDisarm_fail_text()<<endl;
            p->SE_Inflict(room_shrine[choice_container-1-counterTraps]->eventStatusEffect[1],p);
        }
    }
    else
    {
        int x = isInVector(p->inventory,groundItems[choice_container-counterTraps-1-counterShrines]);
        if(x == -1)
            p->inventory.push_back(groundItems[choice_container-counterTraps-1-counterShrines]);
        else{
            p->inventory[x]->setCount(p->inventory[x]->getCount()+1);
            delete groundItems[choice_container-counterTraps-1-counterShrines];
        }
        groundItems.erase(groundItems.begin()+choice_container-counterTraps-1-counterShrines);
    }
    return -2;
}





//Room list functions
struct rList *append_node(room*r, struct rList *rHead)
{

    struct rList *newNode;
    struct rList *ptr;
    newNode=new struct rList;


    newNode->RPL=r;

    if(rHead==NULL)
    {
        rHead=newNode;
        newNode->next=NULL;
       // cout<<"APPENDING "<<rHead->RPL->get_room_name()<<endl;
        return rHead;
    }
    else
        {
            ptr=rHead;
            while(ptr->next!=NULL)
            {
            ptr=ptr->next;

            }
            ptr->next=newNode;
            newNode->next=NULL;
             //cout<<"APPENDING "<<newNode->RPL->get_room_name()<<endl;
            return rHead;
        }

}


void delete_rList(struct rList *rHead)
{


    struct rList* ptr;
    struct rList* tmp;

    while(rHead!=NULL)
    {
        ptr=rHead;
        rHead=rHead->next;
        //cout<<ptr->RPL->get_room_name()<<" is to be deleted next "<<endl;
        delete ptr;
    }

}

struct rList *findRoom(struct rList *rHead,string& s)
{
    struct rList* ptr;
    ptr=rHead;
    while(ptr!=NULL)
    {
        //cout<<"COMPARING "<<ptr->RPL->get_room_name()<<" WITH "<<s<<endl;
        if(ptr->RPL->get_room_name()==s)
            {
                return ptr;
            }
        ptr=ptr->next;
    }
    return NULL;
}

void room::activateTrap(event* e, Creature *p)
{
    int dimaga,roll_container;
    roll_container=p->rollSave(e->getSave());

        if(roll_container>=e->getSaveDC())
        {
            cout<<e->getSave_succ_text()<<endl;
            dimaga=(e->getSaveMulti()*dRoll(e->getDMG(),0,e->getDNum()));
            cout<<p->getName()<<" takes "<<dimaga<<" damage"<<endl;
            p->setCurHP(p->getCurHP()-dimaga);



        }
        else {
            cout << e->getSave_fail_text() << endl;
            dimaga = dRoll(e->getDMG(), 0, e->getDNum());
            cout << p->getName() << " takes " << dimaga << " damage" << endl;
            p->setCurHP(p->getCurHP() - dimaga);
            if(e->eventStatusEffect.size()>0) p->SE_Inflict(e->eventStatusEffect,p);
        }


    e->isDisarmed=true;
}


void printMap(struct rList *rHead, int level){
    if(rHead!=nullptr){
        for (int i = 1; i < level; i++)
            cout<<"\t";
        cout<<rHead->RPL->getRoom_name_ui();
        cout<<endl;
        for (int i=0; i<rHead->RPL->getNumberOfConnections();i++) {
            rList* tmp = findRoom(rHead,rHead->RPL->room_next[i]);
            if(tmp != nullptr)
                printMap(tmp,level+1);
        }
    }
}

struct rList* rHead=nullptr;

void partyTurnTick(struct cList* partyHead,int n)
{
    while(partyHead!=NULL)
    {
        partyHead->CPL->CTurnTick(n);
        partyHead=partyHead->next;
    }
}

