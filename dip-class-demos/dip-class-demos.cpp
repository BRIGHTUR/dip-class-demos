// dip-class-demos.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

//OpenCV�е�mat�Ļ�������demo
int main()
{
	//��ʼ��ʱ
	double start = static_cast<double>(cvGetTickCount());

	//��ȡͼƬ
	//readImage();

	//��ȡ��Ƶ,�Լ�������ͷ
	//readVideo();

	//��ȡͼ������	
	//readSequence();

	//Mat�ĸ��ֻ�������
	useMat();

	//������ʱ
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//��ʾʱ��
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//�ȴ�������Ӧ�����������������
	system("pause");
    return 0;
}

