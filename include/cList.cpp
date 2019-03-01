#include "cList.h"

struct cList *append_node(Creature *c,struct cList *head)
{

    struct cList *newNode;
    struct cList *ptr;
    newNode=new struct cList;

    newNode->CPL=c;

    if(head==nullptr)
    {
        head=newNode;
        newNode->next=nullptr;
        return head;
    }
    else
        {
            ptr=head;
            while(ptr->next!=nullptr)
            {
            ptr=ptr->next;

            }
            ptr->next=newNode;
            newNode->next=nullptr;
            return head;
        }

}

struct cList* prefix_node(  Creature *c, struct cList* head)
{
    struct cList* newNode;

    if(head==nullptr)
    {
        cout<<"ERROR no list created "<<endl;
    }
    else
    {

        newNode=new struct cList;


        newNode->CPL=c;
        newNode->next=head;
        head=newNode;

    }
    return head;
}

void delete_cList(struct cList *head)
{


    struct cList* ptr;
    struct cList* tmp;

    while(head!=nullptr)
    {
        ptr=head;
        head=head->next;
        //cout<<ptr->cInit<<" is to be deleted next "<<endl;
        if(ptr->CPL->isHero()==0) delete ptr->CPL;
        delete ptr;
    }

}

int displayList(struct cList* head)
{
    struct cList* ptr=head;
    if(head==nullptr)
    {
        cout<<"ERROR list not initialized "<<endl;
        return 1;
    }
    else
        while(ptr!=nullptr)
        {
            cout<<ptr->CPL->getName()<<" Init: "<<ptr->CPL->getInit()<<endl;
            ptr=ptr->next;
        }
        cout<<endl;
        return 0;
}

struct cList* insert_node(Creature *c,struct cList *head)
{
    if(head==nullptr)
    {
        return append_node(c,head);
    }
    else if(c->getInit()>head->CPL->getInit()) return prefix_node(c,head);
    else return append_node(c,head);

};

void swapNode(struct cList *a, struct cList *b)
{

    Creature* tempc=a->CPL;
    a->CPL=b->CPL;
    b->CPL=tempc;

};
void sortList(struct cList *head)
{
    int swapped, i;
    struct cList *ptr1;
    struct cList *lptr = nullptr;

    /* Checking for empty list */
    if (head == nullptr)
        return;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->CPL->getInit() < ptr1->next->CPL->getInit())
            {
                swapNode(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
};

struct cList *delete_node(struct cList *head,struct cList *TBD,bool deletHero)
{
    struct cList *prev,*ptr;
    ptr=head;
    prev=ptr;
    while(ptr!=TBD)
    {
        prev=ptr;
        ptr=ptr->next;
    }
    if(ptr==head)
    {
       ptr=ptr->next;
        //cout<<head->CPL->getName()<<" died"<<endl;
       if(deletHero==true || head->CPL->isHero()==0)delete head->CPL;
       delete head;
       return ptr;
    }
    prev->next=ptr->next;
    //cout<<ptr->CPL->getName()<<" died"<<endl;
    if(deletHero==true || head->CPL->isHero()==0) delete ptr->CPL;
    delete ptr;
    return head;
}

struct cList *prune_cList(struct cList* head, float* expPool)
{
    struct cList* ptr,*ptr2;
    ptr=head;
    while(ptr!=nullptr)
    {
        ptr2=ptr->next;
        if(ptr->CPL->getCurHP()<1)
        {
            if(ptr->CPL->isHero()==0)*expPool += ptr->CPL->getExperience();
            cout<<ptr->CPL->getName()<<" died"<<endl;
            head=delete_node(head,ptr);
        }
        ptr=ptr2;
    }
    return head;

};
struct cList* prune_cList(struct cList* head)
{
    struct cList* ptr,*ptr2;
    ptr=head;
    while(ptr!=nullptr)
    {
        ptr2=ptr->next;
        if(ptr->CPL->getCurHP()<1)
        {
            cout<<ptr->CPL->getName()<<" died"<<endl;
            head=delete_node(head,ptr);
        }
        ptr=ptr2;
    }
    return head;

};

struct cList* createParty(int n)
{

    int c=1,choice_container;
    Creature *cptr;
    struct cList* partyHead=nullptr;
    while(c!=n+1) {
        cout<<"Choose a class for party member "<<c<<endl<<endl;

        cout<<"1. Barbarian"<<endl;

        cin>>choice_container;
        switch(choice_container) {
            case 1: {
                cptr = new Hero("barbarian");
                partyHead = append_node(cptr,partyHead);
                c++;
                break;
            }

            default:
                cout << "Invalid input, try again" << endl;
        }

    }
    return partyHead;
}

struct cList* pruneParty(struct cList* partyHead)
{
    struct cList* ptr=partyHead;
    while(ptr!=nullptr)
    {
        if(ptr->CPL->getCurHP()<1)partyHead=delete_node(partyHead,ptr,true);
        ptr = ptr->next;
        
    }

    return partyHead;
}
int partySize(struct cList* partyHead)
{
    int c=0;
    while(partyHead!=nullptr)
    {
        c++;
        partyHead=partyHead->next;
    }
    return c;
}

void levelParty(struct cList* partyHead,float expPool)
{
    while(partyHead!=nullptr) {
        partyHead->CPL->setExperience(partyHead->CPL->getExperience() + expPool);
        partyHead->CPL->checkExperience();
        partyHead=partyHead->next;
    }
}

Creature* getRandomListMember(struct cList* head,int heroTarget)
{
    int n;
    if(heroTarget!=1 && heroTarget!=-1 && heroTarget!=0)
    {
        cout<<"error in getRandomListMember, heroTarget parametar needs to be 1,-1, or 0"<<endl;
        return nullptr;
    }
    if(monsterNum(head)==0 && heroTarget==0)
    {
        return nullptr;
    }
    struct cList* ptr;
    do {
        ptr=head;
        n = rand() % partySize(head);

        for(int i=0; i<n;i++)
        {
            ptr=ptr->next;
        }
    }while((ptr->CPL->isHero()!=heroTarget) || heroTarget==-1);
    return ptr->CPL;
}

int monsterNum(struct cList* head)
{
    int c=0;
    while(head!=NULL)
    {
        if(head->CPL->isHero()==0)c++;
        head=head->next;

    }
    return c;
}

int heroNum(struct cList* head)
{
    int c=0;
    while(head!=NULL)
    {
        if(head->CPL->isHero()==1)c++;
        head=head->next;

    }
    return c;
}
bool isInList(Creature* needle, struct cList* haystack){
    struct cList* tmp = haystack;
    while(tmp!=NULL){
        if(needle == tmp->CPL) {
            return true;
        }
        tmp=tmp->next;
    }
    return false;
}