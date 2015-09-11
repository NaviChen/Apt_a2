/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Yehui Chen
* Student Number   : s3189978
* Course Code      : COSC1076
* Program Code     : BP232
* Start up code provided by Paul Miller
***********************************************************************/
#include "player.h"

/**
 * @param human the human player to initialise
 **/
enum input_result get_human_player(struct player* human)
{
    /* placeholder return value. You should prompt the user 
     * for their name and then initialise all other values in the
     * player struct to sensible values.
     */
    char name[NAMELEN+2];
    printf("Please Enter Your Name: \n");
    printf("Press ENTER or CTRL + D to abort current game\n");

/* assigning name to human player */
    if(fgets(name, NAMELEN+2, stdin) != NULL)
    {
        
    /* test for name length */
        if(name[strlen(name)-1] != '\n')
        {
            return FAILURE;
        }
        
    /* Back to menu if press enter */
        if(strcmp(name, "\n")==0)
        {
            return RTM;
        }

    /* remove '\n' from the end of buffer!! */
        strtok(name,"\n"); 

        

    /* assign name and properties */
        strcpy(human->name, name);
        (*human).type = HUMAN;
        human->counters = 0;
        return SUCCESS;
    } 
    else
    {
        read_rest_of_line();
        return RTM;
    }
    return FAILURE;     
}

/**
 * @param computer the computer player to initialise
 **/
enum input_result get_computer_player(struct player * computer)
{
    /* initialise all variables that are part of the struct to sensible 
     * values */

    strcpy(computer->name, "computer"); /* assigning name to comp player*/
    (*computer).type = COMPUTER;
    computer->counters = 0; 
    return SUCCESS;
}


enum input_result take_turn(struct player * current,
        enum cell_contents board[][BOARDWIDTH])
{
    

    int cmp_move_col, indexH = BOARDHEIGHT-1;
    char human_input[MOVELEN];

/* Human Players input should be set to 'long' for better validating */
    long col, row = BOARDHEIGHT-1;

/* Computer Player's move */
    if(current->type == COMPUTER)
    {
        do
        {
            cmp_move_col = rand()%7;

        }while(validSpace(cmp_move_col, board) != 1);

        while(indexH >= 0)
        {
            if(board[indexH][cmp_move_col] == C_EMPTY)
            {
                board[indexH][cmp_move_col] = current->thiscolor;
                
                current->counters += 1;
                display_board(board);
                return SUCCESS;
            }

            indexH-=1;
        }
    }


/* Human Player's move */
    else
    {
       printf("Please Enter Your Move 1-7:\n");
       printf("Press ENTER or CTRL + D to abort current game\n");

       if(fgets(human_input, MOVELEN+2, stdin) != NULL)
        {

            /* Back to menu if press ENTER */
            if(strcmp(human_input, "\n") == 0)
            {
                return RTM;
            }
            
            if(!sscanf(human_input,"%li",&col))
            {
                printf("Invalid input!");
                return FAILURE;
            }
            
        /* 
        * Check Invalid Move - out of range 
        * Check Invalid Move - Place has been taken already 
        */
            if(col > BOARDWIDTH || col <= 0)
            {   
                printf("Out of range!");
                return FAILURE;
            }

            if(validSpace(col, board)!=1)
            {   
                printf("No Valid Space in this Column");
                return FAILURE;
            }


        }

    /* Back to menu if press ctl + D */
        else
        {
            read_rest_of_line();
            return RTM;
        }

    /* Place Token */

        while(row >= 0 )
        {
            if(board[row][col-1] == C_EMPTY)
            {
                board[row][col-1] = current->thiscolor;

                current->counters += 1;
                display_board(board);/* increase counter by one if success */
                return SUCCESS;
            }
            row -= 1;
        }
        
        
    }

    return 0;
}

/* Function to test if empty place in selected column */
BOOLEAN validSpace(int col, enum cell_contents board[][BOARDWIDTH])
{
    int row = 0;
    while(row < BOARDHEIGHT )
    {
        if(board[row][col] == C_EMPTY)
        {
            return 1;
        }
        row += 1;
    }
    return 0;
}












