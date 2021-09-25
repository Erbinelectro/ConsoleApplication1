/**
 * @file        main.c
 * @brief       Arduino制御用Windowsアプリケーション
 * @author      Keitetsu
 * @date        2017/12/02
 * @copyright   Copyright (c) 2017 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <locale.h>
#include <windows.h>
#include <tchar.h>
#include <conio.h>

#include "ArduinoCtrl.h"
#include "SerialPort.h"

using namespace std;

#define KEY_ESC             0x1B

int main(int argc, _TCHAR* argv[])
{
    ARDUINO_T arduinoLED;
    int retVal;

    /* ロケールの設定 */
    _tsetlocale(LC_ALL, _T("Japanese_Japan.932"));

    /* Arduinoを開く */
    arduinoLED = Arduino_open(_T("\\\\.\\COM7"));
    if (arduinoLED == NULL) {
        exit(EXIT_FAILURE);
    }
    else {
        cout << "opened" << endl;
    }

    /* Arduino制御 */
    int loop;
    int key;
    int retVal;
    int result;

    loop = TRUE;
    result = TRUE;

    cout << "loop start" << endl;

    while (loop)
    {
        if (_kbhit() != 0)
        {
            key = _getch();

            if (key = KEY_ESC) {
                loop = false;
                break;
            }


        }
    }

    //_tprintf(_T("プログラムを終了しました\n"));
    cout << "プログラムを終了しました" << endl;

    retVal = result;

    /* Arduinoを閉じる */
    Arduino_close(arduinoLED);

    if (retVal == FALSE) {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
