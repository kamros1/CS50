#include <cs50.h>
#include <stdio.h>

int main(void)
{
 int h ;

//pierwsza petla------------------- 
do
{
    h = get_int("Whats height??\n");
    printf("%i\n",h); 
}

while (h<1 || h>8);  
//koniec pierwszej petli-------------------------
//druga petla poczatek---------------------------
int space, pr, row;
space=0;
pr=0;
row=1;

do 
{           
        while(space<h-row && space<8 )
            {
                printf(" ");
                space++;
            }
        for(int i=0; i<row; i++)
            {
                printf("#");
                pr++;
            }
                    if((pr+space) % h == 0)
                    {
                     printf("  ");

                            for(int j=0; j<row; j++)
                            {
                            printf("#");
                            };
                    }                                       
            if(pr == row )
            {
            printf("\n");
            row++;
            pr=0;
            space=0;
            }
            if(row>h)
            {
                break;
            }                 
}
while(pr<=2*h);


//koniec main
}

