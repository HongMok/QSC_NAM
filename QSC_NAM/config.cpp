#include "functions.h"


//NAM搜索同类块
int ROW_FIRST = 1;//行优先
int COL_FIRST = 2;//列优先
int DIA_FIRST = 3;//对角优先


//NAM长宽比例限制
int NO_LIMIT = -1;//没有比例限制

CvMat *cm1 = cvCreateMat(512, 512, CV_32FC1);


//
int _nsym = 0;
int _count = 0;
int _coor_table_size = 0;

int METHOD = METHOD_NAM;









