#include "elevator.h"
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

    while (curentList != NULL)
    {

        if (curentList->person->dest == e->currentFloor)
        {
            insert(curentList->person, List_Exit);
            curentList->next = curentList->next->next;
            curentList->person = curentList->next->person;
        }
        curentList = curentList->next;
    }
    return List_Exit;
}

PersonList *enterElevator(Elevator *e, PersonList *list)
{
    int Places = 0;
    PersonList *List_Count = malloc(e->capacity * sizeof(PersonList *));
    List_Count = e->persons;
    while (List_Count->person != NULL)
    {
        Places++;
    }

    for (int i = 0; i < Places; i++)
    {
        if (list->person != NULL)
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