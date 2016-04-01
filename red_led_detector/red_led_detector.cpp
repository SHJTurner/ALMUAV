#include "red_led_detector.h"


Red_led_detector::Red_led_detector()
{
    this->detector = this->ConfigBlobDetector();
}

Red_led_detector::~Red_led_detector()
{

}

Ptr<SimpleBlobDetector> Red_led_detector::ConfigBlobDetector()
{
    SimpleBlobDetector::Params params;
    params.minDistBetweenBlobs = 3.0f;
    params.minThreshold = 0;
    params.maxThreshold = 255;
    params.filterByInertia = false;
    params.filterByConvexity = false;
    params.filterByColor = false;
    params.filterByCircularity = false;
    params.filterByArea = false;
    params.minArea = 1.0f;
    params.maxArea = 100.0f;
    return SimpleBlobDetector::create(params);
}


#if CV_MAJOR_VERSION > 2
void Red_led_detector::dilateErodeMat(UMat &_src) {
    Mat _element = getStructuringElement(MORPH_ELLIPSE,
            Size(2*EROSION_SIZE + 1, 2*EROSION_SIZE+1),
            Point(EROSION_SIZE, EROSION_SIZE));
    dilate(_src, _src, _element, Point(-1, -1), DILATE_ITERATIONS);
    erode(_src, _src, _element, Point(-1, -1), ERODE_ITERATIONS);
}
#else
void Red_led_detector::dilateErodeMat(Mat &_src) {
    Mat _element = getStructuringElement(MORPH_ELLIPSE,
            Size(2*EROSION_SIZE + 1, 2*EROSION_SIZE+1),
            Point(EROSION_SIZE, EROSION_SIZE));
    dilate(_src, _src, _element, Point(-1, -1), DILATE_ITERATIONS);
    erode(_src, _src, _element, Point(-1, -1), ERODE_ITERATIONS);
}
#endif

#if CV_MAJOR_VERSION > 2
void Red_led_detector::detect(UMat &image, vector<Point2f> &distorted_points)
{
    UMat image_HSV, image_inRange;
    cvtColor(image,image_HSV,cv::COLOR_RGB2HSV);
    cv::inRange(image_HSV,Scalar(87,10,80),Scalar(133,255,255),image_inRange);
    this->dilateErodeMat(image_inRange);
    vector<KeyPoint> keyPoints;

    //detector->detect(image_inRange,keyPoints);

    for(KeyPoint point : keyPoints)
    {
        distorted_points.push_back(point.pt);
    }

    imshow("Diplay Filtered",image_inRange);

    return;
}
#else
void Red_led_detector::detect(Mat &image, vector<Point2f> &distorted_points)
{
    Mat image_HSV, image_inRange;
    cvtColor(image,image_HSV,cv::COLOR_RGB2HSV);
    cv::inRange(image_HSV,Scalar(87,10,80),Scalar(133,255,255),image_inRange);
    this->dilateErodeMat(image_inRange);
    vector<KeyPoint> keyPoints;

    //detector->detect(image_inRange,keyPoints);

    for(KeyPoint point : keyPoints)
    {
        distorted_points.push_back(point.pt);
    }

    //image = image_inRange;

    return;
}
#endif

