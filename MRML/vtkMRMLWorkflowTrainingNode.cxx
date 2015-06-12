
#include "vtkMRMLWorkflowTrainingNode.h"

// Standard MRML Node Methods ------------------------------------------------------------

vtkMRMLWorkflowTrainingNode* vtkMRMLWorkflowTrainingNode
::New()
{
  // First try to create the object from the vtkObjectFactory
  vtkObject* ret = vtkObjectFactory::CreateInstance( "vtkMRMLWorkflowTrainingNode" );
  if( ret )
    {
      return ( vtkMRMLWorkflowTrainingNode* )ret;
    }
  // If the factory was unable to create the object, then create it here.
  return new vtkMRMLWorkflowTrainingNode();
}


vtkMRMLNode* vtkMRMLWorkflowTrainingNode
::CreateNodeInstance()
{
  // First try to create the object from the vtkObjectFactory
  vtkObject* ret = vtkObjectFactory::CreateInstance( "vtkMRMLWorkflowTrainingNode" );
  if( ret )
    {
      return ( vtkMRMLWorkflowTrainingNode* )ret;
    }
  // If the factory was unable to create the object, then create it here.
  return new vtkMRMLWorkflowTrainingNode();
}



void vtkMRMLWorkflowTrainingNode
::PrintSelf( ostream& os, vtkIndent indent )
{
  vtkMRMLNode::PrintSelf(os,indent);
}


void vtkMRMLWorkflowTrainingNode
::WriteXML( ostream& of, int nIndent )
{
  Superclass::WriteXML(of, nIndent);
}


void vtkMRMLWorkflowTrainingNode
::ReadXMLAttributes( const char** atts )
{
  Superclass::ReadXMLAttributes(atts);
}


void vtkMRMLWorkflowTrainingNode
::Copy( vtkMRMLNode *anode )
{
  Superclass::Copy( anode );
  vtkMRMLWorkflowTrainingNode *node = ( vtkMRMLWorkflowTrainingNode* ) anode;
  if ( node == NULL )
  {
    return;
  }
  
  this->PrinComps.clear();
  for ( int i = 0; i < node->GetPrinComps().size() )
  {
    vtkSmartPointer< vtkLabelVector > currPrinComp = vtkSmartPointer< vtkLabelVector >::New();
    currPrinComp->Copy( node->GetPrinComps().at( i ) );
    this->PrinComps.push_back( currPrinComp );
  }
  this->Centroids.clear();
  for ( int i = 0; i < node->GetCentroids().size() )
  {
    vtkSmartPointer< vtkLabelVector > currCentroid = vtkSmartPointer< vtkLabelVector >::New();
    currCentroid->Copy( node->GetCentroids().at( i ) );
    this->Centroids.push_back( currCentroid );
  }
  
  this->Mean->Copy( node->GetMean() );
  this->Markov->Copy( node->GetMarkov() );
}


// Constructors & Destructors --------------------------------------------------------------------------

vtkMRMLWorkflowTrainingNode
::vtkMRMLWorkflowTrainingNode()
{
  // Give default values, don't need to initialize vectors
  this->Mean = vtkSmartPointer< vtkLabelVector >::New();
  this->Markov = vtkSmartPointer< vtkMarkovModelRT >::New();
}


vtkMRMLWorkflowTrainingNode
::~vtkMRMLWorkflowTrainingNode()
{
  this->PrinComps.clear();
  this->Centroids.clear();
}


std::string vtkMRMLWorkflowTrainingNode
::ToXMLString( vtkIndent indent )
{
  std::stringstream xmlstring;
  
  xmlstring << indent << "<WorkflowTraining>" << std::endl;
    
  xmlstring << indent.GetNextIndent() << vtkLabelVector::VectorsToXMLString( this->PrinComps, "PrinComps", indent->GetNextIndent() );
  xmlstring << indent.GetNextIndent() << vtkLabelVector::VectorsToXMLString( this->Mean, "Mean", indent->GetNextIndent() );
  xmlstring << indent.GetNextIndent() << vtkLabelVector::VectorsToXMLString( this->Centroids, "Centroids", indent->GetNextIndent() );
  xmlstring << indent.GetNextIndent() << this->Markov->ToXMLString( indent.GetNextIndent() );
  
  xmlstring << indent << "</WorkflowTraining>" << std::endl;
  
  return xmlstring.str();

}


void vtkMRMLWorkflowTrainingNode
::FromXMLElement( vtkXMLDataElement* element )
{
  if ( element == NULL || strcmp( element->GetName(), "WorkflowTraining" ) != 0 )
  {
    return;
  }
  
  int numElements = element->GetNumberOfNestedElements();

  for ( int i = 0; i < numElements; i++ )
  {

    vtkXMLDataElement* noteElement = element->GetNestedElement( i );
    if ( strcmp( noteElement->GetName(), "Vectors" ) != 0 && strcmp( noteElement->GetName(), "MarkovModel" ) != 0 )
    {
      continue;  // If it's not a "Parameter" or "MarkovModel", jump to the next.
    }

	  const char* elementType = noteElement->GetAttribute( "Type" );

	  if ( strcmp( elementType, "PrinComps" ) == 0 )
    {
	    this->PrinComps = vtkLabelVector::VectorsFromXMLElement( noteElement, "PrinComps" );
    }
    if ( strcmp( elementType, "Centroids" ) == 0 )
    {
	    this->Centroids = vtkLabelVector::VectorsFromXMLElement( noteElement, "PrinComps" );
    }
	  if ( strcmp( elementType, "Mean" ) == 0 )
    {
	    this->Mean = vtkLabelVector::VectorBufferFromXMLElement( noteElement ).at(0);
    }
	  if ( strcmp( elementType, "Markov" ) == 0 )
    {
	    this->Markov->FromXMLElement( noteElement );
	  }

  }

}