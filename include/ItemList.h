#ifndef DEEPDARKFANTASY_ITEMLIST_H
#define DEEPDARKFANTASY_ITEMLIST_H

#include "Item.h"

struct ItemList{
    Item* item;
    ItemList* next;
};
struct ItemList* insert_node(Item* item, ItemList* head);


#endif //DEEPDARKFANTASY_ITEMLIST_H
