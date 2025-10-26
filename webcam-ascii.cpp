#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>

const std::string CLEAR_SCREEN = "\033[2J\033[H";
const std::string RESET_COLOR = "\033[0m";

// palette of characters (standard used by default)
const std::string CHARS_SIMPLE = " .:-=+*#%@";
const std::string CHARS_STANDARD = " .·:ıİ+*oO#@";
const std::string CHARS_DETAILED = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

class AsciiWebcam {
private:
    cv::VideoCapture cap;
    std::string chars;
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
        int idx = (pixel_value * (chars.length() - 1)) / 255;
        return chars[idx];
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
    AsciiWebcam(const std::string& char_palette = CHARS_SIMPLE) 
        : chars(char_palette), running(true) {
        
        instance = this;
        signal(SIGINT, signalHandler);
        
        cap.open(0);
        if (!cap.isOpened()) {
            throw std::runtime_error("Unable to open camera");
        }
        
        getTerminalSize();
        std::cout << "Terminal size: " << term_width << "x" << term_height << std::endl;
        std::cout << "Character palette: " << chars.length() << " chars" << std::endl;
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

            //grayscale
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            
            //tar size
            int target_width = term_width;
            int target_height = term_height;
            
            double aspect_ratio = static_cast<double>(gray.cols) / gray.rows;
            target_height = std::min(target_height, static_cast<int>(target_width / (aspect_ratio * 2.0)));
            target_width = std::min(target_width, static_cast<int>(target_height * aspect_ratio * 2.0));
            
            cv::resize(gray, resized, cv::Size(target_width, target_height));
            
            //convert to ascii = display
            std::string ascii_frame = frameToAscii(resized);
            std::cout << CLEAR_SCREEN << ascii_frame << std::flush;
            
            //fps limiting
            if (cv::waitKey(30) == 'q') {
                break;
            }
        }
    }
};

AsciiWebcam* AsciiWebcam::instance = nullptr;

void printHelp() {
    std::cout << "Webcam ASCII Art Viewer v0.2.0\n\n";
    std::cout << "Usage: webcam-ascii [OPTIONS]\n\n";
    std::cout << "Options:\n";
    std::cout << "  -p, --palette NAME    Character palette:\n";
    std::cout << "                          simple (default) - 10 chars\n";
    std::cout << "                          standard         - 12 chars\n";
    std::cout << "                          detailed         - 70 chars\n";
    std::cout << "  -h, --help            Show this help\n\n";
    std::cout << "Examples:\n";
    std::cout << "  webcam-ascii\n";
    std::cout << "  webcam-ascii -p detailed\n";
    std::cout << "  webcam-ascii --palette standard\n";
}

int main(int argc, char* argv[]) {
    std::string palette = "simple";

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            printHelp();
            return 0;
        } else if ((arg == "-p" || arg == "--palette") && i + 1 < argc) {
            palette = argv[++i];
        }
    }

    //selection of char type
    std::string chars = CHARS_SIMPLE;
    if (palette == "standard") {
        chars = CHARS_STANDARD;
    } else if (palette == "detailed") {
        chars = CHARS_DETAILED;
    }

    try {
        AsciiWebcam webcam(chars);
        webcam.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}