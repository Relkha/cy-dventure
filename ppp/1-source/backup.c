#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../2-include/backup.h"
#include "../2-include/util.h"
#define MAX_FILENAME_LENGTH 4096


int save_game(SaveData* saveData) {
    FILE *file = fopen("savegame.txt", "w");
    if(file == NULL){
        return -1;
    }
    
    fprintf(file, "%s\n", saveData->step_filename);
    fprintf(file, "%d\n", saveData->last_choice);
    fclose(file);
    return 0;
}



// Cette fonction charge un jeu précédemment sauvegardé
int load_game(SaveData* save) {
    FILE *file = fopen("savegame.txt", "r");
    char *n = "savegame.txt";
    strcpy(save->step_filename, n);
    if(file == NULL){
        printf("Erreur: Impossible d'ouvrir le fichier de sauvegarde\n");
        exit(EXIT_FAILURE);
    }
    
    char buffer[MAX_FILENAME_LENGTH];
    if(fgets(buffer, MAX_FILENAME_LENGTH, file) == NULL){
        printf("Erreur: Impossible de lire le nom du fichier d'étape dans le fichier de sauvegarde\n");
        fclose(file);
        return -1;
    }
    chomp(buffer);  // N'oubliez pas de retirer le saut de ligne à la fin du nom de fichier
    
    
    strncpy(save->step_filename, buffer, MAX_FILENAME_LENGTH);
    save->step_filename[MAX_FILENAME_LENGTH - 1] = '\0';
    
    int choice;
    if(fscanf(file, "%d", &choice) != 1){
        printf("Erreur: Impossible de lire le dernier choix dans le fichier de sauvegarde\n");
        fclose(file);
        return -1;
    }
    save->last_choice = choice;
    fclose(file);
    return 0;
}




void ask_save(char *nextStepFile, int choice) {
    char answer;

    printf("Voulez-vous sauvegarder votre progression ? (O/N): ");
    scanf(" %c", &answer);  // The space before %c makes scanf skip any whitespace characters, including '\n'

    if (answer == 'O' || answer == 'o') {
        SaveData saveData = { .step_filename = nextStepFile, .last_choice = choice };
        int result = save_game(&saveData);
        if(result == 0) {
            printf("La partie a été sauvegardée.\n");
        } else {
            printf("Erreur lors de la sauvegarde du jeu.\n");
        }
    }
    else if (answer == 'N'|| answer == 'n' ){
        printf("partie non sauvegardé\n");
    }
}

// Retourne 1 si l'utilisateur veut continuer, 0 sinon.
int ask_continue() {
    char userInput[200];
    printf("Voulez-vous continuer votre partie ? (O/N): ");
    fgets(userInput, sizeof(userInput), stdin);
    userInput[strcspn(userInput, "\n")] = 0;

    if (strcmp(userInput, "O") == 0 || strcmp(userInput, "o") == 0) {
        return 1;
    } else if (strcmp(userInput, "N") == 0 || strcmp(userInput, "n") == 0) {
        return 0;
    } else {
        printf("Réponse non reconnue. Assurez-vous d'entrer O pour continuer ou N pour ne pas continuer.\n");
        return ask_continue();
    }
}



