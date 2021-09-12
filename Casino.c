// Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// Function prototypes and global variable declaration/initialization.
int chips = 0;
int pairOfDice();
int craps();
int danysDice();
int buyChips(int *cash);
int sellChips(int numChips);
void statusReport(int numChips,int cash);
int main()
{
    printf("Hello welcome to my casino!\n");
    int option = 0;
    int cash = 1000;
    int *cashPTR = &cash;
    int numChips = 0;
    // Menu loop
    do
    {
        printf("1:Buy chips\n2:Sell chips\n3:Play Craps\n4:Play Dany's Game of Dice\n5:Status report\n6:Quit\n");
        scanf("%i",&option);

        if(option == 1) // Calls buyChips() function.
            chips += buyChips(cashPTR);
        else if(option == 2) // If amount to sell is valid, calls sellChips() function.
        {
            printf("How many chips do you want to sell?\n");
            scanf("%i",&numChips);
            if(numChips <= 0 || numChips > chips)
            {
                printf("You do not have enough chips to sell.\n");
            }
            else
                cash += sellChips(numChips);
        }
        else if(option == 3) // Calls craps() function, then checks whether the user has won or lost the game.
        {
            int crapsResult = craps();
            if(crapsResult == 1)
                printf("You win!\n");
            else if(crapsResult == 0)
            {
                printf("Sorry you've lost.\n");
                if(chips < 1)
                    printf("You have no chips left.\n");
            }
        }
        else if(option == 4) // Calls danysDice() function, then checks whether the user has won or lost the game.
        {
            int gameOfDiceResult = danysDice();
            if(gameOfDiceResult == 1)
            {
                printf("You win!\n");
            }
            else if(gameOfDiceResult == 0)
            {
                printf("Sorry you've lost.\n");
            }
        }
        else if(option == 5) // Calls statusReport function.
            statusReport(chips,cash);
        else if(option == 6) // Sells chips and ends your time at the mini casino.
            printf("After selling your chips, you have $%i. Thanks for playing!\n",(cash + sellChips(chips)));
        else // In the case of invalid input at the menu.
            printf("Incorrect option, please try again.\n");
    }while(option != 6);

    return 0;
}
// The function below is used to roll the dice in both the craps and Dany's game of dice. We use srand() to set seed for rand().
int pairOfDice()
{
        int dice = 0;
        srand(time(NULL));
        for(int i = 0; i < 2;i++)
            dice += (rand() % 6) + 1;
        return dice;
}
// Function below simulates the craps game.
int craps()
{
    int chipsToBet = 0;
    int diceResult = -1;
    int result = 0;

    printf("How many chips would you like to bet?\n");
    scanf("%i",&chipsToBet);
    // First check if we are betting a valid amount of chips.
    if(chipsToBet <= 0) 
    {
        printf("Sorry you can't bet 0 chips. No game played.\n");
        return diceResult;
    }
    else if(chipsToBet > chips)
    {
        printf("You are trying to bet more chips than you have. No game played.\n");
        return diceResult;
    }
    else{
        
        char roll;
        bool inProgress = true;
        while ((getchar()) != '\n'); // Get rid of anything left in buffer.
        // Do-while below runs until there is a winner or loser. 
        do
        {
        printf("Press 'R' and hit enter for your first roll.\n");         
        roll = getchar();

        if(roll == 'r' || roll == 'R')
        {
            result = pairOfDice();
            printf("You rolled a %i\n",result);
            if(result == 7 || result == 11)
            {
                chips += (chipsToBet * 2);
                diceResult = 1;
                inProgress = false;
            }
            else if(result == 2 || result == 3 || result == 12)
            {
                chips -= chipsToBet;
                diceResult = 0;
                inProgress = false;
            }
        }
        else
            printf("Wrong input try again!\n");
            
         while ((getchar()) != '\n');       

        }while(inProgress); // Boolean flag set to false when game is over.

        return diceResult;
    }
}
// The function below simulates Dany's game of dice.
int danysDice()
{
    int chipsToBet = 0;
    int diceResult = -1;
    int result = 0;
    // First check if we are betting a valid amount of chips.
    printf("How many chips would you like to bet?\n");
    scanf("%i",&chipsToBet);
    if(chipsToBet <= 0)
    {
        printf("Sorry that is not allowed. No game played.\n");
        return diceResult;
    }
    else if(chipsToBet > chips)
    {
        printf("You are trying to bet more chips than you have. No game played.\n");
        return diceResult;
    }
    else{
        char roll;
         bool inProgress = true;
        while ((getchar()) != '\n'); // Get rid of anything left in buffer.
        // Do-while below runs until there is a winner or loser.
        do
        {
        printf("Press 'R' and hit enter for your first roll.\n");         
        roll = getchar();

        if(roll == 'r' || roll == 'R')
        {
            result = pairOfDice();
            printf("You rolled a %i\n",result);
            // Similar to craps game except there is only 2 numbers you can roll to win, and one to lose.
            if(result == 12 || result == 11)
            {
                chips += (chipsToBet * 2);
                diceResult = 1;
                inProgress = false;
            }
            else if(result == 2)
            {
                chips -= (chipsToBet * 2);
                diceResult = 0;
                inProgress = false;
            }
        }
        else
            printf("Wrong input try again!\n");
            
         while ((getchar()) != '\n');       

        }while(inProgress); // Boolean flag set to false when game is over.
        
            return diceResult;
    }
}
// Function below allows the user to buy chips.
int buyChips(int *cash)
{
    int amountOfCash = 0;
    int chips = 0;

    printf("How much cash do you want to spend for chips?\n");
    scanf("%i",&amountOfCash);

    if(amountOfCash > *cash) // Check if the user has entered a valid amount of cash to spend on chips.
        printf("Sorry, you do not have that much money. No chips bought.\n");
    else
    {
        *cash = (*cash) - amountOfCash;
        chips = amountOfCash / 11;
        printf("You currently have %i left and bought %i chips.\n",*cash,chips);
    }

    return chips;
}
// Function below sells chips for cash.
int sellChips(int numChips)
{
    int moneyGained = 0;
    chips -= numChips;
    moneyGained = numChips * 10;
    printf("You have sold %i chips for $%i dollars\n",numChips,moneyGained);

    return moneyGained;
}
// Function below simply prints the amount of cash and chips that the user currently holds.
void statusReport(int numChips, int cash){
    printf("You currently have %i dollars left and %i chips.\n",cash,numChips);
}