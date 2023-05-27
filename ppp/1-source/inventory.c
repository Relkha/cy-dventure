#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../2-include/inventory.h"

// Initializes the inventory by setting size to 0 and all item slots to NULL
void inventory_init(Inventory* inventory) {
    inventory->size = 0;
    for(int i=0; i<MAX_INVENTORY_SIZE; i++){
        inventory->items[i] = NULL;
    }
}

// Adds an item to the inventory. If the inventory is full or the item is already in the inventory, the function returns -1. 
// Otherwise, it adds the item and increments the size of the inventory.
int inventory_add_item(Inventory* inventory, const char *item_name) {
    if (inventory->size >= MAX_INVENTORY_SIZE || inventory_contains(inventory, item_name)) {
        return -1;
    }
    inventory->items[inventory->size] = strdup(item_name);
    inventory->size++;
    return 0;
}

// Prints all the items in the inventory
void inventory_print(const Inventory* inventory) {
    printf("Inventory:\n");
    for(int i=0; i<inventory->size; i++){
        printf("%s\n", inventory->items[i]);
    }
}

// Checks if an item is in the inventory. If the item is found, it returns 1. Otherwise, it returns 0.
int inventory_contains(const Inventory* inventory, const char *item_name) {
    for(int i=0; i<inventory->size; i++){
        if (strcmp(inventory->items[i], item_name) == 0) {
            return 1;
        }
    }
    return 0;
}

// Frees the memory allocated to the inventory
void free_inventory(Inventory* inventory) {
    for(int i=0; i<inventory->size; i++){
        free(inventory->items[i]);
    }
    free(inventory);
}

