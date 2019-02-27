#include "combat.h"
#include "cList.h"

int combat(Creature *h,string MonsterList[],int n,string combatText)
{
    struct cList* head=NULL;
    struct cList* ptr=head;
    struct cList* ptr2=head;
    bool fightOverFlag=false;
    Creature *cp[n+1];
    int initiative[n+1];
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
    cp[n]=h;
    initiative[n]=dRoll()+cp[n]->getDEX();
    cout<<cp[n]->getName()<<" rolls "<<initiative[n]<<"("<<initiative[n]-cp[n]->getDEX()<<"+"<<cp[n]->getDEX()<<")"<<" initiative "<<endl;
    cp[n]->setInit(initiative[n]);
    head=insert_node(cp[n],head);

    sortList(head);
    //displayList(head);
    Creature* target;
    Action* action;
    float expPool = 0;
    while(true/*fightOverFlag==false*/)
    {
        ptr=head;
        while(ptr!=NULL /*&& fightOverFlag==false*/)
        {
            ptr->CPL->CTurnTick();
            if(ptr->CPL->getCurHP()<1)              //should handle the situation if the creature dies from a DOT
            {
                ptr=ptr->next;
                dcount++;
                head=prune_cList(head,&expPool);
                continue;
            }
            for(int i=0; i<ptr->CPL->getActionsPerRound(); i++){
                head=prune_cList(head,&expPool);
                do{
                    target = ptr->CPL->chooseTarget(head);
                    action = ptr->CPL->actionChoose(target);
                }while(action==NULL);
                int deathsThisTurn = 0;
                deathsThisTurn+=ptr->CPL->actionExec(head,target,action);
                if(deathsThisTurn>0){
                    dcount+=deathsThisTurn;
                    if(target->getCurHP()<1 && target->isHero())
                        return -1;
                    head=prune_cList(head,&expPool);
                    if(dcount==n){
                        cout<<"Battle won!"<<endl;
                        //split exp pool between party when implemented
                        h->setExperience(h->getExperience()+expPool);
                        h->checkExperience();
                        delete_cList(head);
                        return 1;
                    }
                }
            }
            ptr=ptr->next;
        }
    }
}
