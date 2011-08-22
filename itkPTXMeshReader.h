#ifndef __itkPTXMeshReader__
#define __itkPTXMeshReader__

#include <string>

#include "itkMesh.h"
#include "itkPTXPointInfo.h"

namespace itk
{
	class PTXMeshReader
	{
		public:

			//static unsigned int PointDimension;
			//static unsigned int MaxTopologicalDimension;

			typedef itk::PTXPointInfo	PixelType;
			
			typedef double CoordinateType;
			typedef double InterpolationWeightType;

			//typedef itk::DefaultStaticMeshTraits<PixelType, PointDimension, MaxTopologicalDimension,
			typedef itk::DefaultStaticMeshTraits<PixelType, 3, 2,
				CoordinateType, InterpolationWeightType> MeshTraits;
				//CoordinateType, InterpolationWeightType, CellDataType > MeshTraits; //CellDataType is not necessary for this usage

			//typedef itk::Mesh< PixelType, PointDimension, MeshTraits > MeshType;
				typedef itk::Mesh< PixelType, 3, MeshTraits > MeshType;
	  
			MeshType::Pointer Read(std::string &Filename);
	}; // end of PTXMeshReader
	
} //end itk namespace
#endif