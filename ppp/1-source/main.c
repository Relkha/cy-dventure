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

    
        // Define the initial filename to load the game from
    char *initialStepFilename = "2start.txt";
    
    // Create a pointer to store the initial step of the game
    Step *initialStep;
    
    // Allocate memory to save game data 
    SaveData *saveData = malloc(sizeof(SaveData));
    
    // Allocate memory to save the filename of the step in the game
    saveData->step_filename = malloc(MAX_FILENAME_LENGTH * sizeof(char));
    
    int result;

    // Check if the player wants to continue the game from where they left off
    if (ask_continue() == 1) {
        // Try to load the game
        result = load_game(saveData);
        
        // Check if there was an error when loading the game
        if (result == -1) {
            printf("Error while loading the game\n");
            
            // If there was an error, free the memory allocated for savedata and end the program
            free(saveData);
            return 1;
        }
        
        // If the game loaded correctly, set the initial step to the saved step
        initialStepFilename = saveData->step_filename;
    }

    // Load the initial step
    initialStep = load_step(initialStepFilename, &inventory);
    
    // Check if there was an error when loading the initial step
    if (initialStep == NULL) {
        printf("Error while loading the initial step\n");
        
        // If there was an error, free the memory allocated for the step filename and savedata, then end the program
        free(saveData->step_filename);
        free(saveData);
        return 1;
    }
    else{
        // If the initial step loaded correctly, execute the step
        execute_step(initialStep, &inventory);
    }

    // Free the memory allocated for the initial step
    free_step(initialStep);

    // Print the contents of the inventory at the end of the program
    inventory_print(&inventory);

    // Free the memory allocated for the step filename and savedata at the end of the program
    free(saveData->step_filename);
    free(saveData);
    return 0;
}








