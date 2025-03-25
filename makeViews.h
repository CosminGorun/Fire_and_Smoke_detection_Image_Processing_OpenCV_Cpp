#pragma once
#include <opencv2/core/matx.hpp>
#define WIDHT 500

Mat_<Vec3b> makeViewLine(vector<Mat_<Vec3b>> vec, string name);
Mat_<uchar> makeViewLine(vector<Mat_<uchar>> vec, string name);