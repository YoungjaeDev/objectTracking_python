#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

#include <random>

int main()
{
    cv::TrackerKCF::Params params; // create an instance with default values

    std::cout << "compress_feature: " << params.compress_feature << std::endl;
    std::cout << "compressed_size: " << params.compressed_size << std::endl;
    std::cout << "desc_npca: " << params.desc_npca << std::endl;
    std::cout << "desc_pca: " << params.desc_pca << std::endl;
    std::cout << "detect_thresh: " << params.detect_thresh << std::endl;
    std::cout << "interp_factor: " << params.interp_factor << std::endl;
    std::cout << "lambda: " << params.lambda << std::endl;
    std::cout << "max_patch_size: " << params.max_patch_size << std::endl;
    std::cout << "output_sigma_factor: " << params.output_sigma_factor << std::endl;
    std::cout << "pca_learning_rate: " << params.pca_learning_rate << std::endl;
    std::cout << "resize: " << params.resize << std::endl;
    std::cout << "sigma: " << params.sigma << std::endl;
    std::cout << "split_coeff: " << params.split_coeff << std::endl;
    std::cout << "wrap_kernel: " << params.wrap_kernel << std::endl;

    return 0;
}
