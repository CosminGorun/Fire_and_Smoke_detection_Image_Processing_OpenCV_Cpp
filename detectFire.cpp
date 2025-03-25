#include "detectFire.h"
#include "stdafx.h"
#include "common.h"
#include "makeMeniu.h"
#include "procesing.h"


boolean isFirePixel(Vec3b pixel) {
	Vec3b minFire(7, 80, 80), maxFire(70, 255, 255);
	if (pixel[0]<minFire[0] || pixel[0]>maxFire[0]) { return false; }
	if (pixel[1]<minFire[1] || pixel[1]>maxFire[1]) { return false; }
	if (pixel[2]<minFire[2] || pixel[2]>maxFire[2]) { return false; }
	return true;
}

vector<Mat_<V3>> detectFire(Mat_<V3> img) {
	Mat_<V3> img2(img.size());
	cvtColor(img, img2, COLOR_BGR2HSV);
	Mat_<V3> fireImg(img.size());
	Mat_<V3> fireMask(img.size());
	fireMask.setTo(255);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (isFirePixel(img2(i, j))) {
				fireImg(i, j) = Vec3b(0, 0, 0);
				fireMask(i, j) = Vec3b(0, 69, 255);
			}
			else {
				fireImg(i, j) = img2(i, j);
			}
		}
	}
	cvtColor(fireImg, fireImg, COLOR_HSV2BGR);
	return { img,fireImg,fireMask };
}

vector<Mat_<V3>> detectFireCanal(Mat_<V3> img) {
	auto canals = getCanals(img);
	auto R = canals[2];
	auto G = canals[1];
	auto B = canals[0];
	Vec3b color(0, 0, 0);
	Mat_<V3> fire(img.size());
	Mat_<V3> mask(img.size());
	mask.setTo(255);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (R(i, j) > 200) {
				fire(i, j) = color;
				mask(i, j) = color;
			}
			else {
				fire(i, j) = img(i, j);
			}
		}
	}
	return { img,fire ,mask};
}