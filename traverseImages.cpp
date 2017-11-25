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

Mat &ScanImageAndReduceC(Mat &I, const uchar *const table);

int main(int argc, char **argv)
{//try differnt methods for time comparison ? or be smart and see what happens for different divideWidths ?
    double start = (double)getTickCount();
    int divideWith = 0; // convert our input string to number - C++ style
    stringstream s;
    s << argv[2];
    s >> divideWith;//what soccerey is this?

    if (!s || !divideWith)
    {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }
    
    uchar table[256];
    for (int i = 0; i < 256; ++i)
    table[i] = (uchar)(divideWith * (i / divideWith));

    
    char *imagePath = argv[1];
    
    Mat image;
    Mat imageOutput;
    image = imread(imagePath, 1);
    
    if ( !image.data)
    {
        printf(" No image data Line 38 \n ");
        return -1;
    }
    
    
    //inbuilt method
    Mat lookUpTable(1, 256, CV_8U);
    uchar *p = lookUpTable.data;
    for (int i = 0; i < 256; ++i){
        p[i] = table[i];
    }

    LUT(image, lookUpTable, imageOutput);
    
    double endt = ((double)getTickCount() - start) / getTickFrequency();
    cout << "Times passed in seconds for quantization with inbuilt LUT: " << endt << endl;
    //compare times
    stringstream str ;
    str << "qi" << divideWith;
    String outputImgName = str.str();

    imwrite("./images/output/"+ outputImgName + ".jpg" , imageOutput);
    

    namedWindow(imagePath, CV_WINDOW_AUTOSIZE);
    namedWindow( outputImgName, CV_WINDOW_AUTOSIZE);

    imshow(imagePath , image);
    imshow( outputImgName , imageOutput);
    
    //do we wait till key press ?
    waitKey(0);

    return 0;    
}
// .data return the 1st pointer anywhere
Mat& ScanImageAndReduceC(Mat &I, const uchar *const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    int channels = I.channels();

    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i, j;
    uchar *p;
    for (i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);//gets the pointer to the starting of the i'th row
        for (j = 0; j < nCols; ++j)
        {
            p[j] = table[p[j]];//moves numColums steps fwd in the contigous memory assigning to each value , its reduced map
        }
    }
    return I;

    //for grayscale //understood
    // uchar *p = I.data;
    // for (unsigned int i = 0; i < ncol * nrows; ++i)
    //     *p++ = table[*p];
}

Mat &ScanImageAndReduceIterator(Mat &I, const uchar *const table)
{//slower because of iterator use and not direct pointers , but safer   
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch (channels)
    {
    case 1:
    {
        MatIterator_<uchar> it, end;
        for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
            *it = table[*it];
        break;
    }
    case 3:
    {
        MatIterator_<Vec3b> it, end;
        for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
        {
            (*it)[0] = table[(*it)[0]];
            (*it)[1] = table[(*it)[1]];
            (*it)[2] = table[(*it)[2]];
        }
    }
    }

    return I;
}

Mat &ScanImageAndReduceRandomAccess(Mat &I, const uchar *const table)
{//access of random memory blocks , bad but how are they random ?//unrecommended
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch (channels)
    {
    case 1:
    {
        for (int i = 0; i < I.rows; ++i)
            for (int j = 0; j < I.cols; ++j)
                I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
        break;
    }
    case 3:
    {
        Mat_<Vec3b> _I = I;

        for (int i = 0; i < I.rows; ++i)
            for (int j = 0; j < I.cols; ++j)
            {
                _I(i, j)
                [0] = table[_I(i, j)[0]];
                _I(i, j)
                [1] = table[_I(i, j)[1]];
                _I(i, j)
                [2] = table[_I(i, j)[2]];
            }
        I = _I;
        break;
    }
    }

    return I;
}