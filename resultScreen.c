#include "main.h"

int showResults(int rawWPM, int accuracy, int progress){
    char retryChar;
    int opWPM = rawWPM * accuracy / 100;
    FILE *fPtr = fopen("highestScore.txt", "w");
    int highSc;
    fscanf(fPtr, "%d", &highSc);
    if (highSc < opWPM)
        fprintf(fPtr, "%d", opWPM);
    fclose(fPtr);
    printf(RESET);
    CLS;
    printf("\n\n");
    printf("  ================================================================================\n");
    printf("   TEST COMPLETE!\n");
    printf("  ================================================================================\n\n");

    // display stats
    printf("   Your Results:\n\n");
    printf("   Raw WPM: " CYAN "%d" RESET "\n", rawWPM);
    printf("   Optimized WPM: " CYAN "%d" RESET "\n", opWPM);
    printf("   Accuracy: " GREEN "%d%%" RESET "\n", accuracy);
    printf("   Text Completed: " YELLOW "%d%%" RESET "\n", progress);
    printf("\n");
    printf("  ================================================================================\n\n");
    printf("   Press " CYAN "R" RESET " to try again, or press " CYAN "Q" RESET " to quit\n\n");
    printf("  ================================================================================\n\n");

    printf(HIDE_CURSOR);
    retryChar = getch();
    printf(SHOW_CURSOR);

    if (retryChar == 'Q' || retryChar == 'q')
        exit(0);
    else if (retryChar == 'R' || retryChar == 'r')
        wpmInterface();
    else
        showResults(rawWPM, accuracy, progress);
    return 0;
}