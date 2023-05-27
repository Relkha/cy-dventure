#ifndef STEP_H
#define STEP_H
#include "inventory.h"
// The Description structure represents the description of a story step.
typedef struct Description{ 
	char *text; //pointer to a string containing the text of the description
} Description; 

//The event structure represents an event that occurs during a story step.

typedef struct Event {
	int type; // Integer representing the event type 
	void *data; // Pointer to a data stucture specific to the event 
} Event;

// The choice structure represents a choice that the reader must make at a story step.
typedef struct Choice{
	char *text; // Pointer to a string containing the description of the choice
    int  hasNextStep;
    char *nextStepFile;
}Choice;


// The step structure represents a complete story step.
typedef struct Step{
	Description description; // Descriptio of the step
	Event event; //Event details that occur during this step
	int choice_count; // The number of choices at this step
	Choice *choices; //Pointer to an array of Choice structures containing the possible choices at this step
}Step;
typedef struct{
    char name [100];
    char surname [100];
}Player;
Step *load_step(const char *filename, Inventory *inventory);
void execute_step(Step *step, Inventory *inventory);
void free_step(Step *step);

#endif //STEP_H

	
	
