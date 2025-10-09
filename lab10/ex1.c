#include <stdio.h>
#include <stdlib.h>

// Function to check if page is in frames
int isInFrames(int* frames, int nFrames, int page) {
    for (int i = 0; i < nFrames; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

// FIFO page replacement
int fifo(int* pages, int nPages, int nFrames) {
    int* frames = (int*)malloc(nFrames * sizeof(int));
    for (int i = 0; i < nFrames; i++)
        frames[i] = -1;

    int pageFaults = 0;
    int nextToReplace = 0;

    printf("\nFIFO Page Replacement Process:\n");
    for (int i = 0; i < nPages; i++) {
        int page = pages[i];

        if (!isInFrames(frames, nFrames, page)) {
            // Page fault - replace page
            frames[nextToReplace] = page;
            nextToReplace = (nextToReplace + 1) % nFrames;
            pageFaults++;
        }

        printf("After request %d: ", page);
        for (int j = 0; j < nFrames; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf(pageFaults && frames[nextToReplace == 0 ? nFrames - 1 : nextToReplace - 1] == page ? "(No Page Fault)\n" : "(Page Fault)\n");
    }

    free(frames);
    return pageFaults;
}

// Function to find optimal page to replace
int findOptimal(int* pages, int nPages, int* frames, int nFrames, int currentIndex) {
    int farthest = currentIndex;
    int index = -1;

    for (int i = 0; i < nFrames; i++) {
        int j;
        for (j = currentIndex; j < nPages; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == nPages) // Not found in future
            return i;
    }

    if (index == -1)
        return 0;
    else
        return index;
}

// Optimal page replacement
int optimal(int* pages, int nPages, int nFrames) {
    int* frames = (int*)malloc(nFrames * sizeof(int));
    for (int i = 0; i < nFrames; i++)
        frames[i] = -1;

    int pageFaults = 0;

    printf("\nOptimal Page Replacement Process:\n");
    for (int i = 0; i < nPages; i++) {
        int page = pages[i];

        if (!isInFrames(frames, nFrames, page)) {
            pageFaults++;

            int emptyIndex = -1;
            for (int k = 0; k < nFrames; k++) {
                if (frames[k] == -1) {
                    emptyIndex = k;
                    break;
                }
            }

            if (emptyIndex != -1) {
                frames[emptyIndex] = page;
            } else {
                int replaceIndex = findOptimal(pages, nPages, frames, nFrames, i + 1);
                frames[replaceIndex] = page;
            }
        }

        printf("After request %d: ", page);
        for (int j = 0; j < nFrames; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf(isInFrames(frames, nFrames, page) ? "(Page Fault if new)\n" : "(No Page Fault)\n");
    }

    free(frames);
    return pageFaults;
}

int main() {
    int nFrames, nPages;

    printf("Enter number of frames: ");
    scanf("%d", &nFrames);

    printf("Enter number of page requests: ");
    scanf("%d", &nPages);

    int* pages = (int*)malloc(nPages * sizeof(int));
    printf("Enter page reference string:\n");
    for (int i = 0; i < nPages; i++) {
        scanf("%d", &pages[i]);
    }

    int choice;
    printf("Choose Page Replacement Algorithm:\n1. FIFO\n2. Optimal\nEnter choice: ");
    scanf("%d", &choice);

    int pageFaults = 0;
    if (choice == 1) {
        pageFaults = fifo(pages, nPages, nFrames);
        printf("\nTotal Page Faults (FIFO): %d\n", pageFaults);
    } else if (choice == 2) {
        pageFaults = optimal(pages, nPages, nFrames);
        printf("\nTotal Page Faults (Optimal): %d\n", pageFaults);
    } else {
        printf("Invalid choice!\n");
    }

    free(pages);
    return 0;
}
