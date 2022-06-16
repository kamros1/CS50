#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

// More 255 function
void more255(RGBTRIPLE *some)
{
    if (some -> rgbtRed > 255)
    {
        some  -> rgbtRed = 255;
    }
    if (some -> rgbtGreen > 255)
    {
        some -> rgbtGreen = 255;
    }
    if (some -> rgbtBlue > 255)
    {
        some -> rgbtBlue = 255;
    }

    if (some -> rgbtRed < 0)
    {
        some  -> rgbtRed = 0;
    }
    if (some -> rgbtGreen < 0)
    {
        some -> rgbtGreen = 0;
    }
    if (some -> rgbtBlue < 0)
    {
        some -> rgbtBlue = 0;
    }
}

// Avarage function
double average(int num, ...)
{

    va_list valist;
    double sum = 0.0;
    int i;

    // initialize valist for num number of arguments
    va_start(valist, num);

    // access all the arguments assigned to valist
    for (i = 0; i < num; i++)
    {
        sum += va_arg(valist, int);
    }

    // clean memory reserved for valist
    va_end(valist);

    return sum / num;
}

// Swap funkction
void swap(RGBTRIPLE *wska, RGBTRIPLE *wskb)
{
    RGBTRIPLE temp = *wska;
    *wska = *wskb;
    *wskb = temp;
}

