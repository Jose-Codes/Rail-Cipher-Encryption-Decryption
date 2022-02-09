#include"railcipher.h"
#define MAX_NUM_SENTENCES 5000
#define IN 1
#define OUT 0
static char** sentences[MAX_NUM_SENTENCES];
static int nwordsArray[MAX_NUM_SENTENCES];

int wordCount(char* line) { // counts the number of words in a given line
	int state = OUT, i = 0, count = 0;
	while (line[i])
		if (!isspace(line[i++])) {
			if (state == OUT) {
				count++;
				state = IN;
			}
		}
		else
			state = OUT;
	return count;
}

int getKeys(int* keys) {
	int i = 0; // number of keys (length of biggest sentence)
	char temp[MAX_COMMAND_TOKEN_LENGTH]; 
	if (getCommandWord(temp, MAX_COMMAND_TOKEN_LENGTH, "(") != '(') 
		return 0;
	while (getCommandWord(temp, MAX_COMMAND_TOKEN_LENGTH, ",)") != ')') // gets the string from the buffer
		if (i == MAX_KEY_LENGTH)
			return  0;
		else
			keys[i++] = atoi(temp); // converts the keys to numbers and stores them in the array.
	keys[i++] = atoi(temp);
	return i;
}
void tokenize(char* line, char** tokens) { // split the string by spaces
	int i = 0;
	char* temp;
	temp = strtok(line, " ");
	tokens[i] = (char*)malloc(strlen(temp) * sizeof(char));
	strcpy(tokens[i++], temp);
	while (temp = strtok(NULL, " ")) {
		tokens[i] = (char*)malloc(strlen(temp) * sizeof(char));
		strcpy(tokens[i++], temp);
	}	
	//deleting the dot and possibly a new line from the last token!
	if (tokens[i - 1][strlen(tokens[i - 1]) - 2] == '.')
		tokens[i - 1][strlen(tokens[i - 1]) - 2] = '\0';
	else
		tokens[i - 1][strlen(tokens[i - 1]) - 1] = '\0';
}
int isvalidkey(int* keys, int k) {
	int i, *flag = (int*)malloc(k*sizeof(int));
	for (i = 0; i < k;i++)
		flag[i] = 0;
	for (i = 0; i < k;i++)
		if (keys[i] >= k)
			return 0;
		else
			flag[keys[i]] = 1;
	for (i = 0; i < k;i++)
		if (!flag[i])
			return 0;
	return 1;
}
void handleEncryption(void) {
	// First step, get the keys
	int keys[MAX_KEY_LENGTH]; // holds the encryption key
	char temp, line[MAX_LINE_LENGTH];
	int i = 0, j, k, nwords, nlines, maxwords = -1;
	k = getKeys(keys); // gets the keys and stores them in the array 'keys'

	// Error handling
	if (getchar() != '\n' || k < 1) {
		printf("Error: syntax  of encryption command is not valid!\n");
		return;
	}
	if (!isvalidkey(keys,k)) {
		printf("Error: invalid key! key of length %d must be a permutation of non-negative integers less than %d\n", k, k);
		return;
	}
	i = 0;

	/*Count the number of words and lines*/
	while (1) { // gets the user's next line until the array is full or EOF
		temp = getLine(line, MAX_LINE_LENGTH);
		if (i == MAX_NUM_SENTENCES)
			break;
		nwords = wordCount(line); // count the number of words in the line
		if (!nwords) {
			i--;
			if (temp == EOF)
				break;
			continue;
		}
		if (maxwords < nwords)
			maxwords = nwords;
		nwordsArray[i] = nwords; // number of words in that line
		sentences[i] = (char**)malloc(nwords * sizeof(char*));
		tokenize(line, sentences[i++]);
		if (temp == EOF)
			break;
	}
	nlines = i;

	//more error handling
	if (k < maxwords) {
		printf("Error: the given key is too short for this plaintext.\nThe minimum key length must be %d\n", maxwords);
		return;
	}

	//display the encrypted message
	printf("\nThe encrypted text is:\n");
	for (i = 0; i < k;i++)
		for (j = 0; j < nlines;j++)
			printf("%s ", (keys[i] < nwordsArray[j]) ? sentences[j][keys[i]] : "null");
	printf("\n");
}
