#include "combat.h"
#include "cList.h"

int combat(struct cList* partyHead,string MonsterList[],int n,string combatText)
{
    struct cList* head=NULL;
    struct cList* ptr=partyHead;
    struct cList* ptr2=head;
    bool fightOverFlag=false;
    Creature *cp[n];
    int initiative[n];
    int dcount=0;
    cout<<combatText<<endl;
    for(int i=0; i<n; i++)
    {
        cp[i]=new Monster(MonsterList[i]);

        initiative[i]=dRoll()+cp[i]->getDEX();
        cout<<cp[i]->getName()<<" rolls "<<initiative[i]<<"("<<initiative[i]-cp[i]->getDEX()<<"+"<<cp[i]->getDEX()<<")"<<" initiative "<<endl;
        cp[i]->setInit(initiative[i]);
        head=insert_node(cp[i],head);

    }
    while(ptr!=NULL) {
        initiative[0] = dRoll(20,ptr->CPL->getAdvantage("globalAdv"),1) + ptr->CPL->getDEX();
        cout << ptr->CPL->getName() << " rolls " << initiative[0] << "(" << initiative[0] - ptr->CPL->getDEX() << "+"<< ptr->CPL->getDEX() << ")" << " initiative " << endl;
        ptr->CPL->setInit(initiative[0]);
        head = insert_node(ptr->CPL, head);
        ptr=ptr->next;
    }
    sortList(head);
    //displayList(head);
    Creature* target;
    Action* action;
    float expPool = 0;
    while(true/*fightOverFlag==false*/)
    {
        ptr=head;
        while(ptr!=nullptr /*&& fightOverFlag==false*/)
        {
            ptr->CPL->CTurnTick();
            if(ptr->CPL->getCurHP()<1)              //should handle the situation if the creature dies from a DOT
            {
                ptr=ptr->next;
                dcount++;
                head=prune_cList(head,&expPool);
                partyHead=pruneParty(partyHead);
                continue;
            }
            for(int i=0; i<ptr->CPL->getActionsPerRound(); i++){
                head=prune_cList(head,&expPool);
                do{
                    target = ptr->CPL->chooseTarget(head);
                    action = ptr->CPL->actionChoose(target);
                }while(action==nullptr);
                int deathsThisTurn = 0;
                deathsThisTurn+=ptr->CPL->actionExec(head,target,action);
                if(deathsThisTurn>0){
                    dcount+=deathsThisTurn;
                    head=prune_cList(head,&expPool);
                    partyHead=pruneParty(partyHead);
                    if(partyHead==nullptr) return -1;
                    if(dcount==n){
                        cout<<"Battle won!"<<endl;

                        expPool=expPool/partySize(partyHead);
                        levelParty(partyHead,expPool);//split exp pool between party when implemented

                        delete_cList(head);
                        return 1;
                    }
                }
            }
            ptr=ptr->next;
        }
    }
}
