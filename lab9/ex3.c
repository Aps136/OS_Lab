#include <stdio.h>

int main() {
    int nFrames, nPages;

    printf("Enter number of frames: ");
    scanf("%d", &nFrames);

    printf("Enter number of page requests: ");
    scanf("%d", &nPages);

    int pages[nPages];
    printf("Enter the page reference string:\n");
    for (int i = 0; i < nPages; i++) {
        scanf("%d", &pages[i]);
    }

    int frames[nFrames];
    for (int i = 0; i < nFrames; i++)
        frames[i] = -1;  // Initialize frames as empty

    int pageFaults = 0;
    int nextToReplace = 0;

    printf("\nPage replacement process:\n");
    for (int i = 0; i < nPages; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in frames (page hit)
        for (int j = 0; j < nFrames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // Page fault occurs
            frames[nextToReplace] = page;
            nextToReplace = (nextToReplace + 1) % nFrames;
            pageFaults++;
        }

        // Print current frames state
        printf("After request %d: ", page);
        for (int j = 0; j < nFrames; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        if (found)
            printf("(No Page Fault)\n");
        else
            printf("(Page Fault)\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
