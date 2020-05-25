#define _USE_MATH_DEFINES
#include "ImageProcess.h"

ImageProcess::ImageProcess(){
	this->m_Width=0;
}
ImageProcess::~ImageProcess(){
}
ImageProcess::ImageProcess(std::string name)
{
  // Read the image
  this->m_Image = cv::imread( name, 1 ); 
  if ( !m_Image.data )
  {
     throw "Error: No image data";
  
  } 
  this->m_Width = 1500;
  this->m_Coins.push_back(new Coin( 346, 331, 200));
  this->m_Coins.push_back(new Coin( 263, 211.6, 100));
  this->m_Coins.push_back(new Coin( 211.6, 5, 50));
  this->getBaseName(name);
} 
void ImageProcess::getBaseName(  std::string s)
{
  
  std::stringstream ss( s );
  getline( ss, this->m_BaseName , '.' );
  
}
void ImageProcess::
ResizeImage()
{
  double scale = float(m_Width)/m_Image.size().width;
  resize(this->m_Image, this->m_Image, cv::Size(0, 0), scale, scale);

} 
std::pair <double, double> ImageProcess::
process()
{
   ResizeImage();
   std::pair <double, double>  m_Total;
   cv::Mat bw;
   cvtColor(this->m_Image, bw, cv::COLOR_BGR2GRAY);
   threshold(bw, bw, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
   cv::Mat M = cv::Mat::ones(3, 3, CV_8U);
   dilate(bw, bw, M);
	
  // Perform the distance transform algorithm
  cv::Mat dist;
  distanceTransform(bw, dist, CV_DIST_L2, 5);

  // Normalize the distance image for range = {0.0, 1.0} so we can visualize and threshold it
  normalize(dist, dist, 0, 1, cv::NORM_MINMAX);

  // Threshold to obtain the peaks, this will be the markers for the foreground objects
  threshold(dist, dist, 0.4, 1.0, cv::THRESH_BINARY);
    
	// Dilate a bit the dist image
  cv::Mat kernel1 = cv::Mat::ones(3, 3, CV_8U);
  dilate(dist, dist, kernel1);

  // Create the CV_8U version of the distance image, it is needed for findContours()
  cv::Mat dist_8u;
  dist.convertTo(dist_8u, CV_8U);
	
  // Find total markers
  std::vector<std::vector<cv::Point> > contours;
  cv::findContours(dist_8u, contours, cv::RETR_TREE, cv::CHAIN_APPROX_NONE );

  // Create the marker image for the watershed algorithm
  // Draw the foreground markers
  cv::Mat markers = cv::Mat::zeros(dist.size(), CV_32S);
  for (size_t i = 0; i < contours.size(); i++)
  {
      drawContours(markers, contours, static_cast<int>(i), cv::Scalar(static_cast<int>(i)+1), -1);
  }

  // Draw the background marker
  circle(markers, cv::Point(5,5), 1, cv::Scalar(255), -1);

  // Perform the watershed algorithm
  watershed(this->m_Image, markers);
	
  cv::Mat mark;
  markers.convertTo(mark, CV_8U);
  bitwise_not(mark, mark);
  cv::Mat dst = generateCirles(markers, contours);

  //Get values of coins.
  m_Total.first = contours.size();
  m_Total.second = getTotalValue( contours);

  // Visualize the final images
  cv::imwrite(this->m_BaseName+"FinalResult.png", dst); // Circles
  cv::imwrite(this->m_BaseName+"FinalValue.png", this->m_Image);  // Values and final result

  return m_Total;

} 


cv::Mat ImageProcess::
generateCirles(cv::Mat markers, std::vector<std::vector<cv::Point> > contours)
{
  
   // Generate random colors
  std::vector<cv::Vec3b> colors = generateColors(contours);

  // Create the result image
  cv::Mat dst = cv::Mat::zeros(markers.size(), CV_8UC3);
  // Fill labeled objects with random colors
  for (int i = 0; i < markers.rows; i++)
  {
      for (int j = 0; j < markers.cols; j++)
      {
          int index = markers.at<int>(i,j);
          if (index > 0 && index <= static_cast<int>(contours.size()))
          {
              dst.at<cv::Vec3b>(i,j) = colors[index-1];
          }
      }
  }
  return dst;
  
}



std::vector<cv::Vec3b> ImageProcess::
generateColors(  std::vector<std::vector<cv::Point> > contours)
{
   std::vector<cv::Vec3b> colors;
  for (size_t i = 0; i < contours.size(); i++)
  {
      int b = cv::theRNG().uniform(0, 256);
      int g = cv::theRNG().uniform(0, 256);
      int r = cv::theRNG().uniform(0, 256);
      colors.push_back(cv::Vec3b((uchar)b, (uchar)g, (uchar)r));
  }
         
  return colors;
  
}

double ImageProcess::
getValueImage(  double m_Area)
{
  for(int i =0; i<3; i++)
     if( this->m_Coins[i]->isTheCoin(m_Area))
          return this->m_Coins[i]->getValue();
         
  return 0;
  
}


double ImageProcess::
getTotalValue(  std::vector<std::vector<cv::Point> > contours)
{
   double m_Total=0;
   for (unsigned int i = 0;  i < contours.size();  i++)
  {
   
    double equiDiameter = sqrt( (4 * cv::contourArea(contours[i])) / M_PI);
    double value = getValueImage(equiDiameter);
    m_Total+=value;
    char str[200];
    sprintf(str,"Value: %0.0lf$", value);
    putText(this->m_Image, str ,contours[i][0], cv::FONT_HERSHEY_DUPLEX, 0.9, cv::Scalar(0,255,0), 2);
  }

  char str[200];
  sprintf(str,"TOTAL: %0.0lf",m_Total);
  putText(this->m_Image, str ,cv::Point((this->m_Image.cols/2)-170,(4*this->m_Image.rows/5)), cv::FONT_HERSHEY_DUPLEX, 02, cv::Scalar(0,255,0), 2);
         
  return m_Total;

}
