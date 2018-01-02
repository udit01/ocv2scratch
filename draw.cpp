/*
    Author :- Udit Jain [udit01]

    
*/
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "ocv.h"

// width of the square
#define w 400

//badpractice for large codes
using namespace cv;

/// Function headers
void MyEllipse(Mat img, double angle);
void MyFilledCircle(Mat img, Point center);
void MyPolygon(Mat img);
void MyLine(Mat img, Point start, Point end);

int main(int argc, char **argv)
{
    /// Windows names
    char atom_window[] = "Drawing 1: Atom";
    char rook_window[] = "Drawing 2: Rook";

    /// Create black empty images
    Mat atom_image = Mat::zeros(w, w, CV_8UC3);
    Mat rook_image = Mat::zeros(w, w, CV_8UC3);

    /// 1. Draw a simple atom:

    /// 1.a. Creating ellipses
    MyEllipse(atom_image, 90);
    MyEllipse(atom_image, 0);
    MyEllipse(atom_image, 45);
    MyEllipse(atom_image, -45);

    /// 1.b. Creating circles
    MyFilledCircle(atom_image, Point(w / 2.0, w / 2.0));

    /// 2. Draw a rook

    /// 2.a. Create a convex polygon
    MyPolygon(rook_image);

    /// 2.b. Creating rectangles
    rectangle(rook_image,
              Point(0, 7 * w / 8.0),
              Point(w, w),
              Scalar(0, 255, 255),
              -1,
              8);

    /// 2.c. Create a few lines
    MyLine(rook_image, Point(0, 15 * w / 16), Point(w, 15 * w / 16));
    MyLine(rook_image, Point(w / 4, 7 * w / 8), Point(w / 4, w));
    MyLine(rook_image, Point(w / 2, 7 * w / 8), Point(w / 2, w));
    MyLine(rook_image, Point(3 * w / 4, 7 * w / 8), Point(3 * w / 4, w));

    
    return 0;
}