#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //find average of colors
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.00);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
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
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
        
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
            
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //top left corner variables
    float ravg_lcorner = 0;
    float gavg_lcorner = 0;
    float bavg_lcorner = 0;
    
    //top right corner variables
    float ravg_rcorner = 0;
    float gavg_rcorner = 0;
    float bavg_rcorner = 0;
    
    //bottom left corner variables
    float ravg_blcorner = 0;
    float gavg_blcorner = 0;
    float bavg_blcorner = 0;
    
    //bottom right corner variables
    float ravg_brcorner = 0;
    float gavg_brcorner = 0;
    float bavg_brcorner = 0;
    
    //top row center variables
    float ravg_topcenter = 0;
    float gavg_topcenter = 0;
    float bavg_topcenter = 0;
    
    //bottom row center variables
    float ravg_btmcenter = 0;
    float gavg_btmcenter = 0;
    float bavg_btmcenter = 0;
    
    //left side center variables
    float ravg_lscenter = 0;
    float gavg_lscenter = 0;
    float bavg_lscenter = 0;
    
    //right side center variables
    float ravg_rscenter = 0;
    float gavg_rscenter = 0;
    float bavg_rscenter = 0;
    
    //center variaables
    float ravg_center = 0;
    float gavg_center = 0;
    float bavg_center = 0;
    
    RGBTRIPLE copy_image[height][width];
    
    //create copy of image canvas
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }
    
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            
            //if pixel is at top row left corner 
            if (i == 0 && j == 0)
            {
                //calculate all red average
                ravg_lcorner = (int) round((copy_image[i][j].rgbtRed + copy_image[i][j + 1].rgbtRed + copy_image[i + 1][j].rgbtRed + copy_image[i + 1][j + 1].rgbtRed) / 4.00);
                //calculate all green average
                gavg_lcorner = (int) round((copy_image[i][j].rgbtGreen + copy_image[i][j + 1].rgbtGreen + copy_image[i + 1][j].rgbtGreen + copy_image[i + 1][j + 1].rgbtGreen) / 4.00);
                //calculate all blue average
                bavg_lcorner = (int) round((copy_image[i][j].rgbtBlue + copy_image[i][j + 1].rgbtBlue + copy_image[i + 1][j].rgbtBlue + copy_image[i + 1][j + 1].rgbtBlue) / 4.00);
                
                //new pixel color

                image[i][j].rgbtRed = ravg_lcorner;
                image[i][j].rgbtGreen = gavg_lcorner;
                image[i][j].rgbtBlue = bavg_lcorner;
                
            }
            
            //if pixel is top row right corner
            else if (i == 0 && j == width - 1)
            {
                //calculate all red average
                ravg_rcorner = (int) round((copy_image[i][j].rgbtRed + copy_image[i][j - 1].rgbtRed + copy_image[i + 1][j].rgbtRed + copy_image[i + 1][j - 1].rgbtRed) / 4.00);
                //calculate all green average
                gavg_rcorner = (int) round((copy_image[i][j].rgbtGreen + copy_image[i][j - 1].rgbtGreen + copy_image[i + 1][j].rgbtGreen + copy_image[i + 1][j - 1].rgbtGreen) / 4.00);
                //calculate all blue average
                bavg_rcorner = (int) round((copy_image[i][j].rgbtBlue + copy_image[i][j - 1].rgbtBlue + copy_image[i + 1][j].rgbtBlue + copy_image[i + 1][j - 1].rgbtBlue) / 4.00);
                
                //new pixel color
                image[i][j].rgbtRed = ravg_rcorner;
                image[i][j].rgbtGreen = gavg_rcorner;
                image[i][j].rgbtBlue = bavg_rcorner;
            }
            //if pixel is at bottom row left corner 
            else if(i == height - 1 && j == 0)
            {
                //calculate all red average
                ravg_blcorner = (int) round((copy_image[i][j].rgbtRed + copy_image[i][j + 1].rgbtRed + copy_image[i - 1][j].rgbtRed + copy_image[i -1 ][j + 1].rgbtRed) / 4.00);
                //calculate all green average
                gavg_blcorner = (int) round((copy_image[i][j].rgbtGreen + copy_image[i][j + 1].rgbtGreen + copy_image[i - 1][j].rgbtGreen + copy_image[i - 1][j + 1].rgbtGreen) / 4.00);
                //calculate all blue average
                bavg_blcorner = (int) round((copy_image[i][j].rgbtBlue + copy_image[i][j + 1].rgbtBlue + copy_image[i - 1][j].rgbtBlue + copy_image[i - 1][j + 1].rgbtBlue) / 4.00);
                
                //new pixel color
                image[i][j].rgbtRed = ravg_blcorner;
                image[i][j].rgbtGreen = gavg_blcorner;
                image[i][j].rgbtBlue = bavg_blcorner;
            }
          
            //if pixel is at bottom row right corner 
            else if(i == height -1 && j == width - 1)
            {
                //calculate all red average
                ravg_brcorner = (int) round((copy_image[i][j].rgbtRed + copy_image[i][j - 1].rgbtRed + copy_image[i - 1][j].rgbtRed + copy_image[i - 1][j - 1].rgbtRed) / 4.00);
                //calculate all green average
                gavg_brcorner = (int) round((copy_image[i][j].rgbtGreen + copy_image[i][j - 1].rgbtGreen + copy_image[i - 1][j].rgbtGreen + copy_image[i - 1][j - 1].rgbtGreen) / 4.00);
                //calculate all blue average
                bavg_brcorner = (int) round((copy_image[i][j].rgbtBlue + copy_image[i][j - 1].rgbtBlue + copy_image[i - 1][j].rgbtBlue + copy_image[i - 1][j - 1].rgbtBlue) / 4.00);
                
                //new pixel color
                image[i][j].rgbtRed = ravg_brcorner;
                image[i][j].rgbtGreen = gavg_brcorner;
                image[i][j].rgbtBlue = bavg_brcorner;
            }
          
            //if pixel is top row center
            else if(i == 0 && j < width - 1 && j > 0)
            {
                //calculate all red average
                ravg_topcenter = (int) round((copy_image[i][j].rgbtRed + copy_image[i][j - 1].rgbtRed + copy_image[i][j + 1].rgbtRed + copy_image[i + 1][j - 1].rgbtRed + copy_image[i + 1][j].rgbtRed + copy_image[i + 1][j + 1].rgbtRed) / 6.00);
                //calculate all green average
                gavg_topcenter = (int) round((copy_image[i][j].rgbtGreen + copy_image[i][j - 1].rgbtGreen + copy_image[i][j + 1].rgbtGreen + copy_image[i + 1][j - 1].rgbtGreen + copy_image[i + 1][j].rgbtGreen + copy_image[i + 1][j + 1].rgbtGreen) / 6.00);
                //calculate all blue average
                bavg_topcenter = (int) round((copy_image[i][j].rgbtBlue + copy_image[i][j - 1].rgbtBlue + copy_image[i][j + 1].rgbtBlue + copy_image[i + 1][j - 1].rgbtBlue + copy_image[i + 1][j].rgbtBlue + copy_image[i + 1][j + 1].rgbtBlue) / 6.00);
                
                //new pixel color
                image[i][j].rgbtRed = ravg_topcenter;
                image[i][j].rgbtGreen = gavg_topcenter;
                image[i][j].rgbtBlue = bavg_topcenter;
            }
           
          //if pixel is bottom row center
            else if(i == height - 1 && j < width - 1 && j > 0)
            {
                //calculate all red average
                ravg_btmcenter = (int) round((copy_image[i][j].rgbtRed + copy_image[i][j - 1].rgbtRed + copy_image[i][j + 1].rgbtRed + copy_image[i - 1][j - 1].rgbtRed + copy_image[i - 1][j].rgbtRed + copy_image[i - 1][j + 1].rgbtRed) / 6.00);
                //calculate all green average
                gavg_btmcenter = (int) round((copy_image[i][j].rgbtGreen + copy_image[i][j - 1].rgbtGreen + copy_image[i][j + 1].rgbtGreen + copy_image[i - 1][j - 1].rgbtGreen + copy_image[i - 1][j].rgbtGreen + copy_image[i - 1][j + 1].rgbtGreen) / 6.00);
                //calculate all blue average
                bavg_btmcenter = (int) round((copy_image[i][j].rgbtBlue + copy_image[i][j - 1].rgbtBlue + copy_image[i][j + 1].rgbtBlue + copy_image[i - 1][j - 1].rgbtBlue + copy_image[i - 1][j].rgbtBlue + copy_image[i - 1][j + 1].rgbtBlue) / 6.00);
                
                //new pixel color
                image[i][j].rgbtRed = ravg_btmcenter;
                image[i][j].rgbtGreen = gavg_btmcenter;
                image[i][j].rgbtBlue = bavg_btmcenter;
            }
     
            //if pixel is at left side edge
            else if (i < height - 1 && i > 0 && j == 0)
            {
                //calculate all red average
                ravg_lscenter = (int) round((copy_image[i][j].rgbtRed + copy_image[i][j + 1].rgbtRed + copy_image[i - 1][j].rgbtRed + copy_image[i - 1][j + 1].rgbtRed + copy_image[i + 1][j].rgbtRed + copy_image[i + 1][j + 1].rgbtRed) / 6.00);
                //calculate all green average
                gavg_lscenter = (int) round((copy_image[i][j].rgbtGreen + copy_image[i][j + 1].rgbtGreen + copy_image[i - 1][j].rgbtGreen + copy_image[i - 1][j + 1].rgbtGreen + copy_image[i + 1][j].rgbtGreen + copy_image[i + 1][j + 1].rgbtGreen) / 6.00);
                //calculate all blue average
                bavg_lscenter = (int) round((copy_image[i][j].rgbtBlue + copy_image[i][j + 1].rgbtBlue + copy_image[i - 1][j].rgbtBlue + copy_image[i - 1][j + 1].rgbtBlue + copy_image[i + 1][j].rgbtBlue + copy_image[i + 1][j + 1].rgbtBlue) / 6.00);
                
                //new pixel color
                image[i][j].rgbtRed = ravg_lscenter;
                image[i][j].rgbtGreen = gavg_lscenter;
                image[i][j].rgbtBlue = bavg_lscenter;
            }
            //if pixel is at right side edge
            else if (i < height - 1 && i > 0 && j == width - 1)
            {
                //calculate all red average
                ravg_rscenter = (int) round((copy_image[i][j].rgbtRed + copy_image[i][j - 1].rgbtRed + copy_image[i - 1][j].rgbtRed + copy_image[i - 1][j - 1].rgbtRed + copy_image[i + 1][j].rgbtRed + copy_image[i + 1][j - 1].rgbtRed) / 6.00);
                //calculate all green average
                gavg_rscenter = (int) round((copy_image[i][j].rgbtGreen + copy_image[i][j - 1].rgbtGreen + copy_image[i - 1][j].rgbtGreen + copy_image[i - 1][j - 1].rgbtGreen + copy_image[i + 1][j].rgbtGreen + copy_image[i + 1][j - 1].rgbtGreen) / 6.00);
                //calculate all blue average
                bavg_rscenter = (int) round((copy_image[i][j].rgbtBlue + copy_image[i][j - 1].rgbtBlue + copy_image[i - 1][j].rgbtBlue + copy_image[i - 1][j - 1].rgbtBlue + copy_image[i + 1][j].rgbtBlue + copy_image[i + 1][j - 1].rgbtBlue) / 6.00);
                
                //new pixel color
                image[i][j].rgbtRed = ravg_rscenter;
                image[i][j].rgbtGreen = gavg_rscenter;
                image[i][j].rgbtBlue = bavg_rscenter;
            }
            
            //if pixel is at center
            else if (i < height - 1 && i > 0 && j < width - 1 && j > 0)
            {
                //calculate all red average
                ravg_center = (int) round((copy_image[i][j].rgbtRed + copy_image[i][j - 1].rgbtRed + copy_image[i][j + 1].rgbtRed + copy_image[i + 1][j + 1].rgbtRed + copy_image[i + 1][j].rgbtRed + copy_image[i + 1][j - 1].rgbtRed + copy_image[i - 1][j - 1].rgbtRed + copy_image[i - 1][j].rgbtRed + copy_image[i - 1][j + 1].rgbtRed) / 9.00);
                //calculate all green average
                gavg_center = (int) round((copy_image[i][j].rgbtGreen + copy_image[i][j - 1].rgbtGreen + copy_image[i][j + 1].rgbtGreen + copy_image[i + 1][j + 1].rgbtGreen + copy_image[i + 1][j].rgbtGreen + copy_image[i + 1][j - 1].rgbtGreen + copy_image[i - 1][j - 1].rgbtGreen + copy_image[i - 1][j].rgbtGreen + copy_image[i - 1][j + 1].rgbtGreen) / 9.00);
                //calculate all blue average
                bavg_center = (int) round((copy_image[i][j].rgbtBlue + copy_image[i][j - 1].rgbtBlue + copy_image[i][j + 1].rgbtBlue + copy_image[i + 1][j + 1].rgbtBlue + copy_image[i + 1][j].rgbtBlue + copy_image[i + 1][j - 1].rgbtBlue + copy_image[i - 1][j - 1].rgbtBlue + copy_image[i - 1][j].rgbtBlue + copy_image[i - 1][j + 1].rgbtBlue) / 9.00);
                
                //new pixel color
                image[i][j].rgbtRed = ravg_center;
                image[i][j].rgbtGreen = gavg_center;
                image[i][j].rgbtBlue = bavg_center;
            }
            
        } 
    }
    
    return;
}