#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <ctime>
using namespace std;

///Show cam video
//#define Display

///Image resolution
#define Image_Width 1280
#define Image_Height 720

int main(int argc, char** argv )
{
    ///Print title and OpenCV version
    printf("OpenCV Mat vs UMat FPS test\nTask: Convert to hue and preform color segmentation\nOpenCV Ver.: %d.%d\nTest resolution: %d x %d\n",CV_MAJOR_VERSION,CV_MINOR_VERSION,Image_Width,Image_Height);

#ifdef Display
    printf("Display image: true (This will lower FPS. Comment \"#define Display\" in Mat_vs_UMat_test.cpp and recompile to disable)\n");
    cv::namedWindow("Display Image", cv::WINDOW_NORMAL );
#else
    printf("Display image: false (Uncomment \"#define Display\" in Mat_vs_UMat_test.cpp and recompile to enable)\n");
#endif


    clock_t start, end;
    uint framecounter = 0;


    cv::VideoCapture cam;

    if(argc == 2)
    {
        cam.open(atoi(argv[1]));
    }
    else
    {
        cam.open(0);
    }

    ///Open cam and set resolution
    //cam.open(0);
    if(!cam.isOpened())
    {
        printf("ERROR!: Failed to open camera stream\nIs there a camera connected?");
        return -1;
    }
    else
        printf("Camera stream opened\n");
    cam.set(cv::CAP_PROP_FRAME_WIDTH,Image_Width);
    cam.set(cv::CAP_PROP_FRAME_HEIGHT,Image_Height);

    printf("Capturering 240 images for the test...");
    cout << std::flush;
    //record 240 images
    cv::Mat newimage;
    vector<cv::Mat> images;
    for(uint i = 0; i< 241; i++)
    {
        cam.grab();
        cam.retrieve(newimage,0);
        images.push_back(newimage);
    }
    printf("done\n");

    ///Mat(CPU) fps test
    printf("Mat(CPU) FPS test...\n");
    cv::Mat imageHSV,imageRed;

    start = clock();
    for(cv::Mat image : images)
    {
        if(framecounter == 60)
        {
            end = clock();
            printf("Mean FPS (last 60 frames): %4.2f\n",((double)1/((double(end - start)/60.0)/CLOCKS_PER_SEC)));
            cout << std::flush;
            start = clock();
            framecounter = 0;
        }
        framecounter++;

        cam.grab();
        cam.retrieve(image,0);
        cv::cvtColor(image, imageHSV, cv::COLOR_RGB2HSV); //convert to HSV
        cv::inRange(imageHSV, cv::Scalar(0, 0, 0), cv::Scalar(100, 100, 255), imageRed);

#ifdef Display
        cv::imshow("Display Image", imageRed);
        cv::waitKey(1);
#endif
    }
    cv::UMat newUimage;
    vector<cv::UMat> Uimages;
    for(cv::Mat image : images)
    {
        image.copyTo(newUimage);
        Uimages.push_back(newUimage);
    }

///UMAT(GPU) fps test
    printf("UMat(GPU) FPS test...\n");
    cv::UMat Uimage, UimageHSV,UimageRed;
    start = clock();
    framecounter = 0;
    for(cv::UMat Uimage : Uimages)
    {
        ///Messure time
        if(framecounter == 60)
        {
            end = clock();
            printf("Mean FPS (last 60 frames): %4.2f\n",((double)1/((double(end - start)/60.0)/CLOCKS_PER_SEC)));
            cout << std::flush;
            start = clock();
            framecounter = 0;
        }
        framecounter++;

        ///Process image
        cv::cvtColor(Uimage, UimageHSV, cv::COLOR_RGB2HSV); //convert to HSV
        cv::inRange(UimageHSV, cv::Scalar(100, 0, 0), cv::Scalar(170, 255, 255), UimageRed);

#ifdef Display
        cv::imshow("Display Image", UimageRed);
        cv::waitKey(1);
#endif
    }

    return 0;
}
