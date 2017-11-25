/*
* Tested effect of different levels of quantization, as expected for >= 255 it goes all black
* Why is quantization useful? What does it save ? 
* Check for different methods to compare timings
*
*
*/
// #include <stdio.h>
#include <iostream>
#include <string>
#include "ocv.h"

using namespace std;
using namespace cv;

void Sharpen(const Mat &myImage, Mat &Result);

int main(int argc, char **argv)
{ //try differnt methods for time comparison ? or be smart and see what happens for different divideWidths ?
    double start = (double)getTickCount();
    
    char *imagePath = argv[1];

    Mat image;
    Mat imageOutput;
    image = imread(imagePath, 1);

    if (!image.data)
    {
        printf(" No image data Line 30 \n ");
        return -1;
    }

    // Sharpen(image,imageOutput);
    Mat kern = (Mat_<char>(3, 3) << -1, -1, -1 ,
                                     0, 0, 0 ,
                                     1, 1, 1 );

    filter2D(image, imageOutput, image.depth(), kern);

    double endt = ((double)getTickCount() - start) / getTickFrequency();
    cout << "Times passed in seconds for masking: " << endt << endl;
    //compare times
    stringstream str;
    str << "horizontalEdges-"<< imagePath ;
    String outputImgName = str.str();

    imwrite("./images/output/HorizontalEdges.jpg" , imageOutput);

    namedWindow(imagePath, CV_WINDOW_AUTOSIZE);
    namedWindow(outputImgName, CV_WINDOW_AUTOSIZE);

    imshow(imagePath, image);
    imshow(outputImgName, imageOutput);

    //do we wait till key press ?
    waitKey(0);

    return 0;
}

void Sharpen(const Mat &myImage, Mat &Result)
{
    CV_Assert(myImage.depth() == CV_8U); // accept only uchar images

    Result.create(myImage.size(), myImage.type());
    const int nChannels = myImage.channels();

    for (int j = 1; j < myImage.rows - 1; ++j)
    {
        const uchar *previous = myImage.ptr<uchar>(j - 1);
        const uchar *current = myImage.ptr<uchar>(j);
        const uchar *next = myImage.ptr<uchar>(j + 1);

        uchar *output = Result.ptr<uchar>(j);

        for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i)
        {
            *output++ = saturate_cast<uchar>(5 * current[i] - current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
        }
    }

    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows - 1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols - 1).setTo(Scalar(0));
}