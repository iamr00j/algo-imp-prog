/* A program reading characters from stdin, convert all upper characters to lower 
and all lower characters to upper, and write the result to stdout */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLEN 1000

int main(void)
{
 char *buffer;
 int index=0;
 int ch=0;
 int uppercase=0;
 int lowercase=0;
 printf("Enter string:\n");

 buffer = malloc(MAXLEN);

 while((ch=getchar())!='\0'){

 if(isupper(ch))
 {
  putchar(tolower(ch));
  lowercase++;
 }

 else if(islower(ch))
 {
  putchar(toupper(ch));
  uppercase++;
 }
 
 else
 {
  putchar(ch);
  index++;
 }
 printf("\nRead %d characters in total, %d converted to upper-case, %d to lower-case", index+1, uppercase, lowercase);

return 0;
}
}
