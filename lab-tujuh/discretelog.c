#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 1000

//compute function g^x mod p using fast modular exoponentiaton (fme)
unsigned long fme(unsigned long g, unsigned long x, unsigned long p){
    long d = g;
    long e = x;
    long s = 1;
    //until e=0
    while(e!=0){
        if(e % 2 != 0)
            s = (s*d) % p;
        d = (d*d) % p;
        e = e/2;
    }
    return s;
}

//compute, for a given y the unique integer x such that y=g^x mod p using discrete logarithm (dl)
unsigned long dl(unsigned long y, unsigned long g, unsigned long p){
    long answer =0;
    for(long x = 1; x < p; x++){
        //if g^x mod p =y, then x is our solution
        if(fme(g, x, p) ==y)
            answer = x;
    }
    return answer;
}

int main(int argc, char **argv){

    char *input;
    long g;
    long p;
    long y;
    
    input = malloc(MAX_LENGTH*sizeof(char));
    if(input == NULL)
        fprintf(stderr, "Malloc error!\n");
    
    printf("Testing dl function\n");
    
    printf("Key in base number:\n");
    fgets(input, MAX_LENGTH, stdin);
    sscanf(input, "%ld", &g);
    printf("Key in remainder:\n");
    fgets(input, MAX_LENGTH, stdin);
    sscanf(input, "%ld", &y);
    printf("Key in modulus:\n");
    fgets(input, MAX_LENGTH, stdin);
    sscanf(input, "%ld", &p);
    
    printf(" %ld = %ld^%ld mod %ld\n", y, g,dl(y,g,p) ,p);
    
    return 0;

}
