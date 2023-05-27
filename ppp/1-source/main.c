#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../2-include/step.h"
#include "../2-include/backup.h"
#define SAVE_FILE "savegame.txt"
#define START_FILE "2start.txt"
#define MAX_FILENAME_LENGTH 2048

void print_and_clear(char *message, int wait_time) {
    printf("%s", message);
    fflush(stdout);  // Make sure the message is displayed immediately
    sleep(wait_time);
    for (int i = 0; i < strlen(message); i++) {
        printf("\b \b");  // Overwrite each character with a space, then move the cursor back one space
    }
}

int main() {
    Inventory inventory;
    inventory_init(&inventory);

    print_and_clear(
            "   █   █ █▀▀ █   █▀▀ █▀▀█ █▀▄▀█ █▀▀ 　 ▀▀█▀▀ █▀▀█ 　 █▀▀ █  █    █▀▀▄ ▀█ █▀ █▀▀ █▀▀▄ ▀▀█▀▀ █  █ █▀▀█ █▀▀ \n"
            "   █▄█▄█ █▀▀ █   █   █  █ █ ▀ █ █▀▀ 　   █   █  █ 　 █   █▄▄█ ▀▀ █  █  █▄█  █▀▀ █  █   █   █  █ █▄▄▀ █▀▀ \n"
            "    ▀ ▀  ▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀▀ ▀   ▀ ▀▀▀ 　   ▀   ▀▀▀▀ 　 ▀▀▀ ▄▄▄█    ▀▀▀    ▀   ▀▀▀ ▀  ▀   ▀   ▀▀▀▀ ▀ ▀▀ ▀▀▀ "
            "                                                         \n"
            "                       |                     |>>>          |>>>                  |\n"
            "                       *                     |             |                     *\n"
            "                      / \\                    *             *                    / \\\n"
            "                     /___\\                 _/ \\           / \\_                 /___\\\n"
            "                     [   ]                |/   \\_________/   \\|                [   ]\n"
            "                     [ I ]                /     \\       /     \\                [ I ]\n"
            "                     [   ]_ _ _          /       \\     /       \\          _ _ _[   ]\n"
            "                     [   ] U U |        {#########}   {#########}        | U U [   ]\n"
            "                     [   ]====/          \\=======/     \\=======/          \\====[   ]\n"
            "                     [   ]    |           |   I |_ _ _ _| I   |           |    [   ]\n"
            "                     [___]    |_ _ _ _ _ _|     | U U U |     |_ _ _ _ _ _|    [___]\n"
            "                     \\===/  I | U U U U U |     |=======|     | U U U U U | I  \\===/\n"
            "                      \\=/     |===========| I   | + W + |   I |===========|     \\=/\n"
            "                       |  I   |           |     |_______|     |           |   I  |\n"
            "                       |      |           |     |||||||||     |           |      |\n"
            "                       |      |           |   I ||vvvvv|| I   |           |      |\n"
            "                   _-_-|______|-----------|_____||     ||_____|-----------|______|-_-_\n"
            "                      /________\\         /______||     ||______\\         /________\\\n"
            "                     |__________|-------|________\\_____/________|-------|__________|",5);

    for (int i = 0; i < 100; i++) { // Print 100 newline characters
        printf("\n");
    }


    printf("\033[31m\033[5mPress Enter to start...\033[0m\n");
    getchar(); // Wait for user to press Enter

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








