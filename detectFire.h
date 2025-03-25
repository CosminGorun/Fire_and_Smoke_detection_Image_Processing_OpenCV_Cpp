#pragma once
#include "makeMeniu.h"
#include <opencv2/core/matx.hpp>

boolean isFirePixel(Vec3b pixel);

vector<Mat_<V3>> detectFire(Mat_<V3> img);

vector<Mat_<V3>> detectFireCanal(Mat_<V3> img);