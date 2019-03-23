/**
 *	PROJECT NAME	: tp_04 -> Annuaire	
 *	PROJECT UTILITY	: shows a list of students and allows searching for a specific one
 * 	FILE NAME		: readfile.c
 * 	FILE UTILITY	: Reads a text file under a specific format
 * 	AUTHOR			: Mami Francesco
 * 	CREATION DATE	: 11.03.2019
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include "readfile.h"


int write_file(char*filename,char* file_content,int size)
{
	// Open file for reading
	fp = fopen(filename,"w");
	for(int i = 0; i < size; i++)
	{
		fprintf (fp,"%s\n",file_content[i]);
	}
	fclose();
	
}

//reads a file and returns a table
char* read_file(char *filename, int* file_size)
{	
	char* file_content = malloc(FILE_LENGTH* sizeof(char));
	// Open file for reading
	fp = fopen(filename,"r");
	if (!fp) {
		fprintf(stderr,"file not found: %s\n", filename);
		return EXIT_FAILURE;
	}
	int line_cnt = 0;
	//reads the whole file while placing each line into a 
	while ((fgets(line, FILE_LENGTH, fp)) != NULL ) {		
		file_content[line_cnt] = line;
		line_cnt++;
	}
	// Close the file
	fclose(fp); 
	file_size = line_cnt;
	return file_content;
}



int main(int argc,char** argv) {
	char line[LENGTH];
	FILE *fp;

	// First argument is the file to read
	if (argc != 2) {
		fprintf(stderr,"usage: %s <filename>\n", basename(argv[0]));
		return EXIT_FAILURE;
	}

	// Open file for reading
	fp = fopen(argv[1],"r");
	if (!fp) {
		fprintf(stderr,"file not found: %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	// Read the #lines
	int line_cnt = 0;
	while ((fgets(line,LENGTH,fp)) != NULL ) line_cnt++;
	rewind(fp);

	// Read and print each line in the file
	char sep[] = ";";
	int nb_fields = 3;
	line_cnt = 1;

	while ((fgets(line, LENGTH, fp)) != NULL ) {
		char *token;
		// Point to first token
		token = strtok(line, sep);
		// Iterate through other tokens and store them in fields
		int cnt = 0;
		char *fields[nb_fields];

		while (token) {
			if (cnt >= nb_fields) {
				fprintf(stderr, "line %d has too many fields!\n", line_cnt);
				continue;
			}
			fields[cnt] = token;
			token = strtok(NULL, sep);
			cnt++;
		}

		printf("%s / %s / %d\n", fields[0], fields[1], atoi(fields[2]));
		line_cnt++;
	}

	// Close the file
	fclose(fp); 
	return EXIT_SUCCESS;
}

