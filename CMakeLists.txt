#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8.7)
#-----------------------------------------------------------------------------
# Module name (usually identique to the directory name)
set(MODULE_NAME "WorkflowSegmentation")
set(MODULE_TITLE "Workflow Segmentation")

string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)

#-----------------------------------------------------------------------------
if ( NOT DEFINED ${EXTENSION_NAME}_SUPERBUILD )
  find_package(Slicer REQUIRED)
  include(${Slicer_USE_FILE})
endif()

#-----------------------------------------------------------------------------
# Build module sub libraries
add_subdirectory(MRML)
add_subdirectory(Logic)
add_subdirectory(Widgets)

#-----------------------------------------------------------------------------
set(MODULE_EXPORT_DIRECTIVE "Q_SLICER_QTMODULES_${MODULE_NAME_UPPER}_EXPORT")

# Current_{source,binary} and Slicer_{Libs,Base} already included
set(MODULE_INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}/Logic
  ${CMAKE_CURRENT_BINARY_DIR}/Logic
  ${CMAKE_CURRENT_SOURCE_DIR}/MRML
  ${CMAKE_CURRENT_BINARY_DIR}/MRML
  ${CMAKE_CURRENT_SOURCE_DIR}/Widgets
  ${CMAKE_CURRENT_BINARY_DIR}/Widgets
  ${qSlicerTransformRecorderModuleWidgets_SOURCE_DIR}
  ${qSlicerTransformRecorderModuleWidgets_BINARY_DIR}
  ${vtkSlicerTransformRecorderModuleLogic_SOURCE_DIR}
  ${vtkSlicerTransformRecorderModuleLogic_BINARY_DIR}
  ${vtkSlicerTransformRecorderModuleMRML_SOURCE_DIR}
  ${vtkSlicerTransformRecorderModuleMRML_BINARY_DIR}
  )

set(MODULE_SRCS
  qSlicer${MODULE_NAME}Module.cxx
  qSlicer${MODULE_NAME}Module.h
  qSlicer${MODULE_NAME}ModuleWidget.cxx
  qSlicer${MODULE_NAME}ModuleWidget.h
  qSlicerWorkflowProcedureReader.cxx
  qSlicerWorkflowProcedureReader.h
  qSlicerWorkflowInputReader.cxx
  qSlicerWorkflowInputReader.h
  qSlicerWorkflowTrainingReader.cxx
  qSlicerWorkflowTrainingReader.h
  )

set(MODULE_MOC_SRCS
  qSlicer${MODULE_NAME}Module.h
  qSlicer${MODULE_NAME}ModuleWidget.h
  qSlicerWorkflowProcedureReader.h
  qSlicerWorkflowInputReader.h
  qSlicerWorkflowTrainingReader.h
  )

set(MODULE_UI_SRCS
  Resources/UI/qSlicer${MODULE_NAME}Module.ui
  )

set(MODULE_TARGET_LIBRARIES
  vtkSlicer${MODULE_NAME}ModuleLogic
  vtkSlicer${MODULE_NAME}ModuleMRML
  qSlicer${MODULE_NAME}ModuleWidgets
  vtkSlicerTransformRecorderModuleMRML
  vtkSlicerTransformRecorderModuleLogic
  qSlicerTransformRecorderModuleWidgets
  )
  
set(MODULE_RESOURCES
  Resources/qSlicer${MODULE_NAME}Module.qrc
  )

#-----------------------------------------------------------------------------
slicerMacroBuildQtModule(
  NAME ${MODULE_NAME}
  TITLE ${MODULE_TITLE}
  EXPORT_DIRECTIVE ${MODULE_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${MODULE_INCLUDE_DIRECTORIES}
  SRCS ${MODULE_SRCS}
  MOC_SRCS ${MODULE_MOC_SRCS}
  UI_SRCS ${MODULE_UI_SRCS}
  TARGET_LIBRARIES ${MODULE_TARGET_LIBRARIES}
  RESOURCES ${MODULE_RESOURCES}
  )

#-----------------------------------------------------------------------------
if(BUILD_TESTING)
  #add_subdirectory(Testing)
endif()
