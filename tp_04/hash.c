#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"


Students add_empty_student()
{
    Students new_student;
    new_student.Name[STR_SIZE] = '\0';
    new_student.Class[STR_SIZE] = '\0';
    new_student.Phone = NULL;
    return new_student;
}
Students add_student(char *name, char *class, int phone)
{
    Students new_student;
    new_student.Name[STR_SIZE] = name;
    new_student.Class[STR_SIZE] = class;
    new_student.Phone = phone;
    return new_student;
}

Directory* new_empty_directory(int size)
{
    Directory *new_tab = malloc(size * sizeof(int));
    for (int i = 0; i < DEFAULT_DIREC_SIZE - 1; i++)
    {
        new_tab[i].key_element = 0;
        new_tab[i].state = EMPTY;
        new_tab[i].Student = add_empty_student();
    }
    return new_tab;
}

Directory* new_directory(char* file_content,int size){
    
}

Directory* extend_previous_directory(Directory *old_dir, int size_extension)
{
    directory_size_extension += size_extension;
    old_dir = realloc(old_dir, directory_size_extension);
}

void check_directory_space(Directory *tab,int size){
    int cnt = 0;
    while (&tab[cnt] != EMPTY)
    {
        cnt++;
        //prevents the program from crashing in case the directory is full
        if(cnt >= size){
            cnt = size;
            break;
        };
    } 
    printf("%d %d",cnt,size-cnt);
}

Key get_key_value(char *name, int multiplier)
{
    Key key_val = 0;
    int i = 0;
    while (name[i] != '\0')
    {
        key_val += (int)name[i] * multiplier;
    }
    return key_val;
}

int test_get_key_value()
{
    int tab_len = 10;
    char name_test = "Super";
    Key key_value = get_key_value(name_test, tab_len);
    Key test_value = 5270;
    return (key_value == test_value);
}

Key hash_element(Key key_element, int size)
{
    return (key_element) % size;
}
int hash_element_test(Key key_element, int size,Key test_key_value)
{
    return test_key_value == hash_element_test(key_element,size);
}


int linear_jump(Key key_element, Directory *tab, int size, int jump_value)
{
    int index = (key_element + jump_value) % size;
    return index;
}

int search_insert(Key c, Directory *tab, int size, int jump_value)
{
    int cnt = 0;
    int index_hash = hash_element(c, tab, size);
    while (tab[index_hash].state == FULL)
    {
        //prevents an out of bounds error
        if (cnt > size)
            return -2;
        //prevents adding the same key
        if (tab[index_hash].key_element == c)
            return -1;
        index_hash = index_hash + linear_jump(c, tab, size, jump_value);
        cnt++;
    }
    return index_hash;
}

int search_by_key_value(Key c, Directory *tab, int size, int jump_value)
{
    int cnt = 0;
    int index_hash = hash_element(c, tab, size);
    while (tab[index_hash].state != EMPTY)
    {
        //prevents an out of bounds error
        if (cnt > size)
            return -2;
        //finds the same key values
        if (tab[index_hash].state == FULL && tab[index_hash].key_element == c)
        {
            return index_hash;
        }
        index_hash = index_hash + linear_jump(c, tab, size, jump_value);
        cnt++;
    }
    //key value not found on the directory
    return -1;
}

int search_multiple_by_key_value(Key c, Directory *tab,int*tab_phone, int size, int jump_value)
{
    int cnt = 0;
    int nb_students = 0;
    int index_hash = hash_element(c, tab, size);
    while (tab[index_hash].state != EMPTY)
    {
        //prevents an out of bounds error
        if (cnt > size)
            return nb_students;
        //prevents adding the same key
        if (tab[index_hash].state == FULL && tab[index_hash].key_element == c)
        {
            tab_phone[nb_students] =index_hash;
            nb_students++;
        }
        index_hash = index_hash + linear_jump(c, tab, size, jump_value);
        cnt++;
    }
    return nb_students;   
}


