#pragma once

using namespace std;

vector<Mat_<uchar>> getCanals(Mat_<Vec3b> img);
boolean isInside(Mat img, int i, int j);
uchar incrementChar(uchar val, int increment);
boolean isColor(Vec3b color);
Mat_<Vec3b> overlayMask(Mat_<Vec3b> mask1, Mat_<Vec3b> mask2);