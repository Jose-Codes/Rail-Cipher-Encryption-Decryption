#include"railcipher.h"

/**
 * @brief 
 * Step 1: Get the encryption keys from the user
 * Step 2: Get the sentences from the user
 * Step 3: Use the number of keys and the number of sentences
 *         to reconstruct the table.
 * Step 4: Construct the table by putting the words in their
 *         corresponding columns and rows.
 * Step 5: Iterate through the rows to get the decrypted message.
 */
#define MAX_NUM_SENTENCES 5000
static char** encrypted_sentences[MAX_NUM_SENTENCES];
static int nwordsLine[MAX_NUM_SENTENCES];

void handleDecryption(void) {

	// Step 1: Get keys
    int keys[MAX_KEY_LENGTH]; // holds the encryption key
	char temp, line[MAX_LINE_LENGTH];
	int i = 0, j, k, nwords, nlines, maxwords = -1;
	k = getKeys(keys); // get the encryption keys

	int total_words = 0;

	//Step 2: Get sentences
    while (1) {
		temp = getLine(line, MAX_LINE_LENGTH); 
		if (i == MAX_NUM_SENTENCES)
			break;
		nwords = wordCount(line);
		if (!nwords) {
			i--;
			if (temp == EOF)
				break;
			continue;
		}
		if (maxwords < nwords)
			maxwords = nwords;
		nwordsLine[i] = nwords;
		encrypted_sentences[i] = (char**)malloc(nwords * sizeof(char*));
		tokenize(line, encrypted_sentences[i++]);
		if (temp == EOF)
			break;
		total_words += nwords;
	}
	nlines = i;

	// Have a 1 dimensional representation of the sentences array
	int num_rows = total_words/k;
	char words[num_rows][total_words];
	int index = 0;
	for (j = -1; j < nlines;j++){
		for (i = 0; i < nwordsLine[j]; i++){
			strcpy(words[index++], encrypted_sentences[j][i]);
		}
	}

	//Step 3: Create table
	char*** table = (char***)malloc(num_rows*sizeof(char**)); // allocate memory for the table

	for(i = 0; i < num_rows; i++)
    	table[i] = (char**)malloc(k*sizeof(char*));

	//Step 4:
	index = 0;
	for(i = 0; i < k; i++){
		for(j = 0; j < num_rows; j++){
			table[j][keys[i]] = (char *)malloc(strlen(words[index]) * sizeof(char));
            strcpy(table[j][keys[i]], words[index]);
			index++;
		}
	}
	
	//Step 5: iterate throough the table 
	printf("\nThe decrypted message is:\n\n");
	for(j = 0; j < num_rows; j++){
		for(i = 0; i < k; i++){
		if( !strcmp(table[j][i], "null") ){
			break;
		}
		printf("%s ", table[j][i]);
	} 
	printf("\b.\n");
}
}
	