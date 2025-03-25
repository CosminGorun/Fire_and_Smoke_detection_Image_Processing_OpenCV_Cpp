#include "stdafx.h"
#include "common.h"
#include <opencv2/core/utils/logger.hpp>
#include "makeMeniu.h"
#include "makeViews.h"
#include "detectFire.h"
#include "procesing.h"

using namespace std;
wchar_t* projectpath;

void myhandler(int event, int x, int y, int flags, void* param);

void prelucrare(Mat_<V3> img);

int main() 
{   
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_FATAL);
	Mat_<UC> meniu = make_meniu();
	Parametri param;
	param.meniu = meniu;
	param.curentPrintImage = 0;
	param.nrOfFIles = getNrOfFile();
	cout << "Numarul de fisiere procesate este: " << param.nrOfFIles << endl;
	imshow("meniu", meniu);
	setMouseCallback("meniu", myhandler, &param);
	waitKey(0);
	return 0;
}

void myhandler(int event, int x, int y, int flags, void* param) {
	Parametri* par = (Parametri*)param;
	Mat_<UC> meniu = par->meniu;
	if (event == EVENT_FLAG_LBUTTON) {
		par->imag.release();
		par->imag = getImage((x > meniu.cols / 2), &(par->curentPrintImage),par->nrOfFIles);
		prelucrare(par->imag);
	}
}

void prelucrare(Mat_<V3> img) {
	auto met1 = detectFireCanal(img);
	auto met2 = detectFire(img);
	makeViewLine(getCanals(img), "canale");
	//makeViewLine(met1,"fireRGB");
	//makeViewLine(met2,"fireHSV");
	//auto overlay = overlayMask(met1[2], met2[2]);
	//vector<Mat_<V3>> a = {img,met1[2], met2[2],overlay};
	//makeViewLine(a, "combinate");
}