#include "detectFire.h"
#include "stdafx.h"
#include "common.h"
#include "makeMeniu.h"
#include "procesing.h"
#include "makeViews.h"


boolean isFirePixelHSV(Vec3b pixel) {
	Vec3b minFire(7, 80, 80), maxFire(70, 255, 255);
	if (pixel[0]<minFire[0] || pixel[0]>maxFire[0]) { return false; }
	if (pixel[1]<minFire[1] || pixel[1]>maxFire[1]) { return false; }
	if (pixel[2]<minFire[2] || pixel[2]>maxFire[2]) { return false; }
	return true;
}

float triangular(float x, float a, float b, float c) {
	if (x <= a || x >= c) return 0.0f;
	else if (x < b) return (x - a) / (b - a);
	else return (c - x) / (c - b);
}


float trapezoidal(float x, float a, float b, float c, float d) {
	if (x <= a || x >= d) return 0.0f;
	else if (x < b) return (x - a) / (b - a);
	else if (x <= c) return 1.0f;
	else return (d - x) / (d - c);
}

float evaluateFuzzy(float d1, float d2) {
	
	float low_d1 = triangular(d1, -1.0f, -0.5f, 0.0f);
	float high_d1 = triangular(d1, 0.0f, 0.5f, 1.0f);

	float low_d2 = triangular(d2, -1.0f, -0.5f, 0.0f);
	float high_d2 = triangular(d2, 0.0f, 0.5f, 1.0f);

	float r1 = min(low_d1, low_d2);   
	float r2 = min(low_d1, high_d2);  
	float r3 = min(high_d1, low_d2);  
	float r4 = min(high_d1, high_d2); 

	// Defuzzification: centroid method
	float numerator = r1 * 0.0f + r2 * 0.3f + r3 * 0.5f + r4 * 1.0f;
	float denominator = r1 + r2 + r3 + r4;
	return (denominator == 0.0f) ? 0.0f : numerator / denominator;
}

boolean isFirePixelYCrCB(Vec3b pixel) {
	Vec3b minFire(100, 140, 70);
	Vec3b maxFire(255, 170, 130);
	if (pixel[0]<minFire[0] || pixel[0]>maxFire[0]) { return false; }
	if (pixel[1]<minFire[1] || pixel[1]>maxFire[1]) { return false; }
	if (pixel[2]<minFire[2] || pixel[2]>maxFire[2]) { return false; }
	return true;
}

Mat_<UC> detectFireHSV(Mat_<V3> img) {
	Mat_<V3> img2(img.size());
	cvtColor(img, img2, COLOR_BGR2HSV);
	Mat_<UC> fireMask(img.size());
	fireMask.setTo(0);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (isFirePixelHSV(img2(i, j))) {
				fireMask(i, j) =255;
			}
		}
	}
	return fireMask;
}

Mat_<UC> detectFireYCrCB(Mat_<V3> img) {
	Mat_<V3> img2(img.size());
	cvtColor(img, img2, COLOR_BGR2YCrCb);
	auto canals = getCanals(img2);
	double maxY, maxCr, maxCb;
	minMaxLoc(canals[0], nullptr, &maxY);
	minMaxLoc(canals[1], nullptr, &maxCr);
	minMaxLoc(canals[2], nullptr, &maxCb);
	double Imax = max(maxY, maxCr, maxCb);
	Mat Y, Cr, Cb;
	canals[0].convertTo(Y, CV_32F, 1.0 / Imax);
	canals[1].convertTo(Cr, CV_32F, 1.0 / Imax);
	canals[2].convertTo(Cb, CV_32F, 1.0 / Imax);

	Mat d1 = Y - Cb;
	Mat d2 = Cr - Cb;


	Mat_<UC> fireMask(img.size());
	fireMask.setTo(255);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			float pf = evaluateFuzzy(d1.at<float>(i,j), d2.at<float>(i, j));
			if (pf > 0.6f){
				fireMask(i,j) = 255;
		    }else {
				fireMask(i, j) = 0;
			}
		}
	}
	//cvtColor(fireImg, fireImg, COLOR_YCrCb2BGR);
	return fireMask;
}

Mat_<UC> detectFireRGB(Mat_<V3> img) {
	auto canals = getCanals(img);
	auto R = canals[2];
	Mat_<UC> mask(img.size());
	mask.setTo(0);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (R(i, j) > 180) {
				mask(i, j) = 255;
			}
		}
	}
	return mask;
}

vector<Mat_<V3>> dilateAndDetect(Mat_<V3> img) {

	auto rgbUc = detectFireRGB(img);
	auto hsvUc = detectFireHSV(img);
	auto ycrcbUc = detectFireYCrCB(img);
	
	

	Mat_<uchar> kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

	
	Mat dilatRgb, dilatHsv, dilatYCrCb;
	dilate(rgbUc, dilatRgb, kernel);
	dilate(hsvUc, dilatHsv, kernel);
	dilate(ycrcbUc, dilatYCrCb, kernel);
	vector<Mat_<uchar>> vec = { rgbUc,hsvUc,ycrcbUc };
	makeViewLine("RGB  HSV  YCrCb", vec);
	Mat_<V3> mask3;
	auto mask = overLap({ dilatRgb,dilatHsv,dilatYCrCb });
	cvtColor(mask, mask3, COLOR_GRAY2RGB);
	auto Imask = putMask(img, mask);
	return {  img,mask3,Imask};
}

