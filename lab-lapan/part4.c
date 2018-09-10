//http://syllabus.cs.manchester.ac.uk/ugt/2017/COMP26120/lab/ex8.html
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_LENGTH 1000

FILE *fp;

typedef struct book
{
  double rating;
  double price;
  double relevance;
  int ID;
  int rank;
  char author[MAX_LENGTH];
  char title[MAX_LENGTH];
} B;

B *list;

int read_file(char *infile, int N)
{
  int c;
  if((fp=fopen(infile, "rb")))
    {
      fscanf(fp, "%*s\t%*s\t%*s\t%*s\t%*s\t%*s\t%*s\n");
      c=0;
      while((!feof(fp))&&(c<N))
	{
	  fscanf(fp, "%lf\t%lf\t%lf\t%d\t%d\t%s\t%s\n", &list[c].rating,  &list[c].price, &list[c].relevance, &list[c].ID, &list[c].rank, list[c].title, list[c].author);	
	  c++;
	}
      fclose(fp);      
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",infile);
      exit(-1);
    }
  return(c);
}

int comp_on_rating(const void *a, const void *b)
{
  if ((*(B *)a).rating < (*(B *)b).rating)
  {  
     return -1;
  }
    else 
  {
    if ((*(B *)a).rating > (*(B *)b).rating)
    {
      return 1;
    }
      else
    {
      return 0;
    }
  }  
}

int comp_on_relev(const void *a, const void *b)
{
 
  if ((*(B *)a).relevance < (*(B *)b).relevance)
  {  
     return -1;
  }
     else 
  {
     if ((*(B *)a).relevance > (*(B *)b).relevance)
     { 
       return 1;
     }
       else
     {
       return 0;
     }
  }  
}

int comp_on_price(const void *a, const void *b)
{
 
  if ((*(B *)a).price < (*(B *)b).price)
  { 
     return 1;
  }
     else 
  {
     if ((*(B *)a).price > (*(B *)b).price)
     {
       return -1;
     }
       else
     {
       return 0;
     }
  }  
}

int comp_on_rank(const void *a, const void *b)
{
 
  if ((*(B *)a).rank < (*(B *)b).rank)
  { 
     return 1;
  }
     else 
  {
     if ((*(B *)a).rank > (*(B *)b).rank)
     {
       return -1;
     }
       else
     {
       return 0;
     }
  }  
}

int comp_on_author(const void *a, const void *b)
{
 
  if (strcmp((*(B *)a).author, (*(B *)b).author) < 0)
  { 
     return 1;
  }
  else 
  {
     if (strcmp((*(B *)a).author, (*(B *)b).author) > 0)
     {
       return -1;
     }
       else
     {
       return 0;
     }
  }  
}

int comp_on_title(const void *a, const void *b)
{
 
  if (strcmp((*(B *)a).title, (*(B *)b).title) < 0)
  { 
     return 1;
  }
  else 
  {
     if (strcmp((*(B *)a).title, (*(B *)b).title) > 0)
     {
       return -1;
     }
       else
     {
       return 0;
     }
  }  
}

/* function to compare two temporary structures, and merge them into sorted list adapted from
lecture notes, http://www.geeksforgeeks.org/merge-sort/ 
and https://en.wikipedia.org/wiki/Merge_sort
int n1 refers to size of temp1, int n2 size of temp2 */
void merge(B *temp1, int n1, B *temp2, int n2, B *initlist, 
						int (*compar)(const void *, const void *)){

	int ptr = 0; //pointer for initlist
	int ptr1 = 0; //pointer for temp1
	int ptr2 = 0; //pointer for temp2
	
	while(ptr1 < n1 && ptr2 < n2){
		if((*compar)(&temp1[ptr1] , &temp2[ptr2]) <= 0){
			initlist[ptr] = temp1[ptr1];
			ptr1++;
			ptr++;
		}
		else{
			initlist[ptr] = temp2[ptr2];
			ptr2++;
			ptr++;
		}
	}
	
	//copy the remaining elements of temp1[], if there are any
	while(ptr1 < n1){
		initlist[ptr] = temp1[ptr1];
		ptr1++;
		ptr++;
	}
	
	//copy the remaining elements of temp2[], if there are any
	while(ptr2 < n2){
		initlist[ptr] = temp2[ptr2];
		ptr2++;
		ptr++;
	}
}

