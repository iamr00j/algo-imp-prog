#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gmp.h>

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
unsigned long fme(unsigned long g, unsigned long x, mpz_t p){
    
    mpz_t d, e, s, s1, d1;
    mpz_init (d);
    mpz_init (e);
    mpz_init (s);
    mpz_init (s1);
    mpz_init (d1);
    mpz_set_d (d, g);
    mpz_set_d (e, x);
    mpz_set_d (s, 1);

    //until e=0
    while(e!=0){
        if(e % 2 != 0)
            mpz_mul (s, s, d) //s = (s*d)
            mps_mod (s1, s, p) // s1 = s % p
        mpz_mul (d, d, d); // d= (d*d)
        mpz_mod (d1, d, p); // d1 = d%p
        mpz_tdiv_e (e, e, 2); // e = e/2;
    }
    
    mpz_clear (d);
    mpz_clear (g);
    mpz_clear (e);
    mpz_clear (x);
    mpz_clear (s);
    mpz_clear (s1);
    mpz_clear (d1);
    
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
    mpz_t a, b, M, p, x, y, m, a_inv;
    mpz_init (a);
    mpz_init (b);
    mpz_init (M);
    mpz_init (p);
    mpz_init (x);
    mpz_init (y);
    mpz_init (m);
    mpz_init (a_inv);
    mpz_set_str(p, "65537", 10);
    mpz_set_str(g, "3", 10);

    srand(time(NULL));
    gmp_printf("Prime modulus is %Zd\n", p);
    gmp_printf("Primitive root wrt %Zd is %Zd\n", p, g);
    
    while(1){
        printf("Choose: e (encrypt) | d (decrypt) | k (obtain public key) | x (exit)?\n");
        fgets(input, MAX_LENGTH, stdin);
        strtok(input, "\n");

        if(strcmp(input, "k")==0){
            printf("\nKey in private key:\n");
            fgets(input, MAX_LENGTH, stdin);
            gmp_sscanf(input, "%Zd", &x);
            gmp_powm (y, g, x, p);//y = fme(g, x, p)
            gmp_printf ("Public key is: %Zd\n", y);
        }
        
        else if(strcmp(input, "e")==0){
            printf("\nKey in message to encrypt.\n");
            fgets(input, MAX_LENGTH, stdin);
            gmp_sscanf (input, "%Zd", &M);
            printf("Enter public key:\n");
            fgets(input, MAX_LENGTH, stdin);
            gmp_sscanf(input, "%Zd", &y);
            long k = rand()% (p-1) + 1;
            gmp_powm (a, g, k, p); //a = fme(g,k,p);
            gmp_powm (b, y, k, p); //b = fme(y,k,p);
            gmp_mul (M, M, b);//b = (M*b) % p;
            gmp_mod (b, M, p);
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
            gmp_powm (a_inv, a, p-x-1, p); //long a_inv = fme(a, p-x-1, p);
            gmp_mul (b, b, a_inv);//long m = (b*a_inv) % p;
            gmp_mod (m, b, p);
            gmp_printf("The decrypted secret is %ld.\n", m);
        }
        else if(strcmp(input, "x")==0){
            break;
        }
    }
    mpz_clear(input);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(M);
    mpz_clear(p);
    mpz_clear(g);
    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(m);
    mpz_clear(a_inv);
    
    return 0;
}