#ifndef CLIST_H_INCLUDED
#define CLIST_H_INCLUDED
#include "Creature.h"

struct cList
{
    struct cList *next;
    Creature *CPL;
    int cInit;

};
struct cList *head=NULL;

struct cList* append_node(int n, Creature *c,struct cList *head);
struct cList* prefix_node(int n, Creature *c,struct cList *head);
struct cList* insert_node(int n, Creature *c,struct cList *head);
struct cList* swap_cLists(struct cList ptr1, struct Clist ptr2);
void delete_cList(struct cList *head);
void sortList(struct cList *head);
void swapNode(struct cList *a, struct cList *b);
int displayList(struct cList* head);





struct cList *append_node(int n, Creature *c,struct cList *head)
{

    struct cList *newNode;
    struct cList *ptr;
    newNode=new struct cList;

    newNode->cInit=n;
    newNode->CPL=c;

    if(head==NULL)
    {
        head=newNode;
        newNode->next=NULL;
        return head;
    }
    else
        {
            ptr=head;
            while(ptr->next!=NULL)
            {
            ptr=ptr->next;

            }
            ptr->next=newNode;
            newNode->next=NULL;
            return head;
        }

};

struct cList* prefix_node(int n,  Creature *c, struct cList* head)
{
    struct cList* newNode;

    if(head==NULL)
    {
        cout<<"ERROR no list created "<<endl;
    }
    else
    {

        newNode=new struct cList;

        newNode->cInit=n;
        newNode->CPL=c;
        newNode->next=head;
        head=newNode;

    }
    return head;
};

void delete_cList(struct cList *head)
{


    struct cList* ptr;
    struct cList* tmp;

    while(head!=NULL)
    {
        ptr=head;
        head=head->next;
        //cout<<ptr->cInit<<" is to be deleted next "<<endl;
        delete ptr;
    }

}

int displayList(struct cList* head)
{
    struct cList* ptr=head;
    if(head==NULL)
    {
        cout<<"ERROR list not initialized "<<endl;
        return 1;
    }
    else
        while(ptr!=NULL)
        {
            cout<<ptr->CPL->getName()<<" Init: "<<ptr->cInit<<endl;
            ptr=ptr->next;
        }
        cout<<endl;
        return 0;
}

struct cList* insert_node(int n, Creature *c,struct cList *head)
{
    if(head==NULL)
    {
        return append_node(n,c,head);
    }
    else if(n>head->cInit) return prefix_node(n,c,head);
    else return append_node(n,c,head);

};

void swapNode(struct cList *a, struct cList *b)
{
    int temp = a->cInit;
    Creature* tempc=a->CPL;
    a->CPL=b->CPL;
    b->CPL=tempc;
    a->cInit = b->cInit;
    b->cInit = temp;
};
void sortList(struct cList *head)
{
    int swapped, i;
    struct cList *ptr1;
    struct cList *lptr = NULL;

    /* Checking for empty list */
    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->cInit < ptr1->next->cInit)
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



#endif // CLIST_H_INCLUDED
