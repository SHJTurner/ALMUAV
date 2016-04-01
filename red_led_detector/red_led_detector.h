#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

class Red_led_detector
{
#define ERODE_ITERATIONS        3
#define ERODE_PREP_ITERATIONS   5
#define DILATE_ITERATIONS       3
#define EROSION_SIZE            2

public:
    Red_led_detector();
    ~Red_led_detector();
#if CV_MAJOR_VERSION > 2
    void detect(UMat &image, vector<Point2f> &distorted_points);
#else
    void detect(Mat %image, vector<Point2f>);
#endif
private:
    Ptr<SimpleBlobDetector> ConfigBlobDetector();
    Ptr<SimpleBlobDetector> detector;
#if CV_MAJOR_VERSION > 2
    void dilateErodeMat(UMat &_src);
#else
    void dilateErodeMat(Mat &_src);
#endif
};
