﻿#include "stdafx.h"
#include "funtions.h"
#include <opencv.hpp>



using namespace cv;

int detectPeople()
{

	VideoCapture cap("../testImages\\vtest.avi");

	

	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());





	return 0;
}
