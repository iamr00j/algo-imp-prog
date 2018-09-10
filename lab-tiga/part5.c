/* A program that, given a file-name as a program parameter, 
will read from it to count how many instances of each different character are in the file, 
and then output the counts. 
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 
 FILE *input;
 
 char *file=argv[1];
 char characters[256]={0};
 int character=0;
 int ch=0;
 int index=0;
 
 input=fopen(file,"r");
 
 if(argc!=2){
 fprintf(stderr, "Enter the file name, to read.\n");
 exit(0);
 }//if
 
 while((ch=fgetc(input))!=EOF){
 
 characters[ch] += 1;
 
 }//while 
 
  for(index=0;index<256;index++){
   if(characters[index]>1){
    character = index;
    printf("%2d instances of character 0x%x (%c)\n", characters[index], character, character);
   }//if
   
   else if(characters[index]==1){
    character = index;
    printf("%2d instance of character 0x%x (%c)\n", characters[index], character, character);
   }//else if
   
  }//for
  
 return 0;

}//main
 
 
