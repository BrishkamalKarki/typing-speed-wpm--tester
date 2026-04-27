#include "main.h"

char paragraph[600];
// Defining the struct here for saving the current WPM and user choosen mode
struct info
{
    int accuracy;
    int rawWPM;
    char mode;
    int correct;
    int progress;
} gameState;

// initializing the typing arena  
int iniTester(char mode){  
    gameState.mode = mode;
    gameState.accuracy = 0.0;
    gameState.rawWPM = 0;
    gameState.correct = 0;
    gameState.progress = 0;
    getRandLine();
    return 0;
}

int getRandLine(){ 
    srand(time(0)); // providing the different initial number for generating a random number, number(t)
    int randLineNum = (rand() % 26) * 2 + 1; // setting the output range [0 - 51, odds only], sentences.txt has 51 lines in total 

    FILE *sentenceFile = fopen("sentences.txt", "r");
    int targetLine = randLineNum; // random line number to take
    char sentences[600];
    int line = 0; // which line the cursor is currently in

    for (line = 1; line <= targetLine; line++){
        fgets(sentences, sizeof(sentences), sentenceFile); // reading the whole line (1 line = 1 paragraph)
    }
    strcpy(paragraph, sentences); // for later use
    splitIntoWords(sentences);
    return 0; 
}

int splitIntoWords(char sentences[]){
    char words[200][20]; // 200 words of 20 character (at max) each
    char *word ;
    int wordCount = 0; // count for how many words are there in the paragraph
    
    // taking the words from the full sentences and putting each word in words array
    word = strtok(sentences, " \n"); // returns the pointer to the 1st character of 1st word, words spllited on the basis of ' '
    
    while (word != NULL){
        strcpy(words[wordCount], word);
        word = strtok(NULL, " \n"); // words spllited on the basis of ' ' and '\n'
        wordCount ++;
    }

    wpmCalculator(words, wordCount); 
    return 0;
}

