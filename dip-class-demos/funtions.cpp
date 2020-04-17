#include "stdafx.h"
#include <opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

#define WH_RATIO_HIGH	1.2	
#define WH_RATIO_LOW	0.9	
#define AREA_TH			100

//blob������ʾ������
void rimBlobAnalysis()
{

	//����ͼ������
	Mat srcMat;
	Mat bnyMat;
	Mat disMat;
	Mat sttMat;
	Mat cntMat;
	Mat lblMat;

	//��ȡͼƬ
	srcMat=imread("D:\\rim.png");
	srcMat.copyTo(disMat);
	cvtColor(srcMat,srcMat,COLOR_BGR2GRAY);

	//��ֵ��
	threshold(srcMat,bnyMat,100,255,THRESH_OTSU);

	//��ɫ
	bnyMat = 255 - bnyMat;

	//��ͨ��
	int nComp = connectedComponentsWithStats(bnyMat, lblMat, sttMat, cntMat);

	int * flag = new int[nComp];
	memset(flag, 0, sizeof(int)*nComp);

	//�������
	for (int i = 1; i < nComp; i++) {
		float width = (float)sttMat.at<int>(i, CC_STAT_WIDTH);
		float height= (float)sttMat.at<int>(i, CC_STAT_HEIGHT);
		float ratio = width/height;

		if (
			   (ratio > WH_RATIO_LOW)
			&& (ratio < WH_RATIO_HIGH)
			&& (sttMat.at<int>(i, CC_STAT_AREA) > AREA_TH)
			)
		{
			flag[i] = 1;
		}
	}

	//����
	for (int i = 0; i<srcMat.rows; i++)
	{
		for (int j = 0; j<srcMat.cols; j++)
		{
			int no = lblMat.at<int>(i, j);

			if (flag[no] == 1) {
				disMat.at<Vec3b>(i, j)[0] = 0;
				disMat.at<Vec3b>(i, j)[1] = 255;
				disMat.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}

	delete[] flag;

	imshow("source image",srcMat);
	imshow("binary image",bnyMat);
	imshow("hole image",disMat);

	waitKey(0);

}

void chipBlobAnalysis()
{
	//����ͼ������
	Mat srcMat;
	Mat bnyMat;
	Mat disMat;
	Mat sttMat;
	Mat cntMat;
	Mat lblMat;

	//��ȡͼƬ
	srcMat = imread("F:\\die_on_chip.png");
	srcMat.copyTo(disMat);
	cvtColor(srcMat, srcMat, COLOR_BGR2GRAY);

	//��ֵ��
	threshold(srcMat, bnyMat, 100, 255, THRESH_OTSU);

	//��ʴ����
	cv::Mat element = cv::Mat::ones(3,3, CV_8UC1);
	erode(bnyMat,bnyMat, element, cv::Point(-1, -1));

	//ͨ��findContours����Ѱ����ͨ��
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(bnyMat,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);


	//��������
	for (int i = 0; i < contours.size(); i++) {
		
		//�����С����ı���
		RotatedRect rbox = minAreaRect(contours[i]);

		float width = (float)rbox.size.width;
		float height= (float)rbox.size.height;
		float ratio = width / height;

		if (
			(ratio > WH_RATIO_LOW)
			&& (ratio < WH_RATIO_HIGH)
			)
		{
			drawContours(disMat, contours, i, Scalar(0,255,255), 1, 8);
			cv::Point2f vtx[4];
			rbox.points(vtx);
			for (int i = 0; i < 4; ++i) {
				cv::line(disMat, vtx[i], vtx[i<3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
			}
		}
	}

	imshow("source image", srcMat);
	imshow("binary image", bnyMat);
	imshow("hole image", disMat);

	waitKey(0);
}
