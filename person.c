#include "person.h"
#include <stdlib.h>

Person *createPerson(int src, int dest)
{
    Person *Boby = (Person *)malloc(sizeof(Person));
    Boby->src = src;
    Boby->dest = dest;
    return Boby;
}

PersonList *insert(Person *p, PersonList *list)
{
    PersonList *new_list = (PersonList *)malloc(sizeof(PersonList));
    new_list->Person = p;
    new_list->next = list;
    return new_list;
}