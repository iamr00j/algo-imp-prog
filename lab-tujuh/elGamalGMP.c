#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

#define MAX_LENGTH 1000

typedef struct encrypted_message {
    mpz_t a, b;
} encrypted_message;

/* encrypt message in the form of (a,b)
    * p = prime modulus, 
    * g = prim

encrypted_message encrypt(mpz_t g, mpz_t k, mpz_t p, mpz_t y, mpz_t M){

    encrypted_message E;
    mpz_init(E.a);
    mpz_init(E.b);    

    mpz_powm (E.a, g, k, p);
    mpz_powm (E.b, y, k, p);
    mpz_mul (E.b, E.b, M);
    mpz_mod (E.b, E.b, p);
    
    return E;
}

void test_encrypt(){
    mpz_t g, k, p, y;
    encrypted_message E;
    mpz_init (g);
    mpz_init (k);
    mpz_init (p);
    mpz_init (y);
    mpz_init(E.a);
    mpz_init(E.b);
    
    // ...
    E = encrypt(g, k, p, y...)
}
*/
int main(int argc, char **agrv){
    char *input = malloc(MAX_LENGTH*sizeof(char));
  	if(input ==NULL){
  		fprintf(stderr, "malloc error!\n");
  		return 1;
  	}
    int rndBit = 4;
    mpz_t a, b, M, p, g, x, y, m, a_inv, randNum, k, p1, phi;
    mpz_init (a);
    mpz_init (b);
    mpz_init (M);
    mpz_init (p);
    mpz_init (g);
    mpz_init (x);
    mpz_init (y);
    mpz_init (m);
    mpz_init (a_inv);
    mpz_init (p1);
    mpz_init (k);
    mpz_init (phi);
    mpz_set_str(p, "17", 10);
    mpz_set_str(g, "3", 10);
    gmp_randstate_t rstate;
    gmp_randinit_default(rstate);
    gmp_randseed_ui (rstate, 123456);
    mpz_init (randNum);
    mpz_urandomb(randNum, rstate, rndBit);
    gmp_printf("%Zd\n", randNum);
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
            mpz_powm (y, g, x, p);//y = fme(g, x, p)
            gmp_printf ("Public key is: %Zd\n", y);
        }
        
        else if(strcmp(input, "e")==0){
            printf("\nKey in message to encrypt.\n");
            fgets(input, MAX_LENGTH, stdin);
            gmp_sscanf (input, "%Zd", &M);
            gmp_printf("testing M, %Zd\n", M);
            printf("Enter public key:\n");
            fgets(input, MAX_LENGTH, stdin);
            gmp_sscanf(input, "%Zd", &y);
            mpz_sub_ui (p, p, 3);
            mpz_mod (randNum, randNum, p);//long k = rand()% (p-1) + 1;
            mpz_add_ui (k, randNum, 1);
            mpz_powm (a, g, k, p);//a = fme(g,k,p);
            mpz_powm (b, y, k, p); //b = (M*y^k) % p
            mpz_mul (b, b, M);  
            mpz_mod (b, b, p);
            gmp_printf("The encrypted secret is: (%Zd, %Zd).\n", a, b);
        }
        else if(strcmp(input, "d")==0){
            printf("Enter cypher-text in the form of (a,b).\n");
            fgets(input, MAX_LENGTH, stdin);
            char *text_a = strtok(input+1, ",");
            char *text_b = strtok(NULL, ",");
            text_b[strlen(text_b) - 1] = 0;
            gmp_sscanf(text_a, "%Zd", &a);
            gmp_sscanf(text_b, "%Zd", &b);
            printf("Enter your private key:\n");
            fgets(input, MAX_LENGTH, stdin);
            gmp_sscanf(input, "%Zd", &x);
            mpz_sub_ui(x, x, 1);
            mpz_sub (phi, p, x);
            mpz_powm (a_inv, a, phi, p); //long a_inv = fme(a, p-x-1, p);
            mpz_mul (b, b, a_inv);
            mpz_mod (m, b, p);//long m = (b*a_inv) % p;
            gmp_printf("The decrypted secret is %Zd.\n", m);
        }
        else if(strcmp(input, "x")==0){
            break;
        }
    }
    free(input);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(M);
    mpz_clear(p);
    mpz_clear(g);
    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(m);
    mpz_clear(p1);
    mpz_clear(k);
    mpz_clear(phi);
    mpz_clear(a_inv);
    mpz_clear(randNum);
    gmp_randclear(rstate);
    
    return 0;
}