#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 151
#define STR_SIZE 80
#define DEFAULT_DIREC_SIZE 100


typedef Key;
typedef enum{FULL,EMPTY,DELETED} State_Element;


Directory dir_elem[DEFAULT_DIREC_SIZE];


int sequence_jump(Key key_element,Directory tab[],int size){
    int cnt = 0;
    Key index = hash_element(key_element,size);
    while(tab[index].state == FULL)
    {
        if(cnt > size){
            return -2;
        }
        
        index = hash_element(index,size);
        cnt++;
    }
    tab[index].state = FULL;
    tab[index].key_element = key_element;
}

Key hash_element(Key key_element,int size)
{
    return 1+(key_element %size);
}

int search_insert(Key c,Directory tab[],int size){
    int cnt = 0;
    int index_hash = hash_element(c,tab,SIZE);
    while(tab[index_hash].state != FULL)
    {
    }
}

int search_empty_slot()
{
    
}

int main(){

}
