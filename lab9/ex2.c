#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int start;
    int size;
    struct Block* next;
} Block;

Block* freeList = NULL;

// Add a free block (insert at end)
void addBlock(int start, int size) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    newBlock->start = start;
    newBlock->size = size;
    newBlock->next = NULL;

    if (freeList == NULL) {
        freeList = newBlock;
        return;
    }

    Block* temp = freeList;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newBlock;
}

// Print current free blocks
void printFreeList() {
    printf("Free memory blocks (start, size): ");
    Block* temp = freeList;
    while (temp != NULL) {
        printf("(%d, %d) -> ", temp->start, temp->size);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Worst Fit allocation
int worstFit(int size) {
    Block *prev = NULL, *curr = freeList;
    Block *worst = NULL, *worstPrev = NULL;

    while (curr != NULL) {
        if (curr->size >= size) {
            if (worst == NULL || curr->size > worst->size) {
                worst = curr;
                worstPrev = prev;
            }
        }
        prev = curr;
        curr = curr->next;
    }

    if (worst == NULL) {
        return -1; // No suitable block found
    }

    int allocStart = worst->start;

    if (worst->size == size) {
        // Remove block from free list
        if (worstPrev == NULL) {
            freeList = worst->next;
        } else {
            worstPrev->next = worst->next;
        }
        free(worst);
    } else {
        // Reduce size and move start of free block
        worst->start += size;
        worst->size -= size;
    }

    return allocStart;
}

// Free memory back to free list and merge adjacent blocks
void freeMemory(int start, int size) {
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

    // Merge with next if adjacent
    if (newBlock->next != NULL && newBlock->start + newBlock->size == newBlock->next->start) {
        newBlock->size += newBlock->next->size;
        Block* temp = newBlock->next;
        newBlock->next = temp->next;
        free(temp);
    }

    // Merge with previous if adjacent
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

    // Initialize free list with one big block of total memory
    freeList = NULL;
    addBlock(0, totalMemory);

    printf("Enter number of processes: ");
    scanf("%d", &nProcesses);

    int* allocStartAddresses = (int*)malloc(nProcesses * sizeof(int));

    for (int i = 0; i < nProcesses; i++) {
        int size;
        printf("Enter memory required for process %d: ", i);
        scanf("%d", &size);

        int addr = worstFit(size);
        if (addr == -1) {
            printf("Memory allocation failed for process %d\n", i);
            allocStartAddresses[i] = -1;
        } else {
            printf("Process %d allocated at address %d\n", i, addr);
            allocStartAddresses[i] = addr;
        }

        printFreeList();
    }

    // Optionally, you can test freeing memory here by calling freeMemory()

    free(allocStartAddresses);
    return 0;
}
