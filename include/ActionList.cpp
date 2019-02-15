#include "ActionList.h"

struct ActionList* insert_action(Action* action, struct ActionList* head){
    struct ActionList* newNode;
    struct ActionList* ptr;

    newNode=new struct ActionList;
    newNode->action=action;
    newNode->next=NULL;

    if(head == NULL){
        head=newNode;
        return head;
    }
    else{
        ptr=head;
        while(ptr->next!=NULL){
            ptr=ptr->next;
        }
        ptr->next=newNode;
        return head;
    }
}