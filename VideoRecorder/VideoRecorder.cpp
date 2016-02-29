#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <ctime>
using namespace std;

///Show cam video
#define Display

///Image resolution
#define Image_Width 1280
#define Image_Height 720

#define Device 0
int main(int argc, char** argv )
{
    ///Print title and OpenCV version
    printf("OpenCV Mat vs UMat FPS test\nTask: Convert to hue and preform color segmentation\nOpenCV Ver.: %d.%d\n",CV_MAJOR_VERSION,CV_MINOR_VERSION);

#ifdef Display
    printf("Display image: true (This will lower FPS. Comment \"#define Display\" in Mat_vs_UMat_test.cpp to disable)\n");
    cv::namedWindow("Display Image", cv::WINDOW_NORMAL );
#else
    printf("Display image: false (Uncomment \"#define Display\" in Mat_vs_UMat_test.cpp to enable)\n");
#endif

    cv::VideoCapture cam;

    ///Open cam and set resolution
    cam.open(Device);
    if(!cam.isOpened())
    {
        printf("ERROR!: Failed to open camera stream\nIs there a camera connected?");
        return -1;
    }
    else
        printf("Camera stream opened\n");

    cam.set(cv::CAP_PROP_FRAME_WIDTH,Image_Width);
    cam.set(cv::CAP_PROP_FRAME_HEIGHT,Image_Height);

    ///Open video out stream
    cv::VideoWriter VideoOut("videoOut.avi",1196444237,30,cv::Size(Image_Width,Image_Height));
    if (VideoOut.isOpened())
        printf("Video out stream opened");
    else
    {
        printf("ERROR!:Failed to open video out stream!\n");
        return -1;
    }

    cv::Mat image;
    while(cv::waitKey(1) != 27)
    {
        cam.read(image);
        VideoOut.write(image);
#ifdef Display
        cv::imshow("Display Image",image);
#endif
    }
    VideoOut.release();
    return 0;
}
