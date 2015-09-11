/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Yehui Chen
* Student Number   : s3189978
* Course Code      : COSC1076
* Program Code     : BP232
* Start up code provided by Paul Miller
***********************************************************************/
#include "game.h"


static void swap_players(struct player ** current, struct player ** other)
{
    /* implement a classic swap using a temporary pointer */
    struct player *swapper;

    swapper = *current;

    *current = *other;

    *other = swapper;
}


struct player * play_game(struct player * human , 
        struct player * computer)
{
    /* declaration that allocates the board for the game */
    enum cell_contents board[BOARDHEIGHT][BOARDWIDTH];

    /* random number*/

    int r_color; 

    enum input_result get_human, get_turn;

    struct player *current, *other;

    initialise_board(board);

/* 
 * initiating players and computer
 * pointer to structure '(*computer).name' is same to 'computer->name' 
*/
    r_color = rand()%2;

    
    get_human = get_human_player(human);

    while(get_human != SUCCESS)
    {
        if(get_human == -1)
        {
            return 0;
        }
        printf("Name Length exceeds allowance, Try again\n");
        read_rest_of_line();  /* Clean Invalid Input buffer */
        get_human = get_human_player(human);
    }

    get_computer_player(computer);


/* random assign color, set who evert get white to start firstly as current */

    printf("\n------------------------\n");

    if(r_color == 0)
    {
        human->thiscolor = C_RED;
        computer->thiscolor = C_WHITE;
        printf("%-20s: %s\n%-20s: %s\n", human->name, RED_TOKEN, 
                                computer->name, WHITE_TOKEN);

        current = computer;
        other = human;
    }
    else
    {
        human->thiscolor = C_WHITE;
        computer->thiscolor = C_RED;
        printf("%-20s: %s\n%-20s: %s\n", human->name, WHITE_TOKEN, 
                                computer->name, RED_TOKEN);

        current = human;
        other = computer;
    } 
    printf("------------------------\n");

/* Game starts */

    while(test_for_winner(board) == G_NO_WINNER)
    {
        printf("%s's turn\n", current->name);

        get_turn = take_turn(current, board);

        while(get_turn != SUCCESS)
        {
            if(get_turn == RTM)
            {
                return NULL;
            }
            if(current->type == HUMAN)
            {
                printf(" Try again.\n");

                read_rest_of_line();  /* Clean Invalid Input buffer */
            }
            get_turn = take_turn(current, board);
        }
        swap_players(&current, &other); /* Swap player */
    }


    /* Return the winner */
    if(test_for_winner(board) == G_RED)
    {
        if(human->thiscolor == C_RED)
        {
            return  human;
        }
        else
        {
            return computer;
        }
    }

    else if(test_for_winner(board) == G_WHITE)
    {
        if(human->thiscolor == C_WHITE)
        {
            return  human;
        }
        else
        {
            return computer;
        }
    }

    else
    {
        return NULL;
    }
}


enum game_state test_for_winner(
        enum cell_contents board[][BOARDWIDTH])
{
    
    int i, j;

    int space_left = 0;

/* Test for Draw */
    for(i = 0; i < BOARDHEIGHT; i++)
    {
        for(j = 0; j < BOARDWIDTH; j++)
        {
            if(board[i][j] == C_EMPTY)
            {
                space_left += 1;
            }
        }
    }

    if(space_left == 0)
    {
        printf("No space lefted, this game is draw\n");
        return G_DRAW;
    }


    for(i = 0; i < BOARDWIDTH; i++)
    {
        for(j = 0; j < BOARDHEIGHT; j++)
        {
            if(board[i][j] == C_RED)
            {
                /* horizontal '-' connect */
                if(board[i][j+1] == C_RED
                && board[i][j+2] == C_RED
                && board[i][j+3] == C_RED)
                {
                    return G_RED;
                }

                /* vertical '|' connect */
                if(board[i+1][j] == C_RED
                && board[i+2][j] == C_RED
                && board[i+3][j] == C_RED)
                {
                    return G_RED;
                }

                /* '\' connect */
                if(board[i+1][j+1] == C_RED
                && board[i+2][j+2] == C_RED
                && board[i+3][j+3] == C_RED)
                {
                    return G_RED;
                }

                /* '/' connect */
                if(board[i+1][j-1] == C_RED
                && board[i+2][j-2] == C_RED
                && board[i+3][j-3] == C_RED)
                {
                    return G_RED;
                }

            }

            if(board[i][j] == C_WHITE)
            {
                if(board[i][j+1] == C_WHITE
                && board[i][j+2] == C_WHITE
                && board[i][j+3] == C_WHITE)
                {
                    return G_WHITE;
                }

                if(board[i+1][j] == C_WHITE
                && board[i+2][j] == C_WHITE
                && board[i+3][j] == C_WHITE)
                {
                    return G_WHITE;
                }

                if(board[i+1][j+1] == C_WHITE
                && board[i+2][j+2] == C_WHITE
                && board[i+3][j+3] == C_WHITE)
                {
                    return G_WHITE;
                }

                if(board[i+1][j-1] == C_WHITE
                && board[i+2][j-2] == C_WHITE
                && board[i+3][j-3] == C_WHITE)
                {
                    return G_WHITE;
                }

            }
        }
    }
    return G_NO_WINNER;
}












