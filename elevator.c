#include "elevator.h"
#include <stdio.h>
#include <stdlib.h>

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons)
{
    Elevator *elevator = (Elevator *)malloc(sizeof(Elevator));
    elevator->capacity = capacity;
    elevator->currentFloor = currentFloor;
    elevator->targetFloor = NULL;
    elevator->persons = persons;

    return elevator;
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists)
{
    Building *building = (Building *)malloc(sizeof(Building));
    building->nbFloor = nbFloor;
    building->elevator = elevator;
    building->waitingLists = waitingLists;

    return elevator;
}

PersonList *exitElevator(Elevator *e);

PersonList *enterElevator(Elevator *e, PersonList *list)
{
    int n = 0;
    PersonList *Compte = e->persons;
    while (Compte->next != NULL)
    {
        n++;
        PersonList *Compte = Compte->next;
    }

    for (int i = n, i < e->capacity, i++)
    {
    }
}