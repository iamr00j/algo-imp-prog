//A program that will find the largest integer in an array
#include<stdio.h>

int largest(int array[], int length){
 int index=0;
 int largest=array[0]; //Initialise first element in the array as largest
 int i=0;
 
  for(i=0; i<length;i++){
  if(array[i]>largest){
   largest = array[i];
   index=i;
   }//if
  }//for
  return index;
 }//index
  
int main(void){

 int array1[5]={100, 5, 1, 17,31};
 int index1=largest(array1,5);
 int maximum1 = array1[index1];

 int array2[7]={-17,24,3,-16,26,25,17};
 int index2=largest(array2,7);
 int maximum2 = array2[index2];

 int array3[10]={-60,-21,-58,-22,-30,-25,-27,-100,-40,-4};
 int index3=largest(array3,10);
 int maximum3 = array3[index3];

 printf("The largest element in the array is %d, integer %d.\n", index1, maximum1);
 printf("The largest element in the array is %d, integer %d.\n", index2, maximum2);
 printf("The largest element in the array is %d, integer %d.\n", index3, maximum3);

 return 0;

}//main
