#include "combat.h"

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
                if(ptr->CPL->actionExec(head,ptr2->CPL,ptr->CPL->actionChoose())==1)
                {
                    //cout<<ptr2->CPL->getName()<<" died"<<endl;
                    head=delete_node(head,ptr2);
                    dcount++;
                    targetChoiceIntMax--;
                    if(dcount==n)
                    {
                        cout<<"BATTLE WON!!!"<<endl;
                        delete_cList(head);
                        head=NULL;
                        return 1;
                    }


                }
            }
            else if(ptr->CPL->getCurHP()>0)
            {
                if(ptr->CPL->actionExec(head,cp[n],ptr->CPL->actionChoose())==1)
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
