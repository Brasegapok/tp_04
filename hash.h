#ifndef HASH_H
#define HASH_H

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


int sequence_jump(Key key_element,Directory tab[],int size);
Key hash_element(Key key_element,int size);


#endif /*HASH_H*/