#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

//function declared lower onto the code
Key get_key_value(char *value, int multiplier);


Students* add_empty_student()
{
   Students* new_student;
   new_student->Name[STR_SIZE] = '\0';
   new_student->Class[STR_SIZE] = '\0';
   new_student->Phone = -1;
   return new_student;
}
Students* add_student(char* name, char* class, int phone)
{
   Students *new_student;
   new_student->Name[STR_SIZE] = *name;
   new_student->Class[STR_SIZE] = *class;
   new_student->Phone = phone;
   return new_student;
}

Directory* new_empty_directory(int size)
{
   Directory *new_tab = malloc(size * sizeof(int));
   for (int i = 0; i < DEFAULT_DIREC_SIZE - 1; i++)
   {
       new_tab[i].Key_name = 0;
       new_tab[i].Key_phone = 0;
       new_tab[i].State = EMPTY;
       new_tab[i].Student = add_empty_student();
   }
   return new_tab;
}

Directory* new_directory(char* file_content,int size){
   Directory* tab = malloc(size*sizeof(Directory));
   //defines the character that separates each field from the file
   char sep[] = ";";
   char* token;
   char* student_name;
   char* student_class;
    int student_phone = -1;
   int cnt = 0;
   for(int i = 0; i < size; i++)
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
       if(fields[2] != '\0')
       {
           student_phone = atoi(fields[2]);
           tab[i].Key_phone = get_key_value(fields[2],size);
       }
       else{
           student_phone = -1;
           tab[i].Key_phone =0;
       }

       tab[i].Key_name = get_key_value(student_name,size);
       tab[i].State = FULL;
       tab[i].Student = add_student(student_name,student_class,student_phone);
    }
   return tab;
}

Directory* extend_previous_directory(Directory* old_tab,int* size, int size_extension)
{
   int new_tab_size = *size + size_extension;
   Directory* new_tab = new_empty_directory(new_tab_size);
   //the new directory takes all the values from the old directory as it has made some new space for
   for(int i = 0; i < *size; i++)
   {
       new_tab[i].Key_name= old_tab[i].Key_name;
       new_tab[i].Key_phone = old_tab[i].Key_phone;
       new_tab[i].State = old_tab[i].State;
       new_tab[i].Student = old_tab[i].Student;
   }
   // A VERIFIER
   free(old_tab);
   *size = new_tab_size;
   return new_tab;
}

int print_directory(Directory* tab,int size){
   int nb_students= 0;
   for(int i = 0; i < size; i++)
   {
       //makes sure that the student to add exists
       if(tab[nb_students].State == FULL)
       {
           char* student_name= tab[nb_students].Student->Name;
           char* student_class = tab[nb_students].Student->Class;
           int  student_phone = tab[nb_students].Student->Phone;
           //in case the new student does not have a phone number:
           if(student_phone == -1)
           {
               printf("%s;%s; \n",student_name,student_class);
           }
           printf("%s;%s;%d\n",student_name,student_class,student_phone);
       }
       //prevents out of bounds error
       nb_students++;
   }
   return nb_students;
}

char* prepare_directory_file(Directory* tab,int size,int* file_size){
   char* file_content = malloc(size*sizeof(Directory));
   char * line = "";
   char sep[] = ";";
   char* student_phone
   for(int i = 0; i < size; i++)
   {
       //makes sure the student exists on the directory before adding it into the file
       if(tab[i].State == FULL)
       {
           file_size++;
           //prepares the next line for the file content
           line = tab[i].Student->Name;
           line = strcat(line,sep);
           line = strcat(line,tab[i].Student->Class);
           line = strcat(line,sep);
           if(tab[i].Student->Phone != -1)
           {
               student_phone = sprintf(str, "%d", tab[i].Student->Phone);
               line = strcat(line,);
           }
           file_content[i] = line;
       }
   }

   return file_content;
}


int check_full_directory(Directory* tab, int size){
   for(int i = 0; i < size; i++)
   {
       if(tab[i].State == EMPTY || tab[i].State == DELETED)
       {
           return 0;
       }
   }
   return 1;
}

int check_directory_space(Directory *tab,int size){
   int empty_slots = 0;
   while (&tab[empty_slots] != EMPTY)
   {
       empty_slots++;
       //prevents the program from crashing in case the directory is full
       if(empty_slots >= size){
           empty_slots = size;
           break;
       };
   }
   int directory_space = size-empty_slots;
   return directory_space;
}

Key get_key_value(char *value, int multiplier)
{
   Key key_val = 0;
   int i = 0;
   while (value[i] != '\0')
   {
       key_val += (int)value[i] * multiplier;
   }
   return key_val;
}

int test_get_key_value()
{
    int tab_len = 10;
    char value_test = "Super";
    Key key_value = get_key_value(value_test, tab_len);
    Key test_value = 5270;
    return (key_value == test_value);
}

Key hash_element(Key Key_value, int size)
{
   return (Key_value) % size;
}
int hash_element_test(Key Key_value, int size,Key test_key_value)
{
   return test_key_value == hash_element(Key_value,size);
}


