#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

#include <random>

int main() {
    std::string tracker_type = "KCF"; // back

    std::cout << tracker_type << std::endl;

    cv::Ptr<cv::Tracker> tracker;
    cv::TrackerKCF::Params params;

    // params.compress_feature = 0; // disable feature compression
    // params.resize = 0; // disable image resizing
    // params.sigma = 0.1f; // use a smaller Gaussian kernel
    // params.output_sigma_factor = 0.1f; // use a larger spatial bandwidth
    // params.max_patch_size = 500; // reduce the maximum patch size
    // params.lambda = 0.0001f; // keep the default regularization value

    tracker = cv::TrackerKCF::create(params);
    
    cv::VideoCapture video("Videos/race.mp4");

    if (!video.isOpened()) {
        std::cout << "Error while loading the video!" << std::endl;
        return -1;
    }

    cv::Mat frame;
    bool ok = video.read(frame);

    if (!ok) {
        std::cout << "Error while loading the frame" << std::endl;
        return -1;
    }

    cv::Rect bbox = cv::selectROI(frame);
    tracker->init(frame, bbox);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);

    cv::Scalar colors(distrib(gen), distrib(gen), distrib(gen));

    while (true) {
        cv::Rect2d updated_bbox;
        ok = video.read(frame);

        if (!ok) {
            std::cout << "Error while loading the frame" << std::endl;
            break;
        }

        double start = static_cast<double>(cv::getTickCount());
        // #pragma omp parallel for
        tracker->update(frame, updated_bbox);
        double end = static_cast<double>(cv::getTickCount());

        double track_time = (end - start) / cv::getTickFrequency() * 1000;
        std::cout << "Track time: " << track_time << "ms" << std::endl;

        if (ok) {
            cv::rectangle(frame, updated_bbox, colors, 2, 1);
        } else {
            cv::putText(frame, "Tracking failure!", cv::Point(100, 80), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        }

        cv::imshow("Tracking", frame);
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    video.release();

    return 0;
}
