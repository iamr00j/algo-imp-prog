//http://syllabus.cs.manchester.ac.uk/ugt/2017/COMP26120/lab/ex9.html

#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct 
{ // hash-table entry
  Key_Type element; // only data is the key itself
  enum {empty, in_use, deleted} state;
} cell;

typedef unsigned int Table_size; // type for size-of or index-into hash table

struct table 
{
  cell *cells; Table_size table_size; // cell cells [table_size];
  Table_size num_entries; // number of cells in_use
  // add anything else that you need
  int randomA;
  int randomB;
  int num_collisions;
};

Table initialize_table (Table_size tablesize) 
{
  int i;
  int a;
  int b;
  
  Table newtable = malloc(sizeof(struct table));
  if(newtable == NULL)
    fprintf(stderr, "Malloc error!\n");
  
  cell *newcell = malloc(tablesize*sizeof(cell));
  if(newcell == NULL)
    fprintf(stderr, "Malloc error!\n");
  
  newtable-> cells = newcell;
  for(i=0; i<tablesize; i++){
    newtable->cells[i].element = NULL;
    newtable->cells[i].state = empty;
  }
  
  newtable->table_size = tablesize;
  newtable->num_entries =0;
  a = (rand() % (tablesize-1))+1;
  while(a % tablesize ==0){
    a++;
  }
  b = rand() % tablesize;
  newtable->randomA = a;
  newtable->randomB = b;
  newtable->num_collisions=0;
  
  return newtable;
}

/* function to determine if number is prime */
Boolean prime_number(int number){
  if(number <=1){
    return 0;
  }
  else{
    for(int i=2; i*i<number; i++)
      if(number %i ==0)
        return 0;
  }
  return 1;
}

Table resize(Table thistable){
  int a;
  int b;
  
  int newsize = thistable -> table_size*2;
  while(!prime_number(newsize)){
    newsize++;
  }
  Table newtable = malloc(sizeof(struct table));
  if(newtable == NULL)
    fprintf(stderr, "Malloc error!\n");
  cell *newcell = malloc(newsize*sizeof(cell));
  if(newcell == NULL)
    fprintf(stderr, "Malloc error!\n");
  newtable -> cells = newcell;
  newtable -> table_size = newsize;
  newtable -> num_entries = 0;
  a = (rand() % newsize) +1;
  while (a % newsize ==0){
    a++;
  }
  b = rand() % newsize;
  newtable -> randomA = a;
  newtable -> randomB = b;
  
  for(int i = 0; i<newsize; i++){
    newtable ->cells[i].element = NULL;
    newtable->cells[i].state = empty;
  }
  for(int i =0; i < thistable->table_size; i++){
    if(thistable->cells[i].state == in_use){
      insert(thistable->cells[i].element, newtable);
    }
  }
  return newtable;
}

/*hash function using polynomial hash codes and MAD method. 
  Values a and b are +ve integers not multiple of tablesize.*/
int h(Key_Type element, Table thistable){
  int hash = 0;
  int p = 31;
  int len = strlen(element);
  int tablesize= thistable ->table_size;
  int i;
  int a;
  int b;
  
  for(i = 0; i<len;i++){
    hash = p*hash + element [i];
  }
  
  a = thistable ->randomA;
  b = thistable ->randomB;
  
  return (a*hash +b)%tablesize;
}

//Collision handling. return non-zero
int double_h(int key, Table thistable){
  int prime = 13;
  while(prime>thistable->table_size && prime_number(prime)){
    prime--;
  }
  return prime - (key % prime);
}

Table insert (Key_Type element, Table thistable) {
  if(thistable->num_entries >= thistable->table_size)
    thistable=resize(thistable);
  Key_Type element_copy = strdup(element);
  int hash = h(element_copy, thistable);
  
  while(thistable->cells[hash].element!=NULL && thistable->cells[hash].state == in_use){
    if(strcmp(thistable->cells[hash].element, element_copy)==0){
      hash = (hash+1) % thistable->table_size;
      thistable->num_collisions = thistable->num_collisions+1;
    }
      return thistable;

  }
  
  thistable->cells[hash].element = element_copy;
  thistable->cells[hash].state = in_use;
  thistable->num_entries = thistable ->num_entries +1;
  
  return thistable;
}

Table insert2 (Key_Type element, Table thistable) {
  if(thistable->num_entries >= thistable->table_size)
    thistable=resize(thistable);
  Key_Type element_copy = strdup(element);
  int hash = h(element_copy, thistable);
  int hash2 = double_h(hash, thistable);
  
  while(thistable->cells[hash].element!=NULL && thistable->cells[hash].state == in_use){
    if(strcmp(thistable->cells[hash].element, element_copy)==0){
      hash = (hash+hash2) % thistable->table_size;
      thistable->num_collisions = thistable->num_collisions+1;
    }
      return thistable;

  }
  
  thistable->cells[hash].element = element_copy;
  thistable->cells[hash].state = in_use;
  thistable->num_entries = thistable ->num_entries +1;
  
  return thistable;
}

Boolean find (Key_Type element, Table thistable){
  int hash = h(element, thistable);
  int count = 0;
  
  while(1){
    if(thistable->cells[hash].element == NULL)
      return 0;
    else if(thistable->cells[hash].state == in_use){
      if(strcmp(thistable->cells[hash].element, element)==0)
        return 1;
      else{
        hash = (hash +1)%thistable->table_size;
        count++;
      }
    }
    else{
      hash = (hash+1) % thistable ->table_size;
      count++;
    }

    if(count >= thistable-> num_entries)
      break;
  }
  return 0;
}

Boolean find2 (Key_Type element, Table thistable){
  int hash = h(element, thistable);
  int hash2 = double_h(hash, thistable);
  int count = 0;
  
  while(1){
    if(thistable->cells[hash].element == NULL)
      return 0;
    else if(thistable->cells[hash].state == in_use){
      if(strcmp(thistable->cells[hash].element, element)==0)
        return 1;
      else{
        hash = (hash+hash2)%thistable->table_size;
        count++;
      }
    }
    else{
      hash = (hash+hash2) % thistable ->table_size;
      count++;
    }

    if(count >= thistable-> num_entries)
      break;
  }
  return 0;
}

void print_table(Table thistable){
  for(int i=0; i<thistable->table_size;i++){
    if(thistable->cells[i].state == in_use)
      printf("%s\n", thistable->cells[i].element);
  }
}

void print_stats (Table thistable) 
{
  printf("The size of the table is %d.\n", thistable ->table_size);
  printf("The total number of entries in the table is %d\n", thistable -> num_entries);
  printf("The average number of collisions is %.2f\n", (double)thistable->num_collisions/thistable->num_entries);
}
