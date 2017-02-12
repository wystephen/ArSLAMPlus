//
// Created by steve on 17-2-12.
//

#include <iostream>

#include <thread>

#include <opencv2/videoio.hpp>
#include <opencv/cv.hpp>

void anotherCap()
{
    cv::namedWindow("newtest");
    cv::VideoCapture cap("/dev/video2");
    cv::Mat tmp;
    while(cap.isOpened())
    {
        cap >> tmp;
        std::cout << "tmp...:"<<tmp.rows << " : " << tmp.cols << std::endl;

        cv::imshow("newtest",tmp);
        cv::waitKey(10);

    }
}

int main()
{

//    std::thread t(anotherCap);
//    t.detach();
    cv::VideoCapture cap(2);
    cv::VideoCapture capR(1);
    cap.set(CV_CAP_PROP_FRAME_WIDTH,1280);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,720);
//    cap.set(CV_CAP_PROP_FRAME_WIDTH,320);
//    cap.set(CV_CAP_PROP_FRAME_HEIGHT,240);
//    cap.set(CV_CAP_OPENNI_QVGA_60HZ, 30.0);
//
    capR.set(CV_CAP_PROP_FRAME_WIDTH,1280);
    capR.set(CV_CAP_PROP_FRAME_HEIGHT,720);
//    capR.set(CV_CAP_PROP_FRAME_WIDTH,320);
//    capR.set(CV_CAP_PROP_FRAME_HEIGHT,240);
//    capR.set(CV_CAP_OPENNI_QVGA_60HZ,30.0);

    cv::namedWindow("Test");
    cv::namedWindow("TestR");

    cv::Mat tmp;
    cv::Mat tmpr;

    cv::VideoWriter videoWriter,videoWriter1;
//    videoWriter.open("test_video.avi", -1, cap.get(CV_CAP_PROP_FPS),720*1280, true);
    videoWriter.open("./test_video.avi",0,cap.get(CV_CAP_PROP_FPS),cv::Size(1280,720),true);
    videoWriter1.open("./test_video_r.avi",0,cap.get(CV_CAP_PROP_FPS),cv::Size(1280,720),true);

    while(cap.isOpened())
    {
        cap >> tmp;
        cv::waitKey(10);

        cv::waitKey(10);
//        videoWriter.write(tmp);
        std::cout << tmp.rows << " :: " << tmp.cols << std::endl;


        videoWriter << tmp;

        cv::imshow("Test",tmp);
        cv::waitKey(10);
        capR >> tmpr;

        videoWriter1 << tmpr;
        std::cout << tmpr.rows << "  ::  " << tmpr.cols << std::endl;
        cv::imshow("TestR",tmpr);
        cv::waitKey(10);
    }
}