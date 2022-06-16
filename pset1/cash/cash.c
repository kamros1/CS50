#include <cs50.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
int main (void)
{
float dollars;
do
    {
        dollars = get_float("What is the change?\n");
        printf("Change owed: %.2f$\n",dollars);
    }
while(dollars<0);
//----------------------------------------------------------
int cents = round(100*dollars);
int times1, times5,times10, times25, total=0;
int change25, change5, change10=0;
// times1 mean how many 1 pense
times1=cents % 5;

// change5 means how many 5pense could be
change5=(cents-times1)/5;

//times25 how many 25 penses
change25=(change5 % 5);
times25=(change5-change25)/5;

//change25
times5=change25 % 2;
times10 = (change25-change10)/2;

total=times1+times5+times10+times25;
printf("%i\n",total);
}




#include <cs50.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

    int calculate_change ( int coin, int value);
        int calculate_quaters (int number);
            int calculate_dimes (int number);
                int calculate_nickels (int number);
                    int calculate_pennies (int number);
                        int get_cents (void);

int main(void)
{
    int cents = 0;
    int total = 0;

    cents = get_cents();

    //----------------------------------------------------------
    total += calculate_quaters (cents);
    cents = calculate_change( 25, cents);

    total += calculate_dimes(cents);
    cents = calculate_change( 10, cents);

    total +=  calculate_nickels(cents);
    cents = calculate_change( 5, cents);

    total += calculate_pennies(cents);

    printf("%i\n",total);

}

    // Functions declarations
    int get_cents (void)
    {
        int cents = 0;
        do {
        cents = get_int("What is the change?");
        printf("Change owed: %i\n", cents);
            }
        while (cents <= 0);
        return cents;
    }


    int calculate_change ( int coin, int value)
    {
        return value % coin;
    }

    int calculate_quaters (int number)
    {
        return floor(number / 25);

    }

    int calculate_dimes (int number)
    {
        int dimes = floor(number / 10 );
        return dimes;
    }

    int calculate_nickels (int number)
    {
        int nickels = floor(number / 5 );
        return nickels;
    }

    int calculate_pennies (int number)
    {
        int pennies = number % 5;
        return pennies;
    }










