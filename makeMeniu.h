#pragma once
#define V3 Vec3b
#define UC uchar
#define DIRECTOR "./ImagesBMP"
#define PATHNAME "/fire"
using namespace std;

typedef struct {
	Mat_<UC> meniu;
	int curentPrintImage;
	int nrOfFIles;
	Mat_<V3> imag;
} Parametri;

Mat_<UC> make_meniu();
Mat_<V3> getImage(boolean update, int* curentPrintImage, int nrOfFiles);
int getNrOfFile();
