
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HOW_MANY 7

char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
                      "Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};
enum staff_or_student {staff, student, neither};
enum staff_or_student job[HOW_MANY] = {student, student, neither, neither, student, staff, staff};
char *extrainfo[HOW_MANY] = {"Computer Science", "Artificial Intelligence", " ", " ", 
                              "Software Engineering", "Kilburn 2.72", "Uni Place 4.11"};

struct person{
  char *name;
  int age;
  enum staff_or_student job;
  union pR_tag{
    char *programme;
    char *room;
  } pR;
  struct person *next;
};

int memory = (sizeof(struct person));

int compare_people_by_name(struct person *people1, struct person *people2){
  char *name1 = people1->name;
  char *name2 = people2->name;
  
  return strcmp(name1,name2);
}

int compare_people_by_age(struct person *people1, struct person *people2){
  int age1 = people1->age;
  int age2 = people2->age;
  
  return age1-age2;
}

struct person *insert_start(struct person *head, char *name, int age) {
// insert a new item at the start of linked list
// return new start of linked list

  // If anyone asks why you're not casting on every malloc, just say:
  // "C implicitly casts void pointers"
  struct person *p = malloc(memory);
  
  if(p==NULL){
    fprintf(stderr, "Oops! Not enough memory!");
  }
  
  p->name = name;
  p->age = age;
  p->next = head;
  
  return p;  
}

struct person *insert_end(struct person *head, char *name, int age) {

  struct person *p = malloc(memory);
  
  if(p==NULL){
    fprintf(stderr, "Oops! Not enough memory!");
  }
  
  p->name = name;
  p->age = age;
  p->next = NULL;
  if(head==NULL){
    return p;
  }
  else{
    struct person *root = head;
    while(root -> next != NULL){
      root = root->next;
      root->next = p;
    }
  }
  return p;
  
}

static void insert_sorted(
  struct person **head, char *name, int age,
  enum staff_or_student job, char *extrainfo,
  int (*compare_people)(struct person *, struct person *)) {

  struct person *p = malloc(memory);
  
  if(p==NULL){
    fprintf(stderr, "Oops! Not enough memory!");
  }
  
  p->name = name;
  p->age = age;
  p->job = job;
  p->next = *head;
  if(job==student){
    p-> pR.programme = extrainfo;
  }
  else if(job==staff){
    p->pR.room = extrainfo;
  }
  
  struct person **ptr2ptr = head;//move along the linked list to compare
  while(*ptr2ptr != NULL && (*compare_people)(*ptr2ptr, p)<0){
    ptr2ptr = &(*ptr2ptr)->next;
  }
  p->next = *ptr2ptr;
  *ptr2ptr = p;

}

void print_list(struct person *head) {
  
    while(head!=NULL){
      if(head->job == student){
        printf("Name: %s, Age: %d, Job: Student, Programme Name: %s\n", head->name, head->age, head->pR.programme);
      }
      else if(head->job == staff){
        printf("Name: %s, Age: %d, Job: Staff, Room: %s\n", head->name, head->age, head->pR.room);
      }
      else{
        printf("Name: %s, Age: %d\n", head->name, head->age);
      }
      head = head->next;
    }
  
}

void free_list(struct person *head) {
  
  struct person *temp;
  while(head != NULL){
    temp = head;
    head = head->next;
    free(temp);
  }
  
}
  
int main(int argc, char **argv) {

  int i;
  struct person *head;

  head = NULL;
  
  for(i=0;i<HOW_MANY;i++){
    insert_sorted(&head, names[i], ages[i], job[i], extrainfo[i], compare_people_by_age);
  }

  print_list(head);
  
  free_list(head); 

  return 0;
}
