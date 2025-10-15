#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to find the page in the frames that will not be used for the longest period
int findOptimalReplacement(int frames[], int numFrames, int pages[], int numPages, int currentPageIndex) {
    int maxFutureUse = -1;
    int indexToReplace = -1;

    for (int i = 0; i < numFrames; i++) {
        int futureUse = INT_MAX; // Initialize to maximum possible value (will be a large number)
        int found = 0;

        // Check when the current page in the frame (frames[i]) will be used next
        for (int j = currentPageIndex + 1; j < numPages; j++) {
            if (frames[i] == pages[j]) {
                futureUse = j; // Found the next use, its index is j
                found = 1;
                break;
            }
        }

        // If the page is never used again (found == 0), it's the best one to replace
        if (found == 0) {
            return i;
        }

        // If this page's next use is further in the future than others seen so far
        if (futureUse > maxFutureUse) {
            maxFutureUse = futureUse;
            indexToReplace = i;
        }
    }
    return indexToReplace;
}

void optimalPageReplacement(int *pages, int numPages, int numFrames) {
    // Dynamic allocation for frames and initializing to -1 (empty)
    int *frames = (int *)malloc(numFrames * sizeof(int));
    if (frames == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    int pageFaults = 0;
    int frameCount = 0; // Number of currently occupied frames

    printf("\n--- Simulation Steps ---\n");
    for (int i = 0; i < numPages; i++) {
        int currentPage = pages[i];
        int hit = 0;

        // Check for a hit (page already in a frame)
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == currentPage) {
                hit = 1;
                break;
            }
        }

        printf("Reference: %d | ", currentPage);

        if (hit) {
            printf("Hit. Frames: ");
        } else {
            pageFaults++;
            // Case 1: Frames are not yet full, just add the new page
            if (frameCount < numFrames) {
                frames[frameCount++] = currentPage;
            }
            // Case 2: Frames are full, perform Optimal replacement
            else {
                int replaceIndex = findOptimalReplacement(frames, numFrames, pages, numPages, i);
                frames[replaceIndex] = currentPage;
            }
            printf("Fault (%d). Frames: ", pageFaults);
        }

        // Display current state of frames
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- "); // Placeholder for an empty frame
            }
        }
        printf("\n");
    }

    printf("\n------------------------\n");
    printf("Total Page Faults: %d\n", pageFaults);

    free(frames);
}

int main() {
    int numFrames, numPages;
    int *pages;

    // 1. Read the number of frames
    printf("Enter the number of frames: ");
    if (scanf("%d", &numFrames) != 1 || numFrames <= 0) {
        printf("Invalid number of frames.\n");
        return 1;
    }

    // 2. Read the number of pages
    printf("Enter the number of pages in the reference string: ");
    if (scanf("%d", &numPages) != 1 || numPages <= 0) {
        printf("Invalid number of pages.\n");
        return 1;
    }

    // Dynamic allocation for page reference string
    pages = (int *)malloc(numPages * sizeof(int));
    if (pages == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // 3. Read the page numbers
    printf("Enter the page reference string (separated by spaces):\n");
    for (int i = 0; i < numPages; i++) {
        if (scanf("%d", &pages[i]) != 1) {
            printf("Invalid input for page numbers.\n");
            free(pages);
            return 1;
        }
    }

    // 5. Initialize values in frames to -1 (done inside optimalPageReplacement)
    // 6. Replace the page that will not be used for the longest period of time (done in findOptimalReplacement)

    // Run the simulation
    optimalPageReplacement(pages, numPages, numFrames);

    // 7. Display the number of page faults (done at the end of optimalPageReplacement)

    free(pages);
    return 0; // 8. stop
}