int insert_by_key_value(Students new_student, Key c, Directory *tab, int size, int jump_value)
{
    int index = search_insert(c, tab, size, jump_value);
    switch (index)
    {
    case -2:
        return -2;
        break;
    case -1:
        return -1;
        break;
    default:
        tab[index].state = FULL;
        tab[index].key_element = c;
        tab[index].Student = new_student;
        break;
    }
    return 1;
}

int delete_by_key_value(Key c, Directory *tab, int size, int jump_value)
{
    int index = search_by_key_value(c, tab, size, jump_value); 
    switch (index)
    {
    case -2:
        return -2;
        break;
    case -1:
        return -1;
        break;
    default:
        tab[index].state = DELETED;
        break;
    }
    return 1;
}

void insert_student(char *name, char *class, int phone, Directory *tab, int size)
{
    Key key_value = get_key_value(name, size);
    Students new_student = add_student(name, class, phone);
    int confirmation = insert_by_key_value(new_student, key_value, tab, size, size);
    switch (confirmation)
    {
    case -2:
        printf("Error: the directory is full, cannot add more students");
        
        break;
    case -1:
        printf("Error: Student to insert already exists");
        
        break;
    default:
        //no on screen output as explained on directory.c
        //printf("Student added successfully");
    break;
    }
}

void search_student_by_name(char* name,Directory *tab,int size)
{
    Key key_value = get_key_value(name, size);
    int index = search_by_key_value(key_value,tab,size,size);
    
    switch (index)
    {
    case -2: //Checked the whole directory without finding the student
        //printf("Couldn't find student with given name");
        //printing asked value on directory.c
        printf("-1");
        break;
    case -1: //Encountered a Empty slot on directory, no more students afterwards
        //printf("Couldn't find student with given name");
        //printing asked value on directory.c
        printf("-1");
        break;
    default:
        char* student_name= tab[index].Student.Name;
        char* student_class = tab[index].Student.Class;
        int   student_phone = tab[index].Student.Phone;
        printf("%s;%s;%d",student_name,student_class,student_phone);
    break;
    }
}
void search_student_by_phone(int phone,Directory *tab,int size)
{
    Key c = get_key_value(phone,size);
    int *tab_phone = malloc(size*sizeof(int));
    int nb_students = search_multiple_by_key_value(c,tab,tab_phone,size,size);
    printf("%d \n",nb_students);
    for(int i = 0; i < nb_students; i++)
    {
        char* student_name= tab[tab_phone[i]].Student.Name;
        char* student_class = tab[tab_phone[i]].Student.Class;
        int   student_phone = tab[tab_phone[i]].Student.Phone;
        printf("%s;%s;%d\n",student_name,student_class,student_phone);
    }
    free(tab_phone);
}

void delete_student_by_name(char* name,Directory *tab,int size)
{
    Key key_value = get_key_value(name, size);
    delete_by_key_value(key_value,tab,size,size);
}

void delete_student_by_phone(int phone,Directory *tab,int size)
{
    Key c = get_key_value(phone,size);
    int *tab_phone = malloc(size*sizeof(int));
    int nb_students = search_multiple_by_key_value(c,tab,tab_phone,size,size);
    printf("%d \n",nb_students);
    for(int i = 0; i < nb_students; i++)
    {
        Key key_to_delete = tab[tab_phone[i]].key_element;
        delete_by_key_value(key_to_delete,tab,size,size);
    }
    free(tab_phone);
}

void print_directory(Directory *tab,int size){
    int nb_students= 0;
    while(tab[nb_students].state != EMPTY)
    {
        //makes sure that the student to add exists
        if(tab[nb_students].state != DELETED)
        {
            char* student_name= tab[nb_students].Student.Name;
            char* student_class = tab[nb_students].Student.Class;
            int   student_phone = tab[nb_students].Student.Phone;
        printf("%s;%s;%d\n",student_name,student_class,student_phone);
        }
        nb_students++;
        //prevents out of bounds error
        if(nb_students >size) break;
    }
}

int main()
{
    if(test_get_key_value()) print("test get_key_value successfull!");
    //----------- TEST HASH---------------
    int tab_len = 10;
    Key key_value = 16;
    Key test_key_value = 7;
    hash_element_test(key_value,tab_len,test_key_value);
    //----------- FIN TEST HASH------------
   
}

