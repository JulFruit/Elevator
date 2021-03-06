#include "elevator.h"
#include "person.h"
#include <stdio.h>
#include <stdlib.h>

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons)
{
    Elevator *elevator = (Elevator *)malloc(sizeof(Elevator));
    elevator->capacity = capacity;
    elevator->currentFloor = currentFloor;
    elevator->targetFloor = 0;
    elevator->persons = persons;
    return elevator;
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists)
{
    Building *building = (Building *)malloc(sizeof(Building));
    building->nbFloor = nbFloor;
    building->elevator = elevator;
    building->waitingLists = waitingLists;

    return building;
}

PersonList *exitElevator(Elevator *e)
{
    PersonList *List_Exit = malloc(e->capacity * sizeof(PersonList *));
    PersonList *curentList = e->persons;
    PersonList *Newlist_inv = malloc(e->capacity * sizeof(PersonList *));
    PersonList *Newlist = malloc(e->capacity * sizeof(PersonList *));
    Newlist_inv = NULL;
    List_Exit = NULL;
    Newlist = NULL;

    while (curentList != NULL)
    {
        if (curentList->person->dest == e->currentFloor)
        {
            List_Exit = insert(curentList->person, List_Exit);
        }
        else
        {
            Newlist_inv = insert(curentList->person, Newlist_inv);
        }
        curentList = curentList->next;
    }
    while (Newlist_inv != NULL)
    {
        Newlist = insert(Newlist_inv->person, Newlist);
        Newlist_inv = Newlist_inv->next;
    }
    e->persons = Newlist;
    return List_Exit;
}

PersonList *enterElevator(Elevator *e, PersonList *list)
{
    int Places = 0;
    PersonList *List_Count = malloc(e->capacity * sizeof(PersonList *));
    List_Count = e->persons;
    while (List_Count != NULL)
    {
        Places++;
        List_Count = List_Count->next;
    }

    for (int i = 0; i < e->capacity - Places; i++)
    {
        if (list != NULL)
        {
            e->persons = insert(list->person, e->persons);
            list = list->next;
        }
    }
    return list;
}

void stepElevator(Building *b)
{
    b->waitingLists[b->elevator->currentFloor] = enterElevator(b->elevator, b->waitingLists[b->elevator->currentFloor]);
    b->elevator->currentFloor = b->elevator->targetFloor;
    exitElevator(b->elevator);
};