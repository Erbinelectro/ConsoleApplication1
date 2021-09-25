#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

#include<locale.h>
#include<tchar.h>
#include <Windows.h>
#include "ArduinoCtrl.h"

using namespace std;

#ifdef _DEBUG
#pragma comment(lib, "opencv_world430d.lib")
#else
#pragma comment(lib, "opencv_world430.lib")
#endif

int main()
{
	ARDUINO_T arduinoLED;
	int retVal;
	
	_tsetlocale(LC_ALL, _T("Japanese_Japan.932"));

	arduinoLED = Arduino_open(_T("\\\\.\\COM5"));

	if (arduinoLED == NULL) {
		exit(EXIT_FAILURE);
	}


	const int MaxWidth = 600;
	const char* windowName = "Image";

	cv::VideoCapture cap(0);
	if (!cap.isOpened())//カメラデバイスが正常にオープンしたか確認．
	{
		return -1;
	}

	//顔認識用のカスケードを用意
	string cascade_path = "C:\\opencv\\sources\\samples\\winrt\\FaceDetection\\FaceDetection\\Assets\\haarcascade_frontalface_alt.xml";
	cv::CascadeClassifier cascade;
	cascade.load(cascade_path);

	while (1)
	{
		cv::Mat img;
		cap >> img;
		cv::Mat gray;
		//グレースケール化
		cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

		// gray から顔を探して赤い長方形を img に描画
		vector<cv::Rect> faces;
		cascade.detectMultiScale(gray, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

		int i = 1;
		int x = 0;

		for (auto face : faces) {
			cv::rectangle(img, face, cv::Scalar(0, 0, 255), 2);
			
			cout << face.x - MaxWidth / 2 << "    ";
			
			if (abs(face.x - MaxWidth / 2) < abs(x - MaxWidth / 2)) {
				x = face.x - MaxWidth / 2;
			}

			i++;
		}

		if (i >= 2) {
			cout << "center = " << x << endl;
			retVal = Arduino_execMainLoop(arduinoLED);
		}

		cv::imshow(windowName, img);//画像を表示．

		int key = cv::waitKey(1);
		if (key == 113)//qボタンが押されたとき
		{
			break;//whileループから抜ける
			if (retVal == FALSE) {
				exit(EXIT_FAILURE);
			}

			exit(EXIT_SUCCESS);
		}
	}
	cv::destroyAllWindows();
	return 0;
}