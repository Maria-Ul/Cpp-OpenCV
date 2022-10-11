//
// Created by Мария Ульянова on 11.10.2022.
//
#include <iostream>
#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;

int main() {
    Mat A = imread("/Users/mariaulanova/CLionProjects/Cpp-OpenCV/1556708032_1.jpg", IMREAD_COLOR); // here we'll know the method used (allocate matrix)
    if( A.empty() )
    {
        return EXIT_FAILURE;
    }
    vector<Mat> bgr_planes;
    split( A, bgr_planes );
    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;
    Mat b_hist, g_hist, r_hist;
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate );
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize )*10;
    Mat histImage_r( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    Mat histImage_b( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    Mat histImage_g( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

    normalize(b_hist, b_hist, 0, histImage_b.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage_g.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage_r.rows, NORM_MINMAX, -1, Mat() );
    for( int i = 0; i < histSize; i++ )
    {

        line( histImage_b, Point( bin_w*(i), hist_h ),
              Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage_g, Point( bin_w*(i), hist_h ),
              Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage_r, Point( bin_w*(i), hist_h ),
              Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
              Scalar( 0, 0, 255), 2, 8, 0  );
    }
    imshow("Source image", A );
    imshow("calcHist r", histImage_r );
    imshow("calcHist b", histImage_b );
    imshow("calcHist g", histImage_g );

    waitKey();

    return EXIT_SUCCESS;

}
