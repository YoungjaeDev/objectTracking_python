#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    std::cout << "OpenCV version : " << CV_VERSION << std::endl;
    std::cout << "Major version : " << CV_MAJOR_VERSION << std::endl;
    std::cout << "Minor version : " << CV_MINOR_VERSION << std::endl;
    std::cout << "Subminor version : " << CV_SUBMINOR_VERSION << std::endl;

    std::cout << "Build information:" << std::endl;
    std::string build_info = cv::getBuildInformation();
    std::cout << build_info << std::endl;

    return 0;
}
