#include"railcipher.h"

int main(void) {
	char command[MAX_COMMAND_TOKEN_LENGTH];//placeholder for a command...
	char lastCharacter;
	lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH, " ");
	if (!strcmp(command, "quit"))
		return 0;
	else if (!strcmp(command, "encrypt"))
	{
		if (lastCharacter == '\n')
			printf("Key is missing for encrypt command!.\n");
		else
			handleEncryption();
	}
	else if (!strcmp(command, "decrypt"))
	{
		if (lastCharacter == '\n')
			printf("Key is missing for decrypt command!\n");
		else
			handleDecryption();
	}
	else
		printf("Invalid command!\n");
	return 0;
}
char getCommandWord(char command[], int maxLength, char* delimiter) {
	char c;
	int i = 0, j, n = strlen(delimiter);
	while (isspace(c = getchar()));//skip leading white spaces
	while (i < maxLength - 1 && c != EOF) {
		j = -1;
		while (delimiter[++j] && delimiter[j] != c);
		if (j != n)
			break;
		if (isspace(c))
			break;
		else {
			command[i++] = c;
			c = getchar();
		}
	}
	command[i] = '\0';//end of string sign
	if (!isspace(c))
		return c;
	while(*delimiter)
		if(isspace(*(delimiter++)))
			return c;
	while (isspace(c))//skip trailing white spaces
		c = getchar();
	return c;
}
char getLine(char* line, int maxLength) {
	char lastCharacter;
	int i;
	for (i = 0; i < maxLength - 1 && (line[i] = getchar()) != '\n' && line[i] != EOF; i++);
	lastCharacter = line[i++];
	line[i] = '\0';//end of string sign
	return lastCharacter;
}
