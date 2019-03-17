/**
 *	PROJECT NAME	: tp_04 -> Annuaire	
 *	PROJECT UTILITY	: shows a list of students and allows searching for a specific one
 * 	FILE NAME		: readfile.h
 * 	FILE UTILITY	: contains each function to access through other files
 * 	AUTHOR			: Mami Francesco
 * 	CREATION DATE	: 11.03.2019
 */


#ifndef READFILE_H
#define READFILE_H

#define LENGTH 256

int read_file(filename);
int write_file(char*tab_name,char*tab_class,int*tab_class,int size);

#endif /* READFILE_H */