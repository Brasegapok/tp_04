#ifndef HASH_H
#define HASH_H

#define STR_SIZE 80
#define DEFAULT_DIREC_SIZE 100
#define SIZE_EXTENSION 20


//global variable used to get bigger directories, each bigger directory created will increment this variable by the value of SIZE_EXTENSION 
int directory_size_extension = SIZE_EXTENSION; 

typedef Key;
typedef enum{FULL,EMPTY,DELETED} State_Element;

typedef struct{
    char Name[STR_SIZE];
    char Class[STR_SIZE];
	int  Phone;
} Students;


typedef struct{
    Key key_element;
    State_Element state;
    Students Student;
} Directory ;


void check_directory_space(Directory* tab,int size);
void search_student_by_name(char* name,Directory *tab,int size);
void search_student_by_phone(int phone,Directory *tab,int size);
void insert_student(char *name, char *class, int phone, Directory *tab, int size);
void delete_student_by_name(char* name,Directory *tab,int size);
void delete_student_by_phone(int phone,Directory *tab,int size);
void print_directory(Directory *tab,int size);
#endif /*HASH_H*/