#pragma once

using namespace std;

vector<Mat_<uchar>> getCanals(Mat_<Vec3b> img);
boolean isInside(Mat img, int i, int j);
uchar incrementChar(uchar val, int increment);
boolean isColor(Vec3b color);
Mat_<Vec3b> overlayMask(Mat_<Vec3b> mask1, Mat_<Vec3b> mask2);
Mat_<Vec3b> putMask(Mat_<Vec3b> img, Mat_<Vec3b> mask);
Mat_<Vec3b> putMask(Mat_<Vec3b> img, Mat_<uchar> mask);

vector<Mat_<uchar>> splitImg(Mat_<Vec3b> img);
Mat_<Vec3b> combinImg(vector<Mat_<uchar>> canals);
vector<int> getHistogram(Mat_<uchar> img);
Mat_<uchar> reduceGryNiv(Mat_<uchar> img);
Mat_<uchar> maskConvert(Mat_<Vec3b> img);

Mat_<uchar> overLap(vector<Mat_<uchar>> vec);
