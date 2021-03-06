
#include "vtkLabelRecord.h"

vtkStandardNewMacro( vtkLabelRecord );


vtkLabelRecord
::vtkLabelRecord()
{
  this->Vector = vtkSmartPointer< vtkLabelVector >::New();
}


vtkLabelRecord
::~vtkLabelRecord()
{
}


void vtkLabelRecord
::Copy( vtkLogRecord* otherRecord )
{
  this->vtkLogRecord::Copy( otherRecord );

  vtkLabelRecord* labelRecord = vtkLabelRecord::SafeDownCast( otherRecord ); 
  if ( labelRecord == NULL )
  {
    return;
  }
  
  this->GetVector()->Copy( labelRecord->GetVector() );
}


vtkLabelVector* vtkLabelRecord
::GetVector()
{
  return this->Vector;
}

void vtkLabelRecord
::SetVector( vtkLabelVector* newVector )
{
  this->Vector = newVector;
}


void vtkLabelRecord
::ToTransformRecord( vtkTransformRecord* transformRecord, TrackingRecordType type )
{
  std::stringstream matrixString;
  if ( type == QUATERNION_RECORD && this->GetVector()->Size() == QUATERNION_RECORD ) // If it is in quaternion format
  {
    double quaternion[ 4 ];
    quaternion[ 0 ] = this->GetVector()->GetElement( 3 );
    quaternion[ 1 ] = this->GetVector()->GetElement( 4 );
    quaternion[ 2 ] = this->GetVector()->GetElement( 5 );
    quaternion[ 3 ] = this->GetVector()->GetElement( 6 );
    
    double matrix[ 3 ][ 3 ];
    vtkMath::QuaternionToMatrix3x3( quaternion, matrix );
    
    matrixString << matrix[ 0 ][ 0 ] << " " << matrix[ 0 ][ 1 ] << " " << matrix[ 0 ][ 2 ] << " " << this->GetVector()->GetElement( 0 ) << " ";
    matrixString << matrix[ 1 ][ 0 ] << " " << matrix[ 1 ][ 1 ] << " " << matrix[ 1 ][ 2 ] << " " << this->GetVector()->GetElement( 1 ) << " ";
    matrixString << matrix[ 2 ][ 0 ] << " " << matrix[ 2 ][ 1 ] << " " << matrix[ 2 ][ 2 ] << " " << this->GetVector()->GetElement( 2 ) << " ";
    matrixString << 0 << " " << 0 << " " << 0 << " " << 1;
  }
  else if ( type == MATRIX_RECORD && this->GetVector()->Size() == MATRIX_RECORD ) // If it is in matrix format
  {
    matrixString << this->GetVector()->ToString();
  }
  else
  {
    return;
  }
  
  transformRecord->SetTime( this->GetTime() );
  transformRecord->SetDeviceName( this->GetVector()->GetLabel() );
  transformRecord->SetTransformMatrix( matrixString.str() );
}


void vtkLabelRecord
::FromTransformRecord( vtkTransformRecord* transformRecord, TrackingRecordType type )
{
  std::stringstream matrixString( transformRecord->GetTransformMatrix() );
  std::stringstream trackingString;
  if ( type == QUATERNION_RECORD ) // If it is in quaternion format
  {
    double translation[ 3 ];
    double matrix[ 3 ][ 3 ];
    matrixString >> matrix[ 0 ][ 0 ]; matrixString >> matrix[ 0 ][ 1 ]; matrixString >> matrix[ 0 ][ 2 ]; matrixString >> translation[ 0 ];
    matrixString >> matrix[ 1 ][ 0 ]; matrixString >> matrix[ 1 ][ 1 ]; matrixString >> matrix[ 1 ][ 2 ]; matrixString >> translation[ 1 ];
    matrixString >> matrix[ 2 ][ 0 ]; matrixString >> matrix[ 2 ][ 1 ]; matrixString >> matrix[ 2 ][ 2 ]; matrixString >> translation[ 2 ];
    
    double quaternion[ 4 ];
    vtkMath::Matrix3x3ToQuaternion( matrix, quaternion );
    
    trackingString << translation[ 0 ] << " " << translation[ 1 ] << " " << translation[ 2 ] << " ";
    trackingString << quaternion[ 0 ] << " " << quaternion[ 1 ] << " " << quaternion[ 2 ] << " " << quaternion[ 3 ];
  }
  else if ( type == MATRIX_RECORD ) // If it is in matrix format
  {
    trackingString << transformRecord->GetTransformMatrix();
  }
  else
  {
    return;
  }
  
  this->SetTime( transformRecord->GetTime() );
  this->GetVector()->SetLabel( transformRecord->GetDeviceName() );
  this->GetVector()->FromString( trackingString.str(), type );
}


std::string vtkLabelRecord
::ToXMLString( vtkIndent indent )
{
  std::stringstream xmlstring;

  xmlstring << indent << "<Record";
  xmlstring << " TimeStampSec=\"" << this->GetTimeStampSec() << "\"";
  xmlstring << " TimeStampNSec=\"" << this->GetTimeStampNSec() << "\"";
  xmlstring << " Label=\"" << this->GetVector()->GetLabel() << "\"";
  xmlstring << " Size=\"" << this->GetVector()->Size() << "\"";
  xmlstring << " Values=\"" << this->GetVector()->ToString() << "\"";
  xmlstring << " />" << std::endl;

  return xmlstring.str();
}


void vtkLabelRecord
::FromXMLElement( vtkXMLDataElement* element )
{
  if ( element == NULL || strcmp( element->GetName(), "Record" ) != 0 )
  {
    return;  // If it's not a "record" jump to the next.
  }

  // Call the subclass/dataclass functions
  element->SetName( "log" );
  this->vtkLogRecord::FromXMLElement( element );
  element->SetName( "Vector" );
  this->GetVector()->FromXMLElement( element );
}