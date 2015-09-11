/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Yehui Chen
* Student Number   : s3189978
* Course Code      : COSC1076
* Program Code     : BP232
* Start up code provided by Paul Miller
***********************************************************************/
#include "con4.h"


int main(void)
{
    /* the scoreboard for keeping track of winners */
    scoreboard scores;
    /* the two players and a pointer to who won the last game */
    struct player human_player, computer_player, *winner;

    char User_Input[5], *EndPtr;
    long UserSelect;

    /* with each of the comments below, insert the code that performs 
     * this function 
     */

    /* initialise the scoreboard */
    init_scoreboard(scores);

    /*display menu and get menu choice until the user chooses to quit*/ 
    PrintMenu();
    do
    {
        if(fgets(User_Input, 7, stdin))
        {
            strtok(User_Input,"\n");
            UserSelect = strtol(User_Input, &EndPtr, 10);

            switch(UserSelect)
            {
                case 1: 
                    winner = play_game(&human_player, &computer_player);

                    if(winner == NULL)
                    {
                        printf("NO WINNER");
                        PrintMenu();
                        /*read_rest_of_line();  clear Buffer */
                        break;
                    }
                    else
                    {
                        printf("Winner is: %s\n",winner->name);
                        printf("Score: %d\n", winner->counters);
        
                        /* if(winner->type == HUMAN) */
                        
                        /* Add to ScoreBoard*/
                        add_to_scoreboard(scores, winner);

                        PrintMenu();
                        break;
                    }
                case 2:
                    display_scores(scores);
                    PrintMenu();
                    break;

                case 3:
                    break;

                default:
                    printf("\nInvalid Option, Please enter 1, 2 or 3\n");
                    PrintMenu();
                    break;

            }
        }
    }while(UserSelect != 3);

    return EXIT_SUCCESS;
}



