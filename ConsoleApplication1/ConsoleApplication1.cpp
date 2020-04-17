#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{

	cv::Mat src;
	cv::Mat dsp;
	cv::Mat binary;

	src = imread("rim.png", 0);
	dsp = imread("rim.png");

	float num[100];

	cv::Mat inversedMat = 255 - src;
	threshold(inversedMat, binary, 150, 255, THRESH_OTSU);
	Mat element = getStructuringElement(MORPH_RECT, Size(13, 13));
	morphologyEx(binary, binary, MORPH_OPEN, element);

	//获得连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);


	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rect = minAreaRect(contours[i]);
		Point2f vtx[4];
		rect.points(vtx);
		float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
		float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));
		num[i] = X / Y;
		if ((num[i] >= 0.95) and (num[i] <= 1.1))
		{
			for (int j = 0; j <= 3; j++)
			{
				line(dsp, vtx[j], vtx[(j + 1) % 4], Scalar(0,0,255), 1);
			}
		}
	}
	imshow("dis", dsp);
	waitKey(0);
	return 0;
}