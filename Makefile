main : main.c elevator.c person.c
	gcc -o $@ main.c elevator.c person.c -lncurses ; ./$@