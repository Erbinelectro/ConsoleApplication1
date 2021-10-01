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

#ifdef _DEBUG
#pragma comment(lib, "opencv_world430d.lib")
#else
#pragma comment(lib, "opencv_world430.lib")
#endif

/*
* memo
* 
* _T("")　は　unicode用でもMBCS用でもどっちでも行けるようにみたいな文字列の書き方
* LPCSTR = const char* ?????
*/

//for control arduino
ARDUINO_T arduino;
const int KEY_ESC = 0x1B;
const int KEY_Q = 0x71;
int loop = 1;
int key = 0;
int retVal;
int result = 1;

//for opencv
const int MaxWidth = 600;
const char* windowName = "Image";
cv::CascadeClassifier cascade;
string cascade_path = "C:\\opencv\\sources\\samples\\winrt\\FaceDetection\\FaceDetection\\Assets\\haarcascade_frontalface_alt.xml";
vector<cv::Rect> faces;
int i = 1;
int *GAP;

int main()
{
	cv::Mat img;
	cv::Mat gray;

	// initialize start

	ZeroMemory(GAP, sizeof(GAP));

	_tsetlocale(LC_ALL, _T("Japanese_Japan.932"));

	arduino = Arduino_open(_T("\\\\.\\COM7"));
	cv::VideoCapture cap(0);

	if (arduino == NULL && !cap.isOpened()) { return -1; }
	
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
			
			if (abs(face.x - MaxWidth / 2) < abs(*GAP - MaxWidth / 2)) {
				*GAP = face.x - MaxWidth / 2;
			}

			i++;
		}

		if (i >= 2) {
			cout << "center = " << *GAP << endl;
			
			retVal = SerialPort_write(arduino->port, GAP);

		}

		cv::imshow(windowName, img);//画像を表示.

		/*********** Arduino制御 **************/
		if (_kbhit() != 0)
		{
			key = _getch();

			if (key = KEY_ESC)//ESCボタンが押されたとき
			{
				loop = 0;
				break;//whileループから抜ける
				if (retVal == FALSE) {
					exit(EXIT_FAILURE);
				}

				exit(EXIT_SUCCESS);
			}

		}
	}

	//_tprintf(_T("プログラムを終了しました\n"));
	cout << "プログラムを終了しました" << endl;

	retVal = result;

	/* Arduinoを閉じる */
	Arduino_close(arduino);

	if (retVal == FALSE) {
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);

	cv::destroyAllWindows();
	return 0;
}