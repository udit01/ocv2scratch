/*
Author : Udit Jain [udit01]

This code slices the forward image in desired number of partitions as the 3rd and 4th argument 
1st argument will be the path to the mask and 2nd argument is the path to the image itself
Currently I am pushing folders in an ignore folder not to load the repo too much
Usage:-
./split.out ./mask.jpg ./origImg.png 32 32

the mask and original image may be of different extensions, the not[black] pixels in the mask will be taken out
in the skin directory and rest will be dumped in other directory

Works on linux as used mkdir. Change for windows
Running with CMake by standard add_executables function and adding OpenCv as a dependecy

detectSum function can be changed to provide different varients.

Naming of the images is done according to the porition of which ie 00.png will be top left then grid on remaining similarly
*/

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

// using namespace std;
// using namespace cv;

// void Sharpen(const Mat &myImage, Mat &Result);

bool detectSum(cv::Mat &img);
std::vector<std::string> split(std::string &s, char delimiter);

int main(int argc, char **argv)
{
    //parameters for a number of images
    std::stringstream xStr;
    std::stringstream yStr;

    int numX = 10;
    int numY = 10;

    try
    {
        xStr << argv[3];
        xStr >> numX;

        // i.str("");
        yStr << argv[4];
        yStr >> numY;
    }
    catch (std::exception &e)
    {
        std::cout << "Arguments are not passed correctly";
    }

    double start = (double)cv::getTickCount();

    cv::Mat image;
    cv::Mat imageColored;

    std::string imagePath = argv[2];
    std::string imageColoredPath = argv[1];

    image = cv::imread(imagePath, 1);
    imageColored = cv::imread(imageColoredPath, 1);

    if (!image.data)
    {
        printf(" No image data \n ");
        return -1;
    }

    if (!imageColored.data)
    {
        printf(" No image colored data \n ");
        return -1;
    }

    int height = image.rows / numY;
    int width = image.cols / numX;

    std::vector<std::string> tokens = split(imagePath, '/');
    std::vector<std::string> tokensColor = split(imageColoredPath, '/');

    std::vector<std::string> imageNameWithExt = split(tokens.at(tokens.size() - 1), '.');
    std::vector<std::string> imageColoredNameWithExt = split(tokensColor.at(tokensColor.size() - 1), '.');

    std::stringstream dirName;
    std::stringstream dirNameDetected;

    dirName << imageColoredNameWithExt[0];
    dirName << "_CUT_" << numX << "X" << numY;

    dirNameDetected << imageColoredNameWithExt[0];
    dirNameDetected << "_CUT_" << numX << "X" << numY;
    dirNameDetected << "_skin";

    std::string parentFolderCreateCommand = "mkdir ./ignore" ;
    std::string folderCreateCommand = "mkdir ./ignore/" + dirName.str();
    std::string folderCreateCommandDetcted = "mkdir ./ignore/" + dirNameDetected.str();

    // try{
    system(parentFolderCreateCommand.c_str());
    system(folderCreateCommand.c_str());
    system(folderCreateCommandDetcted.c_str());
    // }
    // catch(std::exception& e){
    //     std::cout<< "Directory couldn't be creadted";
    // }

    std::stringstream dirPath;
    std::stringstream dirPathDetected;
    dirPath << "./ignore/" << dirName.str() << "/";
    dirPathDetected << "./ignore/" << dirNameDetected.str() << "/";

    cv::Mat smallImage;
    cv::Mat smallImageColored;

    // try
    // {

        for (int i = 0; i < numX; i++)
        {
            for (int j = 0; j < numY; j++)
            {
                // cv::Rect rect = cv::Rect(x, y, smallSize.width, smallSize.height);

                std::stringstream cutName;
                smallImage = cv::Mat(image, cv::Rect(i * width, j * height, width, height));
                bool detectIs = detectSum(smallImage);

                std::cout << "Detect for i = " << i << " & j = " << j << " is : " << detectIs << "\n";

                if (detectIs)
                {
                    // cv::namedWindow( "img" , CV_WINDOW_AUTOSIZE);
                    // cv::namedWindow( "imgMask" , CV_WINDOW_AUTOSIZE);
                    // cv::imshow("img", smallImage);
                    // cv::imshow("imgMask", smallImageColored);
                    // cv::waitKey(0);

                    cutName << dirPathDetected.str() << i << j << "." << imageColoredNameWithExt[1];
                    smallImageColored = cv::Mat(imageColored, cv::Rect(i * width, j * height, width, height));
                    cv::imwrite(cutName.str(), smallImageColored);
                }
                else
                {
                    cutName << dirPath.str() << i << j << "." << imageNameWithExt[1];
                    cv::imwrite(cutName.str(), smallImage);
                }

                std::cout << "Done:: " << cutName.str() << '\n';
            }
        }
    // }
    // catch (std::exception &e)
    // {
        
    //     std::cout << "Maybe the file dimensions don't match";
    // }
    double endt = ((double)cv::getTickCount() - start) / cv::getTickFrequency();

    std::cout << "Times passed in seconds for cutting: " << endt << std::endl;

    return 0;
}

std::vector<std::string> split(std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        // std::cout << token <<"Line98\n";
        tokens.push_back(token);
    }
    return tokens;
}

bool detectSum(cv::Mat &img)
{
    cv::Scalar s = cv::sum(img);
    double sum = 0;
    for (int k = 0; k < s.channels; k++)
    {
        sum += s[k];
    }
    if (sum > 0)
    {
        return true;
    }
    return false;
}
