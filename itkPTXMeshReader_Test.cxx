#include "itkMesh.h"
#include "itkLineCell.h"

#include "itkPTXMeshReader.h"
#include "itkPTXPointInfo.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

int main( int argc, char *argv[])
{
	//input required parameters:
	// ./itkPTXImageIO_Test input.ptx
	std::string strInputFilename = argv[1];
		
	//create a mesh object that will be filled by the Read() function
	itk::PTXMeshReader MeshReader;
	
	//Read the PTX file and store it in mesh
	itk::PTXMeshReader::MeshType::Pointer mesh = MeshReader.Read(strInputFilename);
	
	typedef itk::PTXMeshReader::MeshType::PointsContainer::Iterator     PointsIterator;
 	PointsIterator  pointIterator = mesh->GetPoints()->Begin();  
 
	PointsIterator end = mesh->GetPoints()->End();
	while( pointIterator != end ) 
	{
		itk::PTXMeshReader::MeshType::PointType p = pointIterator.Value();  // access the point
		
		itk::PTXMeshReader::PixelType* pix;
		bool success = mesh->GetPointData(pointIterator.Index(), pix);
		if(!success)
		{
			std::cout << "Something went wrong, should never see this!" << std::endl;
			exit(-1);
		}
		std::cout << "Point coord: " << p << std::endl;                    // print the point
		std::cout << "Point color: " << pix->Color << std::endl;           // print the point
		std::cout << "Point intensity: " << pix->Intensity << std::endl;           // print the intensity
		
		++pointIterator;                                // advance to next point
	}
	

	std::cout << "Finished." << std::endl;
	
	return 0;
}