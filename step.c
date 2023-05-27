#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../2-include/step.h"
#include "../2-include/backup.h"
#include "../2-include/util.h"
#include "../2-include/inventory.h"
#define CHOICE_DIR "../3-stories/"


    
void search_item_in_step(Step *step, Inventory *inventory) {
    char *description = step->description.text;
    char *start_item;
    while ((start_item = strchr(description, '#')) != NULL) {
        char *end_item = strchr(start_item + 1, '#');
        if (end_item == NULL) {
            printf("Erreur: Un item a été commencé avec # mais pas terminé\n");
            return;
        }
        int item_length = end_item - start_item - 1;
        char *item = malloc((item_length + 1) * sizeof(char));
        strncpy(item, start_item + 1, item_length);
        item[item_length] = '\0';
        inventory_add_item(inventory, item);
        description = end_item + 1;
    }
}

void search_item_in_choice(Choice *choice, Inventory *inventory) {
    char *description = choice->text;
    char *start_item;
    while ((start_item = strchr(description, '#')) != NULL) {
        char *end_item = strchr(start_item + 1, '#');
        if (end_item == NULL) {
            printf("Erreur: Un item a été commencé avec # mais pas terminé\n");
            return;
        }
        int item_length = end_item - start_item - 1;
        char *item = malloc((item_length + 1) * sizeof(char));
        strncpy(item, start_item + 1, item_length);
        item[item_length] = '\0';
        inventory_add_item(inventory, item);
        description = end_item + 1;
    }
}



void free_choices(Choice *choices, int count) {
    if(choices == NULL)
        return;

    for(int i = 0; i < count; i++) {
        free(choices[i].text);
        free(choices[i].nextStepFile);
    }
    free(choices);
}
void free_step(Step *step) {
    if(step == NULL){
        return;
    }

    free(step->description.text);
    for(int i = 0; i < step->choice_count; i++) {
        free(step->choices[i].text);
        free(step->choices[i].nextStepFile);
    }
    free(step->choices);
    free(step->event.data);
    free(step);
}

void split_string(char* string, char** part1, char** part2, char delimiter) {
    char* delimPos = strchr(string, delimiter);
    if (delimPos != NULL) {
        *delimPos = '\0';  // Fix here
        *part1 = string;
        *part2 = delimPos + 1;
    } else {
        *part1 = string;
        *part2 = NULL;
    }
}



