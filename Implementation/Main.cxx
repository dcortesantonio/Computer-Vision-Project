
#include <iostream>
#include "ImageProcess.h"


int main(int argc, char** argv )
{
  
  // Get command line arguments
  if ( argc < 2 )
  {
  	std::cerr << "Usage: " << argv[ 0 ] << " image_file" << std::endl;
    return( -1 );

  } 

  // Review name of the image.
  std::cout << "-------------------------" << std::endl;
  std::cout << " Read image: "<<argv[ 1 ] << std::endl;
  std::cout << "-------------------------" << std::endl;

  // Read an image
  
   try {
     ImageProcess src(argv[1]);
     std::pair< double, double> m_Total = src.process();
	    std::cout<<"Hay "<<m_Total.first<<" monedas"<<", para un total de :"<<m_Total.second<<"$ "<<std::endl;
   } catch (const char* msg) {
     std::cerr << msg << std::endl;
     return(-1);
   }
  
 
  return 0;

}


