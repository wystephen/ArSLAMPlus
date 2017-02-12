//
// Created by steve on 17-2-12.
//

#include <iostream>

#include <opencv2/videoio.hpp>
#include <opencv/cv.hpp>


int main()
{
    cv::VideoCapture cap("/dev/video1");
    cv::VideoCapture capR("/dev/video2");
    cap.set(CV_CAP_PROP_FRAME_WIDTH,1280);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,720);
//    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
//    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
    cap.set(CV_CAP_OPENNI_QVGA_60HZ, 30.0);
    cv::namedWindow("Test");
    cv::namedWindow("TestR");

    cv::Mat tmp;
    cv::Mat tmpr;

    cv::VideoWriter videoWriter;
//    videoWriter.open("test_video.avi", -1, cap.get(CV_CAP_PROP_FPS),720*1280, true);
    videoWriter.open("./test_video.avi",0,cap.get(CV_CAP_PROP_FPS),cv::Size(1280,720),true);

    while(cap.isOpened())
    {
        cap >> tmp;
        capR >> tmpr;
//        videoWriter.write(tmp);

        videoWriter << tmp;
        cv::imshow("Test",tmp);
        cv::waitKey(10);

//        cv::imshow("TestR",tmpr);
        cv::waitKey(10);
    }
}