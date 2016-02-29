#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <ctime>
#include "CalibrationData.hpp"
using namespace std;


int main(int argc, char** argv )
{
    CalibrationData cal("calibrationdata/ost.yaml");
    cal.printCalibrationData();
    return 0;
}
