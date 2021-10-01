#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

#include <stdio.h>
#include <stdint.h>
#include <locale.h>
#include <windows.h>
#include <tchar.h>
#include <conio.h>

#include "ArduinoCtrl.h"
#include "SerialPort.h"

using namespace std;

MiconConnecter.Form1

#ifdef _DEBUG
#pragma comment(lib, "opencv_world430d.lib")
#else
#pragma comment(lib, "opencv_world430.lib")
#endif

//for opencv
const int MaxWidth = 600;
const char* windowName = "Image";
cv::CascadeClassifier cascade;
string cascade_path = "C:\\opencv\\sources\\samples\\winrt\\FaceDetection\\FaceDetection\\Assets\\haarcascade_frontalface_alt.xml";
vector<cv::Rect> faces;
int i = 1;
int GAP;

int main()
{
	bool loop = true;
	cv::Mat img;
	cv::Mat gray;


	cv::VideoCapture cap(0);

	if (!cap.isOpened()) { return -1; }
	
	cout << "ALL Opened" << endl;

	//initialize end

	cascade.load(cascade_path);//顔認識用のカスケードを用意

	while (loop)
	{
		cap >> img;
		cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY); //グレースケール化
		cascade.detectMultiScale(gray, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30)); // gray から顔を探して赤い長方形を img に描画


		for (auto face : faces) {
			cv::rectangle(img, face, cv::Scalar(0, 0, 255), 2);
			
			cout << endl <<face.x - MaxWidth / 2 << "    ";
			
			if (abs(face.x - MaxWidth / 2) < abs(GAP - MaxWidth / 2)) {
				GAP = face.x - MaxWidth / 2;
			}

			i++;
		}

		if (i >= 2) {
			cout << "center = " << GAP << endl;
			
			
		}

		cv::imshow(windowName, img);//画像を表示.

		int key = cv::waitKey(1);
		if (key == 113)//qボタンが押されたとき
		{
			loop = false;//whileループから抜ける．
		}
	}

	//_tprintf(_T("プログラムを終了しました\n"));
	cout << "プログラムを終了しました" << endl;

	exit(EXIT_SUCCESS);

	cv::destroyAllWindows();
	return 0;
}