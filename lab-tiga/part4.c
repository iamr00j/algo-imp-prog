//A program that will convert temperatures between Celsius and Fahrenheit,
// and is controlled by program parameters

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float c2f(float c){
    return (9*c/5+32);
}

float f2c(float f){
    return (5*(f-32)/9);
}

int main(int argc, char *argv[]){
    float temperature=0;
    float input;
    
    if(argc!=3){
        printf("Please enter only three parameters, the flag and the temperature to convert.\n");
        return 0;
    }
    
    input = atof(argv[2]);
    
    if(strcmp(argv[1],"-f")!=0 && strcmp(argv[1],"-c")!=0){
        printf("Please input either -f or -c as flags.\n");
        return 0;
    }

    if(strcmp(argv[1], "-f") == 0){
        if(input<-459.67){
            printf("Temperatures below absolute zero, ie below -459.67 F, cannot be converted to C.\n");
            return 0;
        }
        temperature = f2c(input);
        printf("%.2f C = %.2f F\n", temperature, input);
        return 0;
    } 
    else if(strcmp(argv[1], "-c") == 0){
        if(input < -273.15){
            printf("Temperatures below absolute zero, ie below -273.15 C, cannot be converted to F.\n");
            return 0;
        }
        temperature = c2f(input);
        printf("%.2f C = %.2f F\n", input, temperature);
        return 0;    
    }
    else{
        printf("Please enter valid flag.\n");
    }

    return 0;
}