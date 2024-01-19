#include <iostream>
#include <string>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

void display(cv::Mat image, std::string windowName = "Image") {
    cv::namedWindow(windowName);
    cv::imshow(windowName, image);
}

int main(void) {
    cv::Mat src = cv::imread("Mandrill.jpg");

    display(src, "src");

    std::vector<cv::Point2f> src_points(4);
    src_points[0] = cv::Point2f(134, 78);
    src_points[1] = cv::Point2f(352, 74);
    src_points[2] = cv::Point2f(80, 234);
    src_points[3] = cv::Point2f(404, 224);

    std::vector<cv::Point2f> dst_points(4);
    dst_points[0] = cv::Point2f(50, 50);
    dst_points[1] = cv::Point2f(462, 50);
    dst_points[2] = cv::Point2f(50, 206);
    dst_points[3] = cv::Point2f(462, 206);

    cv::Mat matrix;
    matrix = cv::getPerspectiveTransform(src_points, dst_points);

    std::cout << matrix << std::endl;

    cv::Mat dst;
    warpPerspective(src, dst, matrix, cv::Size(512, 256));

    display(dst, "dst");

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
