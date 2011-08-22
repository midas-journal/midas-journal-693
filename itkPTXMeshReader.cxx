#include "itkPTXMeshReader.h"
#include "itkLineCell.h"

#include <fstream>

itk::PTXMeshReader::MeshType::Pointer itk::PTXMeshReader::Read(std::string &FileName)
{
	
	typedef MeshType::CellType                CellType;
	typedef itk::LineCell< CellType >         LineType;
	
	typedef CellType::CellAutoPointer         CellAutoPointer;
  
	MeshType::Pointer  mesh = MeshType::New();
	
	std::ifstream infile;
	infile.open(FileName.c_str());
	if(!infile)
	{
		std::cerr << "Could not open ptx file " << FileName << "!" << std::endl;
		return mesh;
	}

	std::string line;
	unsigned int NumPhiPoints, NumThetaPoints;

	getline(infile, line);
	std::stringstream(line) >> NumPhiPoints;

	getline(infile, line);
	std::stringstream(line) >> NumThetaPoints;

	//skip 8 lines (identity matrices - what are they ACTUALLY for? !!!)
	for(int i = 0; i < 8; i++)
	{
		getline(infile, line);
	}
	
	std::cout << "Number of theta points: " << NumThetaPoints << std::endl;
	std::cout << "Number of phi points: " << NumPhiPoints << std::endl;
	
	unsigned int LinkIndex = 0;
	
	for(unsigned int col = 0; col < NumThetaPoints; col++)
	{
		for(unsigned int row = 0; row < NumPhiPoints; row++)	
		{
			//std::cout << "col: " << col << std::endl;
			//std::cout << "row: " << row << std::endl;
			//delcare variables for reading the line
			std::string line;
			getline(infile, line);
			std::stringstream ParsedLine(line);
			
			//delcare variables for the result of the line parsins
			double Intensity;
			unsigned int r,g,b;
			MeshType::PointType Point;
			
			//parse the line
			ParsedLine >> Point[0] >> Point[1] >> Point[2] >> Intensity >> r >> g >> b;
			//std::cout << "Adding point: " << Point << std::endl;
			
			//compute mesh index and set the current point
			unsigned int MeshIndex = col*NumPhiPoints + row;
			mesh->SetPoint(MeshIndex, Point);
			//std::cout << "Added point: " << MeshIndex << std::endl;
						
			//Add the color to the mesh point
			itk::PTXPointInfo::ColorType Color;
			Color[0] = static_cast<unsigned char> (r);
			Color[1] = static_cast<unsigned char> (g);
			Color[2] = static_cast<unsigned char> (b);
						
			itk::PTXPointInfo PointInfo;
			PointInfo.Color = Color;
			PointInfo.Intensity = Intensity;
				
			mesh->SetPointData(MeshIndex,PointInfo);
			
			
			//setup connectivity
			if(row > 0) //the first point has nothing to link to!
			{
				//create a link to the previous point in the column (below the current point)
				CellAutoPointer colline;
				colline.TakeOwnership(  new LineType  );
				
				colline->SetPointId(0, MeshIndex); // line between points 0 and 1
				colline->SetPointId(1, MeshIndex - 1);
				//std::cout << "Linked point: " << MeshIndex << " and " << MeshIndex - 1 << std::endl;
				mesh->SetCell( LinkIndex, colline );
				LinkIndex++;
			}
			
			if(col>0) //points in the first column do not have 'left' neighbors
			{
				//create a link to the point in the same row and previous column (left of the current point)
				CellAutoPointer rowline;
				rowline.TakeOwnership(  new LineType  );
			
				rowline->SetPointId(0, MeshIndex);
				rowline->SetPointId(1, MeshIndex - NumPhiPoints);
				//std::cout << "Linked point: " << MeshIndex << " and " << MeshIndex - NumPhiPoints << std::endl;
				mesh->SetCell(LinkIndex, rowline );
				LinkIndex++;
			}
			
		}
		

	}//end while getline

	infile.close();
	 	
	/*
	std::cout << "Finished adding points." << std::endl;
	
	std::cout << "Points = " << mesh->GetNumberOfPoints() << std::endl;
	std::cout << "Cells  = " << mesh->GetNumberOfCells()  << std::endl;
	*/
	
	return mesh;
}