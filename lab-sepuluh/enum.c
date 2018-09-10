// http://syllabus.cs.manchester.ac.uk/ugt/2017/COMP26120/lab/ex10.html
// enum - full enumeration of knapsack solutions
// (C) Joshua Knowles

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

FILE *fp;  // file pointer for reading the input files
int Capacity;     // capacity of the knapsack (total weight that can be stored)
int Nitems;    // number of items available
int *item_weights;  // vector of item weights
int *item_values;  // vector of item profits or values
int *temp_indexes;  // list of temporary item indexes for sorting items by value/weight
int QUIET=1; // this can be set to 1 to suppress output

extern void read_knapsack_instance(char *filename);
extern void print_instance();
extern void sort_by_ratio();
extern int check_evaluate_and_print_sol(int *sol,  int *total_value, int *total_weight);
void enumerate();
int next_binary(int *str, int Nitems);

int main(int argc, char *argv[])
{
  read_knapsack_instance(argv[1]);
  print_instance();
  enumerate();
  return(0);
}

void enumerate()
{
  // Do an exhaustive search (aka enumeration) of all possible ways to pack
  // the knapsack.
  // This is achieved by creating every binary solution vector of length Nitems.
  // For each solution vector, its value and weight is calculated.


  int i;  // item index
  int solution[Nitems+1];   // (binary) solution vector representing items packed
  int best_solution[Nitems+1];  // (binary) solution vector for best solution found
  int best_value; // total value packed in the best solution
  double j=0;
  int total_value, total_weight; // total value and total weight of current knapsack solution
  int infeasible;  // 0 means feasible; -1 means infeasible (violates the capacity constraint)

  // set the knapsack initially empty
  for(i=1;i<=Nitems;i++)
    {
      solution[i]=0;
    }
  best_value=0;
  int count = 1;
  int best_weight;

 while(!(next_binary(&solution[1], Nitems)))
    {

      /* ADD CODE IN HERE TO KEEP TRACK OF FRACTION OF ENUMERATION DONE */
      int total = (int)pow(2, Nitems);
      if(!QUIET){
        count++;
        printf("Progress: %d / %d \n", count, total);
      }
          // calculates the value and weight and feasibility:
      infeasible=check_evaluate_and_print_sol(solution, &total_value, &total_weight);  
      /* ADD CODE IN HERE TO KEEP TRACK OF BEST SOLUTION FOUND*/
      if(infeasible == 0){
        if(total_value >= best_value){
          for(int i = 1 ; i<=Nitems; i++)
            best_solution[i] = solution[i];
          best_value = total_value;
          best_weight = total_weight;
        }
      }
    }
      
 /* ADD CODE TO PRINT OUT BEST SOLUTION */
  printf("Best solution:\n");
  int pack[Nitems];
  for(i=1;i<=Nitems;i++){
    if(best_solution[i]==1)
      pack[temp_indexes[i]]=1;
    else
      pack[temp_indexes[i]]=0;
  }
 
  printf("Item \tWeight\tValue\n");
  for(i=1;i<=Nitems;i++){
    if(pack[i]==1){
      printf("%d \t %d \t %d\n", i, item_weights[i], item_values[i]);
    }
  }
  printf("Total weight: %d\n", best_weight);
  printf("Total value: %d\n", best_value);
}


int next_binary(int *str, int Nitems)
{
  // Called with a binary string of length Nitems, this 
  // function adds "1" to the string, e.g. 0001 would turn to 0010.
  // If the string overflows, then the function returns 1, else it returns 0.
  int i=Nitems-1;
  while(i>=0)
    {
      if(str[i]==1)
	{
	  str[i]=0;
	  i--;
	}
      else
	{
	  str[i]=1;
	  break;
	}
    }
  if(i==-1)
    {
      return(1);
    }
  else
    {
      return(0);
    }
}
