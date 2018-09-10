// A program that writes the longest to standard output given any number of program parameters.

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

/* if no strings, prompt user to input strings.
store strings into a variable. calculate string length. make the first string the longest string.
compare the first string with other strings. */

    char *strLongest;
    int noOfMaxStr = 0;
    int strLength = 0;
    int i;
    
    for(i=1; i<argc; i++){
   
     if(strlen(argv[i]) == strLongest){
      noOfMaxStr++;
     }
     else if(strlen(argv[i])>strLongest){
      strLongest = argv[i];
      strLength = argv[i];
      noOfMaxStr = 1;
     }
    }
    
    if(strlen(argv[i]) == 0){
     printf("No strings given, please enter string.\n");
     printf("\n");
     }
    else if(noOfMaxStr>1){
     printf("There are %d strings of the same length, including %s", noOfMaxStr, strLongest);
     printf("\n");
     }
    else{
     printf("The longest string is %s.", strLongest);
     printf("\n");
     }
    
    return 0;

}
    