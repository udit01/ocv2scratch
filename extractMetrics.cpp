/*
    Author :- Udit Jain [udit01]

    What about mean in multiple channels ? [fixed as converted to single channel]
    stand-dev same done
*/


#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


int numRows;
int numCols;

std::vector<std::string> split(std::string &s, char delimiter);
int detectSum(cv::Mat &img);
float* computeMeanStdDev(cv::Mat &img);
// float computeStdDev(cv::Mat &img);
void writeCSVfloat(float** m, const char *filePath);
void writeCSVbool(cv::Mat &img, const char *filePath);

int main(int argc, char **argv)
{
    std::stringstream streamX;
    std::stringstream streamY;

    int windowWidth = 32;
    int windowHeight = 32;

    try
    {
        streamX << argv[4];
        streamX >> windowWidth;

        // i.str("");
        streamY << argv[5];
        streamY >> windowHeight;
    }
    catch (std::exception &e)
    {
        printf(" Arguments are not passed correctly \n");
    }

    std::string maskPath = argv[1];
    std::string coloRimagePath = argv[2];
    std::string iRimagePath = argv[3];//after this , used directly inside for loop

    cv::Mat mask = cv::imread(maskPath, 1);
    cv::Mat coloRimage = cv::imread(coloRimagePath, 1);
    cv::Mat iRimage = cv::imread(iRimagePath,1);

    if (!coloRimage.data)
    {
        printf(" No image data \n ");
        return -1;
    }

    if (!mask.data)
    {
        printf(" No mask \n ");
        return -1;
    }

    if (!(coloRimage.size == mask.size))
    {
        printf(" Different sizes of image and it's mask. \n");
    }
    if (!(iRimage.size == mask.size))
    {
        printf(" Different sizes of IR image and it's mask. \n");
    }
    cv::Mat image ;
    cv::cvtColor(coloRimage, image, cv::COLOR_BGR2GRAY);//here is the conversion default used at present

    // printf(image.size);
    // std::cout << image.size << " is the image size\n";
    // std::cout << mask.size << " is the mask size\n";
    
     numRows = image.rows / windowHeight;
     numCols = image.cols / windowWidth;
    
    // std::cout << image.rows << " is the image number of rows\n";
    // std::cout << image.cols << " is the image number of columns\n";
    
    std::cout << numRows << " is the numRows\n";
    std::cout << numCols << " is the numColumns\n";
    
    std::vector<std::string> maskTokens = split(maskPath, '/');
    std::vector<std::string> imageTokens = split(coloRimagePath, '/');
    //mNWE stands for mask name with extension
    std::vector<std::string> maskNameWithExt = split(maskTokens.at(maskTokens.size() - 1), '.');
    std::vector<std::string> imageNameWithExt = split(imageTokens.at(imageTokens.size() - 1), '.');
    
    std::stringstream skinDir;
    std::stringstream noSkinDir;
    skinDir << "./ignore/" << imageNameWithExt[0] << "_cutIn_" << windowWidth << "BY" << windowHeight << "_skin/";
    noSkinDir << "./ignore/" << imageNameWithExt[0] << "_cutIn_" << windowWidth << "BY" << windowHeight << "_noSkin/";
    std::string parentFolderCreateCommand = "mkdir ./ignore";
    std::string folderCreateCommandSkin = "mkdir " + skinDir.str();
    std::string folderCreateCommandNoSkin = "mkdir " + noSkinDir.str();
    
    system(parentFolderCreateCommand.c_str());
    system(folderCreateCommandSkin.c_str());
    system(folderCreateCommandNoSkin.c_str());
    
    cv::Mat maskCut;
    cv::Mat imageCut;
    cv::Mat irImageCut;
    
    // cv::Mat meanMatrix(numRows, numCols, CV_32FC1);
    cv::Mat boolMatrix(numRows, numCols, CV_8UC(1)); //wasted space
    
    unsigned char * boolData = boolMatrix.data;
    int bool_stride = boolMatrix.step;
    // std::cout << "BOOl stride " << bool_stride << "\n";
    // unsigned char * meanData = meanMatrix.data; //because I forget the type
    float **meanMatrixColor = new float*[numRows];
    float **stdDevMatrixColor = new float*[numRows];
    float **meanMatrixIR = new float*[numRows];
    float **stdDevMatrixIR = new float*[numRows];

    float *mstdevCol;
    float *mstdevIR;
    // float **zArray = new float *[imheight];
    // int mean_stride = meanMatrix.step;
    // std::cout << "Mean stride " << mean_stride << "\n";
    
    // printf("CHECKPOINT ::::: 95\n");
    
    for (int i = 0; i < numRows; i++)
    {
        meanMatrixColor[i] = new float[numCols];
        stdDevMatrixColor[i] = new float[numCols];
        meanMatrixIR[i] = new float[numCols];
        stdDevMatrixIR[i] = new float[numCols];

        for (int j = 0; j < numCols; j++)
        {
            // printf("CHECKPOINT 101 ::::: i=%d & j=%d  \n",i,j);
            // std::cout << "Dimensions: i*wWidth = ";
            // printf("Dimensions: i * wh = %d and j * ww = %d\n",i*windowHeight , j*windowWidth);
            std::stringstream cutName;
            
            maskCut = cv::Mat(mask, cv::Rect( j * windowWidth, i * windowHeight ,  windowWidth, windowHeight));
            imageCut = cv::Mat(image, cv::Rect(j * windowWidth, i * windowHeight, windowWidth, windowHeight));
            irImageCut = cv::Mat(iRimage , cv::Rect(j * windowWidth, i * windowHeight, windowWidth, windowHeight));

            int detectSkin = detectSum(maskCut);
            // boolData[i * bool_stride + j] = detectSkin ? 1 : 0;
            // std::cout<<detectSkin<<std::endl;
            boolData[i * bool_stride + j] = detectSkin;//let it remain
            
            mstdevCol = computeMeanStdDev(imageCut);
            mstdevIR = computeMeanStdDev(irImageCut);
            // float meanCol = computeMean(imageCut);
            // float meanIR = computeMean(irImageCut);
            // float stdDevCol = computeStdDev(imageCut);
            // float stdDevIR = computeStdDev(irImageCut);
            // std::cout<<mean<<std::endl;
            
            // meanData[i * mean_stride + j] = mean;//has some error--------------------------------
            // meanMatrix.data.at<float>(i,j) = mean;
            meanMatrixColor[i][j] = mstdevCol[0];
            stdDevMatrixColor[i][j] = mstdevCol[1];
            meanMatrixIR[i][j] = mstdevIR[0];
            stdDevMatrixIR[i][j] = mstdevIR[1];

            if (detectSkin == 1)
            {
           
                cutName << skinDir.str() << i << j << "." << imageNameWithExt[1];
                cv::imwrite(cutName.str(), imageCut);
            }
            else
            {
                cutName << noSkinDir.str() << i << j << "." << imageNameWithExt[1];
                cv::imwrite(cutName.str(), imageCut);
            }

            // std::cout << "Done:: " << cutName.str() << '\n';
        }
    }
    
    // printf("CHECKPOINT ::::: 125\n");
    std::stringstream meanFileCol ;
    std::stringstream meanFileIR ;
    std::stringstream stdDevFileCol ;
    std::stringstream stdDevFileIR ;
    std::stringstream boolFile ;
    
    boolFile << "./ignore/" << imageNameWithExt[0] << "_boolValues.csv";
    meanFileCol << "./ignore/" << imageNameWithExt[0] << "_mean_color.csv";
    stdDevFileCol << "./ignore/" << imageNameWithExt[0] << "_stdDev_color.csv";
    meanFileIR << "./ignore/" << imageNameWithExt[0] << "_mean_ir.csv";
    stdDevFileIR << "./ignore/" << imageNameWithExt[0] << "_stdDev_ir.csv";

    // printf("CHECKPOINT ::::: 157\n");
    // cv::FileStorage fs(meanFile.str(), cv::FileStorage::WRITE);
    // fs << "Mean Matrix" <<meanMatrix; //choose any key here, just be consistant with the one below
    // fs.release();
    // printf("CHECKPOINT ::::: 160\n");
    
    writeCSVbool(boolMatrix , boolFile.str().c_str());

    writeCSVfloat(meanMatrixColor , meanFileCol.str().c_str());
    writeCSVfloat(stdDevMatrixColor , stdDevFileCol.str().c_str());
    writeCSVfloat(meanMatrixIR , meanFileIR.str().c_str());
    writeCSVfloat(stdDevMatrixIR , stdDevFileIR.str().c_str());
    
    return 0;
}

