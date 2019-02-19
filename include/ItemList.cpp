#include "ItemList.h"

struct ItemList* insert_node(Item* item, ItemList* head){
    struct ItemList* newNode;
    struct ItemList* ptr;

    newNode=new struct ItemList;
    newNode->item=item;
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