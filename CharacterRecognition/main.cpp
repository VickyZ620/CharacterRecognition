#include "cv.h"  
#include "highgui.h"  
#include "cxcore.h"
#include "ml.h"		//����CvSVM
#include "stdio.h"
using namespace std;
using namespace cv;

int svmDataTrain();
int recognition(IplImage *test);
int preProcess(char *imgPath, char *correctAnswers, int score);


int main(int argc, char* argv[])
{


	/*printf("\n--------------------��дӢ����ĸʶ����� by �̵�ɭ--------------------\n"
		"|\t\t\t\t\t\t\t\t     |\n"
		"---------------------------------�ȼ�---------------------------------\n"
		"|\t\t\tT - ѵ��������Train��\t\t\t     |\n"
		"|\t\t\tR - ����ʶ��Recognize��\t\t     |\n"
		"|\t\t\tQ - �˳�����Quit��\t\t\t     |\n"
		"----------------------------------------------------------------------\n");*/

	char imgPath[128] = { 0 };
	char correctAnswers[10] = { 0 };
	printf("�������뱾�ο��Ե���ȷ�𰸣�\n");
	scanf("%s", correctAnswers);
	printf("��������ѡ���ⵥ��ѡ��ķ�ֵ��\n");
	int score;
	scanf("%d", &score);
	fflush(stdin);

	for (;;)
	{

		printf("\n--------------------��дӢ����ĸʶ����� by �̵�ɭ--------------------\n"
			"|\t\t\t\t\t\t\t\t     |\n"
			"---------------------------------�ȼ�---------------------------------\n"
			"|\t\t\t\t\t\t\t\t     |\n"
			"|\t\t\tT - ѵ��������Train��\t\t\t     |\n"
			"|\t\t\tR - ʶ����ĸ��Recognize��\t\t     |\n"
			"|\t\t\tQ - �˳�����Quit��\t\t\t     |\n"
			"|\t\t\t\t\t\t\t\t     |\n"
			"----------------------------------------------------------------------\n");


		//�Ӽ��̶�ȡ����
		char operation;
		operation = cin.get();

		if ((char)operation == 'Q')
		{
			//�˳�����
			break;
		}
		if ((char)operation == 'T')
		{
			//ѵ������
			svmDataTrain();
		}
		if ((char)operation == 'R')
		{
			loop:			//ѭ��
			cin.sync();		//������
			cout << "�������ʶ��ͼƬ·�����˳��밴Q����" << endl;
			cin.getline(imgPath, 128);

			string imgPathStr = imgPath;	//���ַ�����תΪ�ַ���

			if (imgPathStr == "Q")
				break;

			string::size_type jpg = imgPathStr.find(".jpg");
			string::size_type jpeg = imgPathStr.find(".jpeg");
			string::size_type png = imgPathStr.find(".png");
			string::size_type bmp = imgPathStr.find(".bmp");
			string::size_type gif = imgPathStr.find(".gif");

			//���·���а�����.jpg����.jpeg����.png����.bmp����.gif��������Ϊ·����ȷ
			if ((jpg != string::npos) || (jpeg != string::npos) || (png != string::npos) || (bmp != string::npos) || (gif != string::npos))
			{
				//cout << "ʶ����..." << endl;

				//Ԥ�����и�ͼƬ������С��һ��
				int ret = preProcess(imgPath, correctAnswers, score);
				if (ret == -1)
				{
					printf("��ͼƬ�����ڣ������Զ��˳�...");
					_sleep(3000);
					return -1;
				}
			}
			else
			{
				cout << "·������ȷ��" << endl;
				goto loop;
			}
		}

		cin.sync();		//��ջ���
	}

	waitKey(0);
	return 0;
}