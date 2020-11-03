#include "./EasyBMP/EasyBMP.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <random>
#include <unistd.h>


int main(){
    srand(time(NULL));
    //color on the right 
    int r1 = rand() % 255;
    int g1 = rand() % 255;
    int b1 = rand() % 255;

    //color on the left
    int r2 = rand() % 255;
    int g2 = rand() % 255;
    int b2 = rand() % 255;

    //the color the gradient currently has
    int cur = r2;
    int cug = g2;
    int cub = b2;

    //the weight to caluclate the next color in the gradient with and the weight increment
    //by which the weight gets increased
    float weight = 0.0;
    float wi = 1.0/255.0;

    //setup for the image
    int img_width = 2000;
    int img_height = 2000;
    EasyBMP::RGBColor col1 (r1,g1,b1);
    EasyBMP::RGBColor col2 (r2,g2,b2);
    EasyBMP::RGBColor mid (cur,cug,cub);
    EasyBMP::Image img(img_width,img_height, "gradient.bmp", col1);

    //the x coordinate to change the pixel at
    int x = 0;
    //the max amount of rows to be painted in the same color
    float max_step = float(img_width)/255.0;
    while(x < img_width){
        //for the amount of steps color rows in the same color
        for (float stepsize = 0.0; stepsize < max_step; stepsize++) {
            //increment x value in here
            for (int y = 0; y < img_height; y++){
                img.SetPixel(x,y,mid);
            }
            x++;
        }
        //recalcualte the weight and then the color to be but for the pixels
        weight += wi;
        //x * c1 + (1-x) * c2
        cur = weight * r1 + (1-weight) * r2;
        cug = weight * g1 + (1-weight) * g2;
        cub = weight * b1 + (1-weight) * b2;
        mid.SetColor(cur,cug,cub);
    }
    //write the final image to file
    img.Write();

    //this part of the code will be related to opening the file for the user to see and admire
    int pid = fork();
    if(pid == 0){
        //im the child now
        execl("/usr/bin/xdg-open", "xdg-open", "gradient.bmp", (char *)0);
        exit(1);
    }
}