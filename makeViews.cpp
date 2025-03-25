#include "stdafx.h"
#include "common.h"
#include "makeMeniu.h"
#include "makeViews.h"

int getHeight(int curentWidht,int curentHeight) {
	float raport = WIDHT / (float) curentWidht;
	return (int)(curentHeight * raport);
}
Mat_<Vec3b> resizeImage(Mat_<Vec3b> img) {
	int height = getHeight(img.cols, img.rows);
	Size size(WIDHT,height);
	//cout << size << endl;
	Mat_<Vec3b> resImg(size);
	resize(img, resImg, size);
	return resImg;
}
Mat_<Vec3b> makeViewLine(vector<Mat_<Vec3b>> vec, string name) {
	Mat_<Vec3b> concat= resizeImage(vec[0]);
	for (int i = 1; i < vec.size(); i++) {
		hconcat(concat, resizeImage(vec[i]), concat);
	}
	imshow(name, concat);
	return concat;
}
Mat_<uchar> resizeImage(Mat_<uchar> img) {
	int height = getHeight(img.cols, img.rows);
	Size size(WIDHT, height);
	//cout << size << endl;
	Mat_<uchar> resImg(size);
	resize(img, resImg, size);
	return resImg;
}
Mat_<uchar> makeViewLine(vector<Mat_<uchar>> vec,string name) {
	Mat_<uchar> concat = resizeImage(vec[0]);
	for (int i = 1; i < vec.size(); i++) {
		hconcat(concat, resizeImage(vec[i]), concat);
	}
	imshow(name, concat);
	return concat;
}