//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: untitled.h
//
// Code generated for Simulink model 'untitled'.
//
// Model version                  : 1.41
// Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
// C/C++ source code generated on : Tue Sep 24 14:48:37 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef untitled_h_
#define untitled_h_
#include <cmath>
#include "rtwtypes.h"
#include "ppl_matlab.hpp"
#include "untitled_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Class declaration for model untitled
class untitled final
{
  // public data and function members
 public:
  // Real-time Model Data Structure
  struct RT_MODEL_untitled_T {
    const char_T * volatile errorStatus;
  };

  // Copy Constructor
  untitled(untitled const&) = delete;

  // Assignment Operator
  untitled& operator= (untitled const&) & = delete;

  // Move Constructor
  untitled(untitled &&) = delete;

  // Move Assignment Operator
  untitled& operator= (untitled &&) = delete;

  // Real-Time Model get method
  untitled::RT_MODEL_untitled_T * getRTM();

  // model initialize function
  static void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  untitled();

  // Destructor
  ~untitled();

  // private data and function members
 private:
  // Real-Time Model
  RT_MODEL_untitled_T untitled_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Scope' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'untitled'
//  '<S1>'   : 'untitled/MATLAB Function'

#endif                                 // untitled_h_

//
// File trailer for generated code.
//
// [EOF]
//
