#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_COMMAND_TOKEN_LENGTH 25
#define MAX_KEY_LENGTH 100
#define MAX_LINE_LENGTH 2500
char getCommandWord(char command[], int maxLength, char* delimiter);
void handleEncryption(void);
void handleDecryption(void);
char getLine(char* line, int limit);
void handleDecryption(void);
