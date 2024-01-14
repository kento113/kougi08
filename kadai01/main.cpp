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
  
  cv::Mat img_lobby = cv::imread("lobby.jpg");
  cv::Mat img_mandrill = cv::imread("Mandrill.png");

  display(img_lobby, "src");

  std::vector<cv::Point2f> lobby_points(4);
  lobby_points[0] = cv::Point2f(373, 415);
  lobby_points[1] = cv::Point2f(370, 716);
  lobby_points[2] = cv::Point2f(497, 729);
  lobby_points[3] = cv::Point2f(496, 398);

  std::vector<cv::Point2f> mandrill_points(4);
  mandrill_points[0] = cv::Point2f(0, 0);
  mandrill_points[1] = cv::Point2f(0, 255);
  mandrill_points[2] = cv::Point2f(255, 255);
  mandrill_points[3] = cv::Point2f(255, 0);

  cv::Mat matrix;
  matrix = cv::getPerspectiveTransform(mandrill_points, lobby_points);

  std::cout << matrix << std::endl;

  cv::Mat img_transformed_mandrill;
  warpPerspective(img_mandrill, img_transformed_mandrill, matrix, cv::Size(img_lobby.cols, img_lobby.rows));

  cv::Mat img_white = img_mandrill.clone();
  img_white = cv::Scalar(255, 255, 255);
  cv::Mat mask;
  warpPerspective(img_white, mask, matrix, cv::Size(img_lobby.cols, img_lobby.rows));

  img_transformed_mandrill.copyTo(img_lobby, mask);

  display(img_lobby, "dst");

//  cv::imwrite("dst_image.jpg", dst);

  cv::waitKey(1000 * 100);
  cv::destroyWindow("src");
  cv::destroyWindow("dst");

  return 0;
}

