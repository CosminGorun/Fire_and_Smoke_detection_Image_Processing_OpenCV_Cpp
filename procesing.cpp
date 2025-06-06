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

Mat_<Vec3b> putMask(Mat_<Vec3b> img, Mat_<Vec3b> mask) {
	Mat_<V3> newImg(img.size());
	V3 color(0, 0, 0);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (isColor(mask(i, j))) {
				newImg(i, j) = color;
			}
			else {
				newImg(i, j) = img(i, j);
			}
		}
	}
	return newImg;
}

Mat_<Vec3b> putMask(Mat_<Vec3b> img, Mat_<uchar> mask) {
	Mat_<V3> newImg(img.size());
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (mask(i,j)==0) {
				newImg(i, j) = 0;
			}
			else {
				newImg(i, j) = img(i, j);
			}
		}
	}
	return newImg;
}

vector<Mat_<uchar>> splitImg(Mat_<V3> img){
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

Mat_<Vec3b> combinImg(vector<Mat_<uchar>> canals) {
	Mat_<Vec3b> img(canals[0].size());
	Mat_<uchar> R(img.size()), G(img.size()), B(img.size());
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			img(i, j)[2]=canals[2](i,j);
			img(i, j)[1] = canals[1](i, j);
			img(i, j)[0] = canals[0](i, j);
		}
	}
	return img;
}

vector<int> getHistogram(Mat_<uchar> img) {
	vector<int> hist(256, 0);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			hist[img(i, j)] +=1;
		}
	}
	return hist;
}

boolean isLocalMax(vector<int> vec, int poz,int TH) {
	for (int i = poz - TH; i <= poz + TH; i++) {
		if (vec[i] > vec[poz]) {
			return false;
		}
	}
	return true;
}

uchar getClosesMax(vector<int> localMax,uchar color) {
	int curentDist = abs(color - localMax[0]);
	int corespMax = 0;
	for (auto curMax : localMax) {
		int dist= abs(color - curMax);
		if (dist < curentDist) {
			curentDist = dist;
			corespMax = curMax;
		}
	}
	return corespMax;
}

Mat_<UC> reduceGryNiv(Mat_<uchar> img) {
	int TH = 5;
	vector<int> localMax;
	auto hist = getHistogram(img);
	for (int i = TH; i < 256-TH; i++) {
		if (isLocalMax(hist, i, TH)) {
			localMax.push_back(i);
		}
	}
	Mat_<UC> grayimg(img.size());
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			grayimg(i, j) = getClosesMax(localMax, img(i, j));
		}
	}
	return grayimg;
}

Mat_<uchar> maskConvert(Mat_<Vec3b> img) {
	Mat_<UC> grayimg(img.size());
	grayimg.setTo(255);
    for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (img(i, j)[0] > 0) {
				grayimg(i, j) = 0;
			}
		}
	}
	return grayimg;
}


Mat_<uchar> overLap(vector<Mat_<uchar>> vec) {
	Mat_<uchar> mask(vec[0].size());
	mask.setTo(255);
	for (int i = 0; i < mask.rows; i++) {
		for (int j = 0; j < mask.cols; j++) {
			int nr = 0;
			for (int k = 0; k < vec.size(); k++) {
				if (vec[k](i, j) == 255) {
					nr++;
				}
				else {
					break;
				}
			}
			if (nr == vec.size()) {
				mask(i, j) = 0;
			}
		}
	}
	return mask;
}