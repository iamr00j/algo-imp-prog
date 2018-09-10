// http://syllabus.cs.manchester.ac.uk/ugt/2017/COMP26120/lab/elGamal_lab_revised.pdf
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_LENGTH 1000

//compute the highest common factor (hcf) of a and b
unsigned long hcf(unsigned long a, unsigned long b){
    
    if(b==0)
        return a;
    else{
        long r = a % b;
        return hcf(b,r);
    }
}

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

//return the unique integer x for a given y, such that xy=1 mod p using inverse modulo prime (imp)
unsigned long imp(unsigned long y, unsigned long p){
    long phi_m =0;
    // for m in the range of 1 to p-1, if the hcf of m and p is 1, phi_m++
    for(long m = 1; m<p; m++){
        if (hcf(m,p) == 1)
            phi_m++;
    }
    //The inverse modulo prime, x can be obtained using the formula
    //(y^(phi_m-1)) mod p
    return fme(y, phi_m-1, p);
}

int main(int argc, char **agrv){
    char *input;
    long p = 65537;
    long g = 3;
    long x;//private key
    long y;//public key
    long a;
    long b;
    long M;
    
    input = malloc(MAX_LENGTH*sizeof(char));
    if(input == NULL){
        fprintf(stderr, "Malloc error!\n");
        return 1;
    }
    
    srand(time(NULL));
    printf("Prime modulus is %ld\n", p);
    printf("Primitive root wrt %ld is %ld\n", p, g);
    
    while(1){
        printf("Choose: e (encrypt) | d (decrypt) | k (obtain public key) | x (exit)?\n");
        fgets(input, MAX_LENGTH, stdin);
        strtok(input, "\n");

        if(strcmp(input, "k")==0){
            printf("\nKey in private key:\n");
            fgets(input, MAX_LENGTH, stdin);
            sscanf(input, "%ld", &x);
            y = fme(g, x, p);
            printf("Public key is: %ld\n", y);
        }
        
        else if(strcmp(input, "e")==0){
            printf("\nKey in message to encrypt.\n");
            fgets(input, MAX_LENGTH, stdin);
            sscanf(input, "%ld", &M);
            printf("Enter public key:\n");
            fgets(input, MAX_LENGTH, stdin);
            sscanf(input, "%ld", &y);
            long k = (rand()%(p-2-1)+ 1);
            a = fme(g,k,p);
            b = fme(y,k,p);
            b = (M*b) % p;
            printf("The encrypted secret is: (%ld, %ld).\n", a, b);
        }
        else if(strcmp(input, "d")==0){
            printf("Enter cypher-text in the form of (a,b).\n");
            fgets(input, MAX_LENGTH, stdin);
            char *text_a = strtok(input+1, ",");
            char *text_b = strtok(NULL, ",");
            text_b[strlen(text_b) - 1] = 0;
            sscanf(text_a, "%ld", &a);
            sscanf(text_b, "%ld", &b);
            printf("Enter your private key:\n");
            fgets(input, MAX_LENGTH, stdin);
            sscanf(input, "%ld", &x);
            long a_inv = fme(a, p - x - 1, p);
            long m = (b*a_inv) % p;
            printf("The decrypted secret is %ld.\n", m);
        }
        else if(strcmp(input, "x")==0){
            break;
        }
    }
    free(input);
    
    return 0;
}