#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;


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
        printf("usage: DisplayImage.out <VideoDevNum> <Frame_Width> <Frame_Height>\nWARNING: No <VideoDevNum> selected\nOpening video device 0\n");
        cam = VideoCapture(0);
    }
    else
    {
        printf("Opening video device %d...\n",atoi(argv[1]));
        cam = VideoCapture(atoi(argv[1]));
    }

    if(argc == 4)
    {
        cam.set(CAP_PROP_FRAME_WIDTH,atoi(argv[2]));
        cam.set(CAP_PROP_FRAME_HEIGHT,atoi(argv[3]));
        printf("Setting Frame_Width: %d and Frame_HEIGH: %d\n",atoi(argv[2]),atoi(argv[3]));
    }
    else
    {
        printf("usage: DisplayImage.out <VideoDevNum> <Frame_Width> <Frame_Height>\n");
        printf("WARNING: No <Frame_Width>/<Frame_Height>!\n");
        printf("Setting Frame_Width: 640 and Frame_HEIGH: 480\n");
        cam.set(CAP_PROP_FRAME_WIDTH,640);
        cam.set(CAP_PROP_FRAME_HEIGHT,480);
    }

    if(!cam.isOpened())
    {
        printf("ERROR!: Failed to open video device\n");
        return -1;
    }
    else
        printf("Device opened\n");

    namedWindow("Display Original Video", WINDOW_AUTOSIZE);
    namedWindow("Display HSV Video",WINDOW_AUTOSIZE);
    namedWindow("HSV Controls",WINDOW_AUTOSIZE);

    createTrackbar( "Hue high", "HSV Controls", &H_high, 255, on_trackbar );
    createTrackbar( "Hue low", "HSV Controls", &H_low, 255, on_trackbar );
    createTrackbar( "Saturation high", "HSV Controls", &S_high, 255, on_trackbar );
    createTrackbar( "Saturation low", "HSV Controls", &S_low, 255, on_trackbar );
    createTrackbar( "Value high", "HSV Controls", &V_high, 255, on_trackbar );
    createTrackbar( "Value low", "HSV Controls", &V_low, 255, on_trackbar );

    while(true)
    {
         cam.read(image);
         cvtColor(image,image_HSV,cv::COLOR_RGB2HSV);
         cv::inRange(image_HSV,Scalar(H_low,S_low,V_low),Scalar(H_high,S_high,V_high),image_inRange);

         imshow("Display Original Video",image);
         imshow("Display HSV Video",image_inRange);
         waitKey(1);
    }

    return 0;

}
