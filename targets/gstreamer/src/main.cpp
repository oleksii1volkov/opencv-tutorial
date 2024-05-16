#include <opencv2/opencv.hpp>

class GStreamerWebCamStreaming {
public:
    static void run() {
        cv::VideoCapture cap(0);

        if (!cap.isOpened()) {
            std::cerr << "Could not open webcam" << std::endl;
            cv::waitKey(0);
            return;
        }

        int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
        int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

        cv::VideoWriter writer_udp(
            "appsrc ! videoconvert ! videoscale ! video/x-raw, width=640, "
            "height=480 ! x264enc ! mpegtsmux !udpsink host=127.0.0.1 "
            "port=5000 "
            "sync=false",
            0, 20, cv::Size(640, 480), true);

        if (!writer_udp.isOpened()) {
            std::cerr << "Could not open VideoWriter" << std::endl;
            cv::waitKey(0);
            return;
        }

        cv::Mat frame;

        while (true) {
            cap >> frame;

            if (frame.empty()) {
                break;
            }

            cv::resize(frame, frame, cv::Size(640, 480));
            writer_udp << frame;

            imshow("Frame", frame);
            cv::waitKey(25);

            if (cv::waitKey(1) == 'q') {
                break;
            }
        }

        cap.release();
    }
};

int main() {
    GStreamerWebCamStreaming::run();

    return 0;
}
