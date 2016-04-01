#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "red_led_detector.h"
#include <ctime>
using namespace std;

#define opencv3

int main(int argc, char** argv )
{
#if CV_MAJOR_VERSION > 2
    cv::UMat image;
#else
    cv::Mat image;
#endif

    clock_t start, end;
    uint framecounter = 0;
    cv::VideoCapture Video;
    Red_led_detector detector;

    printf("Test program for red_led_detector class\nOpenCV Ver.: %d.%d\n",CV_MAJOR_VERSION,CV_MINOR_VERSION);

    if(argc == 2) {
        Video.open(argv[1]);
        if(!Video.isOpened()) {
            printf("ERROR!: Failed to open Video\n");
            return -1;
        }
    }
    else {
        printf("usage: red_led_detector_test_program <VideoPath>\n");
        return -1;
    }


    while(true)
    {
         //if reading a frame fails, try and open video again (it has propperly found the end of vid)
        if(!Video.read(image))
        {
           Video.open(argv[1]);
           Video.read(image);
        }

        //Process
        vector<Point2f> points;
        detector.detect(image,points);
        for(Point2f point : points)
        {
            circle(image,point,4,Scalar(0,255,255),2);
        }

        cv::imshow("Display",image);
        cv::waitKey(1);


    }

    return 0;

/*
///Mat(CPU) fps test
    printf("Mat(CPU) FPS test...\n");
    cv::Mat image, imageHSV,imageRed;
    start = clock();
    for(uint i = 0; i < 201; i++)
    {
        if(framecounter == 50)
        {
            end = clock();
            printf("FPS: %4.2f\n",((double)1/((double(end - start)/50.0)/CLOCKS_PER_SEC)));
            cout << std::flush;
            start = clock();
            framecounter = 0;
        }
        framecounter++;

        cam.grab();
        cam.retrieve(image,0);
        cv::cvtColor(image, imageHSV, cv::COLOR_RGB2HSV); //convert to HSV
        cv::inRange(imageHSV, cv::Scalar(0, 0, 0), cv::Scalar(100, 100, 255), imageRed);


    return 0;*/
}
