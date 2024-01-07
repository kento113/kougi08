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
  
  cv::Mat src = cv::imread("campus_bw.png", 0);

  display(src, "src");

  std::vector<cv::Point2f> src_points(4);
  src_points[0] = cv::Point2f(174, 27);
  src_points[1] = cv::Point2f(162, 151);
  src_points[2] = cv::Point2f(590, 150);
  src_points[3] = cv::Point2f(587, 10);

  std::vector<cv::Point2f> dst_points(4);
  dst_points[0] = cv::Point2f(50, 50);
  dst_points[1] = cv::Point2f(50, 200);
  dst_points[2] = cv::Point2f(460, 200);
  dst_points[3] = cv::Point2f(460, 50);

  cv::Mat matrix;
  matrix = cv::getPerspectiveTransform(src_points, dst_points);

  std::cout << matrix << std::endl;

  cv::Mat dst;
  warpPerspective(src, dst, matrix, cv::Size(512,256));


  display(dst, "dst");

//  cv::imwrite("dst_image.jpg", dst);

  cv::waitKey(1000 * 100);
  cv::destroyWindow("src");
  cv::destroyWindow("dst");

  return 0;
}

