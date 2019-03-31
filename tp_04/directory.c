/**
 *	PROJECT NAME	: tp_04 -> Annuaire	
 *	PROJECT UTILITY	: shows a list of students and allows searching for a specific one
 * 	FILE NAME		: directory.c
 * 	FILE UTILITY	: the main file, allows user interaction to create and build a directory of students
 * 	AUTHOR			: Mami Francesco
 * 	CREATION DATE	: 11.03.2019
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"  
#include "readfile.h"

int main(int argc,char** argv) {
	Phone_directory* phone_directory = NULL;
	Directory* directory;
	int size = 0;
	int file_size;
	char* file_content;
	// !!! DO NOT MODIFY !!!
	FILE* input = stdin;
	if (argc > 1) {
		char *filename = argv[1];
		input = fopen(filename, "r+");
		if (!input) {
			fprintf(stderr, "File not found \"%s\"!", filename);
			return EXIT_FAILURE;
		}
		
		file_size = 0;
		file_content = read_file(filename,&file_size);

		//here is the main directory with it's size
		directory = new_directory(file_content,phone_directory,&file_size);
		size = file_size;
		free(file_content);
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
		char class[STR_SIZE];
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
				file_size = 0;
				file_content = read_file(filename,&file_size);
				
				//removes the previous values of the directory
				free(directory);

				//initialises the new value of the directory
				directory = new_directory(file_content,phone_directory,&file_size);
				size = file_size;
				
				// Display <number of lines read>
				printf("%d\n",file_size);   // !!! Respect the output format !!!
				free(file_content);
				break;

			case 2: // Save to a file
				// Keyboard input <2: filename>
				// (Example) 2: output.txt
				fscanf(input,"%s",filename);  // !!! DO NOT MODIFY !!!
				file_size = 0;
				// Call here your function that saves the file <filename>
				file_content = prepare_directory_file(directory,size,&file_size);
				write_file(filename,file_content,file_size);
				free(file_content);
				// Output <number of written lines>
				printf("%d\n",file_size);   // !!! Respect the output format !!!
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
				
				insert_new_student(name,class,phone,directory,phone_directory,&size);
				// No on-screen output

				break;

			case 4: // Search by name
				// Keyboard input <4: name>
				// (Example) 4: Mathieu Landru
				fgets(line,STR_SIZE, input);    // !!! DO NOT MODIFY !!!
				sscanf(line," %80[^\n]", name);  // !!! DO NOT MODIFY !!!

				// Call your search function <name> in the directory

				search_student_by_name(name,directory,size);
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
				search_student_by_phone(phone,directory,phone_directory,size);
				/*
				printf("4\n"); // number of entries with this phone number
				printf("Michel Joguin;MT1;3458127\n");  // !!! Respect the output format !!!
				printf("Tom Martin;RT4;3458127\n");
				printf("Mathieu Beguin;IT3;3458127\n");
				printf("Mathieu Landru;IT1;3458127\n");
				*/
				break;

			case 6: // Delete by name
				// Keyboard input <6: name>
				// (Example) 6: Mathieu Landru
				fgets(line, STR_SIZE, input);    // !!! DO NOT MODIFY !!!
				sscanf(line," %80[^\n]", name);  // !!! DO NOT MODIFY !!!
				// Call your function to suppress <name> in the directory
				delete_student_by_name(name,directory,phone_directory,size);
				// No output
				break;

			case 7: // Delete by phone
				// Input keyboard <7: phone>
				// (Example) 7: 3458127
				fscanf(input,"%d", &phone);  // !!! DO NOT MODIFY !!! 
				// Call your function to suppress by phone

				delete_student_by_phone(phone, directory,phone_directory,size);

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
				print_directory(directory,size);
				 /*
				printf("Aliaga Belkis;TI1;3380586\n");   // !!! Respect the output format !!!
				printf("Beetschen Stephane;IN2;3380547\n");
				printf("Bejaoui Cyril;IN3;3380564\n");
				printf("Dragon Vincenzo;TI1;3380553\n");
				*/
				break;

			case 9:
				{
					// How full is the directory?
					// Keyboard input <9:> */       
					// Call your function querying how full is the directory
					// Output <elements count> and <taille> from the hash table
					int directory_space = 0;
					//check_directory_space(directory,size);
					printf("%d %d",directory_space,size);
					//printf("87 151\n");   // !!! Respect the output format !!!
					break;
				}     
		}
	} while (choice);

	fclose(input);
	free(phone_directory);
	free(directory);

	return EXIT_SUCCESS;
}
