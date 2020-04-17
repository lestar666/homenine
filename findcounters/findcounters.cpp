﻿
#include <opencv2\opencv.hpp>
#include <iostream>

     using namespace cv;
     using namespace std;

int main()
{

	cv::Mat srcMat;
	cv::Mat dspMat;
	cv::Mat binaryMat;

	srcMat = imread("die_on_chip.png", 0);
	dspMat = imread("die_on_chip.png");

	cv::Mat inversedMat = 255 - srcMat;
	threshold(inversedMat, binaryMat, 150, 255, THRESH_OTSU);
	//获得连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binaryMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rect = minAreaRect(contours[i]);

		drawContours(dspMat, contours, i, Scalar(0,0,255), 1, 8);
		Point2f P[4];
		rect.points(P);
		for (int j = 0; j <= 3; ++j)
		{
			line(dspMat, P[j], P[j < 3 ? j + 1 : 0], Scalar(0,0,255), 2, CV_AA);
		}
	}
	imshow("src", srcMat);
	imshow("dis", dspMat);
	waitKey(0);
	return 0;
}