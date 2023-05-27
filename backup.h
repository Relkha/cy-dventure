// backup.h file
#ifndef BACKUP_H
#define BACKUP_H

// SaveData structure holds the filename of the current step and the last choice made by the user.
typedef struct {
    char* step_filename;
    int last_choice;
} SaveData;

// Function to save the game state to a file. The save file will contain the name of the current step file and the choice made by the user.
// Returns 0 on success, -1 on failure.
int save_game(SaveData* saveData);

// Function to load the game state from a save file. The step filename and the choice will be copied to the output arguments step_filename and choice.
// Returns 0 on success, -1 on failure.
int load_game(SaveData* save);
void ask_save(char *nextStepFile, int choice);
int ask_continue();

#endif /* BACKUP_H */
