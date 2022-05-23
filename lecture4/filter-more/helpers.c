#include "helpers.h"
#include <string.h>
#include <stdint.h>
#include <math.h>
#define or ||
#define not !
#define and &&
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    // get average of all pixels through rgb values

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // get average before it is accessed
            int average = round((image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0);
            // index through rgbtriple uint8_t type
            image[h][w].rgbtRed = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];

    // copy from image to new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = image[i][j];
        }
    }


    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // reflect horizontally
            image[h][w].rgbtRed = new_image[h][width - w - 1].rgbtRed;
            image[h][w].rgbtGreen = new_image[h][width - w - 1].rgbtGreen;
            image[h][w].rgbtBlue = new_image[h][width - w - 1].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // iterate through height and width

    RGBTRIPLE copy_image[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy_image[h][w] = image[h][w];
        }
    }


    // pixel averages
    int red_avg;
    int green_avg;
    int blue_avg;
    float valid_pixels;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // pixels around current pixel accessed with h, w
            int pixels_around[9][2] = {{h, w}, {h, w - 1}, {h, w + 1}, {h - 1, w}, {h + 1, w}, {h - 1, w - 1}, {h + 1, w + 1}, {h - 1, w + 1}, {h + 1, w - 1}};
            valid_pixels = 0;
            red_avg = 0;
            green_avg = 0;
            blue_avg = 0;
            for (int pixel = 0; pixel < 9; pixel++)
            {
                if (pixels_around[pixel][0] >= 0 and pixels_around[pixel][0] < height and pixels_around[pixel][1] >= 0
                    and pixels_around[pixel][1] < width)
                {
                    // get all valid pixels to make sure we don't access garbage values
                    valid_pixels++;
                    red_avg += copy_image[pixels_around[pixel][0]][pixels_around[pixel][1]].rgbtRed;
                    green_avg += copy_image[pixels_around[pixel][0]][pixels_around[pixel][1]].rgbtGreen;
                    blue_avg += copy_image[pixels_around[pixel][0]][pixels_around[pixel][1]].rgbtBlue;
                }
            }
            // replace image pixels with rounded blurred pixels
            image[h][w].rgbtRed = round(red_avg / valid_pixels);
            image[h][w].rgbtGreen = round(green_avg / valid_pixels);
            image[h][w].rgbtBlue = round(blue_avg / valid_pixels);
        }
    }


    return;
}

// truncate to 255
uint8_t truncate(int num)
{
    if (num >= 255)
    {
        return 255;
    }
    return num;
}






// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original_image[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            original_image[h][w] = image[h][w];
        }
    }

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int x_sum[3];
    int y_sum[3];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int matrix[3][3][2] = {{{h + 1, w + 1}, {h + 1, w}, {h + 1, w - 1}}, {{h, w + 1}, {h, w}, {h, w - 1}}, {{h - 1, w + 1}, {h - 1, w}, {h - 1, w - 1}}};
            memset(&x_sum, 0, sizeof(x_sum));
            memset(&y_sum, 0, sizeof(y_sum));


            for (int i = 0; i < 3; i++)

            {
                for (int j = 0; j < 3; j++)
                {
                    if (matrix[i][j][0] >= height or matrix[i][j][0] < 0 or matrix[i][j][1] < 0 or matrix[i][j][1] >= width)
                    {
                        continue;
                    }
                    x_sum[0] += original_image[matrix[i][j][0]][matrix[i][j][1]].rgbtRed * gx[i][j];
                    x_sum[1] += original_image[matrix[i][j][0]][matrix[i][j][1]].rgbtGreen * gx[i][j];
                    x_sum[2] += original_image[matrix[i][j][0]][matrix[i][j][1]].rgbtBlue * gx[i][j];
                    y_sum[0] += original_image[matrix[i][j][0]][matrix[i][j][1]].rgbtRed * gy[i][j];
                    y_sum[1] += original_image[matrix[i][j][0]][matrix[i][j][1]].rgbtGreen * gy[i][j];
                    y_sum[2] += original_image[matrix[i][j][0]][matrix[i][j][1]].rgbtBlue * gy[i][j];
                }
            }
            image[h][w].rgbtRed = truncate(round(sqrt(x_sum[0] * x_sum[0] + y_sum[0] * y_sum[0])));
            image[h][w].rgbtGreen = truncate(round(sqrt(x_sum[1] * x_sum[1] + y_sum[1] * y_sum[1])));
            image[h][w].rgbtBlue = truncate(round(sqrt(x_sum[2] * x_sum[2] + y_sum[2] * y_sum[2])));
        }
    }
    return ;
}
