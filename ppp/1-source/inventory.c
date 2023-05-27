#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../2-include/inventory.h"

void inventory_init(Inventory* inventory) {
    inventory->size = 0;
    for(int i=0; i<MAX_INVENTORY_SIZE; i++){
        inventory->items[i] = NULL;
    }
}

int inventory_add_item(Inventory* inventory, const char *item_name) {
    if (inventory->size >= MAX_INVENTORY_SIZE || inventory_contains(inventory, item_name)) {
        return -1;
    }
    inventory->items[inventory->size] = strdup(item_name);
    inventory->size++;
    return 0;
}

void inventory_print(const Inventory* inventory) {
    printf("Inventory:\n");
    for(int i=0; i<inventory->size; i++){
        printf("%s\n", inventory->items[i]);
    }
}

int inventory_contains(const Inventory* inventory, const char *item_name) {
    for(int i=0; i<inventory->size; i++){
        if (strcmp(inventory->items[i], item_name) == 0) {
            return 1;
        }
    }
    return 0;
}
// Libère la mémoire allouée à l'inventaire
void free_inventory(Inventory* inventory) {
    for(int i=0; i<inventory->size; i++){
        free(inventory->items[i]);
    }
    free(inventory);
}

