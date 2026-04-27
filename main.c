//* WPM TESTER (TYPING SPEED TESTER)

#include "main.h"

int main(){
    wpmInterface(); // loads the mainmenu screen and the typing arena
    return 0; 
}

int wpmInterface(){ 
    char mode = mainMenu();
    iniTester(mode);
    return 0; 
}
