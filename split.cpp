#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "ocv.h"

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

    std::string imagePath = argv[1];
    std::string imageColoredPath = argv[2];

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
    dirNameDetected << "_coloured_peices";

    std::string folderCreateCommand = "mkdir " + dirName.str();
    std::string folderCreateCommandDetcted = "mkdir " + dirNameDetected.str();

    // try{
    system(folderCreateCommand.c_str());
    system(folderCreateCommandDetcted.c_str());
    // }
    // catch(std::exception& e){
    //     std::cout<< "Directory couldn't be creadted";
    // }

    std::stringstream dirPath;
    std::stringstream dirPathDetected;
    dirPath << "./" << dirName.str() << "/";
    dirPathDetected << "./" << dirNameDetected.str() << "/";

    cv::Mat smallImage;
    cv::Mat smallImageColored;

    try
    {

        for (int i = 0; i < numX; i++)
        {
            for (int j = 0; j < numY; j++)
            {
                // cv::Rect rect = cv::Rect(x, y, smallSize.width, smallSize.height);

                std::stringstream cutName;
                smallImage = cv::Mat(image, cv::Rect(i * width, j * height, width, height));
                bool detectIs = detectSum(smallImage);

                std::cout << "Detect for i = " << i << " & j = " << j << " is : " << detectIs << "\n";

                if (!detectIs)
                {
                    cutName << dirPath.str() << i << j << "." << imageColoredNameWithExt[1];
                    smallImageColored = cv::Mat(imageColored, cv::Rect(i * width, j * height, width, height));
                    cv::imwrite(cutName.str(), smallImageColored);
                }
                else
                {
                    cutName << dirPathDetected.str() << i << j << "." << imageNameWithExt[1];
                    cv::imwrite(cutName.str(), smallImage);
                }

                std::cout << "Done:: " << cutName.str() << '\n';
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Maybe the file dimensions are different";
    }
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