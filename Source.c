"#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void displayMenu(void);
void setParams(void);
void calcHamming(void);
void freeStuff(void);

/* declare global vars */
int g_nMaxLen;
int g_bParityOdd;

/* define hamming string as a dynamic array of characters */
char* g_sHammingCode = NULL;

int main()
{
	displayMenu(); // Function call to Display Menu of Options

	printf("\n\nProgram Ending . . .\n");  //Program Ending
	printf("Press ENTER to close --->  ");
	getchar();
	getchar();

	return EXIT_SUCCESS;
}

void displayMenu()
{
	char cInput = '\0'; // Variable for input data
						/* prompt for maximum hamming code length and for even/odd parity (evenodd)*/


	while (cInput != 'c')
	{
		printf("Hamming Code Error detection/correction:\n");
		printf("----------------------------------------\n");
		printf("a) Enter parameters\n");
		printf("b) Check Hamming code\n");
		printf("c) Quit\n\n");

		printf("Enter selection:  ");
		scanf(" %c", &cInput); // Get the character pressed from user

		switch (cInput)
		{
			case 'a':
				setParams(); // Function call to assign values to parameters
				break;

			case 'b':
				calcHamming(); // Function call to calculate hamming code
				break;

			case 'c':
				freeStuff(); // Function call to free dynamically allocated memory
				return;

			default:
				printf("Invalid input. \n"); // Invalid character read
		}
		printf("\n\n");
		getchar();
	}
	return;
}

void setParams()
{
	int inputFlag = 1;
	// Input value for maximum length
	printf("\nEnter the maximum length: ");
	scanf("%d", &g_nMaxLen);

	while (inputFlag == 1)
	{
		// Is parity even or odd
		printf("Enter the parity (0 = even, 1 = odd):  ");
		scanf("%d", &g_bParityOdd);

		if (g_bParityOdd == 1 || g_bParityOdd == 0)
		{
			inputFlag = 0;
		}

		else
			printf("Invalid input. \n\n");
	}

	freeStuff();

	/* allocate memory for hamming string based on maximum length and size of a character element*/
	g_sHammingCode = (char*)malloc(g_nMaxLen * sizeof(char));
}

void calcHamming()
{
	/* declare local vars */
	int nErrorBit = 0;
	int nHammingCodeLen = 0;

	/* prompt for hamming code as a "string"*/
	// Input value for hamming code
	printf("\nEnter the Hamming code: ");
	scanf("%s", g_sHammingCode);

	/* Determine actual Hamming code length & number of parity bits */
	nHammingCodeLen = strlen(g_sHammingCode);

	// int nNumParity = ceil(log(nHammingCodeLen)/log(2));
	/* OUTER LOOP: for each parity bit in the Hamming code*/
	int i = 0;
	for (i = 1; i < nHammingCodeLen; i *= 2) // Parity Bit
	{ /* BEGIN OF OUTER LOOP */

	  /* initialize appropriate local variables */
		int nParityBit = g_bParityOdd;
		/* MIDDLE LOOP: for each starting bit of a sequence */
		int j = 0; // i = 1, 2, 4, 8, 16
		for (j = i; j <= nHammingCodeLen; j = j + (2 * i))// i=1 j->2, i=2 j-> 4, i=4 j -> 12, i=8-> j->16
		{
			/* INNER LOOP: for each bit to be checked, check value and update parity information for current parity bit*/
			int k = 0;
			for (k = j; k <= nHammingCodeLen && (k < (i + j)); k++) // && something with j
				nParityBit ^= (g_sHammingCode[nHammingCodeLen - k] - '0');
		}
		/* update parity checking by including result for parity bit checked in total */
		nErrorBit += nParityBit * i; // Include weight
	}
	/* END OF OUTER LOOP

	/* report error in hamming code based on result from parity bits or report no error if none */

	/* correct hamming code by flipping error bit (if necessary)*/
	if (nErrorBit == 0)
		printf("There is no bit error\n\n");

	else
	{
		printf("%s%d", "There is an error in bit:  ", nErrorBit);
		g_sHammingCode[nHammingCodeLen - nErrorBit] = ('1' + '0') - g_sHammingCode[nHammingCodeLen - nErrorBit];
		printf("\n%s%s\n\n", "The corrected Hamming code is:  ", g_sHammingCode);
	}
	return;
}

void freeStuff()
{
	if (g_sHammingCode != NULL)
	{
		free(g_sHammingCode);
		g_sHammingCode = NULL;
	}
}
