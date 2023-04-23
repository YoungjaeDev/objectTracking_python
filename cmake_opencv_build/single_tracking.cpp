#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <random>

int main() {
    std::vector<std::string> tracker_types = {"BOOSTING", "MIL", "KCF", "TLD", "MEDIANFLOW", "MOSSE", "CSRT"};
    std::string tracker_type = tracker_types.back();

    std::cout << tracker_type << std::endl;

    cv::Ptr<cv::Tracker> tracker;

    if (tracker_type == "BOOSTING") {
        tracker = cv::TrackerBoosting::create();
    } else if (tracker_type == "MIL") {
        tracker = cv::TrackerMIL::create();
    } else if (tracker_type == "KCF") {
        tracker = cv::TrackerKCF::create();
    } else if (tracker_type == "TLD") {
        tracker = cv::TrackerTLD::create();
    } else if (tracker_type == "MEDIANFLOW") {
        tracker = cv::TrackerMedianFlow::create();
    } else if (tracker_type == "MOSSE") {
        tracker = cv::TrackerMOSSE::create();
    } else if (tracker_type == "CSRT") {
        tracker = cv::TrackerCSRT::create();
    }

    std::cout << tracker << std::endl;

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

    cv::Rect2d bbox = cv::selectROI(frame);
    ok = tracker->init(frame, bbox);

    std::cout << ok << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);

    cv::Scalar colors(distrib(gen), distrib(gen), distrib(gen));

    while (true) {
        ok = video.read(frame);

        if (!ok) {
            std::cout << "Error while loading the frame" << std::endl;
            break;
        }

        double start = static_cast<double>(cv::getTickCount());
        ok = tracker->update(frame, bbox);
        double end = static_cast<double>(cv::getTickCount());

        double track_time = (end - start) / cv::getTickFrequency() * 1000;
        std::cout << "Track time: " << track_time << "ms" << std::endl;

        if (ok) {
            cv::rectangle(frame, bbox, colors, 2, 1);
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
