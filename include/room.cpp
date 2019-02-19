#include "room.h"

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
        Survival_SUCC_text=s;
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
        return Survival_FAIL_text;
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


room* room::enterRoom(Creature *p)
{

    room *nRoom=NULL;
    string eChoice;

    if(getRoomEnteredFlag()==false)
    {


        if(numberOfMonsters>0)
        {
            if(combat(p,room_monsters,numberOfMonsters,combat_desc)==-1) return nRoom;
        }
    }
    int current_tries_remain = this->getMaxRollsAllowed();

    int choice_container;

    //bool choice_made_flag=false;;
    cout<<get_room_desc()<<endl;
    while(true)
    {
        //choice_made_flag=false;
        basic_choise_text(p);
        cin>>choice_container;
        switch(choice_container)
        {
            case 1:
                    if(current_tries_remain>0 && this->getRoomEnteredFlag()==false)
                    {
                        if(basic_checks(p)!=5) current_tries_remain--;
                    }
                else cout<<"You have no further interest in this place "<<endl;
                break;
            case 2:
                cout<<"Special Interactions WIP "<<endl;
                special_interactions(p);
                break;
            case 3:
                cout<<"Open Inventory WIP "<<endl;
                break;
            case 4:
                cout<<"Open Spellbook WIP"<<endl;
                break;
            case 5:
                //cout<<"Open Stats WIP "<<endl;
                cout<<p->toString()<<endl;
                break;
            case 6:
                cout<<"EXIT WIP"<<endl;
                eChoice=exit_room(p);
                if(!eChoice.empty())
                {
                    if(findRoom(rHead,eChoice)==NULL)
                    {

                        nRoom=new room(eChoice);
                        //cout<<"Making new Room "<<nRoom->get_room_name()<<endl;
                        if(getRoomEnteredFlag()==false)rHead=append_node(this,rHead);
                        setRoomEnteredFlag(true);
                        return nRoom;
                    }
                    else
                    {

                        if(getRoomEnteredFlag()==false)rHead=append_node(this,rHead);
                       // cout<<"going into old room "<<endl;
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
    cout<<"3. Open Inventory "<<endl;
    cout<<"4. Open Spellbook"<<endl;
    cout<<"5. Open Stats "<<endl;
    cout<<"6. Exit Room "<<endl;
}

int room::basic_checks(Creature *p)
{
    int choice_container,roll_container;
    while(true)
    {
        basic_checks_text();
        cin>>choice_container;
        switch(choice_container)
        {
        case 1:
            roll_container=dRoll()+p->getWIS();
             for(int i=0; i<numberOfTraps;i++) //traps
             {
                 if(room_traps[i]->getSkill()=="Perception" && roll_container>=room_traps[i]->getCheckDC())
                 {
                     room_traps[i]->eDisc=true;
                     cout<<room_traps[i]->getCheck_succ_text()<<endl;
                     return 10;
                 }
             }
             if(roll_container >= this->getDC_Perception() && getDC_Perception()>=0)
            {
                cout<<this->getPerception_SUCC_text()<<endl;

                return 11;
            }
            else
            {
                if(false)         //WIP
                {
                     cout<<this->getPerception_FAIL_text()<<endl;

                }
                else
                {
                    cout<<global_default_Perception_FAIL_text<<endl;

                }
                return 12;
            }
        case 2:
            roll_container=dRoll()+p->getINT();
            for(int i=0; i<numberOfTraps;i++)  //traps
             {
                 if(room_traps[i]->getSkill()=="Investigation" && roll_container>=room_traps[i]->getCheckDC())
                 {
                     room_traps[i]->eDisc=true;
                     cout<<room_traps[i]->getCheck_succ_text()<<endl;
                     return 20;
                 }
             }
            if(roll_container >= this->getDC_Investigation() && getDC_Investigation()>=0)
            {
                cout<<this->getInvestigation_SUCC_text()<<endl;
                                                            //check reward here
                return 21;
            }
            else
            {
                if(false)         //WIP
                {
                     cout<<this->getInvestigation_FAIL_text()<<endl;
                }
                else
                {
                    cout<<global_default_Investigation_FAIL_text<<endl;
                }
                return 22;
            }
        case 3:
            roll_container=dRoll()+p->getWIS();
             for(int i=0; i<numberOfTraps;i++) //traps
             {
                 if(room_traps[i]->getSkill()=="Survival" && roll_container>=room_traps[i]->getCheckDC())
                 {
                     room_traps[i]->eDisc=true;
                     cout<<room_traps[i]->getCheck_succ_text()<<endl;
                     return 30;
                 }
             }
              if(roll_container >= this->getDC_Survival() && getDC_Survival()>=0)
            {
                cout<<this->getSurvival_SUCC_text()<<endl;
                                                            //check reward here
                 return 31;
            }
            else
            {
                if(false)         //WIP
                {
                     cout<<this->getSurvival_FAIL_text()<<endl;
                }
                else
                {
                    cout<<global_default_Survival_FAIL_text<<endl;
                }
                return 32;
            }
        case 4:
             roll_container=dRoll()+p->getINT();
            for(int i=0; i<numberOfTraps;i++)  //traps
             {
                 if(room_traps[i]->getSkill()=="Arcana" && roll_container>=room_traps[i]->getCheckDC())
                 {
                     room_traps[i]->eDisc=true;
                     cout<<room_traps[i]->getCheck_succ_text()<<endl;
                     return 40;
                 }
             }
            if(roll_container >= this->getDC_Arcana() && getDC_Arcana()>=0)
            {
                cout<<this->getArcana_SUCC_text()<<endl;
                                                            //check reward here
                return 41;
            }

            else
            {
                if(false)         //WIP
                {
                     cout<<this->getArcana_FAIL_text()<<endl;
                }
                else
                {
                    cout<<global_default_Arcana_FAIL_text<<endl;
                }
                return 42;
            }
        case 5:
            return 5;
            break;
        default:
            cout<<"Invalid input, try again "<<endl;

        }


    }
}

void room::basic_checks_text()
{
    cout<<"1. Perception "<<endl;
    cout<<"2. Investigation"<<endl;
    cout<<"3. Survival"<<endl;
    cout<<"4. Arcana"<<endl;
    cout<<"5. Back "<<endl;
}

room::room(string name)
{
    ifstream f;
    string path;
    if(PLATFORM_NAME == "windows") path = "rooms\\"+name+".json";
    else path = "./rooms/"+name+".json";
    f.open(path);
    if(f.is_open()){
        Document document = parseFromFile(&f);

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
        if(c.Size()>0){
            for (SizeType i = 0; i <c.Size(); i++){

                this->room_traps[j]=new trap(c[i].GetString());
                //cout<<"ASS"<<endl;
                //cout<<this->room_events[j]<<endl;
                j++;
                this->numberOfTraps++;
            }
        }



}
else cout<<"room file not open"<<endl;
        f.close();
}

string room::exit_room(Creature *p)
{
    string s;
    for(int i=0; i<numberOfTraps; i++)
    {
        if(this->numberOfTraps>0 && room_traps[i]->isDisarmed==false) activateTrap(room_traps[i],p);
    }
    while(true){
    int cContainer=0;
    int j=0;
    for(int i=0; i<this->numberOfConnections; i++)
    {
        cout<<i+1<<". "<<this->room_next[i];if(findRoom(rHead,room_next[i])!=NULL)cout<<" (visited)";
        cout<<endl;
        j=i+2;
    }
    cout<<j<<". Back "<<endl;
    cin>>cContainer;
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
    int choice_container;
    int counter=1;
    int item_counter=0;
    do{             //prints choices and takes input
        counter=1;
        for(int i=0; i<numberOfTraps; i++)
        {
            if(numberOfTraps>0 && room_traps[i]->eDisc==true && room_traps[i]->isDisarmed==false)
            {
                cout<<counter<<". "<<room_traps[i]->getInteract_text()<<endl;
                counter++;
            }
        }
        cout<<counter<<". "<<"Back"<<endl;
        cin>>choice_container;
        if(choice_container>counter || choice_container<1) cout<<"Invalid input, try again! "<<endl;
    }while(choice_container>counter || choice_container<1);
    if(choice_container==counter) return 0;
    else if(choice_container<counter-item_counter)
    {                                                                                   //trap disarm
        if(dRoll()>=room_traps[choice_container-1]->getDisarmDC())
        {
            cout<<room_traps[choice_container-1]->getDisarm_succ_text()<<endl;
            room_traps[choice_container-1]->isDisarmed=true;
            return 1;
        }
        else
        {
            room_traps[choice_container-1]->getDisarm_fail_text();
            return -1;
        }

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

struct rList *findRoom(struct rList *rHead,string s)
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
    int dimaga;
    if(e->getSave()=="DEX")
    {
        if(dRoll()+p->getDEX()>=e->getSaveDC())
        {
            cout<<e->getSave_succ_text()<<endl;
            dimaga=floor(e->getSaveMulti()*dRoll(e->getDMG(),0,e->getDNum()));
            cout<<p->getName()<<" takes "<<dimaga<<" damage"<<endl;
            p->setCurHP(p->getCurHP()-dimaga);
        }
        else
        {
            cout<<e->getSave_fail_text()<<endl;
            dimaga=dRoll(e->getDMG(),0,e->getDNum());
            cout<<p->getName()<<" takes "<<dimaga<<" damage"<<endl;
            p->setCurHP(p->getCurHP()-dimaga);
        }
    }
    else if(e->getSave()=="STR")
    {
        if(dRoll()+p->getSTR()>=e->getSaveDC())
        {
            cout<<e->getSave_succ_text()<<endl;
            dimaga=floor(e->getSaveMulti()*dRoll(e->getDMG(),0,e->getDNum()));
            cout<<p->getName()<<" takes "<<dimaga<<" damage"<<endl;
            p->setCurHP(p->getCurHP()-dimaga);
        }
        else
        {
            cout<<e->getSave_fail_text()<<endl;
            dimaga=dRoll(e->getDMG(),0,e->getDNum());
            cout<<p->getName()<<" takes "<<dimaga<<" damage"<<endl;
            p->setCurHP(p->getCurHP()-dimaga);
        }
    }
    else cout<<"WTF? (can only roll DEX or STR against traps ATM) "<<endl;
}


struct rList *rHead=NULL;