void mysort(B *initlist, int n, int(*compar)(const void *, const void *)){

	//if n <=1, return sorted list
	if(n <= 1)
		return;
	
	//split list into two roughly equal halves, initlist = initlistL + initListR
	int n1 = n/2;
	int n2 = n - n1;
	int i;
	
	B *temp1 = (B *)malloc(n1*sizeof(B));
	B *temp2 = (B *)malloc(n2*sizeof(B));
	if (temp1 == NULL || temp2 == NULL){
		fprintf(stderr, "malloc error!\n");
	}
	
	//copy elements into respective list
	for(i = 0; i < n1; i++){
		temp1[i] = initlist[i];
	}
	for(i = 0; i < n2; i++){
		temp2[i] = initlist[i + n1];
	}
	
	//sort first and second halves
	mysort(temp1, n1, *compar);
	mysort(temp2, n2, *compar);
	
	//merge the sorted list
	merge(temp1, n1, temp2, n2, initlist, *compar);
	
	free(temp1);
	free(temp2);
} 

/* 
function to return a unique integer based on choice to sort search result.
1 to sort by rating
2 to sort by relevance
3 to sort by price
4 to sort by ranking
5 to sort by author
6 to sort by title
*/
int get_choice(char *choice){

	if(strcmp(choice, "rating") == 0){
		return 1;
	}
	else if(strcmp(choice, "relevance") == 0){
		return 2;
	}
	else if(strcmp(choice, "price") == 0){
		return 3;
	}
	else if(strcmp(choice, "ranking") == 0){
		return 4;
	}
  else if(strcmp(choice, "author") == 0){
		return 5;
	}
	else if(strcmp(choice, "title") == 0){
		return 6;
	}
	else{
		return 0;
	}
}

//function to sort list based on choice
void sort_by_choice(int choice, int n){
	
	if(choice == 1){
		mysort(list, n, *comp_on_rating);
	}
	else if(choice == 2){
		mysort(list, n, *comp_on_relev);
	}
	else if(choice == 3){
		mysort(list, n, *comp_on_price);
	}
	else if(choice == 4){
  	mysort(list, n, *comp_on_rank);
	}
	else if(choice == 5){
		mysort(list, n, *comp_on_author);
	}
	else if(choice == 6){
		mysort(list, n, *comp_on_title);
	}
}

// For Part 2 this function
// (1) asks the user if they would like to sort their search results
// (2) asks for the most important field (or key), the next most etc
// (3) calls your sort function
void user_interface(int N)
{
  int mostimportant;
  int secondmost;
  int leastimportant;
  char *input = malloc(MAX_LENGTH*sizeof(char));
    if(input == NULL)
      fprintf(stderr, "Malloc error!\n");
  
  printf("Would you like to do a lexicographic sort?\n");
  fgets(input, MAX_LENGTH, stdin);
  strtok(input, "\n");
  if(strcmp(input, "yes") == 0){
    printf("Which is the most important field? rating, relevance, price, ranking, author, or title?\n");
    fgets(input, MAX_LENGTH, stdin);
    strtok(input, "\n");
    mostimportant = get_choice(input);
    
    printf("Which is the second most important field?\n");
    fgets(input, MAX_LENGTH, stdin);
    strtok(input, "\n");
    secondmost = get_choice(input);
    
    if(mostimportant + secondmost == 3)
      leastimportant = 3;
    else if(mostimportant + secondmost == 4)
      leastimportant = 2;
    else if(mostimportant + secondmost == 5)
      leastimportant = 1;
    
      sort_by_choice(mostimportant, N);
      sort_by_choice(secondmost, N);
      sort_by_choice(leastimportant, N);
  }
  else{
    return;
  }
}
 
void print_results(int N)
{
    int i;
    if((fp=fopen("top20.txt","w")))
    {
      printf("Stars\t Price\t Relev\t ID\t Rank\t Author\t Title\n");
      fprintf(fp, "Stars\t Price\t Relevance\t ID\t Rank\t Author\t Title\n");
      for(i=N-1;i>=N-20;i--)
      {  
	  printf("%g\t %g\t %g\t %d\t %d\t %s\t %s\n", list[i].rating, list[i].price, list[i].relevance, list[i].ID, list[i].rank, list[i].author, list[i].title);
	  fprintf(fp, "%g\t %g\t %g\t %d\t %d\t %s\t %s\n", list[i].rating, list[i].price, list[i].relevance, list[i].ID, list[i].rank, list[i].author, list[i].title);
	  
      }
      fclose(fp);
    }
      else
    {
      fprintf(stderr,"Trouble opening output file top20.txt\n");
      exit(-1);
    }

}

int main(int argc, char *argv[])
{
  int N;

  if(argc!=3)
    {
      fprintf(stderr, "./exec <input_size> <filename>\n");
      exit(-1);
    }

  N=atoi(argv[1]);

  list = (B *)malloc(N*sizeof(B));
  
  N=read_file(argv[2], N);
  
  user_interface(N);
  
  print_results(N);
  
  return(0);
}