int linear_jump(Key Key_value, Directory* tab, int size, int jump_value)
{
   int index = (Key_value + jump_value) % size;
   return index;
}

int search_insert(Key c, Directory* tab, int size, int jump_value)
{
   int cnt = 0;
   int index_hash = hash_element(c, tab, size);
   while (tab[index_hash].State == FULL)
   {
       //prevents an out of bounds error
       if (cnt > size)
           return -2;
       //prevents adding the same key
       if (tab[index_hash].Key_name == c)
           return -1;
       index_hash = index_hash + linear_jump(c, tab, size, jump_value);
       cnt++;
   }
   return index_hash;
}

int search_by_key_name(Key c, Directory* tab, int size, int jump_value)
{
   int cnt = 0;
   int index_hash = hash_element(c, tab, size);
   while (tab[index_hash].State != EMPTY)
   {
       //prevents an out of bounds error
       if (cnt > size)
           return -2;
       //finds the same key values
       if (tab[index_hash].State == FULL && tab[index_hash].Key_name == c)
       {
           return index_hash;
       }
       index_hash = index_hash + linear_jump(c, tab, size, jump_value);
       cnt++;
   }
   //key value not found on the directory
   return -1;
}

int search_by_key_phone(Key c, Directory* tab,int* tab_phone, int size, int jump_value)
{
   int cnt = 0;
   int nb_students = 0;
   int index_hash = hash_element(c, tab, size);
   while (tab[index_hash].State != EMPTY)
   {
       //prevents an out of bounds error
       if (cnt > size)
           return nb_students;
       //prevents adding the same key
       if (tab[index_hash].State == FULL && tab[index_hash].Key_name == c)
       {
           tab_phone[nb_students] =index_hash;
           nb_students++;
       }
       index_hash = index_hash + linear_jump(c, tab, size, jump_value);
       cnt++;
   }
   return nb_students;  
}


int insert_by_key_name(Students* new_student, Key c, Directory* tab, int size, int jump_value)
{
   if(!check_full_directory(tab,size)){
       int index = search_insert(c, tab, size, jump_value);
       switch (index)
       {
       case -2://directory is full
           return -3; //directory shouldn't actually be full here, returns an function error
           break;
       case -1:
           return -1; // directory found the same key value (student) which is not allowed
           break;
       default:
           tab[index].State = FULL;
           tab[index].Key_name = c;
           tab[index].Student = new_student;
           break;
       }
       return 1; //directory added the new student with it's key value
   }
  
}


void insert_new_student(char* student_name, char* student_class, int student_phone, Directory* tab, int size)
{
   Key key_value = get_key_value(student_name, size);
   Students* new_student = add_student(student_name, student_class, student_phone);
   if(check_full_directory(tab,size))
   {
       tab = extend_previous_directory(tab,size,SIZE_EXTENSION);
   }
   int confirmation = insert_by_key_name(new_student, key_value, tab, size, size);
  
   //no on screen output as explained on directory.c, remove comments if needed
   switch (confirmation)
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
   default:
       //printf("Student added successfully");
   break;
   }
}

void search_student_by_name(char* name,Directory* tab,int size)
{
   Key key_value = get_key_value(name, size);
   int index = search_by_key_name(key_value,tab,size,size);
  
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
       //char*student_name;
       //strcpy(student_name, tab[index].Student->Name);
       char* student_name= tab[index].Student->Name;
       char* student_class = tab[index].Student->Class;
       int   student_phone = tab[index].Student->Phone;
       printf("%s;%s;%d",student_name,student_class,student_phone);
   break;
   }
}
void search_student_by_phone(int phone,Directory *tab,int size)
{
   Key c = get_key_value(phone,size);
   int *tab_phone = malloc(size*sizeof(int));
   int nb_students = search_by_key_phone(c,tab,tab_phone,size,size);
   printf("%d \n",nb_students);
   for(int i = 0; i < nb_students; i++)
   {
       char* student_name= tab[tab_phone[i]].Student->Name;
       char* student_class = tab[tab_phone[i]].Student->Class;
       int   student_phone = tab[tab_phone[i]].Student->Phone;
       printf("%s;%s;%d\n",student_name,student_class,student_phone);
   }
   free(tab_phone);
}


int delete_by_key_name(Key c, Directory *tab, int size, int jump_value)
{
   int index = search_by_key_name(c, tab, size, jump_value);
   switch (index)
   {
   case -2:
       return -2;
       break;
   case -1:
       return -1;
       break;
   default:
       tab[index]->State = DELETED;
       break;
   }
   return 1;
}

void delete_student_by_name(char* name,Directory *tab,int size)
{
   Key key_value = get_key_value(name, size);
   delete_by_key_name(key_value,tab,size,size);
}

void delete_student_by_phone(int phone,Directory *tab,int size)
{
   Key c = get_key_value(phone,size);
   int *tab_phone = malloc(size*sizeof(int));
   int nb_students = search_by_key_phone(c,tab,tab_phone,size,size);
   printf("%d \n",nb_students);
   for(int i = 0; i < nb_students; i++)
   {
       tab[tab_phone[i]]->State = DELETED;
   }
   free(tab_phone);
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



