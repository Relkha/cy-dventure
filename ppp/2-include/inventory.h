// inventory.h file
#ifndef INVENTORY_H
#define INVENTORY_H

// Maximum number of items that can be stored in the inventory.
// You can adjust this value based on your needs.
#define MAX_INVENTORY_SIZE 10

// The Inventory structure which holds an array of item names and the current size of the inventory.
typedef struct Inventory {
    int size;
    char* items[MAX_INVENTORY_SIZE];
} Inventory;

// Function to initialize an inventory structure. It sets the size to 0 and all item slots to NULL.
void inventory_init(Inventory* inventory);

// Function to add an item to the inventory. If the inventory is not full, it adds the item and returns 1. If the inventory is full, it returns 0.
int inventory_add_item(Inventory* inventory, const char *item_name);

// Function to print the contents of the inventory. It loops through each item slot and prints the name of the item if it is not NULL.
void inventory_print(const Inventory* inventory);

// Function to check if an item is in the inventory. If the item is found, it returns 1. Otherwise, it returns 0.
int inventory_contains(const Inventory* inventory, const char *item_name);

// Function to free the memory allocated for the items in the inventory. It should be called when the inventory is no longer needed.
void free_inventory(Inventory* inventory);

#endif // INVENTORY_H


