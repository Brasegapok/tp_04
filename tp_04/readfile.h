/**
 *	PROJECT NAME	: tp_04 -> Annuaire	
 *	PROJECT UTILITY	: shows a list of students and allows searching for a specific one
 * 	FILE NAME		: readfile.h
 * 	FILE UTILITY	: contains each function to access through other files related to readfile.c
 * 	AUTHOR			: Mami Francesco
 * 	CREATION DATE	: 11.03.2019
 */

#ifndef READFILE_H
#define READFILE_H

#define FILE_LENGTH 256
#define NB_FIELDS 3


char* read_file(char* filename,int* file_size);
int write_file(char* filename,char* file_content,int size);

#endif /* READFILE_H */