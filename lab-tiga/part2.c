// A program that will print chessboards of any size
#include <stdio.h>

enum square{White, Black};

void chessBoard(int rows, int columns, int array[rows][columns]){ // Z
    int row; // A
    int column; // B
    enum square colour = White;
    
    for(row=0; row < rows; row++){
        
        if ((row % 2) == 0) { // H
            colour = White;
        } else {
            colour = Black;
        }
        
        for(column=0; column < columns; column++){
            switch(colour){
                case White: 
                    array[row][column]=0;
                    break;
                case Black:
                    array[row][column]=1;
                    break;
            }//switch
            
            if (colour == White) { // I
                colour = Black;
            } else {
                colour = White;
            }
        }//for
    }//for
}//board

int main(void){
    int row; // C
    int column; // D
    
    int board1[5][5];
    chessBoard(5,5,board1);
    for(row=0; row<5; row++) {
        for(column=0; column<5; column++) {
            switch (board1[row][column]) {
                case 0:
                printf("0");
                break;
                case 1:
                printf("1");
                break;
            }
        }
        printf("\n");
    }
    printf("\n");
    
    int board2[10][3];
    chessBoard(10,3,board2);
    for(row=0; row<10; row++) {
        for(column=0; column<3; column++) {
            switch (board2[row][column]) { // L
                case 0:
                printf("0");
                break;
                case 1:
                printf("1");
                break;
            }
        }
        printf("\n");
    }
    printf("\n");
    
    int board3[2][12];
    chessBoard(2,12,board3);
    for(row=0; row<2; row++) {
        for(column=0; column<12; column++) {
            switch (board3[row][column]) { // L
                case 0:
                printf("0");
                break;
                case 1:
                printf("1");
                break;
            }
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}