#include "Creature.h"
#include "functions.h"


#ifndef COMBAT_H_INCLUDED
#define COMBAT_H_INCLUDED

int combat(Creature *h,string MonsterList[],int n,string combatText="combatText WIP");


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
        head=insert_node(initiative[i],cp[i],head);

    }
    cp[n]=h;
    initiative[n]=dRoll()+cp[n]->getDEX();
    cout<<cp[n]->getName()<<" rolls "<<initiative[n]<<"("<<initiative[n]-cp[n]->getDEX()<<"+"<<cp[n]->getDEX()<<")"<<" initiative "<<endl;
    head=insert_node(initiative[n],cp[n],head);

    sortList(head);
    displayList(head);

    int targetChoiceInt=1;
    int targetChoiceIntMax=n+1;
    while(true/*fightOverFlag==false*/)
    {
        ptr=head;
        ptr2=head;
        while(ptr!=NULL /*&& fightOverFlag==false*/)
        {
            ptr2=head;
            if(ptr->CPL->isHero()==1 && ptr->CPL->getCurHP()>0) //If players turn
            {

                cout<<"Choose your target (sorted by initiative) "<<endl;
                for(int i=1; i<=n+1; i++)
                {
                    cout<<i<<". "<<ptr2->CPL->getName()<<" "<<ptr2->CPL->getCurHP()<<"/"<<ptr2->CPL->getMaxHP()<<" HP"<<endl;
                    ptr2=ptr2->next;
                    if(ptr2==NULL) break;

                }
                do
                {
                    cin>>targetChoiceInt;
                    if(targetChoiceInt>targetChoiceIntMax) cout<<"Invalid, try again "<<endl;
                }while(targetChoiceInt>targetChoiceIntMax);
                ptr2=head;
                for(int i=1; i<targetChoiceInt; i++)
                {
                    ptr2=ptr2->next;
                }
                if(cp[n]->actionExec(ptr2->CPL,cp[n]->actionChoose())==1)
                {
                    //cout<<ptr2->CPL->getName()<<" died"<<endl;
                    dcount++;
                    if(dcount==n)
                    {
                        cout<<"BATTLE WON!!!"<<endl;
                        delete_cList(head);
                        head=NULL;
                        return 1;
                    }
                    //prune list here?

                }
            }
            else if(ptr->CPL->getCurHP()>0)
            {
                if(ptr->CPL->actionExec(cp[n],ptr->CPL->actionChoose())==1)
                   {
                      // cout<<cp[n]->getName()<<" died"<<endl;
                       delete_cList(head);
                       head=NULL;
                       return -1;

                   }

            }
            ptr=ptr->next;
        }
    }
    delete_cList(head);
    return 0;
}
/*bool combatOverCheck(head,creature* p)
{

    struct cList* tmp=head;
    while(tmp!=NULL)
    {

    }
    return true;
}*/

#endif // COMBAT_H_INCLUDED