Step *load_step(const char *filename, Inventory *inventory) {
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s%s", CHOICE_DIR, filename);

    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", full_path);
        return NULL;
    }
    
    if (file == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier : %s\n", filename);
        return NULL;
    }
    // Check if the file is empty
        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0) {
            fprintf(stderr, "Erreur : le fichier est vide : %s\n", filename);
            fclose(file);
            return NULL;
        }
        fseek(file, 0, SEEK_SET); // Reset the file pointer to the beginning

    Step *step =malloc(sizeof(Step));
    if (step == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour l'étape\n");
        fclose(file);
        return NULL;
    }

    char buffer[1024];
    int choice_count = 0;
    Choice *choices = NULL;
    int choice_found = 0;
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        chomp(buffer);

            // Ignore lines starting with '#'
            if(buffer[0] == '#') {
                continue;
            }

            // Check if there are two '#' in the line. If so, this is an inventory item.
            char* first_hash = strchr(buffer, '#');
            if(first_hash != NULL) {
                char* second_hash = strchr(first_hash+1, '#');
                if(second_hash != NULL) {
                    // We found an inventory item! Now extract it.
                    // Make sure the item string is properly terminated.
                    *second_hash = '\0';
                    char* item_name = first_hash+1;

                    // Now 'item_name' contains the name of the inventory item. You can
                    // add it to your inventory here.

                    // Replace the '#' in the buffer with spaces, effectively removing the inventory item.
                    inventory_add_item(inventory, item_name);
                    *first_hash = ' ';
                    *second_hash = ' ';
                }
            }
        if(strncmp(buffer, "choice", 6) == 0) {
            choice_found = 1;
            choices = realloc(choices, (choice_count+1) * sizeof(Choice));
            if(choices == NULL){
            fprintf(stderr, "Erreur d'allocation de mémoire pour les choix\n");
            free_step(step);
            fclose(file);
                return NULL;
            }
            char *choiceText = buffer+7;
            char *nextStepFile = NULL;
            split_string(choiceText, &choiceText, &nextStepFile, ':');
            choices[choice_count].text = strdup(choiceText);
            if(nextStepFile != NULL){
                char *cleanedNextStepFile = nextStepFile + 1; // Skip the first character ('&')
                choices[choice_count].nextStepFile = strdup(nextStepFile);
                if(choices[choice_count].nextStepFile == NULL){
                    fprintf(stderr, "Erreur d'allocation de mémoire pour le prochain fichier d'étape\n");
                    free_choices(choices, choice_count+1);
                    free_step(step);
                    fclose(file);
                    return NULL;
                }
                choices[choice_count].hasNextStep = 1;
            } else {
                choices[choice_count].nextStepFile = NULL;
                choices[choice_count].hasNextStep = 0;
            }
            if(choices[choice_count].text == NULL){
                fprintf(stderr, "Erreur d'allocation de mémoire pour le choix\n");
                free_choices(choices, choice_count);
                free_step(step);
                fclose(file);
                return NULL;
            }
            choice_count++;
        }
        else if(strncmp(buffer, "Description", 11) == 0) {
            char *description = buffer+12;
            step->description.text = strdup(description);
            if(step->description.text == NULL){
                fprintf(stderr, "Erreur d'allocation de mémoire pour la description\n");
                free_choices(choices, choice_count);
                free_step(step);
                fclose(file);
                return NULL;
            }
        }
        
        else if(strncmp(buffer, "Event", 5) == 0) {
            char *eventData = strchr(buffer, ':');
            if(eventData == NULL){
                fprintf(stderr, "Format de fichier invalide\n");
                free_choices(choices, choice_count);
                free_step(step);
                fclose(file);
                return NULL;
            }
            *eventData = '\0';
            eventData++;
            step->event.data = strdup(eventData);
            if(step->event.data == NULL){
                fprintf(stderr, "Erreur d'allocation de mémoire pour les données d'événement\n");
                free_choices(choices, choice_count);
                free_step(step);
                fclose(file);
                return NULL;
            }
            step->event.type = atoi(buffer+6);
        }
        
    }
    if (choice_found == 0) {
        printf("Vous avez chargé une sauvegarde ou vous avez fini le jeux veuillez le relancer\n");
        free_step(step);
        fclose(file);
        return NULL;
    }
    step->choices = choices;
    step->choice_count = choice_count;
    fclose(file);
    search_item_in_step(step, inventory);
    return step;
}


void execute_step(Step *step, Inventory *inventory) {
    if(step == NULL){
        fprintf(stderr, "Etape invalide\n");
        return;
    }

    printf("%s\n", step->description.text);
    printf("Event: %d, %s\n", step->event.type, (char*)step->event.data);
    
    for(int i = 0; i < step->choice_count; i++) {
        char *text_copy = strdup(step->choices[i].text);
        char *choice_text = strtok(text_copy, ":");
        printf("%d. %s\n", i+1, choice_text);
        free(text_copy);
    }

    int choice = 0;
    while(choice < 1 || choice > step->choice_count) {
        printf("Veuillez faire un choix (1-%d): ", step->choice_count);
        int ret = scanf("%d", &choice);
        
        if(ret != 1) {  // Si scanf a échoué à lire un entier
            int c;
            while((c = getchar()) != '\n' && c != EOF);  // Effacer le buffer d'entrée
            choice = 0;  // Pour être sûr que la boucle continue
            printf("Choix invalide. Essayez à nouveau.\n");
        } else if(choice < 1 || choice > step->choice_count) {
            printf("Choix invalide. Essayez à nouveau.\n");
        }
    }
    

    char *choice_text_copy = strdup(step->choices[choice - 1].text);
    char *choice_text = strtok(choice_text_copy, ":");
    printf("Vous avez choisi: %s\n", choice_text);
    free(choice_text_copy);
    ask_save(step->choices[choice - 1].nextStepFile, choice);

    if (step->choices[choice - 1].hasNextStep){
        Step *nextStep = load_step(step->choices[choice - 1].nextStepFile, inventory);
        if (nextStep != NULL) {
            printf("Chargement de l'étape suivante à partir de: %s\n", step->choices[choice - 1].nextStepFile);
            execute_step(nextStep, inventory);
            free_step(nextStep);
        } else {
            printf("Pas d'étape suivante trouvée. Fin de l'histoire.\n");
        }
    } else {
        printf("Ce choix ne mène à aucune autre étape. Fin de l'histoire.\n");
    }
    for (int i = 0; i < step->choice_count; i++) {
            search_item_in_choice(&step->choices[i], inventory);
        }
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






















