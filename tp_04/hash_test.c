/**
 *	PROJECT NAME	: tp_04 -> Annuaire	
 *	PROJECT UTILITY	: shows a list of students and allows searching for a specific one
 * 	FILE NAME		: hash_test.c
 * 	FILE UTILITY	: tests each function contained on the "hash.c" file
 * 	AUTHOR			: Mami Francesco
 * 	CREATION DATE	: 11.03.2019
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"  


int print_test_int(int value_to_find,int value_found,char* test_name);
int print_test_array(int* value_to_find,int* value_found,int size,char* test_name);
int print_test_phone_directory(Phone_directory* value_to_find,Phone_directory* value_found,int size,char* test_name);
int print_test_directory(Directory* value_to_find,Directory* value_found,int size,char* test_name);
int check_prime_number_test(int value,int test_is_prime_number)
{
    int is_prime_number = check_prime_number(value);
    return print_test_int(test_is_prime_number,is_prime_number,__func__);
}
int find_lower_prime_number_test(int value,int test_prime_number){
    int prime_number = find_lower_prime_number(value);
    return print_test_int(test_prime_number,prime_number,__func__);
}

int find_tab_size_prime_number_test(int value,int size_extension,int test_prime_number){
    int prime_number = find_tab_size_prime_number(value,size_extension);
    return print_test_int(test_prime_number,prime_number,__func__);
}
int test_get_key_name(char* value, int multiplier,Key test_key_value)
{
	Key key_value = get_key_name(value,multiplier);
	return print_test_int(test_key_value,key_value,__func__);
}

int test_get_key_phone(int value, int multiplier,Key test_key_value)
{
	Key key_value = get_key_phone(value,multiplier);
	return print_test_int(test_key_value,key_value,__func__);
}

int hash_1_test(Key key_value, int size, int test_hash_value)
{
	int hash_value= hash_1(key_value, size);
	return print_test_int(test_hash_value,hash_value,__func__);
}

int hash_2_test(Key key_value, int size,int prime_number, int test_hash_value)
{
	int hash_value = hash_2(key_value, size,prime_number);
	return print_test_int(test_hash_value,hash_value,__func__);
}

int double_hash_test(Key key_value, int size,int cnt,int prime_number, int test_hash_value)
{
	int hash_value = double_hash(key_value, size,cnt,prime_number);
	return print_test_int(test_hash_value,hash_value,__func__);
}

int linear_jump_test(Key key_value, int size, int jump_value, int test_index)
{
	int index_value = linear_jump(key_value, size,jump_value);
	return print_test_int(test_index,index_value,__func__);
}

int search_insert_phone_test(Key key_phone,Directory* tab, Phone_directory* phone_tab, int size,int test_index_phone){
	int index_phone = search_insert_phone(key_phone, tab,phone_tab,size);
	return print_test_int(test_index_phone,index_phone,__func__);
}

int search_insert_name_test(Key key_name, Directory* tab, int size,int test_index_name)
{
	int index_name = search_insert_name(key_name,tab,size);
	return print_test_int(test_index_name,index_name,__func__);
}

int search_by_key_name_test(Key key_name, Directory* tab, int size,Key test_index_name){
	int index_name = search_by_key_name(key_name,tab,size);
	return print_test_int(test_index_name,index_name,__func__);
}

int* search_by_key_phone_test(Key key_phone,Directory* tab,Phone_directory* phone_tab, int size, int jump_value,int* test_phone_list){
	int* nb_students = 0;
	int* phone_list = search_by_key_phone(key_phone,nb_students,tab,phone_tab,size,size);
	return print_test_array(test_phone_list,phone_list,size,__func__);
}
int search_by_key_phone_and_directory_index_test(Key key_phone,int student_index,Directory* tab,Phone_directory* phone_tab, int size, int jump_value,int test_phone_index){
	int index_phone = search_by_key_phone_and_directory_index(key_phone,student_index,tab,phone_tab,size,size);
	return print_test_int(test_phone_index,index_phone,__func__);
}

int insert_by_key_phone_test(int student_phone,int student_index,Directory*tab,Phone_directory* phone_tab,int size,Phone_directory* test_phone_tab){
	insert_by_key_phone(student_phone,student_index,tab,phone_tab,size,size);
	return print_test_phone_directory(test_phone_tab,phone_tab,size,__func__);
}

int insert_by_key_name_test(Students* new_student, Key key_name, Directory* tab, int size, Directory* test_tab)
{
	insert_by_key_name(new_student,key_name,tab,tab,size);
	return print_test_phone_directory(test_tab,tab,size,__func__);
}

int delete_by_key_name_test(Key key_name, Directory *tab, int size,Directory* test_tab)
{
	delete_by_key_name(key_name,tab,size);
	return print_test_phone_directory(test_tab,tab,size,__func__);
}
void delete_phone_student_test(int student_phone,int student_index, Directory *tab,Phone_directory* phone_tab, int size,Phone_directory* test_phone_tab)
{
	delete_phone_student(student_phone,student_index,tab,phone_tab);
	return print_test_phone_directory(test_phone_tab,phone_tab,size,__func__);
}

void delete_student_by_phone_test(int student_phone, Directory *tab,Phone_directory* phone_tab, int size,Directory* test_tab)
{
	delete_student_by_phone(student_phone,tab,phone_tab,size);
	return print_test_directory(test_tab,tab,size,__func__);
}


int print_test_int(int value_to_find,int value_found,char* test_name){
	printf("---------- TESTING: %s ----------",test_name);
	printf("value to find: %d , value found: %d:",value_to_find,value_found);
    int test_passed = (value_to_find == value_found);
	if(test_passed)
    {
		printf("%s passed",test_name);
	}
	else{
		printf("%s failed",test_name);
	}
	return test_passed;
	printf("------------ END TEST  -------------",test_name);
}

int print_test_array(int* value_to_find,int* value_found,int size,char* test_name){
	printf("---------- TESTING: %s ----------",test_name);
	int test_passed = 1;
	for(int i = 0; i < size; i++)
	{
		//shows the failed values in case there's one
		if(value_to_find[i] != value_found[i])
		{
			printf("iteration n°%d : value to find: %d , value found: %d:",i,value_to_find[i],value_found[i]);
			test_passed = 0;
		}
	}
	if(test_passed)
    {
		printf("%s passed",test_name);
	}
	else{
		printf("%s failed",test_name);
	}
	printf("------------ END TEST  -------------",test_name);
	return test_passed;
}

int print_test_phone_directory(Phone_directory* value_to_find,Phone_directory* value_found,int size,char* test_name){
	printf("---------- TESTING: %s ----------",test_name);
	int test_passed = 1;
	for(int i = 0; i < size; i++)
	{
		//shows the failed values in case there's one
		if(value_to_find[i].Index_directory != value_found[i].Index_directory)
		{
			printf("iteration n°%d : index to find: %d , index found: %d:",i,value_to_find[i].Index_directory,value_found[i].Index_directory);
			test_passed = 0;
		}
		//shows the failed values in case there's one
		if(value_to_find[i].Key_phone != value_found[i].Key_phone)
		{
			printf("iteration n°%d : key_phone to find: %d , key_phone found: %d:",i,value_to_find[i].Key_phone,value_found[i].Key_phone);
			test_passed = 0;
		}
	}
	if(test_passed)
    {
		printf("%s passed",test_name);
	}
	else{
		printf("%s failed",test_name);
	}
	printf("------------ END TEST  -------------",test_name);
	return test_passed;
}

int print_test_directory(Directory* value_to_find,Directory* value_found,int size,char* test_name){
	printf("---------- TESTING: %s ----------",test_name);
	int test_passed = 1;
	for(int i = 0; i < size; i++)
	{
		//shows the failed values in case there's one
		if(value_to_find[i].Key_name != value_found[i].Key_name)
		{
			printf("iteration n°%d : Key_name to find: %d , key_name found: %d:",i,value_to_find[i].Key_name,value_found[i].Key_name);
			test_passed = 0;
		}
		//shows the failed values in case there's one
		if(value_to_find[i].Student.Name != value_found[i].Student.Name)
		{
			printf("iteration n°%d : student_name to find: %d , student_name found: %d:",i,value_to_find[i].Student.Name,value_found[i].Student.Name);
			test_passed = 0;
		}
		//shows the failed values in case there's one
		if(value_to_find[i].Student.Class != value_found[i].Student.Class)
		{
			printf("iteration n°%d : student_phone to find: %d , student_phone found: %d:",i,value_to_find[i].Student.Class,value_found[i].Student.Class);
			test_passed = 0;
		}
		
		//shows the failed values in case there's one
		if(value_to_find[i].Student.Phone != value_found[i].Student.Phone)
		{
			printf("iteration n°%d : student_name to find: %d , student_name found: %d:",i,value_to_find[i].Student.Phone,value_found[i].Student.Phone);
			test_passed = 0;
		}
	}
	if(test_passed)
    {
		printf("%s passed",test_name);
	}
	else{
		printf("%s failed",test_name);
	}
	printf("------------ END TEST  -------------",test_name);
	return test_passed;
}


void run_tests()
{
	int size= 10;
	Directory* tab = malloc(size*sizeof(Directory));
	Directory* test_tab = malloc(size*sizeof(Directory));
	test_get_key_name("Super",size,5270);
	test_get_key_phone(23,size,230);
	hash_1_test(16, size, 6);
	hash_2_test(16,size,7,1);
	double_hash_test(16,size,7,7,3);
	linear_jump_test(5270,size,10,0);

	//unsure on how to test directory related functions.
	/*
	search_insert_name_test(5279,tab,size,);
	*/
}

int main()
{
    run_tests();
}

