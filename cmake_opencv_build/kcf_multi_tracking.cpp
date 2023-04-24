#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <random>
#include <omp.h>

int main() {
    cv::VideoCapture video("Videos/walking.avi");

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

    // Downscale factor (0.5 means half the size)
    float scale_factor = 1;

    // Resize the frame
    cv::resize(frame, frame, cv::Size(), scale_factor, scale_factor, cv::INTER_LINEAR);

    std::vector<cv::Rect> bboxes;
    std::vector<cv::Scalar> colors;

    while (true) {
        cv::Rect bbox = cv::selectROI(frame);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 255);
        cv::Scalar color(distrib(gen), distrib(gen), distrib(gen));
        
        bboxes.push_back(bbox);
        colors.push_back(color);
        
        std::cout << "Press 'q' and then Enter to start tracking" << std::endl;
        std::cout << "Press any other key and then Enter to select the next object" << std::endl;
        
        if (cv::waitKey(0) == 113) {
            break;
        }
    }

    cv::Ptr<cv::MultiTracker> multi_tracker = cv::makePtr<cv::MultiTracker>();
    cv::TrackerKCF::Params params;

    for (const auto &bbox : bboxes) {
        cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();
        multi_tracker->add(tracker, frame, bbox);
    }

    while (true) {
        ok = video.read(frame);

        if (!ok) {
            std::cout << "Error while loading the frame" << std::endl;
            break;
        }

        // Resize the frame
        cv::resize(frame, frame, cv::Size(), scale_factor, scale_factor, cv::INTER_LINEAR);

        double start = static_cast<double>(cv::getTickCount());
        // #pragma omp parallel for
        for (int i = 0; i < multi_tracker->getObjects().size(); i++) {
            multi_tracker->update(frame);
        }
        double end = static_cast<double>(cv::getTickCount());

        double track_time = (end - start) / cv::getTickFrequency() * 1000;
        std::cout << "Track time: " << track_time << "ms" << std::endl;

        if (ok) {
            for (size_t i = 0; i < multi_tracker->getObjects().size(); i++) {
                cv::rectangle(frame, multi_tracker->getObjects()[i], colors[i], 2, 1);
            }
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
