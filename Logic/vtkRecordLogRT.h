
#ifndef VTKRECORDLOGRT_H
#define VTKRECORDLOGRT_H

#include "vtkObject.h"
#include "vtkSlicerWorkflowSegmentationModuleLogicExport.h"
#include "vtkRecordLog.h"
#include "RecordType.h"

#include <vector>
#include <iostream>


// Class representing a procedure comprised of tracking records
class VTK_SLICER_WORKFLOWSEGMENTATION_MODULE_LOGIC_EXPORT
  vtkRecordLogRT : public vtkRecordLog
{
public:

  static vtkRecordLogRT *New();
  vtkTypeMacro(vtkRecordLogRT, vtkRecordLog);

  void SetMean( ValueRecord newMean );
  void SetPrinComps( std::vector<LabelRecord> newPrinComps );
  void SetCentroids( std::vector<LabelRecord> newCentroids );

  TimeLabelRecord GetRecordRT();
  void SetRecordRT( TimeLabelRecord newRecord );

  LabelRecord DistancesRT( std::vector<ValueRecord> valueRecords );

  TimeLabelRecord DerivativeRT( int order = 1 );

  TimeLabelRecord GaussianFilterRT( double width );

  TimeLabelRecord OrthogonalTransformationRT( int window, int order );

  TimeLabelRecord TransformPCART( std::vector<LabelRecord> prinComps, ValueRecord mean );

  TimeLabelRecord fwdkmeansTransformRT( std::vector<LabelRecord> centroids );

  MarkovRecord ToMarkovRecordRT();

public:

  vtkRecordLogRT();
  ~vtkRecordLogRT();

private:

};

#endif
