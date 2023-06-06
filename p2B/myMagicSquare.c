///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2022, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////
// add your own File Header information here (as provided in p2A or Commenting guide
////////////////////////////////////////////////////////////////////////////////
// Main File:        (myMagicSquare.c)
// This File:        (myMagicSquare.c)
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Lecture 01? Spring 2023
// Instructor:       deppeler
// 
// Author:           (Mohammud Ibrahim)
// Email:            (Mmibrahim2@wisc.edu)
// CS Login:         (mohammud)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
	int size; 
	printf("Enter magic square's size (odd integer >= 3)\n");
	scanf("%d", &size);
	// check if odd or even
	if (size % 2 == 0) {
		printf("Magic square size must be odd.\n");
		exit(1);
	}
	// check if size >= 3
	if (size <= 2) {
		printf("Magic square size must be odd.\n");
	    exit(1);
	}
	// return valid number
	//printf("DEBRUHHHdd")
    return size;   
} 
   
/* TODO:
 * Makes a magic square of size n using the 
 * Siamese magic square algorithm or alternate from assignment 
 * or another valid alorithm that produces a magic square.
 *
 * n is the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 */
MagicSquare *generateMagicSquare(int n) {
	// allocate memory
	MagicSquare *ms = malloc(sizeof(MagicSquare));
	// check allocation
	if (ms == NULL) {
		printf("ERROR: Memory was not allocated\n");
		exit(1);
	}
	//set size
	ms -> size = n;
	// allocate
	ms -> magic_square = malloc(sizeof(int*) * n);
	// loop through square
	for(int i = 0; i < n; i++ ) {
		*(ms -> magic_square + i) = malloc(sizeof(int) * n );
		if(*(ms -> magic_square + i) == NULL) {
			printf("ERROR: Memory not allocated\n");
			exit(1);
		}
	}
	// Siamese magic square algorithm
	// initialize all elements in magic square to 0
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			*(*(ms -> magic_square + i) + j) = 0;
		}
	}

	// initialize variables
	int i = 0; //row
	int j = n / 2; //col
	int prev_i = 0;
	int prev_j = 0;
		
	// fill values and check bounds
	for (int k = 1; k <= n * n; k++) {
		if (i < 0) {
			i = n - 1;
		}
	
		if (j > n - 1) {
			j = 0;
		}
		// check if filled
		if (*(*(ms->magic_square + i) + j) != 0) {
			i = prev_i;
			j = prev_j;
			i++;
		}
		// fill in values
		*(*(ms->magic_square + i) + j) = k;
		prev_i = i;
		prev_j = j;
		// next element
		i--;
		j++;
	}
	// returns a valid MagicSquare pointer
	return ms;
}
/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
	// write to file
	FILE *fp = fopen(filename, "w");
	//check file
	if (fp == NULL) {
		printf("ERROR: Something is wrong with the file");
		exit(1);
	}

	fprintf(fp, "%d\n", magic_square -> size);
	for (int i = 0; i < magic_square -> size; i++) {
		for (int j = 0; j < magic_square -> size - 1; j++) {
			fprintf(fp,"%d,", *(*(magic_square -> magic_square+i)+j));
			}	
		fprintf(fp,"%d\n", *(*(magic_square -> magic_square + i) + magic_square -> size - 1));	
		}
	//close file			
	 if (fclose(fp) != 0) {
		printf("Close file");
		exit(1);
	}
}


/* TODO:
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 * 
 * Add description of required CLAs here
 */
int main(int argc, char **argv) {
    // TODO: Check input arguments to get output filename
	if (argc != 2) {
		printf("ERROR: Wrong number of command line arguments");
		exit(1);
	}
    // TODO: Get magic square's size from user
	int size = getSize();
    // TODO: Generate the magic square by correctly interpreting 
    //       the algorithm(s) in the write-up or by writing or your own.  
    //       You must confirm that your program produces a 
    //       Magic Sqare as described in the linked Wikipedia page.
	MagicSquare *square = generateMagicSquare(size); 
    // TODO: Output the magic square
	fileOutputMagicSquare(square, *(argv+1));
	// Free
	for (int i = 0; i < size; i++) {
		free(*(square -> magic_square+i));
		}
		free(square -> magic_square);
		square = NULL;
    return 0;
} 

// S23

