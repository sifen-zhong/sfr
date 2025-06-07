#include <iostream>
#include <opencv2/opencv.hpp>
/*---------------------------------------------------------------------*/
#include "sfr.h"

int main(int argc, char *argv[]) {
	cv::Mat roi;
	edge(roi, 15, 12, 100, 10);
	blur(roi);
	blur(roi);
	blur(roi);
	//blur(roi);
#if 0
	cv::Mat img = cv::imread("c:/Local/Data/sfr/original_img.bmp", cv::IMREAD_GRAYSCALE);
	cv::Mat roi;

	ROISelection(img, roi);
	
	if (roi.empty())
	{
		std::cerr << "No roi has been cropped" << std::endl;
		return -1;
	}
	cv::imshow("roi", roi);
	cv::waitKey(0);
	cv::destroyAllWindows();

	std::cout << SFRCalculation(roi, 1) << std::endl;
	system("pause");
#endif

	SFRCalculation(roi, 1.0);

	return 0;
}