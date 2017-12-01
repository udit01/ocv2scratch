#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "ocv.h"

// using namespace std;
// using namespace cv;

// void Sharpen(const Mat &myImage, Mat &Result);

std::vector<std::string> split(std::string &s, char delimiter);

    int main(int argc, char **argv)
{ //try differnt methods for time comparison ? or be smart and see what happens for different divideWidths ?
    int numX = 10;
    int numY = 10;

    double start = (double)cv::getTickCount();


    std::string imagePath = argv[1];

    cv::Mat image;
    
    image = cv::imread(imagePath, 1);
    
    
    if (!image.data)
    {
        printf(" No image data Line 30 \n ");
        return -1;
    }
    
    int height = image.rows/numY;
    int width = image.cols/numX;

    // char delimiter = '/';
    // std::cout << "Line 38";
    std::vector<std::string> tokens = split(imagePath,'/');
    
    // Vector<String> a = imagePath.split("/");
    // std::cout << "Line 42";
    std::vector<std::string> imageNameWithExt = split( tokens.at(tokens.size()-1), '.');
    
    std::stringstream dirName ;
    dirName << imageNameWithExt[0];
    dirName << "_CUT_"<<numX<<"X"<<numY;
    // std::cout << " Line 46 "<<dirName.str();
    
    // string folderName = "cropped";
    std::string folderCreateCommand = "mkdir " + dirName.str();
    // std::cout << folderCreateCommand ;
    
    system(folderCreateCommand.c_str());
    
    std::stringstream dirPath ;
    dirPath << "./";
    dirPath << dirName.str();
    dirPath << "/";
    
    cv::Mat smallImage;
    
    for(int i=0 ; i < numX ; i++){
        for(int j=0 ; j < numY; j++){
            // cv::Rect rect = cv::Rect(x, y, smallSize.width, smallSize.height);
            
            std::stringstream cutName;
            smallImage = cv::Mat(image,cv::Rect(i*width, j*height, width, height));
            cutName << dirPath.str() << i << j <<"."<< imageNameWithExt[1];
            std::cout << "Line70:  "<< cutName.str()<<'\n';
            cv::imwrite(cutName.str() , smallImage);
        }
    }
    // imwrite(dirName.str, imageOutput);

    double endt = ((double)cv::getTickCount() - start) / cv::getTickFrequency();

    // namedWindow(imagePath, CV_WINDOW_AUTOSIZE);
    // namedWindow(outputImgName, CV_WINDOW_AUTOSIZE);

    // imshow(imagePath, image);
    // imshow(outputImgName, imageOutput);

    //do we wait till key press ?
    // waitKey(0);

    std::cout << "Times passed in seconds for cutting: " << endt << std::endl;
    //compare times


    return 0;
}

std::vector<std::string>  split(std::string &s, char delimiter)
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
