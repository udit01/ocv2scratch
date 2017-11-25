#include <stdio.h>
#include "ocv.h"
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