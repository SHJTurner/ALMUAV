#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <ctime>
using namespace std;



///Show cam video
#define Display

///Defines
#define Image_Width     1280
#define Image_Height    720

#define ANSI_COLOR_RED  "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
int main(int argc, char** argv )
{
    ///Print title and OpenCV version
    printf("VideoRecorder\nOpenCV Ver.: %d.%d\n",CV_MAJOR_VERSION,CV_MINOR_VERSION);

#ifdef Display
    printf("Display image: true\n");
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
#else
    printf("Display image: false (Uncomment \"#define Display\" in Mat_vs_UMat_test.cpp to enable)\n");
#endif

    cv::VideoCapture cam;
    if ( argc != 2)
    {
        printf(ANSI_COLOR_YELLOW "WARNING: No <VideoDevNum> selected... Opening video device 0\n" ANSI_COLOR_RESET "usage: DisplayImage.out <VideoDevNum>\n");
        cam = cv::VideoCapture(0);
    }
    else
    {
        printf("Opening video device %d... ",atoi(argv[1])); cout.flush();
        cam = cv::VideoCapture(atoi(argv[1]));
    }


    ///Open cam and set resolution
    if(!cam.isOpened())
    {
        printf(ANSI_COLOR_RED "ERROR: Failed to open camera stream (Is there a camera connected?)" ANSI_COLOR_RESET "\n");
        return -1;
    }
    else
        printf("done\n");

    cam.set(cv::CAP_PROP_FRAME_WIDTH,Image_Width);
    cam.set(cv::CAP_PROP_FRAME_HEIGHT,Image_Height);

    cv::Mat image;
    vector<cv::Mat> Mats;
    printf("Recording... (Press esc to stop)\n");
    while(cv::waitKey(1) != 27)
    {
        cam.read(image);

        Mats.push_back(image.clone());

#ifdef Display
        cv::imshow("Display Image",image);
#endif
    }
    printf("Recording stopped\n");
    //Write Video to disk
    ///Open video out stream
    printf("Opening video output... "); cout.flush();
    cv::VideoWriter VideoOut("videoOut.avi",1196444237,30,cv::Size(Image_Width,Image_Height));
    if (VideoOut.isOpened())
        printf("done\n");
    else
    {
        printf("\n" ANSI_COLOR_RED "ERROR: Failed to open video output!\n" ANSI_COLOR_RESET);
        return -1;
    }
    printf("Writing video to disk... "); cout.flush();
    int showCounter = 0, Frame_number = 0;
    //for(cv::Mat iMat : Mats)
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    for(std::vector<cv::Mat>::iterator it = Mats.begin() ; it != Mats.end(); ++it)
    {
        VideoOut.write(*it);

        showCounter++;
        Frame_number++;
        if(showCounter == 20)
        {
            string displayText = "Writing Frame: "+ to_string(Frame_number) + " / " + to_string(Mats.size());
            cv::putText(*it,displayText,cv::Point(80,80),cv::FONT_HERSHEY_SIMPLEX,2.2,cv::Scalar(0,255,0),3);
            cv::imshow("Display Image",*it);
            cv::waitKey(1);
            showCounter = 0;
        }
    }
    VideoOut.release();
    printf("done\n");
    return 0;
}
