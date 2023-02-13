#include "helpers.h"
#include <math.h>


    // define pixel position shortcuts
    #define topleft (buffer[i - 1][j - 1])
    #define topmid (buffer[i - 1][j])
    #define topright (buffer[i - 1][j + 1])
    #define left (buffer[i][j - 1])
    #define mid (buffer[i][j])
    #define right (buffer[i][j + 1])
    #define botleft (buffer[i + 1][j - 1])
    #define botmid (buffer[i + 1][j])
    #define botright (buffer[i + 1][j + 1])

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;

            float avg = round((red + blue + green) / 3);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];

// generate copy of original image into buffer
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = image[i][j];
        }
    }

// loop through each pixel and calculate averages
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // check if pixel exists in corner
            if (i == 0 && j == 0)
            {
                // logic to solve for top left
                float avg_red = round((mid.rgbtRed + right.rgbtRed + botmid.rgbtRed + botright.rgbtRed) / 4.0);
                float avg_blue = round((mid.rgbtBlue + right.rgbtBlue + botmid.rgbtBlue + botright.rgbtBlue) / 4.0);
                float avg_green = round((mid.rgbtGreen + right.rgbtGreen + botmid.rgbtGreen + botright.rgbtGreen) / 4.0);
                image[i][j].rgbtRed = avg_red;
                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
            }
            else if (i == 0  && j == width - 1)
            {
                // logic to solve for top right
                float avg_red = round((mid.rgbtRed + left.rgbtRed + botmid.rgbtRed + botleft.rgbtRed) / 4.0);
                float avg_blue = round((mid.rgbtBlue + left.rgbtBlue + botmid.rgbtBlue + botleft.rgbtBlue) / 4.0);
                float avg_green = round((mid.rgbtGreen + left.rgbtGreen + botmid.rgbtGreen + botleft.rgbtGreen) / 4.0);
                image[i][j].rgbtRed = avg_red;
                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
            }
            else if (i == height - 1 && j == 0)
            {
                // logic to solve for bottom left
                float avg_red = round((mid.rgbtRed + right.rgbtRed + topmid.rgbtRed + topright.rgbtRed) / 4.0);
                float avg_blue = round((mid.rgbtBlue + right.rgbtBlue + topmid.rgbtBlue + topright.rgbtBlue) / 4.0);
                float avg_green = round((mid.rgbtGreen + right.rgbtGreen + topmid.rgbtGreen+ topright.rgbtGreen) / 4.0);
                image[i][j].rgbtRed = avg_red;
                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
            }
            else if (i == height - 1 && j == width - 1)
            {
                // logic to solve for bottom right
                float avg_red = round((mid.rgbtRed + left.rgbtRed + topmid.rgbtRed + topleft.rgbtRed) / 4.0);
                float avg_blue = round((mid.rgbtBlue + left.rgbtBlue + topmid.rgbtBlue + topleft.rgbtBlue) / 4.0);
                float avg_green = round((mid.rgbtGreen + left.rgbtGreen + topmid.rgbtGreen + topleft.rgbtGreen) / 4.0);
                image[i][j].rgbtRed = avg_red;
                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
            }
            // check for edges
            else if (i == 0)
            {
                // logic to solve for top edge
                float avg_red = round((mid.rgbtRed + left.rgbtRed + right.rgbtRed +
                                    botmid.rgbtRed + botleft.rgbtRed + botright.rgbtRed) / 6.0);
                float avg_blue = round((mid.rgbtBlue + left.rgbtBlue + right.rgbtBlue +
                                    botmid.rgbtBlue + botleft.rgbtBlue + botright.rgbtBlue) / 6.0);
                float avg_green = round((mid.rgbtGreen + left.rgbtGreen + right.rgbtGreen +
                                    botmid.rgbtGreen + botleft.rgbtGreen + botright.rgbtGreen) / 6.0);
                image[i][j].rgbtRed = avg_red;
                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
            }
            else if (i == height - 1)
            {
                // logic to solve for bottom edge
                float avg_red = round((mid.rgbtRed + left.rgbtRed + right.rgbtRed +
                                    topmid.rgbtRed + topleft.rgbtRed + topright.rgbtRed) / 6.0);
                float avg_blue = round((mid.rgbtBlue + left.rgbtBlue + right.rgbtBlue +
                                    topmid.rgbtBlue + topleft.rgbtBlue + topright.rgbtBlue) / 6.0);
                float avg_green = round((mid.rgbtGreen + left.rgbtGreen + right.rgbtGreen +
                                    topmid.rgbtGreen + topleft.rgbtGreen + topright.rgbtGreen) / 6.0);
                image[i][j].rgbtRed = avg_red;
                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
            }
            else if (j == 0)
            {
                // logic to solve for left edge
                float avg_red = round((mid.rgbtRed + right.rgbtRed + topmid.rgbtRed + topright.rgbtRed +
                                    botmid.rgbtRed + botright.rgbtRed) / 6.0);
                float avg_blue = round((mid.rgbtBlue + right.rgbtBlue + topmid.rgbtBlue + topright.rgbtBlue +
                                    botmid.rgbtBlue + botright.rgbtBlue) / 6.0);
                float avg_green = round((mid.rgbtGreen + right.rgbtGreen + topmid.rgbtGreen + topright.rgbtGreen +
                                    botmid.rgbtGreen + botright.rgbtGreen) / 6.0);
                image[i][j].rgbtRed = avg_red;
                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
            }
            else if (j == width - 1)
            {
                // logic to solve for right edge
                float avg_red = round((mid.rgbtRed + left.rgbtRed + topmid.rgbtRed + topleft.rgbtRed +
                                    botmid.rgbtRed + botleft.rgbtRed) / 6.0);
                float avg_blue = round((mid.rgbtBlue + left.rgbtBlue + topmid.rgbtBlue + topleft.rgbtBlue +
                                    botmid.rgbtBlue + botleft.rgbtBlue) / 6.0);
                float avg_green = round((mid.rgbtGreen + left.rgbtGreen + topmid.rgbtGreen + topleft.rgbtGreen +
                                    botmid.rgbtGreen + botleft.rgbtGreen) / 6.0);
                image[i][j].rgbtRed = avg_red;
                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
            }
            // calculate averages for all pixels around
            else
            {
                float avg_red = round((mid.rgbtRed + left.rgbtRed + right.rgbtRed + topmid.rgbtRed + topleft.rgbtRed + topright.rgbtRed +
                                        botmid.rgbtRed + botleft.rgbtRed + botright.rgbtRed) / 9.0);
                float avg_blue = round((mid.rgbtBlue + left.rgbtBlue + right.rgbtBlue + topmid.rgbtBlue + topleft.rgbtBlue + topright.rgbtBlue +
                                        botmid.rgbtBlue + botleft.rgbtBlue + botright.rgbtBlue) / 9.0);
                float avg_green = round((mid.rgbtGreen + left.rgbtGreen + right.rgbtGreen + topmid.rgbtGreen + topleft.rgbtGreen + topright.rgbtGreen +
                                        botmid.rgbtGreen + botleft.rgbtGreen + botright.rgbtGreen) / 9.0);
                image[i][j].rgbtRed = avg_red;
                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
        RGBTRIPLE buffer[height][width];

    // generate copy of original image into buffer
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = image[i][j];
        }
    }

    // loop through and determine edge lines
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // logic to calculate top left
            if (i == 0 && j == 0)
            {
                float edge_redx = pow(((mid.rgbtRed * 0) + (right.rgbtRed * 2) + (botmid.rgbtRed * 0) + (botright.rgbtRed * 1)), 2);
                float edge_redy = pow(((mid.rgbtRed * 0) + (right.rgbtRed * 0) + (botmid.rgbtRed * 2) + (botright.rgbtRed * 1)), 2);
                float edge_bluex = pow(((mid.rgbtBlue * 0) + (right.rgbtBlue * 2) + (botmid.rgbtBlue * 0) + (botright.rgbtBlue * 1)), 2);
                float edge_bluey = pow(((mid.rgbtBlue * 0) + (right.rgbtBlue * 0) + (botmid.rgbtBlue * 2) + (botright.rgbtBlue * 1)), 2);
                float edge_greenx = pow(((mid.rgbtGreen * 0) + (right.rgbtGreen * 2) + (botmid.rgbtGreen * 0) + (botright.rgbtGreen * 1)), 2);
                float edge_greeny = pow(((mid.rgbtGreen * 0) + (right.rgbtGreen * 0) + (botmid.rgbtGreen * 2) + (botright.rgbtGreen * 1)), 2);
                float red = round(sqrt(edge_redx + edge_redy));
                float green = round(sqrt(edge_greenx + edge_greeny));
                float blue = round(sqrt(edge_bluex + edge_bluey));
                if (red > 255)
                {
                    red = 255;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                if (green > 255)
                {
                    green = 255;
                }
                image[i][j].rgbtRed = red;
                image[i][j].rgbtBlue = blue;
                image[i][j].rgbtGreen = green;
            }
            // logic to check top right
            else if (i == 0  && j == width - 1)
            {
                float edge_redx = pow(((mid.rgbtRed * 0) + (left.rgbtRed * -2) + (botmid.rgbtRed * 0) + (botleft.rgbtRed * -1)), 2);
                float edge_redy = pow(((mid.rgbtRed * 0) + (left.rgbtRed * 0) + (botmid.rgbtRed * 2) + (botleft.rgbtRed * 1)), 2);
                float edge_bluex = pow(((mid.rgbtBlue * 0) + (left.rgbtBlue * -2) + (botmid.rgbtBlue * 0) + (botleft.rgbtBlue * -1)), 2);
                float edge_bluey = pow(((mid.rgbtBlue * 0) + (left.rgbtBlue * 0) + (botmid.rgbtBlue * 2) + (botleft.rgbtBlue * 1)), 2);
                float edge_greenx = pow(((mid.rgbtGreen * 0) + (left.rgbtGreen * -2) + (botmid.rgbtGreen * 0) + (botleft.rgbtGreen * -1)), 2);
                float edge_greeny = pow(((mid.rgbtGreen * 0) + (left.rgbtGreen * 0) + (botmid.rgbtGreen * 2) + (botleft.rgbtGreen * 1)), 2);
                float red = round(sqrt(edge_redx + edge_redy));
                float green = round(sqrt(edge_greenx + edge_greeny));
                float blue = round(sqrt(edge_bluex + edge_bluey));
                if (red > 255)
                {
                    red = 255;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                if (green > 255)
                {
                    green = 255;
                }
                image[i][j].rgbtRed = red;
                image[i][j].rgbtBlue = blue;
                image[i][j].rgbtGreen = green;
            }
            // logic to calculate bottom left
            else if (i == height - 1 && j == 0)
            {
                float edge_redx = pow(((mid.rgbtRed * 0) + (right.rgbtRed * 2) + (topmid.rgbtRed * 0) + (topright.rgbtRed * 1)), 2);
                float edge_redy = pow(((mid.rgbtRed * 0) + (right.rgbtRed * 0) + (topmid.rgbtRed * -2) + (topright.rgbtRed * -1)), 2);
                float edge_bluex = pow(((mid.rgbtBlue * 0) + (right.rgbtBlue * 2) + (topmid.rgbtBlue * 0) + (topright.rgbtBlue * 1)), 2);
                float edge_bluey = pow(((mid.rgbtBlue * 0) + (right.rgbtBlue * 0) + (topmid.rgbtBlue * -2) + (topright.rgbtBlue * -1)), 2);
                float edge_greenx = pow(((mid.rgbtGreen * 0) + (right.rgbtGreen * 2) + (topmid.rgbtGreen * 0) + (topright.rgbtGreen * 1)), 2);
                float edge_greeny = pow(((mid.rgbtGreen * 0) + (right.rgbtGreen * 0) + (topmid.rgbtGreen * -2) + (topright.rgbtGreen * -1)), 2);
                float red = round(sqrt(edge_redx + edge_redy));
                float green = round(sqrt(edge_greenx + edge_greeny));
                float blue = round(sqrt(edge_bluex + edge_bluey));
                if (red > 255)
                {
                    red = 255;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                if (green > 255)
                {
                    green = 255;
                }
                image[i][j].rgbtRed = red;
                image[i][j].rgbtBlue = blue;
                image[i][j].rgbtGreen = green;
            }
            // logic to check bottom right
            else if (i == height - 1 && j == width - 1)
            {
                float edge_redx = pow(((mid.rgbtRed * 0) + (left.rgbtRed * -2) + (topmid.rgbtRed * 0) + (topleft.rgbtRed * -1)), 2);
                float edge_redy = pow(((mid.rgbtRed * 0) + (left.rgbtRed * 0) + (topmid.rgbtRed * -2) + (topleft.rgbtRed * -1)), 2);
                float edge_bluex = pow(((mid.rgbtBlue * 0) + (left.rgbtBlue * -2) + (topmid.rgbtBlue * 0) + (topleft.rgbtBlue * -1)), 2);
                float edge_bluey = pow(((mid.rgbtBlue * 0) + (left.rgbtBlue * 0) + (topmid.rgbtBlue * -2) + (topleft.rgbtBlue * -1)), 2);
                float edge_greenx = pow(((mid.rgbtGreen * 0) + (left.rgbtGreen * -2) + (topmid.rgbtGreen * 0) + (topleft.rgbtGreen * -1)), 2);
                float edge_greeny = pow(((mid.rgbtGreen * 0) + (left.rgbtGreen * 0) + (topmid.rgbtGreen * -2) + (topleft.rgbtGreen * -1)), 2);
                float red = round(sqrt(edge_redx + edge_redy));
                float green = round(sqrt(edge_greenx + edge_greeny));
                float blue = round(sqrt(edge_bluex + edge_bluey));
                if (red > 255)
                {
                    red = 255;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                if (green > 255)
                {
                    green = 255;
                }
                image[i][j].rgbtRed = red;
                image[i][j].rgbtBlue = blue;
                image[i][j].rgbtGreen = green;
            }
            // logic to check top edge
            else if (i == 0)
            {
                float edge_redx = pow(((mid.rgbtRed * 0) + (left.rgbtRed * -2) + (right.rgbtRed * 2) + (botmid.rgbtRed * 0) +
                                        (botleft.rgbtRed * -1) + (botright.rgbtRed * 1)), 2);
                float edge_redy = pow(((mid.rgbtRed * 0) + (left.rgbtRed * 0) + (right.rgbtRed * 0) + (botmid.rgbtRed * 2) +
                                        (botleft.rgbtRed * 1) + (botright.rgbtRed * 1)), 2);
                float edge_bluex = pow(((mid.rgbtBlue * 0) + (left.rgbtBlue * -2) + (right.rgbtBlue * 2) + (botmid.rgbtBlue * 0) +
                                        (botleft.rgbtBlue * -1) + (botright.rgbtBlue * 1)), 2);
                float edge_bluey = pow(((mid.rgbtBlue * 0) + (left.rgbtBlue * 0) + (right.rgbtBlue * 0) + (botmid.rgbtBlue * 2) +
                                        (botleft.rgbtBlue * 1) + (botright.rgbtBlue * 1)), 2);
                float edge_greenx = pow(((mid.rgbtGreen * 0) + (left.rgbtGreen * -2) + (right.rgbtGreen * 2) + (botmid.rgbtGreen * 0) +
                                        (botleft.rgbtGreen * -1) + (botright.rgbtGreen * 1)), 2);
                float edge_greeny = pow(((mid.rgbtGreen * 0) + (left.rgbtGreen * 0) + (right.rgbtGreen * 0) + (botmid.rgbtGreen * 2) +
                                        (botleft.rgbtGreen * 1) + (botright.rgbtGreen * 1)), 2);
                float red = round(sqrt(edge_redx + edge_redy));
                float green = round(sqrt(edge_greenx + edge_greeny));
                float blue = round(sqrt(edge_bluex + edge_bluey));
                if (red > 255)
                {
                    red = 255;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                if (green > 255)
                {
                    green = 255;
                }
                image[i][j].rgbtRed = red;
                image[i][j].rgbtBlue = blue;
                image[i][j].rgbtGreen = green;
            }
            // logic to calculate bottom edge
            else if (i == height - 1)
            {
                float edge_redx = pow(((mid.rgbtRed * 0) + (left.rgbtRed * -2) + (right.rgbtRed * 2) + (topmid.rgbtRed * 0) +
                                        (topleft.rgbtRed * -1) + (topright.rgbtRed * 1)), 2);
                float edge_redy = pow(((mid.rgbtRed * 0) + (left.rgbtRed * 0) + (right.rgbtRed * 0) + (topmid.rgbtRed * -2) +
                                        (topleft.rgbtRed * -1) + (topright.rgbtRed * -1)), 2);
                float edge_bluex = pow(((mid.rgbtBlue * 0) + (left.rgbtBlue * -2) + (right.rgbtBlue * 2) + (topmid.rgbtBlue * 0) +
                                        (topleft.rgbtBlue * -1) + (topright.rgbtBlue * 1)), 2);
                float edge_bluey = pow(((mid.rgbtBlue * 0) + (left.rgbtBlue * 0) + (right.rgbtBlue * 0) + (topmid.rgbtBlue * -2) +
                                        (topleft.rgbtBlue * -1) + (topright.rgbtBlue * -1)), 2);
                float edge_greenx = pow(((mid.rgbtGreen * 0) + (left.rgbtGreen * -2) + (right.rgbtGreen * 2) + (topmid.rgbtGreen * 0) +
                                        (topleft.rgbtGreen * -1) + (topright.rgbtGreen * 1)), 2);
                float edge_greeny = pow(((mid.rgbtGreen * 0) + (left.rgbtGreen * 0) + (right.rgbtGreen * 0) + (topmid.rgbtGreen * -2) +
                                        (topleft.rgbtGreen * -1) + (topright.rgbtGreen * -1)), 2);
                float red = round(sqrt(edge_redx + edge_redy));
                float green = round(sqrt(edge_greenx + edge_greeny));
                float blue = round(sqrt(edge_bluex + edge_bluey));
                if (red > 255)
                {
                    red = 255;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                if (green > 255)
                {
                    green = 255;
                }
                image[i][j].rgbtRed = red;
                image[i][j].rgbtBlue = blue;
                image[i][j].rgbtGreen = green;
            }
            // logic to check left edge
            else if (j == 0)
            {
                float edge_redx = pow(((mid.rgbtRed * 0) + (right.rgbtRed * 2) + (topmid.rgbtRed * 0) + (topright.rgbtRed * 1) +
                                        (botmid.rgbtRed * 0) + (botright.rgbtRed * 1)), 2);
                float edge_redy = pow(((mid.rgbtRed * 0) + (right.rgbtRed * 0) + (topmid.rgbtRed * -2) + (topright.rgbtRed * -1) +
                                        (botmid.rgbtRed * 2) + (botright.rgbtRed * 1)), 2);
                float edge_bluex = pow(((mid.rgbtBlue * 0) + (right.rgbtBlue * 2) + (topmid.rgbtBlue * 0) + (topright.rgbtBlue * 1) +
                                        (botmid.rgbtBlue * 0) + (botright.rgbtBlue * 1)), 2);
                float edge_bluey = pow(((mid.rgbtBlue * 0) + (right.rgbtBlue * 0) + (topmid.rgbtBlue * -2) + (topright.rgbtBlue * -1) +
                                        (botmid.rgbtBlue * 2) + (botright.rgbtBlue * 1)), 2);
                float edge_greenx = pow(((mid.rgbtGreen * 0) + (right.rgbtGreen * 2) + (topmid.rgbtGreen * 0) + (topright.rgbtGreen * 1) +
                                        (botmid.rgbtGreen * 0) + (botright.rgbtGreen * 1)), 2);
                float edge_greeny = pow(((mid.rgbtGreen * 0) + (right.rgbtGreen * 0) + (topmid.rgbtGreen * -2) + (topright.rgbtGreen * -1) +
                                        (botmid.rgbtGreen * 2) + (botright.rgbtGreen * 1)), 2);
                float red = round(sqrt(edge_redx + edge_redy));
                float green = round(sqrt(edge_greenx + edge_greeny));
                float blue = round(sqrt(edge_bluex + edge_bluey));
                if (red > 255)
                {
                    red = 255;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                if (green > 255)
                {
                    green = 255;
                }
                image[i][j].rgbtRed = red;
                image[i][j].rgbtBlue = blue;
                image[i][j].rgbtGreen = green;
            }
            // logic to check right edge
            else if (j == width - 1)
            {
                float edge_redx = pow(((mid.rgbtRed * 0) + (left.rgbtRed * -2) + (topmid.rgbtRed * 0) + (topleft.rgbtRed * -1) +
                                        (botmid.rgbtRed * 0) + (botleft.rgbtRed * -1)), 2);
                float edge_redy = pow(((mid.rgbtRed * 0) + (left.rgbtRed * 0) + (topmid.rgbtRed * -2) + (topleft.rgbtRed * -1) +
                                        (botmid.rgbtRed * 2) + (botleft.rgbtRed * 1)), 2);
                float edge_bluex = pow(((mid.rgbtBlue * 0) + (left.rgbtBlue * -2) + (topmid.rgbtBlue * 0) + (topleft.rgbtBlue * -1) +
                                        (botmid.rgbtBlue * 0) + (botleft.rgbtBlue * -1)), 2);
                float edge_bluey = pow(((mid.rgbtBlue * 0) + (left.rgbtBlue * 0) + (topmid.rgbtBlue * -2) + (topleft.rgbtBlue * -1) +
                                        (botmid.rgbtBlue * 2) + (botleft.rgbtBlue * 1)), 2);
                float edge_greenx = pow(((mid.rgbtGreen * 0) + (left.rgbtGreen * -2) + (topmid.rgbtGreen * 0) + (topleft.rgbtGreen * -1) +
                                        (botmid.rgbtGreen * 0) + (botleft.rgbtGreen * -1)), 2);
                float edge_greeny = pow(((mid.rgbtGreen * 0) + (left.rgbtGreen * 0) + (topmid.rgbtGreen * -2) + (topleft.rgbtGreen * -1) +
                                        (botmid.rgbtGreen * 2) + (botleft.rgbtGreen * 1)), 2);
                float red = round(sqrt(edge_redx + edge_redy));
                float green = round(sqrt(edge_greenx + edge_greeny));
                float blue = round(sqrt(edge_bluex + edge_bluey));
                if (red > 255)
                {
                    red = 255;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                if (green > 255)
                {
                    green = 255;
                }
                image[i][j].rgbtRed = red;
                image[i][j].rgbtBlue = blue;
                image[i][j].rgbtGreen = green;
            }
            // logic to check all
            else
            {
                float edge_redx = pow(((mid.rgbtRed * 0) + (left.rgbtRed * -2) + (right.rgbtRed * 2) + (topmid.rgbtRed * 0) +
                                        (topleft.rgbtRed * -1) + (topright.rgbtRed * 1) + (botmid.rgbtRed * 0) + (botleft.rgbtRed * -1) + (botright.rgbtRed * 1)), 2);
                float edge_redy = pow(((mid.rgbtRed * 0) + (left.rgbtRed * 0) + (right.rgbtRed * 0) + (topmid.rgbtRed * -2) +
                                        (topleft.rgbtRed * -1) + (topright.rgbtRed * -1) + (botmid.rgbtRed * 2) + (botleft.rgbtRed * 1) + (botright.rgbtRed * 1)), 2);
                float edge_bluex = pow(((mid.rgbtBlue * 0) + (left.rgbtBlue * -2) + (right.rgbtBlue * 2) + (topmid.rgbtBlue * 0) +
                                        (topleft.rgbtBlue * -1) + (topright.rgbtBlue * 1) + (botmid.rgbtBlue * 0) + (botleft.rgbtBlue * -1) + (botright.rgbtBlue * 1)), 2);
                float edge_bluey = pow(((mid.rgbtBlue * 0) + (left.rgbtBlue * 0) + (right.rgbtBlue * 0) + (topmid.rgbtBlue * -2) +
                                        (topleft.rgbtBlue * -1) + (topright.rgbtBlue * -1) + (botmid.rgbtBlue * 2) + (botleft.rgbtBlue * 1) + (botright.rgbtBlue * 1)), 2);
                float edge_greenx = pow(((mid.rgbtGreen * 0) + (left.rgbtGreen * -2) + (right.rgbtGreen * 2) + (topmid.rgbtGreen * 0) +
                                        (topleft.rgbtGreen * -1) + (topright.rgbtGreen * 1) + (botmid.rgbtGreen * 0) + (botleft.rgbtGreen * -1) + (botright.rgbtGreen * 1)), 2);
                float edge_greeny = pow(((mid.rgbtGreen * 0) + (left.rgbtGreen * 0) + (right.rgbtGreen * 0) + (topmid.rgbtGreen * -2) +
                                        (topleft.rgbtGreen * -1) + (topright.rgbtGreen * -1) + (botmid.rgbtGreen * 2) + (botleft.rgbtGreen * 1) + (botright.rgbtGreen * 1)), 2);
                float red = round(sqrt(edge_redx + edge_redy));
                float green = round(sqrt(edge_greenx + edge_greeny));
                float blue = round(sqrt(edge_bluex + edge_bluey));
                if (red > 255)
                {
                    red = 255;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                if (green > 255)
                {
                    green = 255;
                }
                image[i][j].rgbtRed = red;
                image[i][j].rgbtBlue = blue;
                image[i][j].rgbtGreen = green;
            }
        }
    }
    return;
}
