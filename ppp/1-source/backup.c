#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../2-include/backup.h"
#include "../2-include/util.h"
#define MAX_FILENAME_LENGTH 4096

// Function to save the game
int save_game(SaveData* saveData) {
    // Open file to write the game state
    FILE *file = fopen("savegame.txt", "w");
    if(file == NULL){
        // If the file couldn't be opened, return error (-1)
        return -1;
    }
    
    // Write the filename and the last choice to the file
    fprintf(file, "%s\n", saveData->step_filename);
    fprintf(file, "%d\n", saveData->last_choice);
    
    // Close the file after writing
    fclose(file);
    
    // Return success (0)
    return 0;
}

// Function to load the game from the saved file
int load_game(SaveData* save) {
    // Open the file to read the game state
    FILE *file = fopen("savegame.txt", "r");
    char *n = "savegame.txt";
    strcpy(save->step_filename, n);
    if(file == NULL){
        // If the file couldn't be opened, print an error message and exit
        printf("Erreur: Impossible d'ouvrir le fichier de sauvegarde\n");
        exit(EXIT_FAILURE);
    }
    
    // Buffer to store the filename
    char buffer[MAX_FILENAME_LENGTH];
    if(fgets(buffer, MAX_FILENAME_LENGTH, file) == NULL){
        // If the filename couldn't be read, print an error message, close the file, and return error (-1)
        printf("Erreur: Impossible de lire le nom du fichier d'étape dans le fichier de sauvegarde\n");
        fclose(file);
        return -1;
    }
    
    // Remove newline character at the end of the filename
    chomp(buffer); 
    
    // Copy the filename from buffer to the save data
    strncpy(save->step_filename, buffer, MAX_FILENAME_LENGTH);
    save->step_filename[MAX_FILENAME_LENGTH - 1] = '\0';
    
    // Variable to store the last choice
    int choice;
    if(fscanf(file, "%d", &choice) != 1){
        // If the last choice couldn't be read, print an error message, close the file, and return error (-1)
        printf("Erreur: Impossible de lire le dernier choix dans le fichier de sauvegarde\n");
        fclose(file);
        return -1;
    }
    
    // Store the last choice in the save data
    save->last_choice = choice;
    
    // Close the file after reading
    fclose(file);
    
    // Return success (0)
    return 0;
}

// Function to ask the user if they want to save their progress
void ask_save(char *nextStepFile, int choice) {
    char answer;

    // Prompt user for input
    printf("Voulez-vous sauvegarder votre progression ? (O/N): ");
    scanf(" %c", &answer);  // The space before %c makes scanf skip any whitespace characters, including '\n'

    // If the user wants to save the game
    if (answer == 'O' || answer == 'o') {
        // Save the game
        SaveData saveData = { .step_filename = nextStepFile, .last_choice = choice };
        int result = save_game(&saveData);
        // If the game was saved successfully
        if(result == 0) {
            printf("La partie a été sauvegardée.\n");
        } else {
            // If there was an error saving the game
            printf("Erreur lors de la sauvegarde du jeu.\n");
        }
    }
    // If the user doesn't want to save the game
    else if (answer == 'N'|| answer == 'n' ){
        printf("partie non sauvegardé\n");
    }
}

// Function to ask the user if they want to continue playing
int ask_continue() {
    char userInput[200];
    
    // Prompt user for input
    printf("Voulez-vous continuer votre partie ? (O/N): ");
    fgets(userInput, sizeof(userInput), stdin);
    userInput[strcspn(userInput, "\n")] = 0;

    // If the user wants to continue
    if (strcmp(userInput, "O") == 0 || strcmp(userInput, "o") == 0) {
        return 1;
    } 
    // If the user does not want to continue
    else if (strcmp(userInput, "N") == 0 || strcmp(userInput, "n") == 0) {
        return 0;
    } 
    // If the user input is not recognized
    else {
        printf("Réponse non reconnue. Assurez-vous d'entrer O pour continuer ou N pour ne pas continuer.\n");
        // Ask the user again
        return ask_continue();
    }
}




