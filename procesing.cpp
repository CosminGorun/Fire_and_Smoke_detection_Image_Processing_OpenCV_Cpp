#include "stdafx.h"
#include "common.h"
#include "procesing.h"
#include "makeMeniu.h"


vector<Mat_<uchar>> getCanals(Mat_<Vec3b> img) {
	Mat_<uchar> R(img.size()), G(img.size()), B(img.size());
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			R(i, j) = img(i, j)[2];
			G(i, j) = img(i, j)[1];
			B(i, j) = img(i, j)[0];
		}
	}
	return { B,G,R };
}

boolean isInside(Mat img, int i, int j) {
	if (i < 0 || j < 0) return false;
	if (i >= img.rows) return false;
	if (j >= img.cols) return false;
	return true;
}

uchar incrementChar(uchar val, int increment) {
	int a = val + increment;
	if (a > 255) return 255;
	if (a < 0) return 0;
	return (uchar)a;
}

boolean isColor(Vec3b color) {
	if (color[0] < 255) return true;
	if (color[1] < 255) return true;
	if (color[2] < 255) return true;
	return false;
}

Mat_<Vec3b> overlayMask(Mat_<V3> mask1, Mat_<V3> mask2) {
	Mat_<Vec3b> overlay(mask1.size());
	overlay.setTo(255);
	V3 color(0, 0, 0);
	for (int i = 0; i < mask1.rows; i++) {
		for (int j = 0; j < mask1.cols; j++) {
			if (isColor(mask1(i, j)) && isColor(mask2(i, j))) {
				overlay(i, j) = color;
			}
		}
	}
	return overlay;
}