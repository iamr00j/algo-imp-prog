#include <stdio.h>
#include <stdlib.h>

/* these arrays are just used to give the parameters to 'insert',
   to create the 'people' array 
*/
#define HOW_MANY 7
char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
		      "Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};

/* declare your struct for a person here */
struct person{
  char *name;
  int age;
};//struct 

int memory = (sizeof(struct person));

static void insert(struct person **array, char *name, int age) {
  
  static int nextfreeplace = 0;
  printf("insert: function running with argument name=%s, age=%d, nextfreeplace=%d\n", name, age, nextfreeplace);

  /* put name and age into the next free place in the array parameter here */
  /* modify nextfreeplace here */
  struct person *p= (struct person*)malloc(memory);
  if(p==NULL){
    printf("Oops! Not enough memory!");
    exit(1);
  }
  p->name = name;
  p->age = age;
  array[nextfreeplace] = p;
  nextfreeplace += 1;
}

int main(int argc, char **argv) {

  int i;
  /* declare the people array here */
  struct person *people[HOW_MANY];
  
  for(i=0;i<HOW_MANY;i++){
    insert(people, names[i], ages[i]);
  }
  
  /* print the people array here*/
  for(i=0;i<HOW_MANY;i++){
    printf("Name:%s, Age:%d\n", people[i]->name, people[i]->age);
  }
  
  for(i=0;i<HOW_MANY;i++){
    free(people[i]);
  }
}
