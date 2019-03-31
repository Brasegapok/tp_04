/**
 *	PROJECT NAME	: tp_04 -> Annuaire	
 *	PROJECT UTILITY	: shows a list of students and allows searching for a specific one
 * 	FILE NAME		: hash.c
 * 	FILE UTILITY	: contains all the functions used by directory.c to store and modify a directory
 * 	AUTHOR			: Mami Francesco
 * 	CREATION DATE	: 11.03.2019
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"


Students add_student(char* student_name, char* student_class, int student_phone);
Directory* extend_previous_directory(Directory* old_tab, int* size);
Phone_directory* extend_previous_phone_directory(Phone_directory* old_phone_tab, int* size);



int check_prime_number(int value)
{
	if(value != 0 && value != 1)
	{
		for (int i = 0; i < value-1; i++)
		{
			if(value % i == 0){
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
//finds a prime number lower than the one in parameter
int find_lower_prime_number(int value)
{
	int prime_number;
	for (int i = 0; i < value; i++)
	{
		prime_number = value -1;
		if(check_prime_number(prime_number) && prime_number != 1)
		{
			return prime_number;
		}
	}
	//couldn't find prime number
	return -1;
}

//finds a size which is a prime number
int find_tab_size_prime_number(int size){
	int previous_size = 0;
	int new_size = size;
	do
	{
		new_size += SIZE_EXTENSION;
		previous_size = new_size;
		new_size = find_lower_prime_number(new_size);
		//makes sure the new size isn't smaller or equal to the actual size
		if(new_size <= size)
		{
			new_size = previous_size;
		}
	}while(!check_prime_number(new_size));
	return new_size;
}

int print_directory(Directory* tab, int size) {
	int nb_students = 0;
	for (int i = 0; i < size; i++)
	{
		//makes sure that the student to add exists
		if (tab[nb_students].State == FULL)
		{
			char* student_name = tab[nb_students].Student.Name;
			char* student_class = tab[nb_students].Student.Class;
			int  student_phone = tab[nb_students].Student.Phone;
			//in case the new student does not have a phone number:
			if (student_phone == -1)
			{
				printf("%s;%s; \n", student_name, student_class);
			}
			printf("%s;%s;%d\n", student_name, student_class, student_phone);
		}
		//prevents out of bounds error
		nb_students++;
	}
	return nb_students;
}

char* prepare_directory_file(Directory* tab, int size, int* file_size) {
	char* file_content = malloc(size * sizeof(Directory));
	char * line = "";
	char sep[] = ";";
	for (int i = 0; i < size; i++)
	{
		//makes sure the student exists on the directory before adding it into the file
		if (tab[i].State == FULL)
		{
			file_size++;
			//prepares the next line for the file content
			line = tab[i].Student.Name;
			line = strcat(line, sep);
			line = strcat(line, tab[i].Student.Class);
			line = strcat(line, sep);
			if (tab[i].Student.Phone != -1)
			{
				char student_phone[STR_SIZE] = "";
				sprintf(student_phone, "%d", tab[i].Student.Phone);
				line = strcat(line, student_phone);
			}
			file_content[i] = *line;
		}
	}
	return file_content;
}


int check_directory_space(Directory *tab, int size) {
	int empty_slots = 0;
	while (tab[empty_slots].State != EMPTY)
	{
		empty_slots++;
		//prevents the program from crashing in case the directory is full
		if (empty_slots >= size) {
			empty_slots = size;
			break;
		};
	}
	int directory_space = size - empty_slots;
	return directory_space;
}

int check_full_directory(Directory* tab, int size) {
	for (int i = 0; i < size; i++)
	{
		if (tab[i].State == EMPTY || tab[i].State == DELETED)
		{
			return 0;
		}
	}
	return 1;
}

int check_almost_full_directory(Directory*tab,int size)
{
	int directory_space = check_directory_space(tab,size);
	double percentage = (directory_space/size)*100;
	if(percentage <= PERCENTAGE_BEFORE_EXTENSION)
	{
		return 1;
	}
	return 0;
}


Key get_key_name(char *value, int multiplier)
{
	Key key_val = 0;
	int i = 0;
	while (value[i] != '\0')
	{
		key_val += (int)value[i] * multiplier;
		i++;
	}
	return key_val;
}
Key get_key_phone(int value, int multiplier)
{
	return value * multiplier;
}


int hash_1(Key Key_value, int size)
{
	return (Key_value) % size;
}

int hash_2(Key Key_value, int size, int prime_number)
{
	if(size > prime_number)
	{
		return prime_number-(Key_value%prime_number);
	}
	return -1;
}

int double_hash(Key Key_value,int size,int cnt,int prime_number)
{
	//checks if the table has a size equal to a prime number
	if(check_prime_number(size))
	{
		int hash_1_value = hash_1(Key_value,size);
		int hash_2_value = hash_2(Key_value,size,prime_number);
		
		if(hash_1_value != -1 && hash_2_value != -1){
			return (hash_1_value + cnt * hash_2_value) % size;
		}
	}
	return -1;
}
int linear_jump(Key Key_value,int size, int jump_value)
{
	int index = (Key_value + jump_value) % size;
	return index;
}

int search_insert_phone(Key key_phone, Phone_directory* phone_tab, int size,int jump_value)
{
	int cnt = 0;
	int index_hash = hash_1(key_phone, size);
	while (phone_tab[index_hash].Key_phone == key_phone)
	{	
		//prevents an out of bounds error
		if (cnt > size)
			return -2;
		index_hash = linear_jump(index_hash, size, jump_value);
		cnt++;
	}
	return index_hash;
}

int search_insert_name(Key key_name, Directory* tab, int size)
{
	int prime_number= find_lower_prime_number(size);
	if(prime_number == -1)
	{
		return -3;
	}
	int cnt = 0;
	int index_hash = hash_1(key_name, size);
	while (tab[index_hash].State == FULL)
	{	
		//prevents an out of bounds error
		if (cnt > size)
			return -2;
		//prevents adding the same key
		if (tab[index_hash].Key_name == key_name)
			return -1;
		index_hash =  double_hash(index_hash, size, cnt,prime_number);
		if(index_hash == -1)
		{
			//reports a function error
			return -3;
		}
		cnt++;
	}
	return index_hash;
}

int search_by_key_name(Key key_name, Directory* tab, int size)
{
	int prime_number= find_lower_prime_number(size);
	if(prime_number == -1)
	{
		return -3;
	}
	int cnt = 0;
	int index_hash = hash_1(key_name, size);
	while (tab[index_hash].State != EMPTY)
	{
		//prevents an out of bounds error
		if (cnt > size){
			return -2;
		}
		//finds the same key values
		if (tab[index_hash].State == FULL && tab[index_hash].Key_name == key_name)
		{
			return index_hash;
		}
		index_hash =  double_hash(index_hash, size, cnt,prime_number);
		if(index_hash == -1)
		{
			//reports a function error
			return -3;
		}
		cnt++;
	}
	//key value not found on the directory
	return -1;
}

int* search_by_key_phone(Key key_phone,int* nb_students, Directory* tab,Phone_directory* phone_tab, int size, int jump_value)
{
	int* phone_list = malloc(size*sizeof(size));
	int cnt_students = 0;
	int cnt = 0;
	int index_hash = hash_1(key_phone, size);
	int index_directory = phone_tab[index_hash].Index_directory;
	while (tab[index_directory].State != EMPTY)
	{
		//prevents an out of bounds error
		if (cnt > size){
			break;
		}
		//makes sure that the key is available and the one searched
		if (tab[index_directory].State == FULL && phone_tab[index_hash].Key_phone == key_phone)
		{
			phone_list[cnt_students] = index_directory;
			cnt_students++;
		}
		index_hash = linear_jump(index_hash, size, jump_value);
		index_directory = phone_tab[index_hash].Index_directory;
		cnt++;
	}
	*nb_students = cnt_students++;
	return phone_list;
}
int search_by_key_phone_and_directory_index(Key key_phone,int student_index,Directory* tab,Phone_directory* phone_tab, int size, int jump_value){
	int cnt = 0;
	int index_hash = hash_1(key_phone, size);
	int index_directory = phone_tab[index_hash].Index_directory;
	while (tab[index_directory].State != EMPTY)
	{
		//prevents an out of bounds error
		if (cnt > size)
			return -2;
		//makes sure that the key is available and the one searched
		if (tab[index_directory].State == FULL && phone_tab[index_hash].Key_phone == key_phone)
		{
			if(index_directory == student_index)
			{
				return index_hash;
			}
		}
		index_hash = linear_jump(index_hash, size, jump_value);
		index_directory = phone_tab[index_hash].Index_directory;
		cnt++;
	}
	return -1;
}

int insert_by_key_phone(int student_phone,int student_index,Phone_directory* phone_tab,int size){	
	char string_student_phone[STR_SIZE];
	sprintf(string_student_phone, "%d", student_phone);
	Key key_phone = get_key_name(string_student_phone,size);
	int index_key_phone = search_insert_phone(key_phone,phone_tab,size,size);
	switch (index_key_phone)
	{
		case -3: //the function didn't work properly
			return -3;
			break;
		case -2: //directory is full
			return -2;
			break;
		default:
			phone_tab[index_key_phone].Index_directory = student_index;
			phone_tab[index_key_phone].Key_phone = key_phone;
			return index_key_phone;
			break;
	}
}

int insert_by_key_name(Students new_student, Key key_name, Directory* tab, int size)
{
	if (!check_full_directory(tab, size)) {
		int index = search_insert_name(key_name, tab, size);
		switch (index)
		{
		case -3: //the function didn't work properly
			return -3;
		case -2: //directory is full
			return -3; //directory shouldn't actually be full here, returns an function error
			break;
		case -1:
			return -1; // directory found the same key value (student) which is not allowed
			break;
		default:
			tab[index].State = FULL;
			tab[index].Key_name = key_name;
			tab[index].Student = new_student;
			break;
		}
		return index; //directory added the new student with it's key value
	}
	return -2;
}

void insert_new_student(char* student_name, char* student_class, int student_phone, Directory* tab,Phone_directory* phone_tab, int*size)
{
	Key key_value = get_key_name(student_name, *size);
	Students new_student = add_student(student_name, student_class, student_phone);
	if (check_almost_full_directory(tab, *size))
	{
		tab = extend_previous_directory(tab, size);
		phone_tab = extend_previous_phone_directory(phone_tab,size);
	}

	int confirmation_student = insert_by_key_name(new_student, key_value, tab, *size);
	//no on screen output as explained on directory.c, remove comments if needed
	switch (confirmation_student)
	{
	case -3:
		//printf("Error: the insertion didn't work properly");
		break;
	case -2:
		//printf("Error: the directory is full, cannot add more students");
		break;
	case -1:
		//printf("Error: Student to insert already exists");
		break;
	default: //the default case contains the index of the student which can be used elsewhere
		//printf("Student added successfully");
		break;
	}
	int index_student = confirmation_student;
	insert_by_key_phone(student_phone,index_student,phone_tab,*size);
}

void search_student_by_name(char* name, Directory* tab, int size)
{
	Key key_value = get_key_name(name, size);
	int index = search_by_key_name(key_value, tab, size);
	//printing as explained on directory.c, replace with the ones commented if needed
	switch (index)
	{
		case -3: 
		//printf("the function didn't work properly");
		printf("-1");
		break;
	case -2: 
		//printf("Couldn't find student with given name");
		printf("-1");
		break;
	case -1: 
		//printf("Couldn't find student with given name");
		printf("-1");
		break;
	default:
	{
		//char*student_name;
		//strcpy(student_name, tab[index].Student->Name);
		char* student_name = tab[index].Student.Name;
		char* student_class = tab[index].Student.Class;
		int   student_phone = tab[index].Student.Phone;
		printf("%s;%s;%d", student_name, student_class, student_phone);
	}
	break;
	}
}

void search_student_by_phone(int student_phone, Directory *tab,Phone_directory* phone_tab, int size)
{
	Key key_phone = get_key_phone(student_phone, size);
	int* nb_students = 0;
	int* student_list= search_by_key_phone(key_phone,nb_students,tab,phone_tab, size, size);
	
	//Printing results as explained on directory.c
	printf("%d \n", nb_students);
	for (int i = 0; i < *nb_students; i++)
	{
		char* student_name = tab[student_list[i]].Student.Name;
		char* student_class = tab[student_list[i]].Student.Class;
		int   student_phone = tab[student_list[i]].Student.Phone;
		printf("%s;%s;%d\n", student_name, student_class, student_phone);
	}
	free(student_list);
}

int delete_by_key_name(Key key_name, Directory *tab, int size)
{
	int index = search_by_key_name(key_name, tab, size);
	switch (index)
	{
	case -3: //the function didn't work properly
		return -3;
	case -2: //couldn't find the student to delete with given name
		return -2;
		break;
	case -1: //couldn't find the student to delete with given name
		return -1;
		break;
	default:
		tab[index].State = DELETED;
		break;
	}
	//returns the index of the deleted student
	return index;
}
//deletes the phone number related to the person given.
int delete_phone_student(int student_phone,int student_index, Directory *tab, Phone_directory* phone_tab, int size)
{
	Key key_phone = get_key_phone(student_phone,size);
	int index_phone_tab = search_by_key_phone_and_directory_index(key_phone,student_index,tab,phone_tab,size,size);
	if(index_phone_tab > -1)
	{
		phone_tab[index_phone_tab].Index_directory = -1;
		phone_tab[index_phone_tab].Key_phone = -1;
	}
	return index_phone_tab;
}
void delete_student_by_name(char* name, Directory *tab,Phone_directory* phone_tab, int size)
{
	Key key_value = get_key_name(name, size);
	int confirmation = delete_by_key_name(key_value, tab, size);
	//no on screen output as explained on directory.c, remove comments if needed
	switch (confirmation)
	{
	case -3:
		//printf("Error: the function didn't work properly");
		break;
	case -2:
		//printf("Error: couldn't find student to delete with given name");
		break;
	case -1:
		//printf("Error: couldn't find student to delete with given name");
		break;
	default:
		//printf("Student deleted successfully");
		break;
	}
	int student_index = confirmation;
	int student_phone = tab[student_index].Student.Phone;
	delete_phone_student(student_phone,student_index,tab,phone_tab,size);
}

void delete_student_by_phone(int student_phone, Directory *tab,Phone_directory* phone_tab, int size)
{
	Key key_phone = get_key_phone(student_phone, size);
	int* nb_students = 0;
	int* tab_phone = search_by_key_phone(key_phone,nb_students, tab,phone_tab, size, size);
	printf("%d \n", nb_students);
	for (int i = 0; i < *nb_students; i++)
	{
		tab[tab_phone[i]].State = DELETED;
		int index_phone_tab = search_by_key_phone_and_directory_index(key_phone,tab_phone[i],tab,phone_tab,size,size);
		if(index_phone_tab > -1)
		{
			phone_tab[index_phone_tab].Index_directory = -1;
			phone_tab[index_phone_tab].Key_phone = -1;
		}
	}
	free(tab_phone);
}

Students add_empty_student()
{
	char* student_name[STR_SIZE];
	char* student_class[STR_SIZE];
	for (int i = 0; i < STR_SIZE; i++)
	{
		student_name[i] = 0;
		student_class[i] = 0;
	}
	//Students new_student = (Students){strcpy(new_student.Name,student_name),strcpy(new_student.Class,student_class),.Phone = -1};
	Students new_student = (Students){new_student.Name,student_name,.Class =student_class , .Phone = -1};
	return new_student;
}
Students add_student(char* student_name, char* student_class, int student_phone)
{
	/*
	Students new_student;
	
	//new_student->Name = *student_name;
	strcpy(new_student.Name, student_name);
	//new_student->Class = *student_class;
	strcpy(new_student.Class, student_class);
	
	new_student.Phone = student_phone;
	*/
	return (Students){student_name,student_class,student_phone};
}


