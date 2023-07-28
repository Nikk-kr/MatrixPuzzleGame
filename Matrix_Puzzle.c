#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<conio.h>

const int ROWS = 4;
const int COLS = 4;

void assign_element(int array[ROWS][COLS]);
void printRules(int array[ROWS][COLS]);
void print_matrix(int array[ROWS][COLS]);
void shuffle(int array[ROWS][COLS]);
int user_input();
int winner(int array[ROWS][COLS]);
void swap(int *p,int *q);
int shift_left(int array[ROWS][COLS]);
int shift_Right(int array[ROWS][COLS]);
int shift_up(int array[ROWS][COLS]);
int shift_down(int array[ROWS][COLS]);

void printRules(int array[ROWS][COLS]){
    system("cls");
    printf("\t\tMATRIX PUZZLE\n");
    printf("\n\t\tRULES OF THIS GAME");
    printf("\n1.You can move only 1 step at a time by arrow key:");
    printf("\n\tMove Up.   : by Up arrow key");
    printf("\n\tMove Down  : by Down arrow key");
    printf("\n\tMove Left  : by Left arrow key");
    printf("\n\tMove Right : by Right arrow key");
    printf("\n2.You can move number at empty position only\n");
    printf("\n3.For each valid move : Your total number move will decreased by 1");
    printf("\n4.Winning situation : Number in a 4*4 matrix should be in order from 1 to 15");
    printf("\n\n\tWinning Situation:\n");
    print_matrix(array);
    printf("\n\n5.You can exit the game at any time by pressing 'E' or 'e'");
    printf("\nSo try to win in minimum number of move");
    printf("\n\n\tHappy gaming, Good luck");
    printf("\n\nPress any key to start...");
    user_input();
}

void assign_element(int array[ROWS][COLS]){
    int value = 1;
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            if(i == 3 && j == 3)
                array[i][j] = 0;
            else
                array[i][j] = value++;
        }
    }
}

void print_matrix(int array[ROWS][COLS]){
    int i,j;
    printf("---------------------\n");
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            if(array[i][j] != 0)
                printf("| %2d ",array[i][j]);
            else
                printf("|    ");
        }
        printf("|");
        printf("\n");
    }
    printf("---------------------\n");
}

void shuffle(int array[ROWS][COLS]){
    int rand_row = 0;
    int rand_col = 0;
    int temp;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            rand_row = rand() % ROWS;
            rand_col = rand() % COLS;

            if(i == 3 && j == 3 || rand_row == 3 && rand_col == 3)
                continue;
            else{
                temp = array[i][j];
                array[i][j] = array[rand_row][rand_col];
                array[rand_row][rand_col] = temp;
            }
        }
    }
}

int user_input(){
    char input;
    input = _getch();
    if(input == -32)
        input = _getch();
    return input;
}
int winner(int array[ROWS][COLS] ){
    int i,j,k=1;
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++, k++){
            if(i == 3 && j == 3)
                k = 0;
            if(array[i][j] != k)
                break;
        }
        if(j < COLS)
            break;
    }
    if(j < COLS)
        return 0;
    return 1;
}

void swap(int *p,int *q){
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

int shift_left(int array[ROWS][COLS]){
    int i,j;
    for(i = 0; i<ROWS; i++){
        for(j = 0; j < COLS; j++){
            if(array[i][j] == 0)
                break;
        }
        if(j < COLS)
            break;
    }
    if(j == 3)
        return 0;
    swap(&array[i][j],&array[i][j+1]);
    return 1;
}

int shift_Right(int array[ROWS][COLS]){
    int i,j;
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            if(array[i][j] == 0)
                break;
        }
        if(j < COLS)
            break;
    }
    if(j == 0)
        return 0;
    swap(&array[i][j],&array[i][j-1]);
    return 1;
}

int shift_up(int array[ROWS][COLS]){
    int i,j;
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            if(array[i][j] == 0)
                break;
        }
        if(j < COLS)
            break;
    }
    if(i == 3)
        return 0;
    swap(&array[i][j],&array[i+1][j]);
    return 1;
}

int shift_down(int array[ROWS][COLS]){
    int i,j;
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            if(array[i][j] == 0)
                break;
        }
        if(j < COLS)
            break;
    }
    if(i == 0)
        return 0;
    swap(&array[i][j],&array[i-1][j]);
    return 1;
}

int main(){
    char name[20];
    int input,array[ROWS][COLS],move=20;
    printf("Player Name:");
    fgets(name,20,stdin);
    name[strlen(name)-1]='\0';
    assign_element(array);
    system("cls");
    printRules(array);
    while(1){
        assign_element(array);
        srand(time(NULL) * getpid());
        shuffle(array);
        while(!winner(array)){
            system("cls");
            printf("Player Name: %s,  Move remaining: %d\n\n",name,move);
            print_matrix(array);
            if(!move)
                break;
            int key = user_input();
            switch(key){
                case 69:
                case 101:
                    printf("\n     Thanks for Playing ! \n");
                    printf("\nHit 'Enter' to exit the game \n");
                    key = user_input();
                    return 0;
                case 75:
                    if(shift_left(array))
                        --move;
                    break;
                case 77:
                    if(shift_Right(array))
                        --move;
                    break;
                case 72:
                    if(shift_up(array))
                        --move;
                    break;
                case 80:
                    if(shift_down(array))
                        --move;
                    break;
                default:
                    printf("\n\t\tInvalid input");
            }
        }
        if(!move)
            printf("\n\t\t You Lose");
        else
            printf("\n\t\t****You Win****");
        char check;
        printf("\n\t\tDo you want to play again?");
        printf("\n\t\t Press 'Y' or 'y': ");
        fflush(stdin);
        scanf("%c",&check);
        if(check != 'Y' && check != 'y')
            break;
        move = 20;
    }
}
