cmake_minimum_required(VERSION 2.6)

INCLUDE(${CMAKE_SOURCE_DIR}/IJMacros.txt)

PROJECT(itkPTXImageIO)

#The following lines are required to use Dart
ENABLE_TESTING()
INCLUDE(Dart)

SET(Required_Packages
ITK
)

FOREACH(Package ${Required_Packages})
  LOADPACKAGE(${Package})
ENDFOREACH(Package)

SET(Libraries
ITKCommon
ITKIO
)

SET(itkPTXMeshReader)
ADD_EXECUTABLE(itkPTXMeshReader_Test itkPTXMeshReader_Test.cxx itkPTXMeshReader.cxx) 
TARGET_LINK_LIBRARIES(itkPTXMeshReader_Test ${Libraries})