// displaying the typing arena
int wpmCalculator(char words[][20], int wordCount){
    int rowGUI = 3, timerCol = 36, wpmCol = 12, accCol = 24, prgBarCol = 62, newBars = 0, bars = 0;
    int clockIni, timer, initializedTimer = 0;
    char userChar; 
    CLS;  
    printf("  ================================================================================\n");
    printf("                                                             --------------------\n");
    printf("   WPM [" CYAN "000" RESET "] | ACC [" CYAN "000" RESET "] | TIME [" CYAN "00" RESET "]\n");
    printf("                                                             --------------------\n");
    printf("  ================================================================================\n\n\n");
    printf(GREY); 
    // FOR ALREADY WRITTEN
    // currWordIndx    : storing index of the word we reached in words[]
    // numCharPLine    : array storing number of characters written per line ([59, 66, 72, ...])
    // line            : storing which line we are in (line 1 = 0, line 2 = 1, ...)
    // numCharCurrLine : storing number of charcters present in current line
    int currWordIndx = 0, numCharPLine[10], line = 0, numCharCurrLine = 0; 
    char content[600];


    printf("   " SAVE_CURSOR);
    while(1){
        printf("%s ", words[currWordIndx]); 
        numCharCurrLine += strlen(words[currWordIndx]) + 1; // +1 for the space, +1 for the . in the last line
        currWordIndx ++;
        if (currWordIndx % 13 == 0){ // each line will have 13 words
            printf("\n"); 
            printf("   "); 
            numCharPLine[line] = numCharCurrLine;
            line ++; 
            numCharCurrLine = 0; 
        } 
        if (currWordIndx == wordCount) {
            numCharPLine[line] = numCharCurrLine; // for the last line
            break; 
        }
    } 

    printf("\n\n\n  ================================================================================\n\n" LOAD_CURSOR);
    // numTtlCharWrtn       : nunmber of total characters written from the begining
    // currLine             : number/index of the line we are currently in
    /* numCharTillPrevLine  : if [currLine = 0 : numCharTillPrevLine = 0] 
    if [currLine = 1 : numCharTillPrevLine = 0 + 59] ...
    storing the number of characters till previous line -> easy for backspace case to go to the upper line
    */
    // numCharTillCurrLine  : number of the character till the line from the beginning we are currently in
    int numTtlCharWrtn = 0, currLine = 0, numCharTillPrevLine = 0, numCharTillCurrLine = numCharPLine[0];
    line = 0; // num of line user have reached
    int ttlNumCharsInParagraph = strlen(paragraph);
    char ttlCharWritten[600];
    int targetTime;
    if (gameState.mode == '1')
        targetTime = 10;
    else if (gameState.mode == '2')
        targetTime = 20;
    else
        targetTime = 30;
    printf(SHOW_CURSOR); 
    while(1){ 
        if (initializedTimer){
            // timer part over here 
            timer = time(0) - clockIni;  
            printf(SAVE_CURSOR HIDE_CURSOR "\033[%d;%dH\b\b" CYAN "%02d" RESET LOAD_CURSOR SHOW_CURSOR, rowGUI, timerCol, targetTime - timer);

            if (timer > 0 && numTtlCharWrtn > 0){ 
                // raw WPM part over here 
                gameState.rawWPM = (int)(((float)numTtlCharWrtn / 5) / ((float)timer / 60)); 
                printf(SAVE_CURSOR HIDE_CURSOR "\033[%d;%dH\b\b\b" CYAN "%03d" RESET LOAD_CURSOR SHOW_CURSOR, rowGUI, wpmCol, gameState.rawWPM);
                // accuracy part over here 
                gameState.accuracy = ((float)gameState.correct * 100) / (float)numTtlCharWrtn; 
                printf(SAVE_CURSOR HIDE_CURSOR "\033[%d;%dH\b\b\b" CYAN "%03d" RESET LOAD_CURSOR SHOW_CURSOR, rowGUI, accCol, gameState.accuracy);
                // progress bar part over here
                gameState.progress = (int)((float)gameState.correct* 100 / ttlNumCharsInParagraph);
                newBars = (int)gameState.progress / 5;
                if (gameState.progress % 5 == 0 && newBars != bars){ // only drawing for 1 1 bars
                    bars = newBars;
                    printf(SAVE_CURSOR HIDE_CURSOR "\033[%d;%dH" PURPLE, rowGUI, prgBarCol);
                    for( int i = 1; i <= 20; i++ ){
                        if (i > newBars)
                            printf(" ");
                        else
                            printf("|");
                    }
                    printf(RESET LOAD_CURSOR SHOW_CURSOR);
                }
            }
        }
        if (kbhit()){ 
            if (initializedTimer == 0){ 
                clockIni = time(0);  
                initializedTimer = 1; 
            } 
            userChar = getch(); 
            if (kbhit()){ // ignoring copy and paste  
                while (kbhit()) getch(); // checking if there is any buffer remaining, remained - pasted - buffer cleared
                continue; 
            } 
            else if (numTtlCharWrtn >= strlen(paragraph)) // ending the text 
                continue; 
            else if (userChar == '\t') // ignoring 'tab' key 
                continue;  
            else if (userChar == '\r') // ignoring 'enter' key 
                continue;  
            else if (userChar == '\b'){ // backspace key 
                for(currLine = 0; currLine < line; currLine ++ ){ // getting the last character of the previous line we are returning to
                    numCharTillPrevLine += numCharPLine[currLine]; 
                }  

                if (numTtlCharWrtn == 0){ // for the starting of the text, preventing the backspace  
                    continue; 
                }
                else if (numTtlCharWrtn == numCharTillPrevLine){ // for going in the upper line  
                    numCharTillCurrLine -= numCharPLine[line]; 
                    line --; 
                    numTtlCharWrtn --; 
                    printf(MOVE_UP GREY "%c" RESET "\b", numCharPLine[line], paragraph[numTtlCharWrtn]);
                }
                else{ // normal condition backspace
                    numTtlCharWrtn --; 
                    printf("\b" GREY "%c" RESET "\b", paragraph[numTtlCharWrtn]); 
                } 
                if(ttlCharWritten[numTtlCharWrtn] == paragraph[numTtlCharWrtn])
                    gameState.correct--;
                ttlCharWritten[numTtlCharWrtn] = '\0';
                numCharTillPrevLine = 0; 
            } 
            else{ // showing the user entered character in real time 
                ttlCharWritten[numTtlCharWrtn] = userChar;
                if(userChar == paragraph[numTtlCharWrtn]){ 
                    printf(GREEN "%c" RESET, userChar); 
                    gameState.correct++; 
                }
                else{
                    printf(RED "%c" RESET, userChar);
                }
                numTtlCharWrtn ++; 
                if (numTtlCharWrtn == numCharTillCurrLine){ 
                    line ++; // going to the next line 
                    numCharTillCurrLine += numCharPLine[line]; 
                    printf("\n   ");
                } 
            } 
        } 
        if (timer > targetTime)
            break;
        
        }
    showResults(gameState.rawWPM, gameState.accuracy, gameState.progress);
    return 0; 
} 

