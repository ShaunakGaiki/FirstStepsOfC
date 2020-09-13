#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define WIN 10
#define LOSS -10
#define TIE 0 
#define IF_BLANK(i) ((board[i])==(NULL))?(i+'0'):(board[i])
#define MAX(x,y) ((x)>=(y))?(x):(y)
#define MIN(x,y) ((x)<=(y))?(x):(y)
enum enPlayer{Humn,Comp};
char board[9]={NULL};
int iterations=0,iterationsA=0;
int minimaxA(int,int,int);
int minimax(int);
int winOrLoss();
int XorO(int);
void computerA();
void computer();
void human();
void current_board();
int main()
{
	int i,game,choice,move;
	char ochoice;
	time_t t;
	printf("Let's Play Tic-Tac-Toe! You go first.");
	printf("This is the starting board:");
	current_board();
	printf("If you want to play, type 1. If you want to check accuracy, press 2. If you want to check iterations, press 3.");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:
		for(i=0;i<sizeof(board);i++)
		{
			if(i%2==0)
			{
				human();
				continue;
			}
			if(winOrLoss()==LOSS)
			{
				printf("YOU WON! IMPOSSIBLE!");
				return 0;
			}
			if(i%2==1)
			{
				computerA();
				continue;
			}
			if(winOrLoss()==WIN)
			{
				printf("I WON! FEEL THE POWER OF ME!!!");
				return 0;
			}
		}
		current_board();
		printf("TIE");
		return 0;
		break;
	case 2:
		srand((unsigned) time(&t));
		printf("Do you want to test accuracy with Alpha-Beta Pruning (A) or Normal Minimax (N)");
		scanf("\n%c",&ochoice);
		for(game=0;game<10000;game++)
		{
			for(i=0;i<sizeof(board);i++)
			{

				if(i%2==0)
				{
					while(1)
					{
						move=rand()%9;
						if(board[move]==NULL)
						{
							board[move]='X';
							break;
						}
					}
					if(winOrLoss()==LOSS)
					{
						printf("Test Failed at game #%d. Computer Lost. Debug Later",game);
						return 0;
					}
					continue;
				}
				(ochoice=='A')?(computerA()):(computer());
				if(winOrLoss()==WIN)
				{
					printf("Success for test #%d",game);
					goto OEND;
				}
			}
			printf("Success for test #%d",game);
			OEND:;
			for(i=0;i<sizeof(board);i++)
			{
				board[i]=NULL;
			}
		}
	case 3:
		for(i=0;i<sizeof(board);i++)
		{
			if(i%2==0)
			{
				human();
				continue;
			}
			if(winOrLoss()==LOSS)
			{
				printf("YOU WON! Alpha Beta Pruning is: %d iterations and Normal Minimax is: %d iterations",iterationsA,iterations);
				goto END;
			}
			computerA();
			minimax(Humn);
			if(winOrLoss()==WIN)
			{
				printf("I WON! Alpha Beta Pruning is: %d iterations and Normal Minimax is: %d iterations",iterationsA,iterations);
				goto END;
			}
		}
		printf("TIE! Alpha Beta Pruning is: %d iterations and Normal Minimax is: %d iterations",iterationsA,iterations);
		END:break;
	}
	return 0;
}
void computer()
{
	int i,guess,val,best_val,best_move;
	char moves[]={'X','O'};
	best_val=-11;
	best_move=-11;
	for(guess=0;guess<sizeof(board);guess++)
	{
		if(board[guess]!=NULL)
			continue;
		board[guess]=moves[Comp];
		val=minimax(!Comp);
		board[guess]=NULL;
		if(val>=best_val)
		{
			best_move=guess;
			best_val=val;
		}
		if(val==WIN)
			break;
	}
	if(best_move<0)
		return;
	board[best_move]=moves[Comp];
	current_board();			
}
void computerA()
{
	int i,guess,val,best_val,best_move;
	char moves[]={'X','O'};
	best_val=-11;
	best_move=-11;
	for(guess=0;guess<sizeof(board);guess++)
	{
		if(board[guess]!=NULL)
			continue;
		board[guess]=moves[Comp];
		val=minimaxA(!Comp,-11,11);
		board[guess]=NULL;
		if(val>=best_val)
		{
			best_move=guess;
			best_val=val;
		}
		if(best_val==WIN)
			break;
	}
	if(best_move<0)
		return;
	board[best_move]=moves[Comp];
	printf("\nAfter the computer's move (which is: %d) the board looks like this:\n",best_move);
	current_board();			
}
void human()
{
	int move;
	char moves[]={'X','O'};
	printf("\nWhat move do you want to make?\n");
	scanf("%d",&move);
	board[move]=moves[Humn];
	printf("Your move was %d, the board is now:",move);
	current_board();
}
int XorO(int i)
{
	if(board[i]=='O')
		return WIN;
	if(board[i]=='X')
		return LOSS;
}
int winOrLoss()
{
	int i;
	for(i=0;i<(sizeof(board))/3;i++)
	{
		if(board[i*3]==board[i*3+1] && board[i*3+2]==board[i*3] && board[i*3]!=NULL)
			return XorO(i*3);
		if(board[i]==board[i+3] && board[i]==board[i+6] && board[i]!=NULL)
			return XorO(i);
		if(board[0]==board[4] && board[0]==board[8]&& board[0]!=NULL)
			return XorO(0);
		if(board[2]==board[4] && board[2]==board[6] && board[2]!=NULL)
			return XorO(2);
	}
}
int minimaxA(int player,int alpha,int beta)
{
	int i,current_score,optimal_score=((player)==(Comp))?(-11):(11);
	char moves[]={'X','O'};
	iterationsA++;
	if(winOrLoss()==WIN || winOrLoss()==LOSS || winOrLoss()==TIE)
		return winOrLoss();
	for(i=0;i<sizeof(board);i++)
	{
		if(board[i]!=NULL)
			continue;
		board[i]=moves[player];
		current_score=minimaxA(!player,alpha,beta);
		board[i]=NULL;
		if(player==Humn)
		{
			beta=MIN(current_score,beta);
			optimal_score=MIN(current_score,optimal_score);
			if(current_score<alpha)
				break;
			if(beta<=alpha)
				break;
		}
		else
		{
			alpha=MAX(current_score,alpha);
			optimal_score=MAX(current_score,optimal_score);
			if(current_score>=beta)
				break;
			if(beta<=alpha)
				break;
		}
	}
	if(optimal_score==-11){return 0;}
	return optimal_score;
	
}
void current_board()
{
	printf("\n\n   |   |\n %c | %c | %c\n___|___|___\n   |   |\n %c | %c | %c\n___|___|___\n   |   |\n %c | %c | %c\n   |   |\n",
		IF_BLANK(0),IF_BLANK(1),IF_BLANK(2),IF_BLANK(3),IF_BLANK(4),IF_BLANK(5),IF_BLANK(6),IF_BLANK(7),IF_BLANK(8));
}
int minimax(int player)
{
	int i,current_score,optimal_score=((player)==(Comp))?(-11):(11);
	char moves[]={'X','O'};
	iterations++;
	if(winOrLoss()==WIN || winOrLoss()==LOSS || winOrLoss()==TIE)
		return winOrLoss();
	for(i=0;i<sizeof(board);i++)
	{
		if(board[i]!=NULL)
			continue;
		board[i]=moves[player];
		current_score=minimax(!player);
		board[i]=NULL;
		if(player==Humn)
		{
			optimal_score=MIN(current_score,optimal_score);
		}
		else
		{
			optimal_score=MAX(current_score,optimal_score);
		}
	}
	if(optimal_score==-11){return 0;}
	return optimal_score;	
}

