#pragma once
#include <opencv2/core/matx.hpp>
#include "common.h"
#define WIDHT 450

Mat_<Vec3b> makeViewLine(string name,vector<Mat_<Vec3b>> vec);
Mat_<uchar> makeViewLine(string name,vector<Mat_<uchar>> vec);