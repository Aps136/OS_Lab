#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int start;
    int size;
    struct Block* next;
} Block;

Block* freeList = NULL;

void addBlock(int start, int size) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    newBlock->start = start;
    newBlock->size = size;
    newBlock->next = NULL;

    if (freeList == NULL) {
        freeList = newBlock;
        return;
    }

    // Insert at end of free list
    Block* temp = freeList;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newBlock;
}

void printFreeList() {
    printf("Free list blocks (start, size):\n");
    Block* temp = freeList;
    while (temp != NULL) {
        printf("(%d, %d) -> ", temp->start, temp->size);
        temp = temp->next;
    }
    printf("NULL\n");
}

// First Fit allocation
int firstFit(int size) {
    Block *prev = NULL, *curr = freeList;
    while (curr != NULL) {
        if (curr->size >= size) {
            int allocStart = curr->start;

            // If block size equals requested size, remove block from free list
            if (curr->size == size) {
                if (prev == NULL) {
                    freeList = curr->next;
                } else {
                    prev->next = curr->next;
                }
                free(curr);
            } else {
                // Otherwise, reduce size and move start
                curr->start += size;
                curr->size -= size;
            }

            return allocStart; // Return starting address of allocated memory
        }
        prev = curr;
        curr = curr->next;
    }
    return -1; // Allocation failed
}

// Best Fit allocation
int bestFit(int size) {
    Block *prev = NULL, *curr = freeList;
    Block *best = NULL, *bestPrev = NULL;

    while (curr != NULL) {
        if (curr->size >= size) {
            if (best == NULL || curr->size < best->size) {
                best = curr;
                bestPrev = prev;
            }
        }
        prev = curr;
        curr = curr->next;
    }

    if (best == NULL) {
        return -1; // No suitable block found
    }

    int allocStart = best->start;

    if (best->size == size) {
        // Remove block from free list
        if (bestPrev == NULL) {
            freeList = best->next;
        } else {
            bestPrev->next = best->next;
        }
        free(best);
    } else {
        best->start += size;
        best->size -= size;
    }

    return allocStart;
}

void freeMemory(int start, int size) {
    // Add the freed block back to free list and merge if adjacent blocks found
    Block* newBlock = (Block*)malloc(sizeof(Block));
    newBlock->start = start;
    newBlock->size = size;
    newBlock->next = NULL;

    if (freeList == NULL) {
        freeList = newBlock;
        return;
    }

    Block* prev = NULL;
    Block* curr = freeList;

    // Insert in sorted order by start address
    while (curr != NULL && curr->start < start) {
        prev = curr;
        curr = curr->next;
    }

    newBlock->next = curr;
    if (prev == NULL) {
        freeList = newBlock;
    } else {
        prev->next = newBlock;
    }

    // Merge adjacent blocks
    // Merge with next
    if (newBlock->next != NULL && newBlock->start + newBlock->size == newBlock->next->start) {
        newBlock->size += newBlock->next->size;
        Block* temp = newBlock->next;
        newBlock->next = temp->next;
        free(temp);
    }

    // Merge with previous
    if (prev != NULL && prev->start + prev->size == newBlock->start) {
        prev->size += newBlock->size;
        prev->next = newBlock->next;
        free(newBlock);
    }
}

int main() {
    int totalMemory, nProcesses;

    printf("Enter total memory size: ");
    scanf("%d", &totalMemory);

    // Initialize free list with entire memory block
    freeList = NULL;
    addBlock(0, totalMemory);

    printf("Enter number of processes: ");
    scanf("%d", &nProcesses);

    int* allocStartAddresses = (int*)malloc(nProcesses * sizeof(int));

    printf("Choose allocation strategy:\n1. First Fit\n2. Best Fit\nEnter choice: ");
    int choice;
    scanf("%d", &choice);

    for (int i = 0; i < nProcesses; i++) {
        int size;
        printf("Enter memory required for process %d: ", i);
        scanf("%d", &size);

        int addr = -1;
        if (choice == 1)
            addr = firstFit(size);
        else if (choice == 2)
            addr = bestFit(size);
        else {
            printf("Invalid choice!\n");
            free(allocStartAddresses);
            return 1;
        }

        if (addr == -1) {
            printf("Memory allocation failed for process %d\n", i);
            allocStartAddresses[i] = -1;
        } else {
            printf("Process %d allocated at address %d\n", i, addr);
            allocStartAddresses[i] = addr;
        }

        printFreeList();
    }

    // Example freeing memory (optional)
    /*
    printf("Freeing memory for process 1\n");
    if (allocStartAddresses[1] != -1)
        freeMemory(allocStartAddresses[1], 50);  // Assume size 50 for demo

    printFreeList();
    */

    free(allocStartAddresses);
    return 0;
}
