#ifndef CLIST_H
#define CLIST_H
#include "Creature.h"

using namespace std;

struct cList
{
    struct cList *next;
    Creature *CPL;
};

struct cList* append_node( Creature *c,struct cList *head);
struct cList* prefix_node( Creature *c,struct cList *head);
struct cList* insert_node( Creature *c,struct cList *head);
struct cList* swap_cLists(struct cList ptr1, struct Clist ptr2);
void delete_cList(struct cList *head);
struct cList* delete_node(struct cList *head,struct cList *TBD);
void sortList(struct cList *head);
void swapNode(struct cList *a, struct cList *b);
int displayList(struct cList* head);
struct cList* prune_cList(struct cList* head);

#endif // CLIST_H_INCLUDED