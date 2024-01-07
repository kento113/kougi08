#include <iostream>
#include <string>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


void display(cv::Mat image, std::string windowName = "Image") {
    cv::namedWindow(windowName);
    cv::imshow(windowName, image);
}

int main(void){
  
  cv::Mat src = cv::imread("Mandrill.jpg");

  display(src, "src");

  std::vector<cv::Point2f> src_points(4);
  src_points[0] = cv::Point2f(140, 40);
  src_points[1] = cv::Point2f(140, 90);
  src_points[2] = cv::Point2f(240, 90);
  src_points[3] = cv::Point2f(240, 40);

  std::vector<cv::Point2f> dst_points(4);
  dst_points[0] = cv::Point2f(127, 0);
  dst_points[1] = cv::Point2f(0, 127);
  dst_points[2] = cv::Point2f(127, 255);
  dst_points[3] = cv::Point2f(255, 127);

  cv::Mat matrix;
  matrix = cv::getPerspectiveTransform(src_points, dst_points);

  cv::Mat dst1, dst2, dst3;
  warpPerspective(src, dst1, matrix, cv::Size(256,256), cv::INTER_NEAREST);
  display(dst1, "INTER_NEAREST");

  warpPerspective(src, dst2, matrix, cv::Size(256,256), cv::INTER_LINEAR);
  display(dst2, "INTER_LINEAR");

  warpPerspective(src, dst3, matrix, cv::Size(256,256), cv::INTER_CUBIC);
  display(dst3, "INTER_CUBIC");

  cv::waitKey(1000 * 100);
  cv::destroyWindow("src");
  cv::destroyWindow("INTER_NEAREST");
  cv::destroyWindow("INTER_LINEAR");
  cv::destroyWindow("INTER_CUBIC");

  return 0;
}

