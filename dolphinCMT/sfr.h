#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#define M_PI 3.1415

bool SFRCalculation(cv::Mat &ROI, double gamma);

void ROISelection(cv::Mat& img, cv::Mat& roi);
void ROImouseEvent(int event, int x, int y, int flag, void* params);

void edge(cv::Mat& Edge, int rows, int cols, int r_e, int c_e);
void blur(cv::Mat& img);
