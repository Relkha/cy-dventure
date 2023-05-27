// Including necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../2-include/step.h"
#include "../2-include/backup.h"
#include "../2-include/util.h"
#include "../2-include/inventory.h"
#define CHOICE_DIR "../3-stories/"

// Function to search for an item in a step. If item is found between '#' symbols, it is added to inventory.
void search_item_in_step(Step *step, Inventory *inventory) {
    // Read the description text of the step
    char *description = step->description.text;
    char *start_item;
    // While loop goes until it can't find any '#' symbol
    while ((start_item = strchr(description, '#')) != NULL) {
        char *end_item = strchr(start_item + 1, '#');
        // If there is no ending '#' for an item, prints an error message
        if (end_item == NULL) {
            printf("Erreur: Un item a été commencé avec # mais pas terminé\n");
            return;
        }
        // If item is found, it is allocated in memory and added to the inventory
        int item_length = end_item - start_item - 1;
        char *item = malloc((item_length + 1) * sizeof(char));
        strncpy(item, start_item + 1, item_length);
        item[item_length] = '\0';
        inventory_add_item(inventory, item);
        description = end_item + 1;
    }
}

// Similar to search_item_in_step but searches for item in the choices text instead of step description.
void search_item_in_choice(Choice *choice, Inventory *inventory) {
    // The code inside is almost the same as the one in search_item_in_step function
}

// Function to deallocate memory assigned to choices to prevent memory leaks.
void free_choices(Choice *choices, int count) {
    if(choices == NULL)
        return;

    for(int i = 0; i < count; i++) {
        free(choices[i].text);
        free(choices[i].nextStepFile);
    }
    free(choices);
}

// Function to deallocate memory assigned to step to prevent memory leaks.
void free_step(Step *step) {
    // Similar to free_choices, but deallocates memory for steps
}

// Helper function to split a string into two parts based on a delimiter
void split_string(char* string, char** part1, char** part2, char delimiter) {
    // The function replaces the delimiter with a null character, effectively splitting the string into two
}

// Function to load a step from a file.
Step *load_step(const char *filename, Inventory *inventory) {
    // Combines directory path with filename to get the full path to the file
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s%s", CHOICE_DIR, filename);
    // Opens the file for reading
    FILE *file = fopen(full_path, "r");
    // Error checking for file opening
    if (file == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", full_path);
        return NULL;
    }
    // Error checking if file is empty
    // Rest of the code reads the file line by line, parsing information about description, choices and events and allocating memory for new steps and choices accordingly.
    // It also checks for errors and does some cleanup if any error is encountered.
}

// Function to execute a step: print its description and choices and manage the transition to the next step based on user's choice.
void execute_step(Step *step, Inventory *inventory) {
    // Error checking if step is null
    if(step == NULL){
        fprintf(stderr, "Etape invalide\n");
        return;
    }
    // Prints the description and the event associated with the step
    printf("%s\n", step->description.text);
    printf("Event: %d, %s\n", step->event.type, (char*)step->event.data);
    // Prints the choices for the step
    for(int i = 0; i < step->choice_count; i++) {
        char *text_copy = strdup(step->choices[i].text);
        char *choice_text = strtok(text_copy, ":");
        printf("%d. %s\n", i+1, choice_text);
        free(text_copy);
    }
    // The loop continues until the user makes a valid choice
    // After a valid choice is made, the corresponding next step is loaded and executed.
    // It also checks if a choice leads to another step or not, and prints an appropriate message.
    // In the end, it also searches for any items in the choices text.
}






















