#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the mean variable
            int mean = (int) ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0 + 0.5);

            image[i][j].rgbtBlue = mean;
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtRed = mean;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Set the values of the images according to the sepia values
            image[i][j].rgbtRed = fmin(255, (int) (0.393 * originalRed + +0.769 * originalGreen + 0.189 * originalBlue + 0.5));
            image[i][j].rgbtGreen = fmin(255, (int) (0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue + 0.5));
            image[i][j].rgbtBlue = fmin(255, (int) (0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue + 0.5));
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //  Swap pixel's values
            RGBTRIPLE new = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = new;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize variables to store the sum of red, green, and blue values
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            float count = 0.00;
            // Loop through a 3x3 grid around the current pixel
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Calculate the coordinates of the neighboring pixel
                    int currentK = i + k;
                    int currentL = j + l;
                    //// Check if the neighboring pixel is out of bounds
                    if (currentK < 0 || currentK > (height - 1) || currentL < 0 || currentL > (width - 1))
                    {
                        continue;
                    }
                    // Sum the red, green, and blue values of the neighboring pixel
                    totalRed += image[currentK][currentL].rgbtRed;
                    totalGreen += image[currentK][currentL].rgbtGreen;
                    totalBlue += image[currentK][currentL].rgbtBlue;

                    count++;
                }
            }
            // Calculate the new pixel values by averaging the neighboring pixels
            new[i][j].rgbtRed = round(totalRed / count);
            new[i][j].rgbtGreen = round(totalGreen / count);
            new[i][j].rgbtBlue = round(totalBlue / count);
        }
    }
    // Copy the modified image back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new[i][j];
        }
    }
    // Return from the function
    return;
}
