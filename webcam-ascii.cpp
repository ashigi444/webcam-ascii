#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>

const std::string CLEAR_SCREEN = "\033[2J\033[H";
const std::string RESET_COLOR = "\033[0m";

const std::string CHARS = " .:-=+*#%@";

class AsciiWebcam {
private:
    cv::VideoCapture cap;
    int term_width;
    int term_height;
    volatile bool running;

    static AsciiWebcam* instance;

    void getTerminalSize() {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        term_width = w.ws_col;
        term_height = w.ws_row - 1;
    }

    char pixelToAscii(int pixel_value) {
        int idx = (pixel_value * (CHARS.length() - 1)) / 255;
        return CHARS[idx];
    }

    std::string frameToAscii(const cv::Mat& frame) {
        std::string result;
        result.reserve(frame.rows * (frame.cols + 1));
        
        for (int y = 0; y < frame.rows; y++) {
            for (int x = 0; x < frame.cols; x++) {
                int pixel = frame.at<uchar>(y, x);
                result += pixelToAscii(pixel);
            }
            result += "\n";
        }
        return result;
    }

    static void signalHandler(int signum) {
        if (instance) {
            instance->running = false;
        }
    }

public:
    AsciiWebcam() : running(true) {
        instance = this;
        signal(SIGINT, signalHandler);
        
        cap.open(0);
        if (!cap.isOpened()) {
            throw std::runtime_error("Cam ERROR");
        }
        
        getTerminalSize();
        std::cout << "Terminal size: " << term_width << "x" << term_height << std::endl;
        std::cout << "Press Ctrl+C to exit" << std::endl;
        sleep(2);
    }

    ~AsciiWebcam() {
        std::cout << CLEAR_SCREEN;
        cap.release();
    }

    void run() {
        cv::Mat frame, gray, resized;
        
        while (running) {
            cap >> frame;
            if (frame.empty()) {
                std::cerr << "Failed to capture frame" << std::endl;
                break;
            }

            // to greyscale
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            
            // target size
            int target_width = term_width;
            int target_height = term_height;
            
            // characters are roughly 2:1 tall:wide
            double aspect_ratio = static_cast<double>(gray.cols) / gray.rows;
            target_height = std::min(target_height, static_cast<int>(target_width / (aspect_ratio * 2.0)));
            target_width = std::min(target_width, static_cast<int>(target_height * aspect_ratio * 2.0));
            
            cv::resize(gray, resized, cv::Size(target_width, target_height));
            
            std::string ascii_frame = frameToAscii(resized);
            std::cout << CLEAR_SCREEN << ascii_frame << std::flush;
            
            // fps limiting
            if (cv::waitKey(60) == 'q') {
                break;
            }
        }
    }
};

AsciiWebcam* AsciiWebcam::instance = nullptr;

int main() {
    try {
        AsciiWebcam webcam;
        webcam.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}