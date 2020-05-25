#ifndef ImageProcessProcess__H
#define ImageProcessProcess__H

#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "Coin.h"

class ImageProcess
{
private:
cv::Mat m_Image;
std::string m_BaseName;
double m_Width;
std::vector<Coin *> m_Coins;

public:
ImageProcess( );
ImageProcess( std::string name);
virtual ~ImageProcess();
void getBaseName(  std::string s );
void ResizeImage();
cv::Mat generateCirles(cv::Mat markers, std::vector<std::vector<cv::Point> > contours);
std::vector<cv::Vec3b> generateColors(  std::vector<std::vector<cv::Point> > contours);
double getTotalValue(std::vector<std::vector<cv::Point> > contours);
std::pair<double, double> process();
double getValueImage(  double m_Area);
};

#endif
