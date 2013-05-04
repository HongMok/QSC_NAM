#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
#include "vector"
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;



struct GrayLevel
{
	int g1;
	int g2;
	int g3;
	int g4;
};



struct CouplePoints
{
	int x1;
	int y1;
	int x2;
	int y2;
};