Phone_directory* new_empty_phone_directory(int size){
	Phone_directory* new_tab_phone = malloc(size * sizeof(Phone_directory));
	for (int i = 0; i < size - 1; i++)
	{
		new_tab_phone[i].Index_directory = -1;
		new_tab_phone[i].Key_phone = -1;
	}
	return new_tab_phone;
}

Directory* new_empty_directory(int size)
{
	Directory* new_tab = malloc(size * sizeof(Directory));
	for (int i = 0; i < size - 1; i++)
	{
		new_tab[i].Key_name = -1;
		new_tab[i].State = EMPTY;
		new_tab[i].Student = add_empty_student();
	}
	return new_tab;
}

//created the main directory in which the students are contained
Directory* new_directory(char* file_content,Phone_directory* tab_phone, int* size) {
	Phone_directory* new_tab_phone = new_empty_phone_directory(*size);
	//defines a bigger size for the actual size and makes sure it's a prime number
	*size= find_tab_size_prime_number(*size);
	Directory* tab = malloc(*size * sizeof(Directory));
	//defines the character that separates each field from the file
	char sep[] = ";";
	char* token;
	char* student_name;
	char* student_class;
	int student_phone = -1;
	int cnt = 0;
	for (int i = 0; i < *size; i++)
	{
		// Point to first token
		token = &file_content[i];
		// Iterate through other tokens and store them in fields
		cnt = 0;
		char *fields[MAX_FIELDS];
		while (token) {
			if (cnt >= MAX_FIELDS) {
				//fprintf(stderr, "line %d has too many fields!\n", cnt);
				continue;
			}
			fields[cnt] = token;
			token = strtok(NULL, sep);
			cnt++;
		}

		student_name = fields[0];
		student_class = fields[1];
		//checks if the student has a phone number or not
		if (*fields[2] != '\0')
		{
			student_phone = atoi(fields[2]);
		}
		else {
			student_phone = -1;
		}

		Students new_student = add_student(student_name, student_class, student_phone);
		Key student_key = get_key_name(student_name, *size);
		int student_index = insert_by_key_name(new_student,student_key,tab,*size);
		new_tab_phone[i].Index_directory = student_index;
		if(student_phone != 1){
			insert_by_key_phone(student_phone,student_index,tab_phone,*size);
		}
	}
	return tab;
}

Directory* extend_previous_directory(Directory* old_tab, int* size)
{
	int new_tab_size = find_tab_size_prime_number(*size);
	Directory* new_tab = new_empty_directory(new_tab_size);
	//the new directory takes all the values from the old directory as it has made some new space for
	for (int i = 0; i < *size; i++)
	{
		new_tab[i].Key_name = old_tab[i].Key_name;
		new_tab[i].State = old_tab[i].State;
		new_tab[i].Student = old_tab[i].Student;
	}
	// A VERIFIER
	free(old_tab);
	*size = new_tab_size;
	return new_tab;
}
Phone_directory* extend_previous_phone_directory(Phone_directory* old_phone_tab, int* size)
{
	Phone_directory* new_phone_tab = new_empty_phone_directory(*size);
	//the new directory takes all the values from the old directory as it has made some new space for
	for (int i = 0; i < *size; i++)
	{
		new_phone_tab[i].Key_phone = old_phone_tab[i].Key_phone;
		new_phone_tab[i].Index_directory = old_phone_tab[i].Key_phone;
	}
	// A VERIFIER
	free(old_phone_tab);
	return new_phone_tab;
}