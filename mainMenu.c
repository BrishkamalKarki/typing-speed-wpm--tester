#include "main.h"

// loading the initial main menu
int mainMenu(){
    CLS;
    printf("\n\n\n" CYAN );
    printf("  __        __  ____    __  __     _____   _____   ____    _____   _____   ____  \n");
    printf("  \\ \\      / / |  _ \\  |  \\/  |   |_   _| | ____| / ___|  |_   _| | ____| |  _ \\ \n");
    printf("   \\ \\ /\\ / /  | |_) | | |\\/| |     | |   |  _|   \\___ \\    | |   |  _|   | |_) |\n");
    printf("    \\ V  V /   |  __/  | |  | |     | |   | |___   ___) |   | |   | |___  |  _ < \n");
    printf("     \\_/\\_/    |_|     |_|  |_|     |_|   |_____| |____/    |_|   |_____| |_| \\_\\\n");
    printf("\n"); 
    printf("                            A terminal typing speed test\n" RESET);
    printf("\n");
    printf("  ================================================================================\n");
    printf("\n");
    printf("   HIGHEST SCORE  : " CYAN " 000 " RESET "WPM\n");
    printf("\n");
    printf("  ================================================================================\n");
    printf("\n");
    printf("   SELECT TIME\n");
    printf("\n");
    printf("   [ " CYAN "1" RESET " ]  " CYAN "10" RESET " seconds\n" );
    printf("   [ " CYAN "2" RESET " ]  " CYAN "20" RESET " seconds\n" );
    printf("   [ " CYAN "3" RESET " ]  " CYAN "30" RESET " seconds\n" );
    printf("\n");
    printf("  ================================================================================\n");
    printf("\n");
    printf("   press key ["CYAN "1" RESET "," CYAN "2" RESET "," CYAN "3" RESET "]" RESET " to select  | " CYAN " Q " RESET "to quit\n");
    printf("\n");
    printf("  ================================================================================\n");
    printf("\n\n");

    getMode();
    return 0;
}

// taking the mode input from the user
int getMode(){
    gameState.mode = getch();
    if (gameState.mode == 'Q')
        exit(0);
    if (gameState.mode != '1' && gameState.mode != '2' && gameState.mode != '3')
        mainMenu();
    return 0;
}