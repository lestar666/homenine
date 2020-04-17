
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

	float num[100];

	cv::Mat inversedMat = 255 - srcMat;
	threshold(inversedMat, binaryMat, 150, 255, THRESH_OTSU);
	Mat element = getStructuringElement(MORPH_RECT, Size(13, 13));
	morphologyEx(binaryMat, binaryMat, MORPH_OPEN, element);

	//获得连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binaryMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rect = minAreaRect(contours[i]);
		Point2f vtx[4];
		rect.points(vtx);
		float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
		float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));
		num[i] = X / Y;
		if ((num[i] >= 0.9) and (num[i] <= 1.0))
		{
			for (int j = 0; j <= 3; j++)
			{
				line(dspMat, vtx[j], vtx[(j + 1) % 4], Scalar(0, 0, 255), 1);
			}
		}
	}
	imshow("src", srcMat);
	imshow("dis", dspMat);
	waitKey(0);
	return 0;
}