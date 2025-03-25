//#include "myHeader.h"
#include "stdafx.h"
#include "common.h"
#include "makeMeniu.h"

Mat_<UC> make_meniu() {
	Mat_<UC> img(40, 200);
	img.setTo(255);
	for (int i = 0; i < img.rows; i++) {
		img(i, img.cols / 2) = 0;
	}
	cv::putText(img, "prev", Point(20,img.rows/2), cv::FONT_HERSHEY_SIMPLEX,1, Scalar(0,0,0), 2);
	cv::putText(img, "next", Point(120,img.rows/2), cv::FONT_HERSHEY_SIMPLEX,1, Scalar(0,0,0), 2);
	return img;
}
string getCurentImagePath(int curentPrintImage) {
	string text = DIRECTOR;
	text += PATHNAME;
	text += to_string(curentPrintImage);
	text += ".bmp";
	cout <<"Imaginea procesata acum este: " << text << endl;
	return text;
}
void changeImg(boolean index, int* curentPrintImage, int nrOfFiles) {
	if (index) {
		*curentPrintImage = (*curentPrintImage + 1) % nrOfFiles;
	}
	else {
		*curentPrintImage == 0 ? *curentPrintImage = nrOfFiles - 1 : (*curentPrintImage)--;
	}
}
Mat_<V3> getImage(boolean update, int* curentPrintImage,int nrOfFiles) {
	changeImg(update, curentPrintImage, nrOfFiles);
	string imgName = getCurentImagePath(*curentPrintImage);
	Mat_<V3> img = imread(imgName);
	return img;
}

int getNrOfFile() {
	system("python ./convertor_PY/convertImages.py ./Images ./ImagesBMP");
	system("python ./convertor_PY/nrOfFile.py ./ImagesBMP ./convertor_PY/nrOfFile.txt");
	int nrOfFile = 0;
	FILE* input = fopen("./convertor_PY/nrOfFile.txt","r");
	fscanf(input, "%d", &nrOfFile);
	fclose(input);
	return nrOfFile;
}
