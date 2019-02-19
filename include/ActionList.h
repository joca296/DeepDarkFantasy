#ifndef DEEPDARKFANTASY_ACTIONLIST_H
#define DEEPDARKFANTASY_ACTIONLIST_H

#include "Action.h"

struct ActionList{
    struct ActionList* next;
    Action* action;
};
struct ActionList* insert_node(Action* action, struct ActionList* head);

#endif //DEEPDARKFANTASY_ACTIONLIST_H
