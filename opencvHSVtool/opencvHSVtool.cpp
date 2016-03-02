#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

bool videofile = false;

void on_trackbar( int, void* )
{
}
const cv::Scalar black(0,0,0);

int main(int argc, char** argv )
{   

    UMat image,image_HSV,image_inRange, image_inRange2, image_inRangeAdded,image_masked;
    int filter2Enabled = 0, display_color = 0;
    int H_high = 255, H_low = 0, S_high = 255, S_low = 0, V_high = 255, V_low = 0;
    int H_high2 = 255, H_low2 = 0, S_high2 = 255, S_low2 = 0, V_high2 = 255, V_low2 = 0;
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


    std::string filter1name = "HSV Controls: Filter 1";
    std::string filter2name = "HSV Controls: Filter 2";
    std::string OriginalName = "Display Original";
    std::string HSVName = "Display HSV";
    namedWindow(OriginalName, WINDOW_NORMAL);
    namedWindow(HSVName,WINDOW_NORMAL);
    namedWindow(filter1name,WINDOW_NORMAL);
    namedWindow(filter2name,WINDOW_NORMAL);

    createTrackbar( "Colored output", filter1name, &display_color, 1, on_trackbar );
    createTrackbar( "Hue low", filter1name, &H_low, 180, on_trackbar );
    createTrackbar( "Hue high", filter1name, &H_high, 180, on_trackbar );
    createTrackbar( "Saturation low", filter1name, &S_low, 255, on_trackbar );
    createTrackbar( "Saturation high", filter1name, &S_high, 255, on_trackbar );
    createTrackbar( "Value low", filter1name, &V_low, 255, on_trackbar );
    createTrackbar( "Value high", filter1name, &V_high, 255, on_trackbar );

    createTrackbar( "Enable Filter 2", filter2name, &filter2Enabled, 1, on_trackbar );
    createTrackbar( "Hue low 2", filter2name, &H_low2, 180, on_trackbar );
    createTrackbar( "Hue high 2", filter2name, &H_high2, 180, on_trackbar );
    createTrackbar( "Saturation low 2", filter2name, &S_low2, 255, on_trackbar );
    createTrackbar( "Saturation high 2", filter2name, &S_high2, 255, on_trackbar );
    createTrackbar( "Value low 2", filter2name, &V_low2, 255, on_trackbar );
    createTrackbar( "Value high 2", filter2name, &V_high2, 255, on_trackbar );
    if(videofile){
        printf("Press esc to exit (Video is looping)\n");
        while(true)
        {
            if(cam.read(image))
            {
                cvtColor(image,image_HSV,cv::COLOR_RGB2HSV);
                if(filter2Enabled == 1)
                {
                cv::inRange(image_HSV,Scalar(H_low,S_low,V_low),Scalar(H_high,S_high,V_high),image_inRange);
                cv::inRange(image_HSV,Scalar(H_low2,S_low2,V_low2),Scalar(H_high2,S_high2,V_high2),image_inRange2);
                cv::addWeighted(image_inRange,1.0,image_inRange2,1.0,1.0,image_inRangeAdded);
                }
                else
                {
                    cv::inRange(image_HSV,Scalar(H_low,S_low,V_low),Scalar(H_high,S_high,V_high),image_inRangeAdded);
                }

                if(display_color == 1)
                {
                        Mat(image.rows,image.cols,CV_8UC3, Scalar(0,0,0)).copyTo(image_masked);
                        image.copyTo(image_masked,image_inRangeAdded);
                        imshow(HSVName,image_masked);
                }
                else
                        imshow(HSVName,image_inRangeAdded);
                image.copyTo(image_masked,image_inRangeAdded);
                imshow(OriginalName,image);

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
             if(filter2Enabled == 1)
             {
             cv::inRange(image_HSV,Scalar(H_low,S_low,V_low),Scalar(H_high,S_high,V_high),image_inRange);
             cv::inRange(image_HSV,Scalar(H_low2,S_low2,V_low2),Scalar(H_high2,S_high2,V_high2),image_inRange2);
             cv::addWeighted(image_inRange,1.0,image_inRange2,1.0,1.0,image_inRangeAdded);
             }
             else
             {
                 cv::inRange(image_HSV,Scalar(H_low,S_low,V_low),Scalar(H_high,S_high,V_high),image_inRangeAdded);
             }
             if(display_color == 1)
             {
                     Mat(image.rows,image.cols,CV_8UC3, Scalar(0,0,0)).copyTo(image_masked);
                     image.copyTo(image_masked,image_inRangeAdded);
                     imshow(HSVName,image_masked);
             }
             else
                     imshow(HSVName,image_inRangeAdded);

             image.copyTo(image_masked,image_inRangeAdded);
             imshow(OriginalName,image);
             if(waitKey(1) == 27)
             {
                 break;
             }
        }
    }


    return 0;

}
