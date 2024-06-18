#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PLAYER 'X'
#define CPU 'O'
#define empty ' '

void generate_board(char board[3][3]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            board[i][j] = empty;
            
        }
    }
}

void print_board(char board[3][3]){
    system("cls");
    printf("\n");
    printf(" %c | %c | %c \n",board[0][0],board[0][1],board[0][2]);
    printf("___________\n");
    printf(" %c | %c | %c \n",board[1][0],board[1][1],board[1][2]);
    printf("___________\n");
    printf(" %c | %c | %c \n",board[2][0],board[2][1],board[2][2]);
    
  
}

int end_game(char board[3][3]){
    for (int i = 0; i < 3 ;i++){
        for (int j = 0; j < 3; j++){
            if (board[i][j]== empty){
                return 0;
            }
        }
    }
    return 1;
}

int win(char board[3][3], char e) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == e && board[i][1] == e && board[i][2] == e) ||
            (board[0][i] == e && board[1][i] == e && board[2][i] == e)) {
            return 1;
        }
    }

    if ((board[0][0] == e && board[1][1] == e && board[2][2] == e) ||
        (board[0][2] == e && board[1][1] == e && board[2][0] == e)) {
        return 1;
    }

    return 0;
}

int valid_case(char board[3][3],int pmove){
    int c=1;

    for (int i = 0; i < 3; i++)    {
        for (int j = 0; j < 3; j++)
        {   
            
            if (c==pmove){       
                if (board[i][j]==empty){
                    return 1;
                }   
    
                else{ 
                return 0;
                }
            }
            c++;
        }   
        
    }
    return 0;
    
}

void playerturn(char board[3][3],char e){
    
    while (1)
    {
    int pmove;
    printf("enter your move(line and column): ");
    scanf("%d",&pmove); 
    while (pmove < 1 && pmove > 9)
    {
        printf("try again: ");
        scanf("%d",&pmove);
    }
   // printf("\n result valid: %d\n",valid_case(board,pmove));
    if (valid_case(board,pmove)==0)
    {
        printf("!! WRONG CASE !!\n");
            
    }
    else{
        int found=0;
        int c=1;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {   
                if (c==pmove)
                {
                    found=1;
                    board[i][j]=e;  
                    break;
                }
                c++;
            }
            if (found==1)
            {
                break;
            }
            
        }
        break;    
    }
    
    }    
}


int maxmin(char board[3][3],int ismaxminplayer){
    if (win(board,PLAYER)==1)
    {
        return -1;
    }
    if (win(board,CPU)==1)
    {
        return 1;
    }
    if (end_game(board)==1)
    {
        return 0;
    }
    if (ismaxminplayer==1){
        int bestscore= - 1000;
        for ( int i = 0; i < 3; i++){
            for (int  j = 0; j < 3; j++){
                if (board[i][j]==empty){
                    board[i][j]=CPU;
                    int score=maxmin(board,0);
                    board[i][j]=empty;
                    if (score>bestscore){
                        bestscore=score;
                    }
                }
            }
        }
        return bestscore;
    }
    if (ismaxminplayer==0){
        int bestscore = 1000;
        for ( int i = 0; i < 3; i++){
            for (int  j = 0; j < 3; j++){
                if (board[i][j]==empty){
                    board[i][j]=PLAYER;
                    int score=maxmin(board,1);
                    board[i][j]=empty;
                    if (score<bestscore){
                        bestscore=score;
                    }
                }
            }
        }
        return bestscore;
    }

}
void AI_bestmove(char board[3][3]){
    int bestscore=-1000;
    int bestX,bestY;
    for ( int i = 0; i < 3; i++){
        for (int  j = 0; j < 3; j++){
            if (board[i][j]==empty){
                board[i][j]=CPU;
                int score=maxmin(board,0);
                board[i][j]=empty;
                if (score>bestscore){
                    bestscore=score;
                    bestX=i;
                    bestY=j;
                }
            }
        }
    }
    board[bestX][bestY]=CPU;
}

void match(char board[3][3],int *score_p,int *score_cpu){
    
    while (1)
    {
        printf("PLAYER 1 TURN: \n");
        printf("\n");
        playerturn(board,PLAYER);
        print_board(board);
        if (win(board,PLAYER))
        {
            (*score_p)++;
            printf("PLAYER 1 IS THE WINNER");
            break;
        }
        
        if (end_game(board)==1){
            printf("DRAW \n");
            break;
        }
        
        printf("PLAYER 2 TURN: \n");
        printf("\n");
        playerturn(board,CPU);
        print_board(board);
        if (win(board,CPU))
        {
            (*score_cpu)++;
            printf("PLAYER 2 IS THE WINNER");
            break;
        }
        if (end_game(board)==1){
            printf("DRAW \n");
            break;
        }
    }
    
}



void matcheithAI(char board[3][3],int *score_p,int *score_cpu){
    
    while (1)
    {
        printf("PLAYER 1 TURN: \n");
        printf("\n");
        playerturn(board,PLAYER);
        print_board(board);
        if (win(board,PLAYER))
        {
            (*score_p)++;
            printf("PLAYER 1 IS THE WINNER");
            break;
        }
        
        if (end_game(board)==1){
            printf("DRAW \n");
            break;
        }
        
        AI_bestmove(board);
        print_board(board);
        if (win(board,CPU))
        {
            (*score_cpu)++;
            printf("AI IS THE WINNER");
            break;
        }
        if (end_game(board)==1){
            printf("DRAW \n");
            break;
        }
    }
}

void show_score(int p,int cp){
    printf("   PLAYER 1 (X)   |    PLAYER 2 (O)  \n");
    printf("       %d          |       %d         \n",p,cp);
}
int main() {
    char board[3][3];
    int v=1,score_p=0,score_cpu=0;
    int gstyle;
    printf("          WELCOME TO TIC-TAC-TOE GAME\n                  |     |                  \n                  |     |                  \n_________________________________________\n                  |     |                  \n                  |     |                  \n_________________________________________\n                  |     |                  \n                  |     |                  \nyou can play one of this mode: \n1 - player vs AI \n2-player1 vs player2\n");
    scanf("%d",&gstyle);
    while (gstyle!=1 && gstyle!=2)
    {
        printf("you can play one of this mode: \n1 - player vs AI \n2-player1 vs player2\n");
        scanf("%d",&gstyle);
    }
    
    if (gstyle==1)
    {
       while (v==1)
    {   
        generate_board(board);
        print_board(board);
        matcheithAI(board,&score_p,&score_cpu);
        printf("\nwould you contnue YES/1 or NO/0: ");
        scanf("%d",&v);
        while (v!=0 && v!=1)
        {
            printf("\nwould you contnue YES/1 or NO/0: ");
            scanf("%d",&v);
        }
        
    }
    }
    else
    {
        while (v==1)
    {   
        generate_board(board);
        print_board(board);
        match(board,&score_p,&score_cpu);
        printf("\nwould you contnue YES/1 or NO/0: ");
        scanf("%d",&v);
        while (v!=0 && v!=1)
        {
            printf("\nwould you contnue YES/1 or NO/0: ");
            scanf("%d",&v);
        }
        
    }
    }
    
    
    printf("\n");
    show_score(score_p,score_cpu);     

   return 0;
}
