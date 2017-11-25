#include <stdio.h>
// #include <opencv2/cv.h>
#include <opencv2/core/core.hpp>

#include <opencv2/opencv.hpp>
#include "IntroConfig.h"

using namespace cv;

int main(int argc, char **argv)
{
    // ver::printVersion();

    if (argc != 2)
    {
        printf("usage is: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    
    Mat image;
    image = imread(argv[1], 1);

    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);

    waitKey(0);

    return 0;
}