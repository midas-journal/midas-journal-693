#ifndef __itkPTXPointInfo_h
#define __itkPTXPointInfo_h

#include "itkRGBPixel.h"
#include "itkPoint.h"
			
namespace itk
{
	class PTXPointInfo
	{
		public:
			typedef itk::RGBPixel<unsigned char> ColorType; //note: the ptx format uses unsigned chars for color
			
			ColorType Color;
			double Intensity;
			
	};
	
} //end itk namespace

#endif // __itkPTXPointInfo_h