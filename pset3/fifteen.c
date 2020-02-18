/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

//#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(int n);
void draw(int n);
bool move(int tile, int n);
bool won(int n);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init(d);

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        printf("\n");
        draw(d);

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won(d))
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile;
        scanf("%d", &tile);
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile, d))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(int n)
{
    // TODO
    int i, j; 
    int k = (n * n) - 1;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(j == n - 1 && i == n - 1)
            {
                board[i][j] = 0;
            }
            else
            {
                if(k == 2 && j == n - 3)
                {
                    if (n % 2 == 1)
                    {

                    }
                    else
                    {
                        board[i][j] = k - 1;
                        j++;
                    }
                }
                board[i][j] = k;
                k--;
            }
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(int n)
{
    // TODO
    int i, j;

    for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if(board[i][j] == 0)
                	printf(" ");
            	else
                	printf("%d", board[i][j]);
                if (j < n - 1)
                {
                	if(board[i][j] / 10 == 0)
                		printf(" ");
                    printf("|");
                }
            }
            printf("\n");
        }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile, int n)
{

    // TODO
    int i, j;
    int x0 = 0, y0 = 0, xtile, ytile;
    for(i = 0; i < n; i++)
    {
    	for(j = 0; j < n; j++)
    	{
			if(board[i][j] == 0)
			{
				x0 = i;
				y0 = j;
			}
			if(board[i][j] == tile)
			{
				xtile = i;
				ytile = j;
			}
		} 		
   	}
   	if(abs(x0 - xtile) + abs(y0 - ytile) == 1)
   	{
   		board[x0][y0] = board[xtile][ytile];
   		board[xtile][ytile] = 0;
   		return true;
   	}
    else
    	return false;
	
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(int n)
{
    // TODO
    int i, j;
    for (int i = 0; i < n; i++)
    {
    	for(j = 0; j < n; j++)
    	{	
    		if(i == n - 1 && j == n - 1)
    		{
    			if(board[i][j] == 0)
    				return true;
    		}
    		else if(board[i][j] != n * i + j + 1)
    			return false;
    	}
    }
    if(i == n && j == n)
    	return true;
 	else
   		return false;
}