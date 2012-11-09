
#ifndef MARKOVMODEL_H
#define MARKOVMODEL_H

#include "RecordType.h"
#include "vtkObject.h"
#include "vtkSlicerWorkflowSegmentationModuleLogicExport.h"

#include <vector>
#include <iostream>

// Class representing a procedure comprised of tracking records
class VTK_SLICER_WORKFLOWSEGMENTATION_MODULE_LOGIC_EXPORT
  vtkMarkovModel : public vtkObject
{
public:

  static vtkMarkovModel *New();

  vtkMarkovModel* DeepCopy();

  void SetSize( int numNewStates, int numNewSymbols );
  int GetNumStates();
  int GetNumSymbols();

  std::vector<LabelRecord> GetA();
  std::vector<LabelRecord> GetZeroA();
  std::vector<LabelRecord> GetLogA();

  std::vector<LabelRecord> GetB();
  std::vector<LabelRecord> GetZeroB();
  std::vector<LabelRecord> GetLogB();

  LabelRecord GetPi();
  LabelRecord GetZeroPi();
  LabelRecord GetLogPi();


  void InitializeEstimation( int numEstStates, int numEstSymbols );
  void AddEstimationData( std::vector<MarkovRecord> sequence );
  void AddPseudoData( LabelRecord pseudoPi, std::vector<LabelRecord> pseudoA, std::vector<LabelRecord> pseudoB );
  void EstimateParameters();
  std::vector<MarkovRecord> CalculateStates( std::vector<MarkovRecord> sequence );
  

private:

	void ZeroParameters();
	void NormalizeParameters();

public:

  vtkMarkovModel();
  vtkMarkovModel( int numInitStates, int numInitSymbols );
  ~vtkMarkovModel();

protected:

	std::vector<LabelRecord> A; // State transition matrix
	std::vector<LabelRecord> B; // Observation matrix
	LabelRecord pi;	// Initial state vector

	int numStates;
	int numSymbols;

};

#endif