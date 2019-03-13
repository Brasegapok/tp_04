#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "hash.h"  // uncomment when "hash.h" is ready to be used

#define STR_SIZE 80
#define DEFAULT_DIREC_SIZE 100

typedef struct{
    char Name[STR_SIZE];
    char Class[STR_SIZE];
		int  Phone;
} Students;

Students directory[DEFAULT_DIREC_SIZE];

int new_tab(){
	/*
	size_t myarray_size = 1000;
   mystruct* myarray = malloc(myarray_size * sizeof(mystruct));

   myarray_size += 1000;
   mystruct* myrealloced_array = realloc(myarray, myarray_size * sizeof(mystruct));
   if (myrealloced_array) {
     myarray = myrealloced_array;
   } else {
     // deal with realloc failing because memory could not be allocated.
   }
   */
}


int main(int argc,char** argv) {
	// !!! DO NOT MODIFY !!!
	FILE* input = stdin;
	if (argc > 1) {
		char *filename = argv[1];
		input = fopen(filename, "r+");
		if (!input) {
			fprintf(stderr, "File not found \"%s\"!", filename);
			return EXIT_FAILURE;
		}
	}

	int choice;
	do {
		// !!! DO NOT MODIFY this output!!!
		fprintf(stderr,"\nSELECTION\n\n");
		fprintf(stderr,"0: quit\n");
		fprintf(stderr,"1: load file\n");
		fprintf(stderr,"2: save to file\n");
		fprintf(stderr,"3: insert a person (name;class;phone)\n");
		fprintf(stderr,"4: search by name\n");
		fprintf(stderr,"5: search by phone#\n");
		fprintf(stderr,"6: delete by name\n");
		fprintf(stderr,"7: delete by phone#\n");
		fprintf(stderr,"8: display dictionary content\n");
		fprintf(stderr,"9: how full is the directory?\n");
		fprintf(stderr,"Entrez votre choix:\n");

		char name[STR_SIZE];   
		char class[4];
		int phone;

		char filename[STR_SIZE];
		char line[STR_SIZE];

		fscanf(input, "%d:", &choice);  // !!! DO NOT MODIFY !!!

		switch(choice) {
			case 0: // Quit
				// Keyboard input <0:>
				break;

			case 1: // Load a file
				// Keyboard input <1: filename>
				// (Example) 1: students.txt
				fscanf(input,"%s",filename);  // !!! DO NOT MODIFY !!!
				// Call here your function that loads the file <filename>
				
				// Display <number of lines read>
				printf("101\n");   // !!! Respect the output format !!!
				break;

			case 2: // Save to a file
				// Keyboard input <2: filename>
				// (Example) 2: output.txt
				fscanf(input,"%s",filename);  // !!! DO NOT MODIFY !!!
				// Call here your function that saves the file <filename>


				// Output <number of written lines>
				printf("103\n");   // !!! Respect the output format !!!
				break;

			case 3: // Insert a person
				// Keyboard input <3: name;class;phone>
			    // (Example) 3: Michel Deriaz;IT4;9234567
				fgets(line,STR_SIZE,input);                    // !!! DO NOT MODIFY !!!
				int char_count;                                // !!! DO NOT MODIFY !!!
				char* ptr = line;                              // !!! DO NOT MODIFY !!!
				sscanf(ptr," %80[^;]%n", name, &char_count);   // !!! DO NOT MODIFY !!!
				ptr += char_count+1;                           // !!! DO NOT MODIFY !!!
				sscanf(ptr,"%80[^;]%n", class, &char_count);  // !!! DO NOT MODIFY !!!
				ptr += char_count+1;                          
				sscanf(ptr,"%d",&phone);           


				// Call here your function to insert name, class, phone in directory.
				
				/*----------*/
				// No on-screen output

				break;

			case 4: // Search by name
				// Keyboard input <4: name>
				// (Example) 4: Mathieu Landru
				fgets(line,STR_SIZE, input);    // !!! DO NOT MODIFY !!!
				sscanf(line," %80[^\n]", name);  // !!! DO NOT MODIFY !!!

				// Call your search function <name> in the directory

				/*----------*/
				// Output <name;class;phone>

				printf("Mathieu Landru;IT1;3458127\n");  // !!! Respect the output format !!! 
				//printf("-1\n"); // print -1 if not found
				break;

			case 5: // Search by phone
				// Keybaord input <5: phone>
				// (Example) 5: 3458127
				fscanf(input,"%d", &phone);   // !!! DO NOT MODIFY !!!
				// Call your fonction to search by phone number
				// Output:
				//               <number of elements>
				//               <name1;class1;phone>
				//               <name2;class2;phone>
				//               <name3;clase3;phone>
				//               ....

				//
				printf("4\n"); // number of entries with this phone number
				printf("Michel Joguin;MT1;3458127\n");  // !!! Respect the output format !!!
				printf("Tom Martin;RT4;3458127\n");
				printf("Mathieu Beguin;IT3;3458127\n");
				printf("Mathieu Landru;IT1;3458127\n");
				break;

			case 6: // Delete by name
				// Keyboard input <6: name>
				// (Example) 6: Mathieu Landru
				fgets(line, STR_SIZE, input);    // !!! DO NOT MODIFY !!!
				sscanf(line," %80[^\n]", name);  // !!! DO NOT MODIFY !!!
				// Call your function to suppress <name> in the directory
				/*--------*/
				// No output
				break;

			case 7: // Delete by phone
				// Input keyboard <7: phone>
				// (Example) 7: 3458127
				fscanf(input,"%d", &phone);  // !!! DO NOT MODIFY !!! 
				// Call your function to suppress by phone

				/*-------*/

				// No output
				break;

			case 8: // Display the directory
				// Keyboard input <8:> */       
				// Call your function that prints the directory
				// Output
				//              <name1;class1;phone>
				//              <name2;class2;phone>
				//              <name3;class3;phone>
				//              ....
				 
				printf("Aliaga Belkis;TI1;3380586\n");   // !!! Respect the output format !!!
				printf("Beetschen Stephane;IN2;3380547\n");
				printf("Bejaoui Cyril;IN3;3380564\n");
				printf("Dragon Vincenzo;TI1;3380553\n");
				break;

			case 9: // How full is the directory?
				// Keyboard input <9:> */       
				// Call your function querying how full is the directory
				// Output <elements count> and <taille> from the hash table
				printf("87 151\n");   // !!! Respect the output format !!!
				break;     
		}
	} while (choice);

	fclose(input);

	return EXIT_SUCCESS;
}
