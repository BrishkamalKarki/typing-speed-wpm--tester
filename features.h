// ansi codes for the colour coding
#define PURPLE  "\033[38;2;102;47;115m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"   
#define YELLOW  "\033[1;33m"   
#define CYAN    "\033[1;36m"   
#define GREY    "\033[90m"   
#define RESET   "\033[0m"  // RESET should be used to reset the colour of the terminal to default
 
#define MOVE_UP   "\033[1A\033[%dC\b" // going to the upper line of the rightest side 
#define SAVE_CURSOR "\033[s" 
#define LOAD_CURSOR "\033[u" 
#define CLS       system("cls") // function call for blacking out the terminal - CLI command 
#define HIDE_CURSOR	"\033[?25l"
#define SHOW_CURSOR	"\033[?25h"
#define MOVE_TO_TIME "\033[%d;%d"

 