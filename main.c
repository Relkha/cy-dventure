#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../2-include/step.h"
#include "../2-include/backup.h"
#define SAVE_FILE "savegame.txt"
#define START_FILE "2start.txt"
#define MAX_FILENAME_LENGTH 2048


int main() {
    Inventory inventory;
    inventory_init(&inventory);
    
    char *initialStepFilename = "2start.txt";
    Step *initialStep;
    SaveData *saveData = malloc(sizeof(SaveData));
    saveData->step_filename = malloc(MAX_FILENAME_LENGTH * sizeof(char));
    int result;

    if (ask_continue() == 1) {
        result = load_game(saveData);
        if (result == -1) {  // Vérification d'une erreur de load_game
            printf("Erreur lors du chargement de la sauvegarde\n");
            free(saveData);  // Libération de la mémoire en cas d'erreur
            return 1;
        }
        initialStepFilename = saveData->step_filename;
    }

    initialStep = load_step(initialStepFilename, &inventory);
    if (initialStep == NULL) {
        printf("Erreur lors du chargement de l'étape initiale\n");
        free(saveData->step_filename);  // Libération de la mémoire pour le step_filename
        free(saveData);  // Libération de la mémoire pour saveData
        return 1;
    }
    else{
        execute_step(initialStep, &inventory);
    }

    free_step(initialStep);

    // Imprimer l'inventaire à la fin du programme
    
    inventory_print(&inventory);

    // Libération de la mémoire à la fin du programme
    free(saveData->step_filename);  // Libération de la mémoire pour le step_filename
    free(saveData);  // Libération de la mémoire pour saveData
    return 0;
}








