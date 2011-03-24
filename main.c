#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAXPOOL		10000
#define MAXWORDLENGTH	10000
#define MAXSHUFFLE	MAXPOOL*1000

float probs[] = { 
	0.0651, // A
	0.0257, // B
	0.0284, // C
	0.0541, // D
	0.1669, // E
	0.0204, // F
	0.0365, // G
	0.0406, // H
	0.0782, // I
	0.0019, // J
	0.0188, // K
	0.0283, // L
	0.0301, // M
	0.0992, // N
	0.0229, // O
	0.0094, // P
	0.0007, // Q
	0.0654, // R
	0.0678, // S
	0.0674, // T
	0.0370, // U
	0.0107, // V
	0.0140, // W
	0.0002, // X
	0.0003, // Y
	0.0100  // Z
};

//char charPool[MAXPOOL];
char *charPool;

int main(int argc, char** arg)
{
	if(argc != 2)
	{	
		printf("USAGE: germanmonkey <wordlength>\n");
		return 1;
	}
	int wordlength = atoi(arg[1]);
	if(wordlength <= 0 || wordlength > MAXWORDLENGTH)
	{
		printf("<wordlength> must be between 1 and %d\n", MAXWORDLENGTH);
		return 1;
	}

	srand(time(NULL)); 
	
	printf("\nTrying to generate german words of length %d\n", wordlength);
	printf("Filling char Pool...\n");

	int probSize = sizeof(probs)/sizeof(float);
	int poolSize = 0;
	int c;
	int i = 0, k = 0;

	// Calculating size of Poolarray, since the sum of all probabilities
	// maybe isn't 1!
	for (c = 0; c < probSize; c++) {
		poolSize += MAXPOOL*probs[c];
	}
	charPool = (char*)malloc(sizeof(char)*poolSize);

	for(c = 0; c < probSize; c++)
	{
		int charReps = probs[c] * MAXPOOL;
		//printf("%c, max = %d\n", c + 97, charReps);
		for(i = 0; i < charReps; i++)
		{
			charPool[k] = c + 97;
			k++;
		}
	}

	/*
	printf("Shuffling char Pool...\n");

	for(i = 0; i < MAXSHUFFLE; i++)
	{
		int i1, i2;
		i1 = rand() % MAXPOOL;
		i2 = rand() % MAXPOOL;
		char temp = charPool[i2];
		charPool[i2] = charPool[i1];
		charPool[i1] = temp;
	}
	*/

	/*
	printf("Printing char Pool...\n");
	for(i = 0; i < MAXPOOL; i++)
		printf("%c", charPool[i]);
	printf("\n");
*/

	printf("Creating random word...\n");
	char word[wordlength+1];
	for(i = 0; i < wordlength; i++)
	{
		k = rand() % MAXPOOL;
		c = charPool[k];
		//printf("%c ", c);
		word[i] = c;
	}
	word[wordlength] = 0;

	printf("\nWort = %s\n", word);

	printf("Calculating effective Probability of letters...\n");
	printf("Wordlength = %d\n", wordlength);

	int	occurance[26];
	float 	effProb[26];
	float 	probDiff[26];
	float	relDiff[26];
	for(c = 0; c < 26; c++)
	{
		k = 0;
		for(i = 0; i < wordlength; i++)
			if(word[i] == c+97)
				k++;
		occurance[c] = k;
		effProb[c] = (float)k / wordlength;
		probDiff[c] = probs[c] - effProb[c];
		relDiff[c] = probDiff[c] / probs[c];
		printf("%c:  k = %d \t Prob = %f \t diff = %f \t relDiff = %.2f%%\n", 
				c+97, occurance[c], effProb[c], probDiff[c], fabs(relDiff[c])*100);
	}

	printf("\n%s\n\n",word);


	free(charPool);
	return 0;
}

