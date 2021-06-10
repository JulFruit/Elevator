#include &lt; time.h & gt;
#include &lt; stdlib.h & gt;
#include &lt; ncurses.h & gt;
#include &quot; elevator.h & quot;
#include &quot; person.h & quot;
#define HEIGHT 30
#define WIDTH 40
#define PERSON_WIDTH 3
void DisplayPersonList(WINDOW *win, PersonList *list, int level, int offset)
{
    while (list != NULL)
    {
        // display 25 for a person going from floor 2 to floor 5
        mvwaddch(win, level, offset, &#39; 0 & #39; + list - &gt; person - &gt; src);
        mvwaddch(win, level, offset + 1, &#39; 0 & #39; + list - &gt; person - &gt; dest);
        list = list - &gt;
        next;
        offset += PERSON_WIDTH;
    }
}
void DisplayElevator(WINDOW *win, int nbFloor, Elevator *e, int offset)
{
    //Display elevator
    // [23 24 31 30 42]
    int level = 3 * (nbFloor - e - &gt; currentFloor); // 3 lines per level
mvwaddch(win, level, offset+1, &#39;[&#39;);
DisplayPersonList(win, e-&gt;persons, level, offset+2);
mvwaddch(win, level, offset+2+ (PERSON_WIDTH*e-&gt;capacity), &#39;]&#39;);
}

void DisplayBuilding(WINDOW *win, Building *b)
{
    int offset = 1;
    // display wall
    // | |
    // |[23 24 31 30 42]| 31 32
    // | |
    int right_wall = offset + 3 + (PERSON_WIDTH * b - &gt; elevator - &gt; capacity);
    for (int i = 0; i & lt; b - &gt; nbFloor; ++i)
    {
        int level = 3 * i + 1;
        mvwaddch(win, level, offset, &#39; | &#39;);
        mvwaddch(win, level + 1, offset, &#39; | &#39;);
        mvwaddch(win, level, right_wall, &#39; | &#39;);
        mvwaddch(win, level + 1, right_wall, &#39; | &#39;);
    }
    for (int i = offset + 1; i & lt; right_wall; i++)
    {
        mvwaddch(win, 3 * (b - &gt; nbFloor) + 1, i, &#39; _ & #39;);
    }
    DisplayElevator(win, b - &gt; nbFloor, b - &gt; elevator, offset);
    for (int i = 0; i & lt; b - &gt; nbFloor; i++)
    {
        int level = 3 * (b - &gt; nbFloor - i);
        DisplayPersonList(win, b - &gt; waitingLists[i], level, right_wall + 2);
    }
}

int main()
{
    srand(time(NULL)); // should only be called once
    // generate list of waiting persons
    int nbFloor = 5;
    PersonList **waitingLists = malloc(nbFloor * sizeof(PersonList *));
    for (int currentFloor = 0; currentFloor & lt; nbFloor; currentFloor++)
    {
        waitingLists[currentFloor] = NULL;
        int nbPerson = 5; // 5 persons in the waiting list
        for (int j = 0; j & lt; nbPerson; j++)
        {
            int dest = rand() % (nbFloor);
            Person *p = createPerson(currentFloor, dest);
            waitingLists[currentFloor] = insert(p, waitingLists[currentFloor]);
        }
    }
    // Initialize building and elevator
    int capacity = 3;
    int currentFloor = 0;
    Elevator *elevator = create_elevator(capacity, currentFloor, NULL);
    Building *building = create_building(nbFloor, elevator, waitingLists);
    // Initialize ncurse display
    initscr(); // initialize ncurses
    noecho();  // do not display in window the pressed keys
    halfdelay(2);
    WINDOW *win = newwin(HEIGHT, WIDTH, 0, 0);
    // Animation loop
    bool run = true;

    while (run)
    {
        // Generate people in function of input (or quit if &#39;q&#39;)
        int input = wgetch(win);
        if (input == &#39; q & #39;)
        {
            run = false;
        }
        else
        {
            int level = input - &#39;
            0 & #39;
            ;
            if (0 &lt; = level & amp; &amp; level & lt; nbFloor)
            {
                building - &gt;
                elevator - &gt;
                targetFloor = level;
            }
        }
        // Update state machine of elevator !!!!
        stepElevator(building);
        wclear(win);    // clear display area
        box(win, 0, 0); // display border of window
        DisplayBuilding(win, building);
        wrefresh(win); // actual display function
    }
    endwin(); // correct ending of ncurses
    return 0;
}