#include "datastruct.h"


//config
extern int ROW_FIRST;
extern int COL_FIRST;
extern int DIA_FIRST;

extern int NO_LIMIT;

extern CvMat *cm1;

extern int _nsym;
extern int _count;
extern int _coor_table_size;

extern int METHOD;
const int METHOD_NAM = 1;
const int METHOD_FRAG_NAM = 2;
const int METHOD_AC_NAM = 3;
const int METHOD_AC_FRAG_NAM = 4;


//NAM
bool IsHomogeneousBlock(IplImage *img, CouplePoints ps, double epsilon);
void RNAMencoding(IplImage *img, double epsilon, vector<GrayLevel> &P, vector<char> &Q, vector<CouplePoints> &blks, int &frag_num, int HWratio = NO_LIMIT, int DIRpriority = ROW_FIRST);
void RNAMdecoding(IplImage *img, double epsilon, vector<GrayLevel> &P, vector<char> &Q, int &frag_num);
void RefineImage(IplImage *img, vector<CouplePoints> &blks, vector<GrayLevel> &P);


//CoordinateHelper
void CompressCoordinate(CvMat *R, vector<char> &Q);

void DecompressCoordinate(CvMat *R, vector<char> &Q);
void test();
char *advanced_dec2binstr(int d, int &len);
int advanced_binstr2dec(vector<char> &Q, int start_i, int &len);

void Fragment_CompressCoordinate(CvMat *R, vector<char> &Q, int frag_num);
void Fragment_DecompressCoordinate(CvMat *R, vector<char> &Q, int frag_num);

void dispIline(CvMat *R, int i);

void AC_CompressCoordinate(CvMat *R, int &NSYM, int &count);
void AC_DecompressCoordinate(CvMat *R, int NSYM, int count);

int calMaxNum(vector<int> &Q);

void ac_compress_array(vector<int> &Q, int NSYM);
void ac_decompress_array(vector<int> &Q, int NSYM, int count);

void AC_Fragment_CompressCoordinate(CvMat *R, int &NSYM, int &count, int frag_num);
void AC_Fragment_DecompressCoordinate(CvMat *R, int NSYM, int count, int frag_num);




//util
void VectorAddStr(vector<char> &Q, char *str, int len);
char *dec2binstr(int d, int len);
int binstr2dec(vector<char> &Q, int start_i, int len);
void ShowSegmentation(IplImage *img1, vector<CouplePoints> &C);

void setPS(CouplePoints &ps, int x1, int y1, int x2, int y2);

double PSNR ( IplImage *img1 , IplImage *imggest );

double BPP ( vector<GrayLevel> &P ,int M , int N , vector<char> &Q );

int calCodingPoint(vector<GrayLevel> &P);

void copyMat(CvMat *R1, CvMat *R2);

bool isSameMat(CvMat *R1, CvMat *R2);

int calFragNum(vector<GrayLevel> &P, CvMat *R);

void img2mat(IplImage *srcImg, CvMat *R);