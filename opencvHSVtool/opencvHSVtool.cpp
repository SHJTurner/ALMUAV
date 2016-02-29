#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

bool videofile = false;

void on_trackbar( int, void* )
{
}


int main(int argc, char** argv )
{   

    UMat image,image_HSV,image_inRange;
    int H_high = 255, H_low = 0, S_high = 255, S_low = 0, V_high = 255, V_low = 0;
    VideoCapture cam;

    if ( argc != 2 && argc != 4 )
    {
        printf("usage: opencvHSVtool <VideoDevNum> <Frame_Width> <Frame_Height> or opencvHSVtool <VideoFilePath>\nWARNING: No <VideoDevNum> or <VideoFilePath> selected\nOpening video device 0\n");
        cam = VideoCapture(0);
    }
    else if(argc == 4)
    {
        printf("Opening video device %d...\n",atoi(argv[1]));
        cam = VideoCapture(atoi(argv[1]));
        cam.set(CAP_PROP_FRAME_WIDTH,atoi(argv[2]));
        cam.set(CAP_PROP_FRAME_HEIGHT,atoi(argv[3]));
        printf("Setting Frame_Width: %d and Frame_HEIGH: %d\n",atoi(argv[2]),atoi(argv[3]));
    }
    else if(argc == 2)
    {
        cam = VideoCapture(argv[1]);
        videofile = true;
    }

    if(!cam.isOpened())
    {
        printf("ERROR!: Failed to open video device\n");
        return -1;
    }
    else
        printf("Device opened\n");

    namedWindow("Display Original Video", WINDOW_NORMAL);
    namedWindow("Display HSV Video",WINDOW_NORMAL);
    namedWindow("HSV Controls",WINDOW_NORMAL);


    createTrackbar( "Hue low", "HSV Controls", &H_low, 180, on_trackbar );
    createTrackbar( "Hue high", "HSV Controls", &H_high, 180, on_trackbar );
    createTrackbar( "Saturation low", "HSV Controls", &S_low, 255, on_trackbar );
    createTrackbar( "Saturation high", "HSV Controls", &S_high, 255, on_trackbar );
    createTrackbar( "Value low", "HSV Controls", &V_low, 255, on_trackbar );
    createTrackbar( "Value high", "HSV Controls", &V_high, 255, on_trackbar );
    if(videofile){
        printf("Press esc to exit (Video is looping)\n");
        while(true)
        {
            if(cam.read(image))
            {
                cvtColor(image,image_HSV,cv::COLOR_RGB2HSV);
                cv::inRange(image_HSV,Scalar(H_low,S_low,V_low),Scalar(H_high,S_high,V_high),image_inRange);
                imshow("Display Original Video",image);
                imshow("Display HSV Video",image_inRange);
                if(waitKey(1) == 27)
                {
                    break;
                }
            }
            else
            {
                cam = VideoCapture(argv[1]);
            }
        }


    }
    else{
        printf("Press esc to exit\n");
        while(true)
        {
             cam.read(image);
             cvtColor(image,image_HSV,cv::COLOR_RGB2HSV);
             cv::inRange(image_HSV,Scalar(H_low,S_low,V_low),Scalar(H_high,S_high,V_high),image_inRange);
             imshow("Display Original Video",image);
             imshow("Display HSV Video",image_inRange);
             if(waitKey(1) == 27)
             {
                 break;
             }
        }
    }


    return 0;

}
