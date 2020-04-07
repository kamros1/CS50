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







