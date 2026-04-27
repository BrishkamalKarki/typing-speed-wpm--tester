#include "main.h"

int showResults(int rawWPM, int accuracy, int progress){
    char retryChar;
    int opWPM = rawWPM * accuracy / 100;
    FILE *fPtr = fopen("highestScore.txt", "r");
    int highSc;
    fscanf(fPtr, "%d", &highSc);
    if (highSc < opWPM){
        FILE *wfPtr = fopen("highestScore.txt", "w");
        fprintf(wfPtr, "%d", opWPM);
        highSc = opWPM;
        fclose(wfPtr);
    }
    fclose(fPtr);

    printf(RESET);
    CLS;
    printf("\n\n");
    printf("  ================================================================================\n");
    printf("   TEST COMPLETED\n");
    printf("  ================================================================================\n\n");

    // display stats over here
    printf("   YOUR RESULTS:\n\n");
    printf("   RAW WPM          [ " CYAN "%03d" RESET " ]\n", rawWPM);
    printf("   OPTIMIZED WPM    [ " CYAN "%03d" RESET " ]\n", opWPM);
    printf("   HIGHEST WPM      [ " CYAN "%03d" RESET " ]\n", highSc);
    printf("   ACCURACY         [ " GREEN "%03d%%" RESET " ]\n", accuracy);
    printf("   TEXT COMPLETED   [ " YELLOW "%03d%%" RESET " ]\n", progress);
    printf("\n");
    printf("  ================================================================================\n\n");
    printf("   press " CYAN "R" RESET " to go to Main Menu | press " CYAN "Q" RESET " to quit\n\n");
    printf("  ================================================================================\n\n");

    printf(HIDE_CURSOR);
    retryChar = getch();

    if (retryChar == 'Q')
        exit(0);
    else if (retryChar == 'R')
        wpmInterface();
    else
        showResults(rawWPM, accuracy, progress);
    return 0;
}