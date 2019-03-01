#pragma once
#include <vector>
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
struct cList* delete_node(struct cList *head,struct cList *TBD,bool deletHero=false);
void sortList(struct cList *head);
void swapNode(struct cList *a, struct cList *b);
int displayList(struct cList* head);
struct cList* prune_cList(struct cList* head, float* expPool);
struct cList* prune_cList(struct cList* head);
struct cList* createParty(int n);
struct cList* pruneParty(struct cList* partyHead);
void levelParty(struct cList* partyHead,float exp);
int partySize(struct cList* partyHead);
Creature* getRandomListMember(struct cList* head,int heroTarget=1);
int monsterNum(struct cList* head);
int heroNum(struct cList* head);
bool isInList(Creature* needle, struct cList* haystack);