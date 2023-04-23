#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

#include <random>

int main() {
    std::vector<std::string> tracker_types = {"KCF", "CSRT"};
    std::string tracker_type = tracker_types.front(); // back

    std::cout << tracker_type << std::endl;

    cv::Ptr<cv::Tracker> tracker;
    cv::TrackerKCF::Params params;

    if (tracker_type == "KCF") {
        tracker = cv::TrackerKCF::create();
    }  else if (tracker_type == "CSRT") {
        tracker = cv::TrackerCSRT::create();
    }

    params.resize = true;
    
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

    cv::Rect bbox = cv::selectROI(frame);
    tracker->init(frame, bbox);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);

    cv::Scalar colors(distrib(gen), distrib(gen), distrib(gen));

    while (true) {
        cv::Rect updated_bbox;
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