// RGB Avarage function
RGBTRIPLE averageRGB(int num, ...)
{

    va_list valist;
    RGBTRIPLE temp;

    double sumgreen = 0.0;
    double sumblue = 0.0;
    double sumred = 0.0;

    int i;

    // initialize valist for num number of arguments
    va_start(valist, num);

    // access all the arguments assigned to valist
    for (i = 0; i < num; i++)
    {
        temp = va_arg(valist, RGBTRIPLE);

        sumgreen += temp.rgbtGreen;
        sumblue += temp.rgbtBlue;
        sumred += temp.rgbtRed;
    }

    temp.rgbtGreen = round(sumgreen / (double)num);
    temp.rgbtBlue = round(sumblue / (double)num);
    temp.rgbtRed = round(sumred / (double)num);

    // clean memory reserved for valist
    va_end(valist);

    more255(&temp);

    return temp;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float av;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            av = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / ((float)3));
            image[i][j].rgbtRed = av;
            image[i][j].rgbtGreen = av;
            image[i][j].rgbtBlue = av;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red, green, blue;

            red = round((float)0.393 * image[i][j].rgbtRed + (float)0.769 * image[i][j].rgbtGreen + (float)0.189 * image[i][j].rgbtBlue);
            green = round((float)0.349 * image[i][j].rgbtRed + (float)0.686 * image[i][j].rgbtGreen + (float)0.168 * image[i][j].rgbtBlue);
            blue = round((float)0.272 * image[i][j].rgbtRed + (float)0.534  * image[i][j].rgbtGreen + (float)0.131 * image[i][j].rgbtBlue);

            if (red > 255)
            {
                red = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            if (blue > 255)
            {
                red = 255;
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;


        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Swap line
    for (int i = 0; i < (width / 2); i++)
    {
        swap(&image[height][i], &image[height][width - 1 - i]);
    }

    if (height == 0)
    {
        return;
    }

    else
    {
        reflect(height - 1, width, image);
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageout[height][width];

    for (int w = 0; w < height; w++)
    {
        if (w == 0)
        {
            // Case for first line
            for (int l = 0; l < width; l++)
            {
                // Case first column
                if (l == 0)
                {
                    imageout[w][l] = averageRGB(4, image[w][l], image[w][l + 1], image[w + 1][l + 1], image[w + 1][l]);
                }

                // Case for last column
                else if (l == (width - 1))
                {
                    imageout[w][l] = averageRGB(4, image[w][l - 1], image[w][l], image[w + 1][l], image[w + 1][l - 1]);
                }

                // Case for middle column
                else
                {
                    imageout[w][l] = averageRGB(6, image[w + 1][l - 1], image[w + 1][l], image[w + 1][l + 1], image[w][l + 1], image[w][l],
                                                image[w][l - 1]);
                }
            }
        }

        // case for last line
        else if (w == (height - 1))
        {
            for (int l = 0; l < width; l++)
            {

                // Case first column
                if (l == 0)
                {
                    imageout[w][l] = averageRGB(4, image[w][l], image[w][l + 1], image[w - 1][l], image[w - 1][l + 1]);
                }

                // Case for last column
                else if (l == (width - 1))
                {
                    imageout[w][l] = averageRGB(4, image[w][l - 1], image[w][l], image[w - 1][l], image[w - 1][l - 1]);
                }

                // Case for middle column
                else
                {
                    imageout[w][l] = averageRGB(6, image[w - 1][l - 1], image[w - 1][l], image[w - 1][l + 1], image[w][l + 1], image[w][l],
                                                image[w][l - 1]);
                }
            }
       }

        // Case for middle line
        else
        {
            for (int l = 0; l < width; l++)
            {
                // Case first column
                if (l == 0)
                {
                    imageout[w][l] = averageRGB(6, image[w - 1][l], image[w - 1][l + 1], image[w][l + 1], image[w + 1][l + 1], image[w + 1][l],
                                                image[w][l]);
                }

                // Case for last column
                else if (l == (width - 1))
                {
                    imageout[w][l] = averageRGB(6, image[w - 1][l], image[w - 1][l - 1], image[w][l - 1], image[w + 1][l - 1], image[w + 1][l],
                                                image[w][l]);
                }

                // Case for middle column
                else
                {
                    imageout[w][l] = averageRGB(9, image[w + 1][l - 1], image[w + 1][l], image[w + 1][l + 1], image[w][l + 1], image[w][l],
                                                image[w][l - 1], image[w - 1][l - 1], image[w - 1][l], image[w - 1][l + 1]);
                }
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageout[i][j];
        }
    }
    return;
}

// Function and struct connected to edge function------------------------

// Create struct with float values
struct RGBfloat
{
    float rgbtRed;
    float rgbtGreen;
    float rgbtBlue;
};

// More 255 function for special RGBfloat structure
void more255float(struct RGBfloat *some)
{
    if (some -> rgbtRed > 255)
    {
        some  -> rgbtRed = 255;
    }
    if (some -> rgbtGreen > 255)
    {
        some -> rgbtGreen = 255;
    }
    if (some -> rgbtBlue > 255)
    {
        some -> rgbtBlue = 255;
    }

    if (some -> rgbtRed < 0)
    {
        some  -> rgbtRed = 0;
    }
    if (some -> rgbtGreen < 0)
    {
        some -> rgbtGreen = 0;
    }
    if (some -> rgbtBlue < 0)
    {
        some -> rgbtBlue = 0;
    }
}

// Function to multiply RGB values and return RGBfloat
struct RGBfloat multiRGBfloat(RGBTRIPLE a, int i)
{
    struct RGBfloat temp;

    temp.rgbtRed = i * a.rgbtRed;
    temp.rgbtGreen = i * a.rgbtGreen;
    temp.rgbtBlue = i * a.rgbtBlue;

    return temp;
}

// Function to sum RGBfloat
struct RGBfloat  sumRGBfloat(int num, ...)
{
    va_list valist;
    struct RGBfloat temp;
    struct RGBfloat ret;

    ret.rgbtRed = 0;
    ret.rgbtGreen = 0;
    ret.rgbtBlue = 0;

    // initialize valist for num number of arguments
    va_start(valist, num);

    // access all the arguments assigned to valist
    for (int j = 0; j < num; j++)
    {
        temp = va_arg(valist, struct RGBfloat);

        ret.rgbtRed += temp.rgbtRed;
        ret.rgbtGreen += temp.rgbtGreen;
        ret.rgbtBlue += temp.rgbtBlue;
    }

    // clean memory reserved for valist
    va_end(valist);

    return ret;
}

// Final combine function return
RGBTRIPLE combine(struct RGBfloat gx, struct RGBfloat gy)
{
    struct RGBfloat ret;
    RGBTRIPLE retRGBTRIPLE;

    ret.rgbtRed = round(sqrt(pow(gx.rgbtRed, 2) + pow(gy.rgbtRed, 2)));
    ret.rgbtGreen = round(sqrt(pow(gx.rgbtGreen, 2) + pow(gy.rgbtGreen, 2)));
    ret.rgbtBlue = round(sqrt(pow(gx.rgbtBlue, 2) + pow(gy.rgbtBlue, 2)));

    more255float(&ret);

    retRGBTRIPLE.rgbtRed = ret.rgbtRed;
    retRGBTRIPLE.rgbtGreen = ret.rgbtGreen;
    retRGBTRIPLE.rgbtBlue = ret.rgbtBlue;

    return retRGBTRIPLE;
}

// gx function
struct RGBfloat gx(int height, int width, RGBTRIPLE image[height][width], int w, int c)
{
    // Declaration for temporary struct RGBTRIPLE
    struct RGBfloat temp;

    // First line:
    if (w == 0)
    {
        // First column:
        if (c == 0)
        {
            temp = sumRGBfloat(2, multiRGBfloat(image[w][c + 1], 2),
                               multiRGBfloat(image[w + 1][c + 1], 1));
        }

        // Last column:
        else if (c == (width - 1))
        {
            temp  = sumRGBfloat(2, multiRGBfloat(image[w][c - 1], -2),
                                multiRGBfloat(image[w + 1][c - 1], -1));
        }

        // Middle column:
        else
        {
            temp  = sumRGBfloat(4, multiRGBfloat(image[w][c - 1], -2), multiRGBfloat(image[w][c + 1], 2),
                                multiRGBfloat(image[w + 1][c - 1], -1), multiRGBfloat(image[w + 1][c + 1], 1));
        }
    }

    // Last line:
    else if (w == (height - 1))
    {
        // First column:
        if (c == 0)
        {
            temp  = sumRGBfloat(2, multiRGBfloat(image[w - 1][c + 1], 1),
                                multiRGBfloat(image[w][c + 1], 2));
        }

        // Last column:
        else if (c == (width - 1))
        {
            temp  = sumRGBfloat(2, multiRGBfloat(image[w - 1][c - 1], -1),
                                multiRGBfloat(image[w][c - 1], -2));
        }

        // Middle column:
        else
        {
            temp  = sumRGBfloat(4, multiRGBfloat(image[w - 1][c - 1], -1), multiRGBfloat(image[w - 1][c + 1], 1),
                                multiRGBfloat(image[w][c - 1], -2), multiRGBfloat(image[w][c + 1], 2));
        }
    }


    // Middle line:
    else
    {
        // First column:
        if (c == 0)
        {
            temp  = sumRGBfloat(3, multiRGBfloat(image[w - 1][c + 1], 1),
                                multiRGBfloat(image[w][c + 1], 2),
                                multiRGBfloat(image[w + 1][c + 1], 1));
        }

        // Last column:
        else if (c == (width - 1))
        {
            temp  = sumRGBfloat(3, multiRGBfloat(image[w - 1][c - 1], -1),
                                multiRGBfloat(image[w][c - 1], -2),
                                multiRGBfloat(image[w + 1][c - 1], -1));
        }

        // Middle column:
        else
        {
            temp  = sumRGBfloat(6, multiRGBfloat(image[w - 1][c - 1], -1), multiRGBfloat(image[w - 1][c + 1], 1),
                                multiRGBfloat(image[w][c - 1], -2), multiRGBfloat(image[w][c + 1], 2),
                                multiRGBfloat(image[w + 1][c - 1], -1), multiRGBfloat(image[w + 1][c + 1], 1));
        }
    }

    return temp;
}

// gy function
struct RGBfloat gy(int height, int width, RGBTRIPLE image[height][width], int w, int c)
{
    // Declaration for temporary struct RGBTRIPLE
    struct RGBfloat temp;

    // First line:
    if (w == 0)
    {
        // First column:
        if (c == 0)
        {
            temp = sumRGBfloat(2, multiRGBfloat(image[w + 1][c], 2), multiRGBfloat(image[w + 1][c + 1], 1));
        }

        // Last column:
        else if (c == (width - 1))
        {
            temp  = sumRGBfloat(2, multiRGBfloat(image[w + 1][c - 1], 1), multiRGBfloat(image[w + 1][c], 2));
        }

        // Middle column:
        else
        {
            temp  = sumRGBfloat(3, multiRGBfloat(image[w + 1][c - 1], 1), multiRGBfloat(image[w + 1][c], 2), multiRGBfloat(image[w + 1][c + 1],
                                1));
        }
    }

    // Last line:
    else if (w == (height - 1))
    {
        // First column:
        if (c == 0)
        {
            temp  = sumRGBfloat(2, multiRGBfloat(image[w - 1][c], -2), multiRGBfloat(image[w - 1][c + 1], -1));
        }

        // Last column:
        else if (c == (width - 1))
        {
            temp  = sumRGBfloat(2, multiRGBfloat(image[w - 1][c - 1], -1),  multiRGBfloat(image[w - 1][c], -2));
        }

        // Middle column:
        else
        {
            temp  = sumRGBfloat(3, multiRGBfloat(image[w - 1][c - 1], -1), multiRGBfloat(image[w - 1][c], -2),
                                multiRGBfloat(image[w - 1][c + 1], -1));
        }
    }

    // Middle line:
    else
    {
        // First column:
        if (c == 0)
        {
            temp  = sumRGBfloat(4, multiRGBfloat(image[w - 1][c], -2), multiRGBfloat(image[w - 1][c + 1], -1),
                                multiRGBfloat(image[w + 1][c], 2), multiRGBfloat(image[w + 1][c + 1], 1));
        }

        // Last column:
        else if (c == (width - 1))
        {
            temp  = sumRGBfloat(4, multiRGBfloat(image[w - 1][c - 1], -1), multiRGBfloat(image[w - 1][c], -2),
                                multiRGBfloat(image[w + 1][c - 1], 1), multiRGBfloat(image[w + 1][c], 2));
        }

        // Middle column:
        else
        {
            temp  = sumRGBfloat(6, multiRGBfloat(image[w - 1][c - 1], -1), multiRGBfloat(image[w - 1][c], -2),
                                multiRGBfloat(image[w - 1][c + 1], -1), multiRGBfloat(image[w + 1][c - 1], 1),
                                multiRGBfloat(image[w + 1][c], 2), multiRGBfloat(image[w + 1][c + 1], 1));
        }
    }

    return temp;
}

// Edges function
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageout[height][width];

    // Go to each pixel in arr
    for (int w = 0; w < height; w++)
    {
        for (int k = 0; k < width; k++)
        {
            imageout[w][k] =  combine(gx(height, width, image, w, k), gy(height, width, image, w, k));
        }
    }

    // Copy imageout to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageout[i][j];
        }
    }
    return;
}