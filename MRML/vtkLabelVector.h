
#ifndef __vtkLabelVector_h
#define __vtkLabelVector_h

// Standard Includes
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

// VTK includes
#include "vtkObject.h"
#include "vtkObjectBase.h"
#include "vtkObjectFactory.h"
#include "vtkXMLDataElement.h"
#include "vtkSmartPointer.h"

// Workflow Segmentation includes
#include "vtkSlicerWorkflowSegmentationModuleMRMLExport.h"

// This class stores a vector of values and a string label
class VTK_SLICER_WORKFLOWSEGMENTATION_MODULE_MRML_EXPORT 
vtkLabelVector : public vtkObject
{
public:
  vtkTypeMacro( vtkLabelVector, vtkObject );

  // Standard MRML methods
  static vtkLabelVector* New();

protected:

  // Constructo/destructor
  vtkLabelVector();
  virtual ~vtkLabelVector();

  
public:

  //
  void Copy( vtkLabelVector* otherVector );

  void AddElement( double newValue );
  void SetElement( int index, double newValue );
  void IncrementElement( int index, double step = 1 );
  double GetElement( int index );
  void FillElements( int size, double value );
  int Size();
  
  void SetAllValues( std::vector< double > newValues );
  std::vector< double > GetAllValues();
  
  void Concatenate( vtkLabelVector* otherVector );
  
  std::string ToString();
  void FromString( std::string instring, int size );

  std::string GetLabel();
  void SetLabel( std::string newLabel );
  void SetLabel( int newLabel );

  std::string ToXMLString( vtkIndent indent );
  void FromXMLElement( vtkXMLDataElement* element );
  
  // Static helper methods
  static std::string VectorsToXMLString( std::vector< vtkSmartPointer< vtkLabelVector > > vectors, std::string name, vtkIndent indent );
  static std::string VectorsToXMLString( vtkLabelVector* vector, std::string name, vtkIndent indent );
  static std::vector< vtkSmartPointer< vtkLabelVector > > VectorsFromXMLElement( vtkXMLDataElement* element, std::string name ); // Note: This will create the labels vectors, whoever uses the function is responsible for deleting

  //static void CopyVector( std::vector< vtkSmartPointer< vtkLabelVector > > from, std::vector< vtkSmartPointer< vtkLabelVector > > to );
  
protected:
  
  std::vector< double > Values;
  std::string Label;
  
};

#endif