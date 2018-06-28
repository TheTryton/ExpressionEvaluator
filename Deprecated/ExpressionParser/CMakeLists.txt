cmake_minimum_required(VERSION 3.8)
project(Evaluator)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(Evaluator_Sources
	Include/CAddOperation.h
	Source/CAddOperation.cpp
	
	Include/CCosFunction.h
	Source/CCosFunction.cpp
	
	Include/CDivideOperation.h
	Source/CDivideOperation.cpp

	Include/CExpFunction.h
	Source/CExpFunction.cpp

	Include/CExpression.h
	Source/CExpression.cpp

	Include/CExpressionEvaluationManager.h
	Source/CExpressionEvaluationManager.cpp

	Include/CLogFunction.h
	Source/CLogFunction.cpp

	Include/CMultiplyOperation.h
	Source/CMultiplyOperation.cpp

	Include/CParameter.h
	Source/CParameter.cpp

	Include/CPowerOperation.h
	Source/CPowerOperation.cpp

	Include/CRuntimeOperation.h
	Source/CRuntimeOperation.cpp

	Include/CSinFunction.h
	Source/CSinFunction.cpp

	Include/CSubtractOperation.h
	Source/CSubtractOperation.cpp

	Include/CTanFunction.h
	Source/CTanFunction.cpp

	Include/CValue.h
	Source/CValue.cpp

	Include/IElement.h
	Source/IElement.cpp

	Include/IFunction.h
	Source/IFunction.cpp

	Include/IOperation.h
	Source/IOperation.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Evaluator_Sources})

add_library(Evaluator STATIC ${Evaluator_Sources})

target_include_directories(Evaluator PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Include)

set_target_properties (Evaluator PROPERTIES FOLDER Deprecated/ExpressionParser)

add_subdirectory(Examples/Drawer)