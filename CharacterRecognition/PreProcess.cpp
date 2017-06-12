#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
#include "ml.h"		//����CvSVM
#include <string>

using namespace cv;
using namespace std;

string recognition(IplImage *test);
string resultStr;

int preProcess(char* imgPath, char *correctAnswers, int score)
{
	//cout << imgPath << endl;
	//IplImage *srcImage = cvLoadImage("D:\\testImg\\exam.jpg", CV_LOAD_IMAGE_COLOR);	//��ȡͼƬ
	IplImage *srcImage = cvLoadImage(imgPath, CV_LOAD_IMAGE_COLOR);	//��ȡͼƬ
	if (srcImage == NULL)
	{
		return -1;
	}

	cout << "ʶ����..." << endl;

	printf("ͼƬ�Ŀ�͸߷ֱ�Ϊ��%d,%d\n", cvGetSize(srcImage).width, cvGetSize(srcImage).height);

	IplImage* grayImage = cvCreateImage(cvGetSize(srcImage), 8, 1);
	cvCvtColor(srcImage, grayImage, CV_BGR2GRAY);
	cvSaveImage("grayImage.jpg", grayImage);

	//IplImage *sobelImage = cvCreateImage(cvGetSize(srcImage), 8, 1);
	IplImage *binaryImage = cvCreateImage(cvGetSize(srcImage), 8, 1);

	//1. Sobel���ӣ�x�������ݶ�
	//cvSobel(grayImage, sobelImage, 1, 0, 3);

	//2. ��ֵ��
	cvThreshold(grayImage, binaryImage, 110, 255, CV_THRESH_BINARY_INV);
	cvNamedWindow("��ֵ�����ͼ��", CV_WINDOW_NORMAL);
	cvShowImage("��ֵ�����ͼ��", binaryImage);
	cvSaveImage("binaryImage.jpg", binaryImage);

	//3. ���ͺ͸�ʴ�����ĺ˺���
	//Mat dilateElement = getStructuringElement(MORPH_RECT, Size(30, 9));	//����
	//Mat erodeElement = getStructuringElement(MORPH_RECT, Size(24, 6));	//��ʴ
	//IplConvKernel *dilateElement = cvCreateStructuringElementEx(30, 9, 0, 0, CV_SHAPE_RECT, NULL);
	//IplConvKernel *erodeElement = cvCreateStructuringElementEx(24, 6, 0, 0, CV_SHAPE_RECT, NULL);

	////4. ����һ�Σ�������ͻ��
	//IplImage *dilateImage = cvCreateImage(cvGetSize(srcImage), 8, 1);	//����ͼ��
	//cvDilate(binaryImage, dilateImage, dilateElement, 1);

	//5. ��ʴһ�Σ�ȥ��ϸ�ڣ������ߵȡ�ע������ȥ��������ֱ����
	//IplImage *erodeImage = cvCreateImage(cvGetSize(srcImage), 8, 1);	//����ͼ��
	//cvErode(dilateImage, erodeImage, dilateElement, 1);

	////6. �ٴ����ͣ�����������һЩ
	////IplImage *dilateImage02 = cvCreateImage(cvGetSize(srcImage), 8, 1);	//����ͼ��
	////cvDilate(erodeImage, dilateImage02, dilateElement, 3);

	////7. �洢�м�ͼƬ
	//cvSaveImage("binaryImage.jpg", binaryImage);
	//cvSaveImage("dilateImage.jpg", dilateImage);
	//cvSaveImage("erodeImage.jpg", erodeImage);
	//cvSaveImage("dilateImage02.jpg", dilateImage02);


	//���ָ�
	int imgID = 0;
	char imgName[56] = { 0 };

	for (int i = 0; i < 10; i++)	//10����񣬱���
	{
		//cvDrawRect(srcImage, cvPoint(0, 0), cvPoint(0 + 530 * i, 0), CV_RGB(255, 0, 0));
		//cvSetImageROI(binaryImage, cvRect(1000 + 420 * i, 600, 320, 350));
		cvSetImageROI(binaryImage, cvRect(615 + 305 * i, 330, 270, 280));

		IplImage* gridImage = cvCreateImage(cvGetSize(binaryImage), 8, 1);
		cvCopy(binaryImage, gridImage);
		cvResetImageROI(binaryImage);

		sprintf(imgName, "�ָ���ͼƬ_%d", imgID++);
		cvNamedWindow(imgName, CV_WINDOW_NORMAL);
		cvShowImage(imgName, gridImage);


		//ʶ�𣺷ֱ��ÿ���и������ͼƬ����ʶ��
		resultStr = recognition(gridImage);
	}







	//IplImage* srcImage = cvLoadImage(".\\TestData\\test.jpg", CV_LOAD_IMAGE_COLOR);	//��ȡͼƬ

	////IplImage* imgDst = new IplImage[50];
	//cvSmooth(srcImage, srcImage, CV_BLUR);
	//IplImage* afterThresholdImg = cvCreateImage(cvGetSize(srcImage), 8, 1);		//����ͼ��
	//IplImage* grayImg = cvCreateImage(cvGetSize(srcImage), 8, 1);		//����ͼ��

	//cvCvtColor(srcImage, grayImg, CV_BGR2GRAY);									//ת��Ϊ�Ҷ�ͼ��grayImg�����ǵ�ͨ��ͼ
	//cvThreshold(grayImg, afterThresholdImg, 110, 255, CV_THRESH_BINARY_INV);	//CV_THRESH_BINARY_INVʹ�ñ���Ϊ��ɫ���ַ�Ϊ��ɫ�������ҵ������������ַ��������
	//cvNamedWindow("��ֵ�����ͼ��", CV_WINDOW_NORMAL);
	//cvShowImage("��ֵ�����ͼ��", afterThresholdImg);		//��ʾ��ֵ�����ͼ��

	//CvSeq* contours = NULL;		//�����߿�����
	//CvMemStorage* storage = cvCreateMemStorage(0);

	//int count = cvFindContours(afterThresholdImg, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL);
	//printf("����������%d\n", count);
	//int idx = 0;
	//char szName[56] = { 0 };

	//int normalizedNameIdx = 0;
	//char normalizedName[56] = { 0 };
	////int tempCount = 0;  
	//
	//for (CvSeq* c = contours; c != NULL; c = c->h_next) {
	//	CvRect rc = cvBoundingRect(c, 0);
	//	if (rc.height * rc.width < 64)
	//	{
	//		continue;     //������������Ĵ�С����ɸѡ  
	//	}
	//	cvDrawRect(grayImg, cvPoint(rc.x, rc.y), cvPoint(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 0, 0));
	//	IplImage* imgNo = cvCreateImage(cvSize(rc.width, rc.height), 8, 1);
	//	cvSetImageROI(grayImg, rc);
	//	cvCopyImage(grayImg, imgNo);
	//	cvResetImageROI(grayImg);
	//	sprintf(szName, "wnd_%d", idx++);
	//	cvNamedWindow(szName, CV_WINDOW_NORMAL);
	//	cvShowImage(szName, imgNo); //������и������ͼ����������򣬻���ϵ��£����ԱȽ�rc.x,rc.y;  

	//	//��С��һ��
	//	IplImage* newSizeImg = cvCreateImage(cvSize(32, 32), 8, 1);
	//	//newSizeImg = cvCreateImage(cvSize(32, 32), 8, 1);
	//	cvResize(imgNo, newSizeImg, CV_INTER_LINEAR);

	//	sprintf(normalizedName, "��һ����ĻҶ�ͼ��_%d", normalizedNameIdx++);
	//	cvNamedWindow(normalizedName, CV_WINDOW_NORMAL);
	//	cvShowImage(normalizedName, newSizeImg);

	//	//ʶ�𣺷ֱ��ÿ���и������ͼƬ����ʶ��
	//	resultStr = recognition(newSizeImg);

	//	//�ͷ���Դ
	//	cvReleaseImage(&imgNo);
	//	//cvReleaseImage(&newSizeImg);
	//}
	//reverse(resultStr.begin(), resultStr.end());	//��ת����ַ���
	printf("\nʶ������%s\n", resultStr.c_str());

	string correctAnswersStr = correctAnswers;
	int totalScore = 0;
	for (int i = 0; i < 10; i++)
	{
		if (resultStr[i] == correctAnswersStr[i])
			totalScore += score;
	}
	printf("��ͬѧѡ�����ܷ�Ϊ��%d��\n", totalScore);
	return 0;
}