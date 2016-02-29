#include "CalibrationData.hpp"

CalibrationData::CalibrationData(string _filePath){
    cv::FileStorage fs = cv::FileStorage(_filePath,cv::FileStorage::READ);
    this->width = (int)fs["image_width"];
    this->height = (int)fs["image_height"];
    fs["camera_name"] >> this->camera_name;
    fs["camera_matrix"] >> this->camera_matrix;
    fs["distortion_model"] >> this->distortion_model;
    fs["distortion_coefficients"] >> this->distortion_coff;
    fs["rectification_matrix"] >> this->rectification_matrix;
    fs["projection_matrix"] >> this->projection_matrix;
}

void CalibrationData::printCalibrationData(){
    cout << "Image width: " << this->width << " Image height: " << this->height << endl;
    cout << "Camera name: " << this->camera_name.c_str() << endl;
    cout << "Camera matrix:" << endl << this->camera_matrix << endl;
    cout << "Distortion model: "  << this->distortion_model << endl;
    cout << "Distortion coefficients:" << endl << this->distortion_coff << endl;
    cout << "Rectification matrix:" << endl << this->rectification_matrix << endl;
    cout << "Projection matrix:" << endl << this->projection_matrix << endl;
}
