// datagen.cpp
#include "sfr.h"

void edge(cv::Mat& Edge, int rows, int cols, int r_e, int c_e)
{
	int r_h = rows / 2;
	int c_h = cols / 2;
	Edge = cv::Mat::zeros(rows, cols, CV_8UC1);
	for (int i = 0; i < rows; ++i)
	{
		int r = i - r_h;
		int rce = r * c_e;
		uchar* edgePtr = Edge.ptr<uchar>(i);
		for (int j = 0; j < cols; ++j)
		{
			int c = j - c_h;
			int cre = c * r_e;
			edgePtr[j] = rce <= cre ? 0xF0 : 0x10;
		}
	}
}

void blur(cv::Mat& img)
{
	cv::GaussianBlur(img, img, cv::Size(3, 3), 0);
}
