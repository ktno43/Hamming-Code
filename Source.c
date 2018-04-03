/*****************************************
Kyle Nguyen
COMP 222
Spring 2018
Prof. Robert McIlhenny
T/R 3:30 P.M - 4:45 P.M

Assignment #3: Hamming Code
Source.c

Version 3.0

The program works as expected and follows
program specifications.  Given a maximum
length it creates a dynamic array of
characters for the hamming string.
Depending on the parity (even/odd) it
will check the hamming string for any
errors.  If an error is found the error
bit will be displayed as well as the
corrected hamming code.  If there is no
error nothing will be done.
*****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function Prototypes
void displayMenu(void);
void setParams(void);
void calcHamming(void);
void freeStuff(void);

// Global Variables
int g_nMaxLen;
int g_bParityOdd;

// Hamming string as a dynamic array of characters
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

		// If parity is valid, continue
		if (g_bParityOdd == 1 || g_bParityOdd == 0)
		{
			inputFlag = 0;
		}

		else // Else invalid number
			printf("Invalid input. \n\n");
	}

	freeStuff(); // Be sure to free before allocating

	// Allocate memory for hamming string based on maximum length and size of char
	g_sHammingCode = (char*)malloc(g_nMaxLen * sizeof(char));
}

void calcHamming()
{
	int nErrorBit = 0;
	int nHammingCodeLen = 0;

	// Input string for hamming code
	printf("\nEnter the Hamming code: ");
	scanf("%s", g_sHammingCode);

	// Determine actual Hamming code length & number of parity bits 
	nHammingCodeLen = strlen(g_sHammingCode);

	// OUTER LOOP: for each parity bit in the Hamming code
	int i = 0;
	for (i = 1; i < nHammingCodeLen; i *= 2) // Parity Bit
	{
		int nParityBit = g_bParityOdd;

		// MIDDLE LOOP: for each starting bit of a sequence 
		int j = 0; // i = 1, 2, 4, 8, 16
		for (j = i; j <= nHammingCodeLen; j = j + (2 * i)) 
		{
			// INNER LOOP: for each bit to be checked, check value and update parity information for current parity bit
			int k = 0;
			for (k = j; k <= nHammingCodeLen && (k < (i + j)); k++) 
				nParityBit ^= (g_sHammingCode[nHammingCodeLen - k] - '0'); // XOR with parity bit
		}
		// Update parity checking by including result for parity bit checked in total
		nErrorBit += nParityBit * i; // Include weight
	}

	// Report error in hamming code based on result from parity bits or report no error if none 

	// If no error
	if (nErrorBit == 0)
		printf("There is no bit error\n\n");

	else // Else correct hamming code by flipping error bit 
	{
		printf("%s%d", "There is an error in bit:  ", nErrorBit); // Display error bit

		g_sHammingCode[nHammingCodeLen - nErrorBit] = ('1' + '0') - g_sHammingCode[nHammingCodeLen - nErrorBit]; // Perform the correction

		printf("\n%s%s\n\n", "The corrected Hamming code is:  ", g_sHammingCode); // Display the corrected hamming code
	}
	return;
}

void freeStuff()
{
	if (g_sHammingCode != NULL) // When the string is not NULL
	{
		free(g_sHammingCode); // Free up memory
		g_sHammingCode = NULL; // Reassign to NULL
	}
}
