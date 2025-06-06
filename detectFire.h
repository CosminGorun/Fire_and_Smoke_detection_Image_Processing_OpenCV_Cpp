#pragma once
#include "makeMeniu.h"
#include "stdafx.h"
#include "common.h"
#include "makeMeniu.h"
#include "procesing.h"
#include <opencv2/core/matx.hpp>


Mat_<UC> detectFireHSV(Mat_<V3> img);
Mat_<UC> detectFireYCrCB(Mat_<V3> img);
Mat_<UC> detectFireRGB(Mat_<V3> img);
vector<Mat_<V3>> dilateAndDetect(Mat_<V3> img);