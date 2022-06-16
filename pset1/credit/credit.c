#include <cs50.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

int main (void)
{

double crednum;
double crednum1=0, crednum2=0;
int r1, r2;
float r1z=0, r1x=0;
int z, sum=0, sum1=0, sum2=0;

  crednum=get_long("Number: \n");
        crednum1=crednum / 10;
        crednum2=crednum;
        crednum1=floor(crednum1);

// First sum1 calc----------------
for (int i = 0; i < 9; i++)
{
    r1=(long)crednum1%10;
    r1=r1*2;

// In case of more then 10---------
        if (r1 >= 10)
        {
           r1z=(int)r1%10;
           r1x=r1/10;
           r1x=floor(r1x);
           r1 =r1z+r1x;
        }

//--------------------------------
    sum1=r1+sum1;

    crednum1=(double)crednum1/100;
    crednum1=floor(crednum1);
}

// Second sum2---------------------
for (int j = 0; j < 9; j++)
{
    r2=(long)crednum2%10;
    sum2=sum2+r2;


    crednum2=crednum2/100;
    crednum2=floor(crednum2);
}

sum=sum1+sum2;

if (sum%10 == 0)
{


// End of sum check----------------

    int dig13, dig14, dig15, dig16;

// 13th dig calc
        crednum=crednum/1000000000000;
        crednum=floor(crednum);

        dig13=(long)crednum%10;

// 14th dig calc
        crednum=crednum/10;
        crednum=floor(crednum);

        dig14=(long)crednum%10;

// 15th dig calc
        crednum=crednum/10;
        crednum=floor(crednum);

        dig15=(long)crednum%10;

// 16th dig calc
        crednum=crednum/10;
        crednum=floor(crednum);

        dig16=(long)crednum%10;

// 1st condition to AMEX--------------------------
                  if (dig16 == 0 && dig15 == 3 && (dig14 == 4 || dig14 == 7))
                    {
                        printf("AMEX\n");
                    }

// 2nd condition for Mastercard--------------------
                    else if (dig16 == 5 &&
                    (dig15 == 1 || dig15 == 2 || dig15 == 3 || dig15 == 4 || dig15 == 5))
                    {
                        printf("MASTERCARD\n");
                    }

// 3rd condition for Visa---------------------------
                    else if (dig16 == 4 || (dig13 == 4 && dig15 == 0 && dig14 == 0))
                    {
                        printf("VISA\n");
                    }

                    else
                    {
                        printf("INVALID\n");
                    }
}

// Invalid comm-------------------
else
{
    printf("INVALID\n");

}
}
