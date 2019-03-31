/**
 *	PROJECT NAME	: tp_04 -> Annuaire	
 *	PROJECT UTILITY	: shows a list of students and allows searching for a specific one
 * 	FILE NAME		: hash.h
 * 	FILE UTILITY	: contains each function to access through other files related to hash.c
 * 	AUTHOR			: Mami Francesco
 * 	CREATION DATE	: 11.03.2019
 */
#ifndef HASH_H
#define HASH_H

#define MAX_FIELDS 3
#define STR_SIZE 80
//#define DEFAULT_DIREC_SIZE 100
#define SIZE_EXTENSION 100
#define PERCENTAGE_BEFORE_EXTENSION 20.0

typedef int Key;
typedef enum{FULL,EMPTY,DELETED} State_Element;

typedef struct{
    char Name[STR_SIZE];
    char Class[STR_SIZE];
	int  Phone;
} Students;

typedef struct{
    Key Key_name;
    State_Element State;
    Students Student;
} Directory ;

typedef struct{
    Key Key_phone;
    int Index_directory;
}Phone_directory;



Directory* new_directory(char* file_content,Phone_directory* phone_tab,int* size);
char* prepare_directory_file(Directory* tab,int size,int *file_size);

int check_directory_space(Directory* tab,int size);
void search_student_by_name(char* name,Directory* tab,int size);
void search_student_by_phone(int student_phone,Directory* tab,Phone_directory* phone_tab,int size);
void insert_new_student(char* student_name, char* student_class, int student_phone, Directory* tab, Phone_directory* phone_tab, int* size);
void delete_student_by_name(char* name,Directory* tab,Phone_directory* phone_tab,int size);
void delete_student_by_phone(int phone,Directory* tab,Phone_directory* phone_tab,int size);
int print_directory(Directory *tab,int size);


#endif /*HASH_H*/
