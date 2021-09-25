#include <iostream>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib, "opencv_world430d.lib")
#else
#pragma comment(lib, "opencv_world430.lib")
#endif

int main()
{
    const char* windowName = "Image";

    cv::Mat img = cv::imread("C:\\Users\\oswys\\デスクトップ\\kogakuin.png", 0);
    if (img.empty()) {
        return -1;
    }
    std::cout << "load success" << std::endl;
    cv::imshow(windowName, img);

    cv::waitKey(0);

    return 0;
}