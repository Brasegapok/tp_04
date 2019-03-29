#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"  


void print_test_int(int value_to_find,int value_found);


int check_prime_number_test(int value,int test_is_prime_number)
{
    int is_prime_number = check_prime_number(value);
    print_test_int(test_is_prime_number,is_prime_number,__func__);
    return test_is_prime_number == is_prime_number;
}
int find_lower_prime_number_test(int value,int test_prime_number){
    int prime_number = find_lower_prime_number(value);
    print_test_int(test_prime_number,prime_number,__func__);
    return test_prime_number == prime_number;
}

int find_tab_size_prime_number_test(int value,int size_extension,int test_prime_number){
    int prime_number = find_tab_size_prime_number(value,size_extension);
    print_test_int(test_prime_number,prime_number,__func__);
    return test_prime_number == prime_number;
}

int hash_1_test(Key key_value, int size, int test_hash_value)
{
	int hash_value= hash_1(key_value, size);
	print_test_int(test_hash_value,hash_value,__func__);
	return test_hash_value == hash_value;
}

int hash_2_test(Key key_value, int size,int prime_number, int test_hash_value)
{
	int hash_value = hash_2(key_value, size,prime_number);
	print_test_int(test_hash_value,hash_value,__func__);
	return test_hash_value == hash_value;
}

int double_hash_test(Key key_value, int size,int cnt,int prime_number, int test_hash_value)
{
	int hash_value = double_hash(key_value, size,cnt,prime_number);
	print_test_int(test_hash_value,hash_value,__func__);
	return test_hash_value == hash_value;
}

int test_get_key_value(char* value, int multiplier,Key test_key_value)
{
	Key key_value = get_key_value(value,multiplier);
	print_test_int(test_key_value,key_value,__func__);
	return (key_value == test_key_value);
}

void print_test_int(int value_to_find,int value_found,char* test_name){
	printf("value to find: %d , value found: %d:",value_to_find,value_found);
    if(value_to_find == value_found)
    {
		printf("%s passed",test_name);
	}
	else{
		printf("%s failed",test_name);
	}
}
void run_tests()
{
	test_get_key_value("Super",10,5270);
	hash_1_test(16, 10, 6);

}

int main()
{
    run_tests();
}