void writeCSVfloat(float** m, const char * filePath)
{
    
    // cv::FileStorage file(filePath, cv::FileStorage::WRITE);
    // file << img;

    std::ofstream fout(filePath);

    if (!fout)
    {
        std::cout << "File Not Opened" << std::endl;
        return;
    }

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            // std::cout<< m[i][j] << " Line173\n";
            fout << m[i][j] << ", ";
        }
        fout << std::endl;
    }

    fout.close();
    return;
}
void writeCSVbool(cv::Mat &m, const char *filePath)
{

    // cv::FileStorage file(filePath, cv::FileStorage::WRITE);
    // file << img;

    std::ofstream fout(filePath);

    if (!fout)
    {
        std::cout << "File Not Opened" << std::endl;
        return;
    }

    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            // std::cout << m.at<bool>(i,j)<<"Line 218\n";
            fout << m.at<bool>(i, j) << ", ";
        }
        fout << std::endl;
    }

    fout.close();
    return;
}
float* computeMeanStdDev(cv::Mat& img){
    cv::Scalar mean,stdDev;
    float* res = new float[2];
    cv::meanStdDev(img,mean,stdDev,cv::Mat());
    res[0] = mean[0];
    res[1] = stdDev[0];
    return res;//what if multiple channels?
}

std::vector<std::string> split(std::string & s, char delimiter)
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

int detectSum(cv::Mat & img)
{
    cv::Scalar s = cv::sum(img);
    double sum = 0;
    for (int k = 0; k < s.channels; k++)
    {
        sum += s[k];
    }
    if (sum > 0)
    {
        return 1;
    }
    return 0;
}