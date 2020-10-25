#include "./EasyBMP/EasyBMP.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

    /*
        To generate a gradient pick two starting colors. these are currently defined through
        the variables r1..b1 and r2..b2. 
        Then based on the width of the image and the colorspace(rbg with 8 bit) calculate
        how many pixels shoudl be colored in the the color before moving on to the next color. 
        The variable holding this information is incremented after each pass of n written rows
        It is applied to all three color values r, g and b and these are saved in cu?


        have to have the x value for the fomular saved as maybe weight in a float and incremented by 
        1 / 255 as a float.

        whith the weight then calculate the current color to be drawn for the stepsize of pixels and then 
        with the next iteration increment the weight by 1/255 again.
    */

int main(){
    int r1;
    int g1;
    int b1 = 255;

    int r2 = 255;
    int g2;
    int b2;

    int cur = r1;
    int cug = g1;
    int cub = b1;


    float weight = 0.0;
    float wi = 1.0/255.0;


    //img.setpixel for changing pixel values
    int img_width = 180;
    int img_height = 2000;
    EasyBMP::RGBColor col1 (r1,g1,b1);
    EasyBMP::RGBColor col2 (r2,g2,b2);
    EasyBMP::RGBColor mid (cur,cug,cub);
    EasyBMP::Image img(img_width,img_height, "gradient.bmp", col1);

    int x = 0;
    float max_step = float(img_width)/255.0;
    while(x < img_width){
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




    img.Write();
}
