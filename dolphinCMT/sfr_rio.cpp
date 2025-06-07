#include "sfr.h"

void ROImouseEvent(int event, int x, int y, int flag, void* params)
{
	cv::Point* ptr = (cv::Point*)params;

	if (event == cv::EVENT_LBUTTONDOWN && ptr[0].x == -1 && ptr[0].y == -1)
	{
		ptr[0].x = x;
		ptr[0].y = y;
	}

	if (flag == cv::EVENT_FLAG_LBUTTON)
	{
		ptr[1].x = x;
		ptr[1].y = y;
	}

	if (event == cv::EVENT_LBUTTONUP && ptr[2].x == -1 && ptr[2].y == -1)
	{
		ptr[2].x = x;
		ptr[2].y = y;
	}

}

void ROISelection(cv::Mat& img, cv::Mat& roi)
{
	cv::Point* Corners = new cv::Point[3];
	Corners[0].x = Corners[0].y = -1;
	Corners[1].x = Corners[1].y = -1;
	Corners[2].x = Corners[2].y = -1;

	cv::namedWindow("ROI select(Press Esc to close window)", cv::WINDOW_NORMAL);
	cv::imshow("ROI select(Press Esc to close window)", img);

	bool downFlag = false, upFlag = false;
	while (cv::waitKey(1) != 27)
	{
		cv::setMouseCallback("ROI select(Press Esc to close window)", ROImouseEvent, Corners);

		if (Corners[0].x != -1 && Corners[0].y != -1) { downFlag = true; }
		if (Corners[2].x != -1 && Corners[2].y != -1) { upFlag = true; }

		if (downFlag && !upFlag && Corners[1].x != -1)
		{
			cv::Mat LocalImage = img.clone();
			cv::rectangle(LocalImage, Corners[0], Corners[1], cv::Scalar(255, 255, 255), 2);
			cv::imshow("ROI select(Press Esc to close window)", LocalImage);
		}

		if (downFlag && upFlag)
		{

			cv::Rect ROIBox;
			ROIBox.width = abs(Corners[0].x - Corners[2].x);
			ROIBox.height = abs(Corners[0].y - Corners[2].y);

			if (ROIBox.width < 5 && ROIBox.height < 5)
			{
				std::cerr << "ROI size too small, please re-crop the ROI" << std::endl;
			}


			ROIBox.x = Corners[0].x < Corners[1].x ? Corners[0].x : Corners[1].x;
			ROIBox.y = Corners[0].y < Corners[1].y ? Corners[0].y : Corners[1].y;

			roi = img(ROIBox);
			downFlag = upFlag = false;

			Corners[0].x = Corners[0].y = -1;
			Corners[1].x = Corners[1].y = -1;
			Corners[2].x = Corners[2].y = -1;

		}

	}
	cv::destroyWindow("ROI select(Press Esc to close window)");

	delete[] Corners;
}
